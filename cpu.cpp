#include "cpu.h"
#include "instructions.h"
#include <cstdint>
#include <memory>

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

CPU_Context::CPU_Context(std::unique_ptr<CPU> cpu)
    : halted(false), stepping(false), curr_opcode(0), mem_dest(0),
      fetch_data(0) {
  m_cpu = std::move(cpu);
}

void CPU_Context::setHalted(bool state) { halted = state; }
bool CPU_Context::isHalted() const { return halted; }
void CPU_Context::setStepping(bool state) { stepping = state; }
bool CPU_Context::isStepping() const { return stepping; }
CPU *CPU_Context::getCPU() const { return m_cpu.get(); }
void CPU_Context::setCPU(std::unique_ptr<CPU> cpu) { m_cpu = std::move(cpu); }

uint16_t CPU_Context::getFetchData() const { return fetch_data; }

uint16_t CPU_Context::getMemDest() const { return mem_dest; }

uint8_t CPU_Context::getCurrOpcode() const { return curr_opcode; }

void CPU_Context::setFetchData(uint16_t data) { fetch_data = data; }

void CPU_Context::setMemDest(uint16_t dest) { mem_dest = dest; }

void CPU_Context::setCurrOpcode(uint8_t opcode) { curr_opcode = opcode; }

void CPU_Context::setIsDestMem(bool state) { destIsMem = state; }

bool CPU_Context::isDestMem() const { return destIsMem; }

void CPU_Context::fetchInstruction() {

  setCurrOpcode(m_cpu->bus.readByte(m_cpu->PC++));
  curr_inst = instructions[curr_opcode];
}

void CPU_Context::fetchData() {
  setMemDest(0);
  setIsDestMem(false);
  switch (curr_inst.getMode()) {
  case AddrMode::IMP:
    return;
  case AddrMode::R:
  }
}

bool CPU_Context::step() {
  if (!halted) {
  }
}
