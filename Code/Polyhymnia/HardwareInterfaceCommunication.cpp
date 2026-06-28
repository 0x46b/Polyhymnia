#include "HardwareInterfaceCommunication.h"

void HardwareInterfaceCommunication::Initialize(SPIClass* spiConnection) {
  _spiConnection = spiConnection;

  pinMode(HW_INTERFACE_SS, OUTPUT);
  _spiConnection->setMOSI(HW_INTERFACE_MOSI);
  _spiConnection->setMISO(HW_INTERFACE_MISO);
  _spiConnection->setSCK(HW_INTERFACE_SCK);
  _spiConnection->setBitOrder(LSBFIRST);
  _spiConnection->setDataMode(SPI_MODE0);
  _spiConnection->setClockDivider(SPI_CLOCK_DIV128);
  _spiConnection->begin();
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
  Serial.print("Received id: ");
  Serial.print(state.Id);

  state.Offset = ReceiveByte();
  Serial.print("Received offset: ");
  Serial.print(state.Offset);
  
  state.Type = static_cast<OscillatorType>(ReceiveByte());
  Serial.print("Received type: ");
  Serial.print(state.Type);
  
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
  Serial.println("Initializing com");
  _communicationActive = true;
  digitalWrite(HW_INTERFACE_SS, LOW);
}

void HardwareInterfaceCommunication::EndCommunication() {
  Serial.println("Ending com");
  _communicationActive = false;
  digitalWrite(HW_INTERFACE_SS, HIGH);
}

void HardwareInterfaceCommunication::SendByteWithStatusHandling(uint8_t byte) {
  uint8_t moduleState = SPI.transfer(byte);
  if (moduleState != MODULE_LISTENING) {
    switch (moduleState) {
      case MODULE_BUSY:
        Serial.println("Module busy");
        // TODO Do something, I dunno what ATM
        break;
      case MODULE_FAILURE:
        Serial.println("Module failure");
        // TODO Do something, I dunno what ATM
        break;
      default:
      Serial.print("Unknown response:");
      Serial.println(moduleState, HEX);
        // TODO Do something, I dunno what ATM
        break;
    }
  }
}

void HardwareInterfaceCommunication::SendFrame(SPI_Frame command) {
  Serial.print("Sending Frame: {");
  Serial.print(command.command, HEX);
  Serial.print(", ");
  Serial.print(command.payload, HEX);
  Serial.println("}");
  SendByteWithStatusHandling(command.command);
  SendByteWithStatusHandling(command.payload);
}

uint8_t HardwareInterfaceCommunication::ReceiveByte(){
  return SPI.transfer(0);
}