#include "memory.h"
#include <cstdint>

Memory::Memory() : m_memory(MEMORY_SIZE, 0) {}

uint8_t Memory::readByte(uint16_t address) {
  if (address >= MEMORY_SIZE) {
    std::cerr << "Error: Attempted to read outside memory bounds at address 0x"
              << std::hex << address << std::endl;
    return 0xFF; // Return a default value (e.g., 0xFF) or throw an exception
  }
  return m_memory[address];
}
