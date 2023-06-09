#include "emulator_function.h"

uint32_t get_code8(Emulator *emu, int index) {
  return emu->memory[emu->eip + index];
}

int32_t get_sign_code8(Emulator *emu, int index) {
  return (int8_t)emu->memory[emu->eip + index];
}

uint32_t get_code32(Emulator *emu, int index) {
  int i;
  uint32_t ret = 0;

  // little endian
  for (i = 0; i < 4; i++) {
    ret |= get_code8(emu, index + i) << (i * 8);
  }
  return ret;
}

int32_t get_sign_code32(Emulator *emu, int index) {
  return (int32_t)get_code32(emu, index);
}
