#include "instructions.h"

// --- Getters Implementations ---

InstructionType Instruction::getType() const { return type; }

AddrMode Instruction::getMode() const { return mode; }

RegType Instruction::getReg1() const { return reg1; }

RegType Instruction::getReg2() const { return reg2; }

CondType Instruction::getCond() const { return cond; }

uint8_t Instruction::getParam() const { return param; }

// --- Setters Implementations ---

void Instruction::setType(InstructionType newType) { type = newType; }

void Instruction::setMode(AddrMode newMode) { mode = newMode; }

void Instruction::setReg1(RegType newReg1) { reg1 = newReg1; }

void Instruction::setReg2(RegType newReg2) { reg2 = newReg2; }

void Instruction::setCond(CondType newCond) { cond = newCond; }

void Instruction::setParam(uint8_t newParam) { param = newParam; }
