#pragma once
#include "cart.h"
#include "memory.h"

class Bus {
public:
  Bus(Memory &memory);

  uint8_t readByte(uint16_t address);

  uint16_t readWord(uint16_t address);

  void writeByte(uint16_t address, uint8_t value);

  void writeWord(uint16_t address, uint16_t value);

private:
  // Reference to the Memory object. In a full emulator, this would
  // be a collection of references to various components (ROM, RAM, PPU, APU,
  // etc.).
  Memory &m_memory;
};
