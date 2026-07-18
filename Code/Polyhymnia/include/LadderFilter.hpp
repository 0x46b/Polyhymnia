#ifndef LADDER_FILTER_HPP
#define LADDER_FILTER_HPP

#include "SerialLogger.hpp"
#include "Settings.hpp"
#include <Audio.h>
#include <inttypes.h>

/*! Wrapper-class for the teensy-filter */
class LadderFilter {
private:
  AudioFilterLadder *_teensyFilter; /**< Teensy-implementation of the filter */
  Logger *_logger;                  /**< Logger-instance */

  /*! Calculate the cutoff-frequency from a MIDI-CC-value
   * \returns The cutoff-frequency
   * \param[in] midiValue The MIDI-value for the cutoff-frequency (0-127)
   */
  float CalculateCutoff(uint8_t midiValue);

  /*! Sets the cutoff-frequency
   * \param[in] value the cutoff-frequency
   */
  void SetCutoff(uint8_t value);

  /*! Sets the resonance-frequency
   * \param[in] value the resonance-frequency
   */
  void SetResonance(uint8_t value);

public:
  LadderFilter(AudioFilterLadder *teensyFilter, Logger *logger);
  ~LadderFilter(void);

  /*! Handles a MIDI-CC-message
   * \param[in] cc CC-value
   * \param[in] value MIDI-value
   */
  void HandleMidiCC(uint8_t cc, uint8_t value);

  /*! Initializes with default values
   */
  void Initialize(void);

  /*! Initializes with values from the given settings
   * \param[in] Settings (see FilterSetting)
   */
  void Initialize(FilterSetting setting);
};

#endif