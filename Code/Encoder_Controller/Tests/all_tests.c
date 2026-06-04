#include <stdio.h>
#include "spi_command_tests.h"


int main(int argc, char **argv) {
  int result = 0;
  printf("Running tests for SPI-commands...\n");
  result -= runGenerateReadCommandTest(0x1, 0x11);
  result -= runDecodeCommandTest(0xaf, 0xa);
  result -= runDecodeDataTest(0xaf, 0xf);

  if(result == 0) {
    printf("All Tests passed: [OK]\n");
    return 0;
  }

  printf("%i Tests failed!\n", (-1 * result));
}
