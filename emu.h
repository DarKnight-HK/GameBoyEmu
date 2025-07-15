#pragma once
#include "bus.h"
#include "cart.h"
#include "cpu.h"
#include "memory.h"
#include <cstdint>

class Emu {
public:
  Emu(); // Constructor

  bool paused;
  bool running;
  uint64_t ticks;
  int emu_run(int argc, char **argv);

private:
  Memory m_memory;
  Bus m_bus;
  CPU m_cpu;
  Cart m_cart;
};
