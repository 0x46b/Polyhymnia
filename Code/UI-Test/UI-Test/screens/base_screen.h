#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H
#include <lvgl.h>
#include <screen_types.h>

class BaseScreen {
protected:
  lv_obj_t *_screen;

public:
  virtual void setup() = 0;
  virtual void on_load() = 0;
  virtual void on_unload() = 0;
}

#endif
