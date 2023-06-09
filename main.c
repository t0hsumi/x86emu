#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emulator.h"
#include "emulator_function.h"
#include "instruction.h"

// 1 MB memory
#define MEMORY_SIZE (1024 * 1024)

char *registers_name[] = {"EAX", "ECX", "EDX", "EBX",
                          "ESP", "EBP", "ESI", "EDI"};

static Emulator *create_emu(size_t size, uint32_t eip, uint32_t esp) {
  Emulator *emu = malloc(sizeof(Emulator));
  emu->memory = malloc(size);

  memset(emu->registers, 0, sizeof(emu->registers));

  emu->eip = eip;
  emu->registers[ESP] = esp;

  return emu;
}

static void destroy_emu(Emulator *emu) {
  free(emu->memory);
  free(emu);
}

// output register value and program counter
static void dump_registers(Emulator *emu) {
  int i;

  for (i = 0; i < REGISTER_COUNT; i++) {
    printf("%s = %08x\n", registers_name[i], emu->registers[i]);
  }

  printf("EIP = %08x\n", emu->eip);
}

int main(int argc, char *argv[]) {
  FILE *binary;
  Emulator *emu;

  if (argc != 2) {
    printf("Usage: ./px86 filename\n");
    return 1;
  }

  // memory size, eip, esp
  emu = create_emu(MEMORY_SIZE, 0x7c00, 0x7c00);
  binary = fopen(argv[1], "rb");
  if (binary == NULL) {
    printf("%s : cannot open the file\n", argv[1]);
    return 1;
  }

  fread(emu->memory + 0x7c00, 1, 0x200, binary);
  fclose(binary);

  init_instructions();

  while (emu->eip < MEMORY_SIZE) {
    uint8_t code = get_code8(emu, 0);
    // output program counter and binary to be executed
    printf("EIP = %X, CODE = %02X\n", emu->eip, code);

    if (instructions[code] == NULL) {
      // stop program when unimplemented instruction is detected
      printf("\n\n Not Implemented: %x\n", code);
      break;
    }

    // execute code
    instructions[code](emu);

    if (emu->eip == 0x00) {
      printf("\n\nend of program.\n\n");
      break;
    }
  }

  dump_registers(emu);
  destroy_emu(emu);
  return 0;
}
