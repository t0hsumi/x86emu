/*
   modrm

   lists of procedures related to ModR/M.
   Only parse_modrm operates eip. At the end of parse_modrm,
   eip is considered to point to next opcode 
*/

#ifndef MODRM_H_
#define MODRM_H_

#include <stdint.h>

#include "emulator.h"

typedef struct {
  uint8_t mod;
  union {
    uint8_t opecode;
    uint8_t reg_index;
  };
  uint8_t rm;

  uint8_t sib;
  union {
    int8_t disp8;
    uint32_t disp32;
  };
} ModRM;

// parse to make appropriate ModR/M byte
// require the first argument emu->eip to point ModR/M byte
void parse_modrm(Emulator *emu, ModRM *modrm);

// calculate memory address based on ModR/M
uint32_t calc_memory_address(Emulator *emu, ModRM *modrm);

// write back the value to memory or register according to modrm
void set_rm32(Emulator *emu, ModRM *modrm, uint32_t value);

// write back the value to the register according to modrm
void set_r32(Emulator *emu, ModRM *modrm, uint32_t value);

// get the value of register
uint32_t get_r32(Emulator *emu, ModRM *modrm);

// get the value of register or memory
uint32_t get_rm32(Emulator *emu, ModRM *modrm);

#endif
