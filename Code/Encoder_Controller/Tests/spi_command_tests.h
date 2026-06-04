#include <stdio.h>
#include "../spi_commands.h"

int runGenerateReadCommandTest(uint8_t encoderId, uint8_t expectedOutput) {
  uint8_t command = GenerateReadCommand(encoderId);
  if(command != expectedOutput) {
    printf("GenerateReadCommand(0x%02b): Expected 0x%02b, got 0x%02b\n", encoderId, expectedOutput, command);
    return -1;
  }

  printf("GenerateReadCommand(0x%02b): [OK]\n", encoderId);
  return 0;
}

int runDecodeCommandTest(uint8_t msg, uint8_t expectedCommand) {
  uint8_t command = DecodeCommand(msg);
  if(command != expectedCommand){
    printf("DecodeCommand(0x%02b): Expected 0x%02b, got 0x%02b\n", msg, expectedCommand, command);
    return -1;
  }

  printf("DecodeCommand(0x%02b): [OK]\n", msg);
  return 0;
}

int runDecodeDataTest(uint8_t msg, uint8_t expectedData) {
  uint8_t data = DecodeData(msg);
  if(data != expectedData){
    printf("DecodeData(0x%02b): Expected 0x%04b, got 0x%02b\n", msg, expectedData, data);
    return -1;
  }

  printf("DecodeData(0x%02b): [OK]\n", msg);
  return 0;
}

