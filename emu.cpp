#include "emu.h"
#include "bus.h"
#include "cart.h"
#include "cpu.h"
#include "memory.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include <iostream>
#include <memory>

Emu::Emu()
    : running(false), paused(false), ticks(0), m_memory(), m_bus(m_memory),
      m_cart(), m_cpuContext(std::make_unique<CPU>(m_bus)) {}
void delay(uint32_t ms) { SDL_Delay(ms); }

int Emu::emu_run(int argc, char **argv) {
  this->running = true;

  if (argc < 2) {
    std::cout << "Usage: emu <rom_file>\n";
    return -1;
  }
  if (m_cart.load_cart(argv[1]) != true) {
    return -3;
  }
  SDL_Init(SDL_INIT_VIDEO);
  std::cout << "SDL INIT\n";
  TTF_Init();
  std::cout << "TTF INIT\n";

  while (this->running) {
    if (this->paused) {
      delay(10);
      continue;
    }
    if (!m_cpuContext.getCPU()->step()) {
      std::cout << "CPU Stopped\n";
      return -3;
    }
    this->ticks++;
  }
  return 0;
}
