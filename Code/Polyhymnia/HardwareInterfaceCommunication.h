#ifndef HARDWARE_INTERFACE_COMMUNICATION_H
#define HARDWARE_INTERFACE_COMMUNICATION_H
#endif

#include <SPI.h>
#include "spi_commands.hpp"
#include "control_types.h"

#define HW_INTERFACE_SCK 27
#define HW_INTERFACE_MOSI 26
#define HW_INTERFACE_MISO 39
#define HW_INTERFACE_SS 37

/* Class for communicating with the different hardware-interfaces (OSC-Encoders etc.)*/
class HardwareInterfaceCommunication {
private:
  SPIClass* _spiConnection;
  bool _communicationActive;
  void InitiateCommunication();
  void EndCommunication();
  void SendByteWithStatusHandling(uint8_t byte);
  void SendFrame(SPI_Frame command);
  uint8_t ReceiveByte();

public:
  void Initialize(SPIClass* spiConnection);
  OscillatorState GetOscillatorState(uint8_t id);
  void SetOscillatorWaveform(uint8_t id, OscillatorType type);
  EnvelopeState GetEnvelopeState();
  FilterState GetFilterState();
  LFOState GetLFOState();
};