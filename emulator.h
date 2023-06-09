#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <stdint.h>

enum Register { EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, REGISTER_COUNT };

typedef struct {
  uint32_t registers[REGISTER_COUNT];
  uint32_t eflags;

  // memory (byte seq)
  uint8_t *memory;
  // instruction pointer (PC)
  uint32_t eip;
} Emulator;


#endif
