#pragma once
#include "bus.h"
#include "instructions.h"
#include <cstdint>
#include <iostream>
#include <memory>
class CPU {
public:
  Bus &bus;
  CPU(Bus &bus);
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

  // Helper methods to set and get individual flag bits
  void setFlag(uint8_t flag, bool set);
  bool getFlag(uint8_t flag);

  // Flag masks for the F register
  static const uint8_t FLAG_Z = 0x80; // Zero Flag (Bit 7)
  static const uint8_t FLAG_N = 0x40; // Subtract Flag (Bit 6)
  static const uint8_t FLAG_H = 0x20; // Half Carry Flag (Bit 5)
  static const uint8_t FLAG_C = 0x10; // Carry Flag (Bit 4)
private:
  // Helper method to combine two 8-bit registers into a 16-bit word
  uint16_t getBC() { return (static_cast<uint16_t>(B) << 8) | C; }
  uint16_t getDE() { return (static_cast<uint16_t>(D) << 8) | E; }
  uint16_t getHL() { return (static_cast<uint16_t>(H) << 8) | L; }
  uint16_t getAF() { return (static_cast<uint16_t>(A) << 8) | F; }

  // Helper method to set two 8-bit registers from a 16-bit word
  void setBC(uint16_t value) {
    B = (value >> 8) & 0xFF;
    C = value & 0xFF;
  }
  void setDE(uint16_t value) {
    D = (value >> 8) & 0xFF;
    E = value & 0xFF;
  }
  void setHL(uint16_t value) {
    H = (value >> 8) & 0xFF;
    L = value & 0xFF;
  }
  void setAF(uint16_t value) {
    A = (value >> 8) & 0xFF;
    F = value & 0xF0;
  } // Lower 4 bits of F are always 0
};

class CPU_Context {
private:
  std::unique_ptr<CPU> m_cpu;

  uint16_t fetch_data;

  uint16_t mem_dest;

  uint8_t curr_opcode;

  bool halted;

  bool stepping;

  bool destIsMem;

public:
  Instruction curr_inst;

  CPU_Context(std::unique_ptr<CPU> cpu);

  void fetchData();

  void fetchInstruction();

  void decode();

  bool step();

  void setHalted(bool state);

  bool isHalted() const;

  void setStepping(bool state);

  bool isStepping() const;

  bool isDestMem() const;

  void setIsDestMem(bool state);

  CPU *getCPU() const;

  void setCPU(std::unique_ptr<CPU> cpu);

  uint16_t getFetchData() const;

  uint16_t getMemDest() const;

  uint8_t getCurrOpcode() const;

  void setFetchData(uint16_t data);

  void setMemDest(uint16_t dest);

  void setCurrOpcode(uint8_t opcode);
};
