#include "cpu.h"
#include <cstdint>

CPU::CPU(Bus &bus) : bus(bus) {
  // Initialize registers to their power-on state for the Game Boy
  // These values are typical for the Game Boy's boot ROM
  A = 0x01;
  F = 0xB0; // Z, N, H, C flags are typically set as 10110000 (0xB0)
  B = 0x00;
  C = 0x13;
  D = 0x00;
  E = 0xD8;
  H = 0x01;
  L = 0x4D;
  SP = 0xFFFE; // Stack Pointer usually starts high in RAM
  PC = 0x0100; // Program Counter usually starts after the boot ROM (0x100)
               // If no boot ROM, it starts at 0x0000 for some emulators.
               // For now, we assume a ROM will be loaded that starts execution
               // at 0x100.
  std::cout << "CPU initialized." << std::endl;
}

// Sets a specific flag in the F register.

void CPU::setFlag(uint8_t flag, bool set) {
  if (set) {
    F |= flag;
  } else {
    F &= ~flag; // clear the flag
  }
  F &= 0xF0; // Ensure the lower 4 bits of F are always 0
}

// Gets the state of a specific flag from the F register.
bool CPU::getFlag(uint8_t flag) { return (F & flag) != 0; }

int CPU::step() {
  uint8_t opcode = bus.readByte(PC);
  PC++;
  std::cout << "Fetched opcode: 0x" << std::hex << static_cast<int>(opcode)
            << " at PC: 0x" << std::hex << static_cast<int>(PC - 1)
            << std::endl;

  // Placeholder for instruction execution.
  // This is where the core logic for each Game Boy instruction will go.
  // For example, if opcode == 0x00 (NOP - No Operation), it would do nothing.
  // If opcode == 0x3E (LD A, n), it would read the next byte into register A.

  // Example of a simple instruction (NOP - No Operation, Opcode 0x00)
  if (opcode == 0x00) {
    // NOP takes 4 cycles
    return 4;
  }
  // Add more instruction implementations here as you go!

  // For any unimplemented opcode, we'll print a warning and return a default
  // cycle count.
  std::cerr << "Warning: Unimplemented opcode 0x" << std::hex
            << static_cast<int>(opcode) << " at address 0x" << std::hex
            << static_cast<int>(PC - 1) << std::endl;

  // Return a default number of cycles for now.
  // Real instructions have varying cycle counts.
  return 4;
}
