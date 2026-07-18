#ifndef SETTINGS_H
#define SETTINGS_H

#include "Constants.hpp"
#include "WaveformTypes.hpp"

/*! Settings for system-stuff.
 * Different settings that are not directly related to the synthesizer-part
 */
typedef struct SystemSettings {
  /*! Show the bootscreen on startup.
   * If set to true the bootscreen and version-infos will get shown briefly on
   * the display after startup. If set to false the bootscreen will not get
   * shown and the homescreen is shown directly
   */
  bool ShowBootscreen;

  const char *BootscreenFilepath; /**< Path to the bootscreen-file to show, if
                                     ShowBootscreen is set to true */

  int MidiChannel; /**< MIDI-Channel to listen for. Set to 0 to deactivate and
                      respond to every channel  */
} SystemSettings;

/*! Settings for one single DCO.
 * Used to save/load patches (see PatchSetting)
 */
typedef struct DCOSetting {
  oscillator_waveform Waveform; /**< Waveform of the DCO */
  float Detune;                 /**< Value for detuning (min:0, max: 1) */
} DCOSetting;

/*! Settings for the noise-oscillator
 * Used to save/load patches (see PatchSetting)
 */
typedef struct NoiseSetting {
  float Gain;
} NoiseSetting;

/*! Configuration parameters for a standard ADSR (Attack, Decay, Sustain,
 * Release) volume envelope.
 *
 * This structure defines the duration and level characteristics used to shape
 * the amplitude of a sound over time. Used for saving/loading patches (see
 * PatchSetting)
 */
typedef struct EnvelopeSetting {
  float Attack;  /**< The time in ms taken for the signal to rise from zero to
                    its peak  level. */
  float Decay;   /**< The time in ms taken for the signal to fall from the peak
                    level to  the sustain level. */
  float Sustain; /**< The constant level of the signal during the sustained
                    sustain phase (0.0 to 1.0). */
  float Release; /**< The time in ms taken for the signal to decay from the
                    sustain level to zero after the key is released. */
} EnvelopeSetting;

typedef struct MixerSetting {
  float VCO1Gain;
  float VCO2Gain;
  float VCO3Gain;
  float NoiseGain;
} MixerSetting;

typedef struct FilterSetting {
  int Type;
  float Cutoff;
  float Resonance;
} FilterSetting;

typedef struct LFOSetting {
  float Rate;
  float Amount;
} LFOSetting;

typedef struct PatchSetting {
  const char *Name;
  DCOSetting VCO1;
  DCOSetting VCO2;
  DCOSetting VCO3;
  NoiseSetting Noise;
  EnvelopeSetting Envelope;
  MixerSetting Mixer;
  FilterSetting Filter;
  LFOSetting LFO;
} PatchSetting;

// Class-Definitions
class Settings {
private:
  bool _loadedSuccessfully = false;
  const char *_filename;

public:
  SystemSettings System;
  PatchSetting Patches[NUMBER_OF_PATCHES];

  Settings(const char *filename);

  bool LoadSettings();

  bool Save();

  bool is_loaded();
};

#endif