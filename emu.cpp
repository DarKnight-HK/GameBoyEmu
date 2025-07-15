#include "emu.h"
#include "cart.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include <iostream>

Emu::Emu(CPU &cpu) : running(false), paused(false), ticks(0), cpu(cpu) {}

void delay(uint32_t ms) { SDL_Delay(ms); }

int Emu::emu_run(int argc, char **argv) {
  this->running = true;

  if (argc < 2) {
    std::cout << "Usage: emu <rom_file>\n";
    return -1;
  }
  //
  // if (!cart_load(argv[1])) {
  //   printf("Failed to load ROM file: %s\n", argv[1]);
  //   return -2;
  // }

  // printf("Cart loaded..\n");

  SDL_Init(SDL_INIT_VIDEO);
  std::cout << "SDL INIT\n";
  TTF_Init();
  std::cout << "TTF INIT\n";

  while (this->running) {
    if (this->paused) {
      delay(10);
      continue;
    }
    if (!cpu.step()) {
      std::cout << "CPU Stopped\n";
      return -3;
    }
    this->ticks++;
  }
  return 0;
}
