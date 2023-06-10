#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <stdint.h>

enum Register { EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, REGISTER_COUNT,
 AL = EAX, CL = ECX, DL = EDX, BL = EBX,
 AH = AL+4, CH = CL+4, DH = DL+4 , BH = BL+4};

typedef struct {
  uint32_t registers[REGISTER_COUNT];
  uint32_t eflags;

  // memory (byte seq)
  uint8_t *memory;
  // instruction pointer (PC)
  uint32_t eip;
} Emulator;


#endif
