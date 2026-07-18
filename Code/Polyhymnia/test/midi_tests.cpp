#include "MIDI.hpp"
#include "doctest.h"

TEST_CASE("midivalue_to_frequency will have correct bounds") {
  float result = MIDI::midivalue_to_frequency(-10);
  CHECK(result == 0);
  result = MIDI::midivalue_to_frequency(128);
  CHECK(result == 0);
}