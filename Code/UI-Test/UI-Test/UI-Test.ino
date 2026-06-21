#include "libraries/lv_conf.h"
#include <lvgl.h>
#include <ILI9341_T4.h>
#include <SD.h>

#include "config.h"
#include "ui/ui.h"

// 2 diff buffers with about 8K memory each
ILI9341_T4::DiffBuffStatic<8000> diff1;
ILI9341_T4::DiffBuffStatic<8000> diff2;

// the internal framebuffer for the ILI9341_T4 driver (150KB)
// in DMAMEM to save space in the lower (faster) part of RAM.
DMAMEM uint16_t internal_fb[LX * LY];

// the screen driver object
ILI9341_T4::ILI9341Driver tft(PIN_CS, PIN_DC, PIN_SCK, PIN_MOSI, PIN_MISO, PIN_RESET);

lv_color_t lvgl_buf[LX * BUF_LY];  // memory for lvgl draw buffer (25KB)

lv_display_t* disp;  // pointer to lvgl display object

bool initialize_sd_card() {
  Serial.print("SD-card Initialization");

  // see if the card is present and can be initialized:
  if (!SD.begin(SD_CS)) {
    Serial.println("[FAILED]");
    return false;
  }

  Serial.println("[OK]");
  return true;
}

void my_log_cb(lv_log_level_t level, const char * buf)
{
  Serial.print(buf);
}

void initialize_logging(){
  lv_log_register_print_cb(my_log_cb);
}

/** LVGL Callback to draw on the screen */
void my_disp_flush(lv_display_t* disp, const lv_area_t* area, uint8_t* px_map) {
  const bool redraw_now = lv_disp_flush_is_last(disp);                                      // check if when should update the screen (or just buffer the changes).
  tft.updateRegion(redraw_now, (uint16_t*)px_map, area->x1, area->x2, area->y1, area->y2);  // update the interval framebuffer and then redraw the screen if requested
  lv_disp_flush_ready(disp);                                                                // tell lvgl that we are done and that the lvgl draw buffer can be reused immediately
}

/*use Arduinos millis() as tick source*/
static uint32_t my_tick(void) {
  return millis();
}

/**INIT BUTTONS */
void init_buttons() {
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  pinMode(ENTER_BTN, INPUT_PULLUP);
}

lv_key_t my_last_key() {
  if (!digitalRead(LEFT_BTN)) {
    Serial.println("Left pressed!");
    return LV_KEY_LEFT;
  }
  if (!digitalRead(RIGHT_BTN)) {
    Serial.println("Right pressed!");
    return LV_KEY_RIGHT;
  }
  if (!digitalRead(ENTER_BTN)) {
    Serial.println("Enter pressed!");
    return LV_KEY_ENTER;
  }

  return LV_KEY_ESC;
}

bool key_pressed() {
  bool result = !digitalRead(LEFT_BTN) || !digitalRead(RIGHT_BTN) || !digitalRead(ENTER_BTN);

  if (result) {
    Serial.println("Btn pressed!");
  }

  return result;
}

void encoder_with_keys_read(lv_indev_t* indev, lv_indev_data_t* data) {
  if (key_pressed()) {
    /* Get the last pressed or released key
       * use LV_KEY_ENTER for encoder press */
    data->key = my_last_key();
    data->state = LV_INDEV_STATE_PRESSED;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}
// ------------------------------
// Init the ILI9341_T4 driver.
// ------------------------------
void init_tft_driver() {
  //tft.output(&Serial);  // send debug info to serial port.
  while (!tft.begin(SPI_SPEED))
    ;                                  // init
  tft.setFramebuffer(internal_fb);     // set the internal framebuffer
  tft.setDiffBuffers(&diff1, &diff2);  // set the diff buffers
  tft.setRotation(1);                  // portrait mode 0 : 240x320
  tft.setDiffGap(4);                   // with have large 8K diff buffers so we can use a small gap.
  tft.setVSyncSpacing(1);              // lvgl is already controlling framerate: we just set this to 1 to minimize screen tearing.
  tft.setRefreshRate(100);             // 100Hz refresh, why not...
  tft.clear(0);

  // Set BACKLIGHT to on
  pinMode(PIN_BACKLIGHT, OUTPUT);
  digitalWrite(PIN_BACKLIGHT, HIGH);

  Serial.println("TFT Driver setup done");
}

// ------------------------------
// Init LVGL
// ------------------------------
void init_lvgl() {
  lv_init();

  lv_tick_set_cb(my_tick);

  disp = lv_display_create(LX, LY);
  lv_display_set_flush_cb(disp, my_disp_flush);
  lv_display_set_buffers(disp, lvgl_buf, nullptr, LX * BUF_LY * sizeof(int16_t), LV_DISPLAY_RENDER_MODE_PARTIAL);
}

void showBootscreen(int showInSeconds){
    lv_obj_t * screen = lv_screen_active();
    lv_obj_t * image = lv_image_create(screen);
    lv_image_set_src(image, "S:/imgs/Bootup_Screen_distorted.bmp");
    lv_obj_set_align(image, LV_ALIGN_CENTER);
}

void showGif(){
  lv_obj_t *img = lv_gif_create(lv_screen_active());
    lv_gif_set_color_format(img, LV_COLOR_FORMAT_ARGB8888);
    lv_gif_set_src(img, "S:/imgs/nyan-cat-rainbow.gif");
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

void setup() {
   Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }
  initialize_sd_card();
  init_buttons();
  init_tft_driver();
  init_lvgl();
  initialize_logging();

  Serial.println("LGVL Setup done");
  lv_group_t* group = lv_group_create();
  lv_group_set_default(group);

  lv_indev_t* indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_ENCODER);
  lv_indev_set_read_cb(indev, encoder_with_keys_read);
  lv_indev_set_group(indev, group);
  //showGif();
  //create_menu(group);
  
  //showBootscreen(5);
}

void loop() {
  lv_timer_handler();  // lvgl gui handler
  delay(5);
}
