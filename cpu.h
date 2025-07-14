#pragma once
#include <cstdint>
#include <iostream>

class CPU {
public:
  // 8-bit registers
  uint8_t A; // Accumulator
  uint8_t B;
  uint8_t C;
  uint8_t D;
  uint8_t E;
  uint8_t H;
  uint8_t L;
  uint8_t F; // Flags register (Zero, Subtract, Half Carry, Carry)

  // 16-bit registers
  uint16_t SP; // Stack Pointer
  uint16_t PC; // Program Counter
  int step();
};
