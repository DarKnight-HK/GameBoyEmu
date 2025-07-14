#include "memory.h"
#include <algorithm>
#include <cstdint>
#include <vector>
Memory::Memory() : m_memory(MEMORY_SIZE, 0) {}

uint8_t Memory::readByte(uint16_t address) {
  if (address >= MEMORY_SIZE) {
    std::cerr << "Error: Attempted to read outside memory bounds at address 0x"
              << std::hex << address << std::endl;
    return 0xFF; // Return a default value (e.g., 0xFF) or throw an exception
  }
  return m_memory[address];
}

void Memory::writeByte(uint16_t address, uint8_t value) {
  if (address >= MEMORY_SIZE) {
    std::cerr << "Error: Attempted to read outside memory bounds at address 0x"
              << std::hex << address << std::endl;
    return;
  }
  m_memory[address] = value;
}

uint16_t Memory::readWord(uint16_t address) {
  if (address >= MEMORY_SIZE) {
    std::cerr << "Error: Attempted to read outside memory bounds at address 0x"
              << std::hex << address << std::endl;
    return 0xFFFF;
  }
  uint8_t lsb = m_memory[address];
  uint8_t msb = m_memory[address + 1];
  return (static_cast<uint16_t>(msb << 8) | lsb);
}

void Memory::writeWord(uint16_t address, uint16_t value) {
  if (address >= MEMORY_SIZE) {
    std::cerr << "Error: Attempted to read outside memory bounds at address 0x"
              << std::hex << address << std::endl;
    return;
  }

  // Split a 16-bit unsigned integer into two 8-bit parts:
  // - high_byte contains the upper 8 bits (bits 8-15)
  // - low_byte contains the lower 8 bits (bits 0-7)
  writeByte(address, static_cast<uint8_t>(value & 0xFF));
  writeByte(address + 1, static_cast<uint8_t>((value >> 8) & 0xFF));
}

/**
 * @brief Loads a ROM (Read-Only Memory) into the memory.
 *
 * For now, this will simply copy the ROM data into the beginning of
 * our simulated memory. In a real emulator, this would involve
 * handling cartridge headers and Memory Bank Controllers (MBCs).
 *
 * @param romData A vector of bytes representing the ROM content.
 */

void Memory::loadROM(const std::vector<uint8_t> &romData) {
  if (romData.size() >= MEMORY_SIZE) {
    std::cerr << "ROM Size is larger than memory size" << std::endl;
  }
  size_t bytesToCopy =
      std::min(romData.size(), static_cast<size_t>(MEMORY_SIZE));
  for (size_t i = 0; i < bytesToCopy; ++i) {
    m_memory[i] = romData[i];
  }
  std::cout << "ROM loaded successfully. Size: " << bytesToCopy << " bytes."
            << std::endl;
}
