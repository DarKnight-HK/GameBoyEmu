
#include "emu.h"
#include <iostream>

int main(int argc, char *argv[]) {
  Emu emulator;

  int result = emulator.emu_run(argc, argv);

  if (result == 0) {
    std::cout << "Emulator finished successfully." << std::endl;
  } else {
    std::cerr << "Emulator exited with error code: " << result << std::endl;
  }

  return result;
}
