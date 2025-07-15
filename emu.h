#pragma once
#include <cstdint>
class Emu_Context {
public:
  Emu_Context();
  static bool paused;
  static bool running;
  uint64_t ticks;
  int emu_run(int argc, char **argv);
};
