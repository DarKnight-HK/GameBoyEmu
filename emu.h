#pragma once
#include "cpu.h"
#include <cstdint>
class Emu {
public:
  Emu(CPU &cpu);
  bool paused;
  bool running;
  uint64_t ticks;
  int emu_run(int argc, char **argv);

private:
  CPU &cpu;
};
