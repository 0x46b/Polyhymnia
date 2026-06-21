#ifndef SCREEN_SETTINGS_H
#define SCREEN_SETTINGS_H

#include "Settings.hpp"
#include "base_screen.h"
#include <lvgl.h>

/* The screen for managing all system-settings */
class SettingScreen : BaseScreen {
private:
  lv_obj_t *_screen;
  static lv_subject_t _showBootscreen;
  lv_observer_t *_showBootscreenObserver;

  static lv_subject_t _bootscreenFilepath;
  char _bootscreenFilepathBuffer[255];

  static lv_subject_t _midiChannelIndex;
  lv_observer_t *_midiChannelIndexObserver;

  SystemSettings _systemSettings;

  /* Sets the initial values for the subjects using the systemSettings  */
  void initialize_subjects() {
    if (_systemSettings.ShowBootscreen) {
      lv_subject_init_int(&_showBootscreen, 1);
    } else {
      lv_subject_init_int(&_showBootscreen, 0);
    }

    lv_subject_init_string(&_bootscreenFilepath, &_bootscreenFilepathBuffer,
                           nullptr, sizeof(_bootscreenFilepathBuffer),
                           _systemSettings.BootscreenFilepath);

    lv_subject_init_int(&_midiChannelIndex, _systemSettings.MidiChannel + 1);
  }

  /* Opens a file-explorer, so the user can select a bootscreen-file.
   * If a file is selected it sets the path into the textareas subject,
   * switches back to the settings-screen and deletes the file-explorer
   */
  static void file_explorer_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target_obj(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
      const char *path = lv_file_explorer_get_current_path(obj);
      const char *filename = lv_file_explorer_get_selected_file_name(obj);
      char buffer[255];
      strcpy(&buffer, path);
      strcat(&buffer, '/');
      strcat(&buffer, filename);
      lv_subject_copy_string(&bootscreenFilepath, buffer);
    }

    lv_obj_t *fileExplorer = lv_screen_active();
    lv_screen_load(_screen);
    lv_obj_delete(fileExplorer);
  }

  /* Callback for the filepath textarea. Opens a file-explorer to handle file
   * choosing */
  static void filePath_event_cb(lv_event_t *e) {
    lv_obj_t *file_explorer = lv_file_explorer_create(lv_screen_active());
    lv_file_explorer_open_dir(file_explorer, "S:/imgs");
    lv_obj_add_event_cb(file_explorer, file_explorer_event_handler,
                        LV_EVENT_ALL, NULL);
  }

public:
  /* Creates a new screen stored into _screen and initialize subjects
   * If screen is already created, nothing will happen
   */
  void setup() {
    if (_screen != nullptr) {
      // TODO: Add lvgl-log here
      return;
    }

    initialize_subjects();

    _screen = lv_obj_create(NULL);
    lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_flex_main_place(screen, LV_FLEX_ALIGN_CENTER, 0);
    lv_obj_set_style_flex_cross_place(screen, LV_FLEX_ALIGN_CENTER, 0);
    lv_obj_set_style_flex_track_place(screen, LV_FLEX_ALIGN_CENTER, 0);
    lv_obj_set_style_pad_column(screen, 24, 0);

    lv_obj_t *content = lv_checkbox_create(_screen);
    lv_checkbox_set_text(content, "Show Bootscreen");
    _checkBoxObserver = lv_obj_bind_checked(cont, &_showBootscreen);

    lv_obj_t *container = lv_obj_create(screen);
    content = lv_label_create(container);
    lv_label_set_text(content, "Bootscreen Path:");

    content = lv_textarea_create(container);
    lv_textarea_set_one_line(content, true);
    lv_obj_add_event_cb(content, filePath_event_cb, LV_EVENT_READY, NULL);

    container = lv_obj_create(screen);
    content = lv_label_create(container);
    lv_label_set_text(content, "MIDI Channel:");

    content = lv_dropdown_create(container);
    lv_obj_set_width(dropdown, 160);
    lv_dropdown_set_options(
        content, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16");
    midiChannelIndexObserver =
        lv_dropdown_bind_value(content, &_midiChannelIndex);
  }

  /* Set screen active */
  void on_load() { lv_screen_load(_screen); }

  void on_unload() { lv_obj_delete(_screen); }
};

#endif
