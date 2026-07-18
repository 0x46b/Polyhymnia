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

/*! Settings for the volume of the different DCOs.
 * A single "tone" consists of mixing all DCOs together. With this setting you
 * can define of the ratios.
 * Used for saving/loading patches (see PatchSetting)
 * \remark{Note: Due to the nature of how teensy handles volume all volumes
 * added shouldn't exceed 1, else distortion is highly probable}
 */
typedef struct MixerSetting {
  float DCO1Gain;  /**< Gain for DCO 1 */
  float DCO2Gain;  /**< Gain for DCO 2 */
  float DCO3Gain;  /**< Gain for DCO 3 */
  float NoiseGain; /**< Gain for Noise */
} MixerSetting;

/*! Settings for the filter-section
 * Used for saving/loading patches (see PatchSetting)
 */
typedef struct FilterSetting {
  int Type; /**< filter-type \todo{Not implemented yet, but already mentioned
               for future use.}*/
  float Cutoff;    /**< Cutoff-corner-frequency */
  float Resonance; /**< Resonance-level (0 to 1.8, values over 1.0 can cause the
                      filter to self oscillate)*/
} FilterSetting;

typedef struct LFOSetting {
  float Rate;
  float Amount;
} LFOSetting;

/*! Settings used to store/load patches.
 */
typedef struct PatchSetting {
  const char *Name; /**< Name of the patch, shown in the UI */
  DCOSetting DCO1;
  DCOSetting DCO2;
  DCOSetting DCO3;
  NoiseSetting Noise;
  EnvelopeSetting Envelope;
  MixerSetting Mixer;
  FilterSetting Filter;
  LFOSetting LFO;
} PatchSetting;

/*! Manages (loading/saving) the settings */
class Settings {
private:
  bool _loadedSuccessfully = false;
  const char *_filename;

public:
  SystemSettings System;
  PatchSetting Patches[NUMBER_OF_PATCHES];

  /** Initializes a new settings-object for settings with the given filename
   * \param[in] filename Filename of the settings in *.json-format to use for
   * persistance
   */
  Settings(const char *filename);

  /*! Read the settings saved under filename and populate the values into System
   * and Patches */
  bool LoadSettings();

  /*! Saves System and Patches to the file at filename*/
  bool Save();

  /*! \returns True, if the settings where already loaded, false otherwise */
  bool is_loaded();
};

#endif