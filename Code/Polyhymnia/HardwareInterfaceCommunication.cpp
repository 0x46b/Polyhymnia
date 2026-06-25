#include "HardwareInterfaceCommunication.h"

void HardwareInterfaceCommunication::Initialize(SPIClass* spiConnection) {
  _spiConnection = spiConnection;

  pinMode(HW_INTERFACE_SS, OUTPUT);
  _spiConnection->setMOSI(HW_INTERFACE_MOSI);
  _spiConnection->setMISO(HW_INTERFACE_MISO);
  _spiConnection->setSCK(HW_INTERFACE_SCK);
  SPI.begin();
}

OscillatorState HardwareInterfaceCommunication::GetOscillatorState(uint8_t id) {
  SPI_Frame frame{
    ReadOSC,
    id
  };
  InitiateCommunication();
  SendFrame(frame);

  OscillatorState state;
  state.Id = ReceiveByte();
  state.Offset = ReceiveByte();
  state.Type = static_cast<OscillatorType>(ReceiveByte());
  EndCommunication();
  return state;
}

void HardwareInterfaceCommunication::SetOscillatorWaveform(uint8_t id, OscillatorType type) {
  spi_command waveformCommand;

  switch (type) {
    case SAW:
      waveformCommand = SetWaveformSaw;
      break;
    case TRIANGLE:
      waveformCommand = SetWaveformTriangle;
      break;
    case SQUARE:
      waveformCommand = SetWaveformSquare;
      break;
    case SINE:
      waveformCommand = SetWaveformSine;
      break;
  };

  SPI_Frame frame{
    waveformCommand,
    id
  };
  InitiateCommunication();
  SendFrame(frame);
  EndCommunication();
}

EnvelopeState HardwareInterfaceCommunication::GetEnvelopeState() {
  SPI_Frame frame{
    ReadEnvelope,
    0
  };
  InitiateCommunication();
  SendFrame(frame);

  EnvelopeState state;
  state.Attack = ReceiveByte();
  state.Decay = ReceiveByte();
  state.Sustain = ReceiveByte();
  state.Release = ReceiveByte();
  EndCommunication();
  return state;
}

FilterState HardwareInterfaceCommunication::GetFilterState() {
  SPI_Frame frame{
    ReadFilter,
    0
  };
  InitiateCommunication();
    SendFrame(frame);

  FilterState state;
  state.Cutoff = ReceiveByte();
  state.Resonance = ReceiveByte();
  EndCommunication();
  return state;
}

LFOState HardwareInterfaceCommunication::GetLFOState() {
  SPI_Frame frame{
    ReadLFO,
    0
  };

  InitiateCommunication();

  SendFrame(frame);
  LFOState state;
  state.Frequency = ReceiveByte();
  state.Amount = ReceiveByte();

  EndCommunication();
  return state;
}

void HardwareInterfaceCommunication::InitiateCommunication() {
  _communicationActive = true;
  digitalWrite(HW_INTERFACE_SS, HIGH);
}

void HardwareInterfaceCommunication::EndCommunication() {
  _communicationActive = false;
  digitalWrite(HW_INTERFACE_SS, LOW);
}

void HardwareInterfaceCommunication::SendByteWithStatusHandling(uint8_t byte) {
  uint8_t moduleState = SPI.transfer(byte);
  if (moduleState != MODULE_LISTENING) {
    switch (moduleState) {
      case MODULE_BUSY:
        // TODO Do something, I dunno what ATM
        break;
      case MODULE_FAILURE:
        // TODO Do something, I dunno what ATM
        break;
      default:
        // TODO Do something, I dunno what ATM
        break;
    }
  }
}

void HardwareInterfaceCommunication::SendFrame(SPI_Frame command) {
  SendByteWithStatusHandling(command.command);
  SendByteWithStatusHandling(command.payload);
}