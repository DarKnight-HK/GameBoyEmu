#pragma once

#include <cstdint>

enum class AddrMode : uint8_t {
  IMP,   // Implied addressing (no operand)
  R_D16, // Register to 16-bit immediate data (e.g., LD BC, d16)
  R_R,   // Register to Register (e.g., LD A, B)
  MR_R,  // Memory at Register to Register (e.g., LD (BC), A)
  R,     // Register (e.g., INC B)
  R_D8,  // Register to 8-bit immediate data (e.g., LD A, d8)
  R_MR,  // Register to Memory at Register (e.g., LD A, (BC))
  R_HLI, // Register to Memory at HL, then increment HL (e.g., LD A, (HLI))
  R_HLD, // Register to Memory at HL, then decrement HL (e.g., LD A, (HLD))
  HLI_R, // Memory at HL to Register, then increment HL (e.g., LD (HLI), A)
  HLD_R, // Memory at HL to Register, then decrement HL (e.g., LD (HLD), A)
  R_A8,  // Register to Memory at (0xFF00 + 8-bit immediate) (e.g., LDH A, (a8))
  A8_R,  // Memory at (0xFF00 + 8-bit immediate) to Register (e.g., LDH (a8), A)
  HL_SPR, // HL to SP + signed 8-bit immediate (e.g., LD HL, SP+r8)
  D16,    // 16-bit immediate data (e.g., JP d16)
  D8,     // 8-bit immediate data (e.g., JR d8)
  D16_R,  // 16-bit immediate data to Register (e.g., LD (a16), SP)
  MR_D8,  // Memory at Register to 8-bit immediate data (e.g., LD (HL), d8)
  MR,     // Memory at Register (e.g., INC (HL))
  A16_R,  // 16-bit immediate address to Register (e.g., LD (a16), A)
  R_A16   // Register to 16-bit immediate address (e.g., LD A, (a16))
};

enum class RegType : uint8_t {
  NONE, // No register
  A,    // Accumulator (8-bit)
  F,    // Flags register (8-bit)
  B,    // B register (8-bit)
  C,    // C register (8-bit)
  D,    // D register (8-bit)
  E,    // E register (8-bit)
  H,    // H register (8-bit)
  L,    // L register (8-bit)
  AF,   // AF register pair (16-bit)
  BC,   // BC register pair (16-bit)
  DE,   // DE register pair (16-bit)
  HL,   // HL register pair (16-bit)
  SP,   // Stack Pointer (16-bit)
  PC    // Program Counter (16-bit)
};

enum class InstructionType : uint8_t {
  NONE,
  NOP,
  LD,
  INC,
  DEC,
  RLCA,
  ADD,
  RRCA,
  STOP,
  RLA,
  JR,
  RRA,
  DAA,
  CPL,
  SCF,
  CCF,
  HALT,
  ADC,
  SUB,
  SBC,
  AND,
  XOR,
  OR,
  CP,
  POP,
  JP,
  PUSH,
  RET,
  CB, // Prefix for CB-prefixed instructions
  CALL,
  RETI,
  LDH,
  JPHL,
  DI,
  EI,
  RST,
  ERR, // Error/Unknown instruction
  // CB instructions (moved to their own enum or just listed here)
  RLC,
  RRC,
  RL,
  RR,
  SLA,
  SRA,
  SWAP,
  SRL,
  BIT,
  RES,
  SET
};

enum class CondType : uint8_t {
  NONE, // No condition (always true)
  NZ,   // Not Zero (Z flag is 0)
  Z,    // Zero (Z flag is 1)
  NC,   // Not Carry (C flag is 0)
  C     // Carry (C flag is 1)
};

class Instruction {
public:
  Instruction(InstructionType type = InstructionType::NONE,
              AddrMode mode = AddrMode::IMP, RegType reg1 = RegType::NONE,
              RegType reg2 = RegType::NONE, CondType cond = CondType::NONE,
              uint8_t param = 0)
      : type(type), mode(mode), reg1(reg1), reg2(reg2), cond(cond),
        param(param) {}

  // --- Getters ---

  InstructionType getType() const;
  AddrMode getMode() const;
  RegType getReg1() const;
  RegType getReg2() const;
  CondType getCond() const;
  uint8_t getParam() const;

  // --- Setters ---

  void setType(InstructionType newType);
  void setMode(AddrMode newMode);
  void setReg1(RegType newReg1);
  void setReg2(RegType newReg2);
  void setCond(CondType newCond);
  void setParam(uint8_t newParam);

private:
  InstructionType type;
  AddrMode mode;
  RegType reg1;
  RegType reg2;
  CondType cond;
  uint8_t param;
};
