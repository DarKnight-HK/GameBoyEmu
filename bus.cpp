#include "bus.h"

Bus::Bus(Memory &memory) : m_memory(memory) {
  std::cout << "Bus initialized." << std::endl;
}

uint8_t Bus::readByte(uint16_t address) { return m_memory.readByte(address); }

void Bus::writeByte(uint16_t address, uint8_t value) {

  m_memory.writeByte(address, value);
}

uint16_t Bus::readWord(uint16_t address) {
  // Read the least significant byte (LSB) from the current address
  uint8_t lsb = readByte(address);
  // Read the most significant byte (MSB) from the next address
  uint8_t msb = readByte(address + 1);
  // Combine them into a 16-bit word (MSB << 8 | LSB)
  return (static_cast<uint16_t>(msb) << 8) | lsb;
}

void Bus::writeWord(uint16_t address, uint16_t value) {
  writeByte(address, static_cast<uint8_t>(value & 0xFF));
  writeByte(address + 1, static_cast<uint8_t>((value >> 8) & 0xFF));
}
