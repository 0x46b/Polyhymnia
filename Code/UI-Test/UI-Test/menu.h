#ifndef SCREENS_H
#define SCREENS_H
#include <lvgl.h>
#include "custom_icons_def.h"

lv_obj_t* add_menu_entry(const char* labelContent, lv_obj_t* page, lv_group_t* group) {
  lv_obj_t* cont = lv_menu_cont_create(page);
  lv_obj_t* label = lv_label_create(cont);
  lv_label_set_text(label, labelContent);

  lv_group_add_obj(group, cont);
  lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_add_flag(cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

  return cont;
}

lv_obj_t* add_menu_entry(const char* symbol, const char* labelContent, lv_obj_t* page, lv_group_t* group) {
  lv_obj_t* cont = lv_menu_cont_create(page);
  lv_obj_t * label1 = lv_label_create(cont);
  lv_label_set_text(label1, symbol);

  lv_obj_t* label = lv_label_create(cont);
  lv_label_set_text(label, labelContent);
  lv_group_add_obj(group, cont);
  lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_add_flag(cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

  return cont;
}

lv_obj_t* create_menu(lv_group_t* group) {
  /*Create a menu object*/
  lv_obj_t* menu = lv_menu_create(lv_scr_act());
  lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
  lv_obj_center(menu);

  lv_obj_t* cont;

  /*Create a sub page*/
  lv_obj_t* patch_page = lv_menu_page_create(menu, NULL);

  add_menu_entry(LV_SYMBOL_AUDIO, "Supersaw", patch_page, group);
  add_menu_entry(LV_SYMBOL_AUDIO, "Square", patch_page, group);
  add_menu_entry(LV_SYMBOL_AUDIO, "Shwifty Bass", patch_page, group);

  lv_obj_t* visualization_page = lv_menu_page_create(menu, NULL);

  add_menu_entry(LV_SYMBOL_AUDIO, "FFT", visualization_page, group);
  add_menu_entry(LV_SYMBOL_AUDIO, "Waveform", visualization_page, group);
  add_menu_entry(LV_SYMBOL_AUDIO, "GIF", visualization_page, group);

  lv_obj_t* patch_edit_page = lv_menu_page_create(menu, NULL);

  add_menu_entry("Name", patch_edit_page, group);
  add_menu_entry("Oscillators", patch_edit_page, group);
  add_menu_entry("LFO", patch_edit_page, group);
  add_menu_entry("Envelope", patch_edit_page, group);

  /*Create a main page*/
  lv_obj_t* main_page = lv_menu_page_create(menu, NULL);

  cont = add_menu_entry(CUST_ICON_POO, "Patches", main_page, group);
  lv_menu_set_load_page_event(menu, cont, patch_page);

  cont = add_menu_entry(CUST_ICON_CLAPPERBOARD, "Visualization", main_page, group);
  lv_menu_set_load_page_event(menu, cont, visualization_page);

  cont = add_menu_entry(CUST_ICON_HAND_FIST, "Live-Edit", main_page, group);
  lv_menu_set_load_page_event(menu, cont, patch_edit_page);
  
  add_menu_entry(CUST_ICON_FLASK_VIAL, "Settings", main_page, group);
  add_menu_entry(CUST_ICON_CAT, "LED-Matrix", main_page, group);

  lv_menu_set_sidebar_page(menu, main_page);
  lv_group_focus_next(group);

  return menu;
}




#endif