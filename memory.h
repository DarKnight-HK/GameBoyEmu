#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

const uint16_t MEMORY_SIZE = 0x10000; // 65536 bytes (0x0000 to 0xFFFF)

class Memory {
public:
  Memory();
  uint8_t readByte(uint16_t address);
  void writeByte(uint16_t address, uint8_t value);

  uint16_t readWord(uint16_t address);
  void writeWord(uint16_t address, uint16_t value);

private:
  // The main memory array, representing 64KB of addressable memory.
  std::vector<uint8_t> m_memory;
};
