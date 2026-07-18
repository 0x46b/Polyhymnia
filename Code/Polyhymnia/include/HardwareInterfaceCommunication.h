#ifndef HARDWARE_INTERFACE_COMMUNICATION_H
#define HARDWARE_INTERFACE_COMMUNICATION_H

#include <SPI.h>

#include "control_types.h"
#include "spi_commands.hpp"

#define HW_INTERFACE_SCK 27
#define HW_INTERFACE_MOSI 26
#define HW_INTERFACE_MISO 39
#define HW_INTERFACE_SS 10

/*! Class for communicating with the different hardware-interfaces (OSC-Encoders
 * etc.)*/
class HardwareInterfaceCommunication {
private:
  SPIClass *_spiConnection;
  bool _communicationActive;
  void InitiateCommunication();
  void EndCommunication();
  void SendByteWithStatusHandling(uint8_t byte);
  void SendFrame(SPI_Frame command);
  uint8_t ReceiveByte();

public:
  HardwareInterfaceCommunication();
  void Initialize();
  OscillatorState GetOscillatorState(uint8_t id);
  void SetOscillatorWaveform(uint8_t id, OscillatorType type);
  EnvelopeState GetEnvelopeState();
  FilterState GetFilterState();
  LFOState GetLFOState();
};
#endif