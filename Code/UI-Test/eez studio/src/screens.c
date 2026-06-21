#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

static void event_handler_cb_bootup_bootup(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: MainGroup
        lv_group_remove_all_objs(groups.MainGroup);
    }
}

static void event_handler_cb_dashboard_dashboard(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: MainGroup
        lv_group_remove_all_objs(groups.MainGroup);
    }
}

static void event_handler_cb_patches_patches(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: MainGroup
        lv_group_remove_all_objs(groups.MainGroup);
        lv_group_add_obj(groups.MainGroup, objects.obj6);
    }
}

static void event_handler_cb_visualization_visualization(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: MainGroup
        lv_group_remove_all_objs(groups.MainGroup);
        lv_group_add_obj(groups.MainGroup, objects.obj7);
        lv_group_add_obj(groups.MainGroup, objects.obj8);
    }
}

static void event_handler_cb_settings_settings(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: MainGroup
        lv_group_remove_all_objs(groups.MainGroup);
        lv_group_add_obj(groups.MainGroup, objects.chck_show_bootscreen);
        lv_group_add_obj(groups.MainGroup, objects.drp_bootscreen_mode);
        lv_group_add_obj(groups.MainGroup, objects.drp_midichannel);
        lv_group_add_obj(groups.MainGroup, objects.save_button);
        lv_group_add_obj(groups.MainGroup, objects.abort_button);
    }
}

static void event_handler_cb_settings_chck_show_bootscreen(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target_obj(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_show_bootscreen(value);
        }
    }
}

static void event_handler_cb_settings_drp_bootscreen_mode(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target_obj(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_bootscreen_type(value);
        }
    }
}

static void event_handler_cb_settings_drp_midichannel(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target_obj(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_midichannel(value);
        }
    }
}

static void event_handler_cb_gif_visualization_gif_visualization(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: MainGroup
        lv_group_remove_all_objs(groups.MainGroup);
    }
}

static void event_handler_cb_fft_visualization_fft_visualization(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: MainGroup
        lv_group_remove_all_objs(groups.MainGroup);
    }
}

static void event_handler_cb_patch_edit_patch_edit(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: MainGroup
        lv_group_remove_all_objs(groups.MainGroup);
    }
}

//
// Screens
//

void create_screen_bootup() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.bootup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, action_switch_to_main, LV_EVENT_SCREEN_LOADED, (void *)0);
    lv_obj_add_event_cb(obj, event_handler_cb_bootup_bootup, LV_EVENT_ALL, 0);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "S:\\imgs\ui_image_bootup_screen.bin");
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_spinner_create(parent_obj);
                    lv_obj_set_pos(obj, 34, 129);
                    lv_obj_set_size(obj, 80, 80);
                    add_style_spinner_style(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj0 = obj;
                    lv_obj_set_pos(obj, 0, 224);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 16);
                    add_style_default_label_style(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0x877e59), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Version: ");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 43, 224);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 16);
                    add_style_default_label_style(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0x877e59), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
    }
    
    tick_screen_bootup();
}

void tick_screen_bootup() {
    {
        const char *new_val = get_var_version();
        const char *cur_val = lv_label_get_text(objects.obj1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj1;
            lv_label_set_text(objects.obj1, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_dashboard() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.dashboard = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, action_open_settings, LV_EVENT_TRIPLE_CLICKED, (void *)0);
    lv_obj_add_event_cb(obj, event_handler_cb_dashboard_dashboard, LV_EVENT_ALL, 0);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 160, 120);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_oscillator(obj, 11);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 160, 0);
            lv_obj_set_size(obj, 160, 120);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_oscillator(obj, 19);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 0, 120);
            lv_obj_set_size(obj, 160, 120);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_oscillator(obj, 27);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 160, 120);
            lv_obj_set_size(obj, 160, 120);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_adsr(obj, 35);
        }
    }
    
    tick_screen_dashboard();
}

void tick_screen_dashboard() {
    tick_user_widget_oscillator(11);
    tick_user_widget_oscillator(19);
    tick_user_widget_oscillator(27);
    tick_user_widget_adsr(35);
}

void create_screen_patches() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.patches = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_patches_patches, LV_EVENT_ALL, 0);
    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 10, 9);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_header_label_style(obj);
            lv_label_set_text_static(obj, "Patches");
        }
        {
            lv_obj_t *obj = lv_list_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 10, 33);
            lv_obj_set_size(obj, 297, 195);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_default_label_style(obj);
                    lv_label_set_text_static(obj, "Patch 1");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_default_label_style(obj);
                    lv_label_set_text_static(obj, "Patch 2");
                }
            }
        }
    }
    
    tick_screen_patches();
}

void tick_screen_patches() {
}

void create_screen_visualization() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.visualization = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_visualization_visualization, LV_EVENT_ALL, 0);
    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 10, 9);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_header_label_style(obj);
            lv_label_set_text_static(obj, "Visualization");
        }
        {
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.obj7 = obj;
            lv_obj_set_pos(obj, 10, 51);
            lv_obj_set_size(obj, 297, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "FFT\nWaveform\nGIF");
            lv_dropdown_set_selected(obj, 0);
            add_style_dropdown_style(obj);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj8 = obj;
            lv_obj_set_pos(obj, 112, 154);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_start_visualization, LV_EVENT_PRESSED, (void *)0);
            add_style_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Start");
                }
            }
        }
    }
    
    tick_screen_visualization();
}

void tick_screen_visualization() {
}

void create_screen_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_settings_settings, LV_EVENT_ALL, 0);
    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // chck_show_bootscreen
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.chck_show_bootscreen = obj;
            lv_obj_set_pos(obj, 9, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text_static(obj, "Show Bootscreen");
            lv_obj_add_event_cb(obj, event_handler_cb_settings_chck_show_bootscreen, LV_EVENT_ALL, 0);
            add_style_checkbox_style(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 9, 92);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_default_label_style(obj);
            lv_label_set_text_static(obj, "Bootscreen File:");
        }
        {
            // drp_bootscreen_mode
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.drp_bootscreen_mode = obj;
            lv_obj_set_pos(obj, 157, 82);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "Distorted\nNormal");
            lv_obj_add_event_cb(obj, event_handler_cb_settings_drp_bootscreen_mode, LV_EVENT_ALL, 0);
            add_style_dropdown_style(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 9, 146);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_default_label_style(obj);
            lv_label_set_text_static(obj, "MIDI Channel:");
        }
        {
            // drp_midichannel
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.drp_midichannel = obj;
            lv_obj_set_pos(obj, 157, 136);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16");
            lv_obj_add_event_cb(obj, event_handler_cb_settings_drp_midichannel, LV_EVENT_ALL, 0);
            add_style_dropdown_style(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 9, 11);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_header_label_style(obj);
            lv_label_set_text_static(obj, "System Settings");
        }
        {
            // save button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.save_button = obj;
            lv_obj_set_pos(obj, 9, 180);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_save_settings, LV_EVENT_PRESSED, (void *)0);
            add_style_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Save");
                }
            }
        }
        {
            // abort button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.abort_button = obj;
            lv_obj_set_pos(obj, 207, 180);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_exit_settings, LV_EVENT_PRESSED, (void *)0);
            add_style_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Abort");
                }
            }
        }
    }
    
    tick_screen_settings();
}

void tick_screen_settings() {
    {
        bool new_val = get_var_show_bootscreen();
        bool cur_val = lv_obj_has_state(objects.chck_show_bootscreen, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.chck_show_bootscreen;
            if (new_val) {
                lv_obj_add_state(objects.chck_show_bootscreen, LV_STATE_CHECKED);
            } else {
                lv_obj_remove_state(objects.chck_show_bootscreen, LV_STATE_CHECKED);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.drp_bootscreen_mode) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_bootscreen_type();
            int32_t cur_val = lv_dropdown_get_selected(objects.drp_bootscreen_mode);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.drp_bootscreen_mode;
                lv_dropdown_set_selected(objects.drp_bootscreen_mode, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        if (!(lv_obj_get_state(objects.drp_midichannel) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_midichannel();
            int32_t cur_val = lv_dropdown_get_selected(objects.drp_midichannel);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.drp_midichannel;
                lv_dropdown_set_selected(objects.drp_midichannel, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_gif_visualization() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gif_visualization = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_gif_visualization_gif_visualization, LV_EVENT_ALL, 0);
    
    tick_screen_gif_visualization();
}

void tick_screen_gif_visualization() {
}

void create_screen_fft_visualization() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.fft_visualization = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_fft_visualization_fft_visualization, LV_EVENT_ALL, 0);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_chart_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
        }
    }
    
    tick_screen_fft_visualization();
}

void tick_screen_fft_visualization() {
}

void create_screen_patch_edit() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.patch_edit = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_patch_edit_patch_edit, LV_EVENT_ALL, 0);
    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 9, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_header_label_style(obj);
            lv_label_set_text_static(obj, "Editing ");
        }
        {
            // patch_name
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.patch_name = obj;
            lv_obj_set_pos(obj, 89, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_header_label_style(obj);
            lv_label_set_text_static(obj, "Patch 1");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 9, 57);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_default_label_style(obj);
            lv_label_set_text_static(obj, "Name:");
        }
        {
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            lv_obj_set_pos(obj, 92, 47);
            lv_obj_set_size(obj, 217, 36);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_placeholder_text(obj, "Patchname");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 28, 174);
            lv_obj_set_size(obj, 100, 50);
            add_style_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Save");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 188, 174);
            lv_obj_set_size(obj, 100, 50);
            add_style_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Abort");
                }
            }
        }
    }
    
    tick_screen_patch_edit();
}

void tick_screen_patch_edit() {
}

void create_user_widget_oscillator(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 9, 3);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_header_label_style(obj);
            lv_label_set_text_static(obj, "DCO");
        }
        {
            // dco_number
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 63, 3);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_header_label_style(obj);
            lv_label_set_text(obj, "");
        }
        {
            // waveform_sine
            lv_obj_t *obj = lv_line_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
            lv_obj_set_pos(obj, 0, 27);
            lv_obj_set_size(obj, 160, 93);
            static lv_point_precise_t line_points[] = {
                { 0, 40 },
                { 1, 38 },
                { 2, 36 },
                { 3, 35 },
                { 4, 33 },
                { 5, 31 },
                { 6, 30 },
                { 7, 28 },
                { 8, 26 },
                { 9, 25 },
                { 10, 23 },
                { 11, 22 },
                { 12, 20 },
                { 13, 19 },
                { 14, 18 },
                { 15, 16 },
                { 16, 15 },
                { 17, 14 },
                { 18, 12 },
                { 19, 11 },
                { 20, 10 },
                { 21, 9 },
                { 22, 8 },
                { 23, 7 },
                { 24, 6 },
                { 25, 5 },
                { 26, 4 },
                { 27, 4 },
                { 28, 3 },
                { 29, 2 },
                { 30, 2 },
                { 31, 1 },
                { 32, 1 },
                { 33, 1 },
                { 34, 0 },
                { 35, 0 },
                { 36, 0 },
                { 37, 0 },
                { 38, 0 },
                { 39, 0 },
                { 40, 0 },
                { 41, 0 },
                { 42, 1 },
                { 43, 1 },
                { 44, 2 },
                { 45, 2 },
                { 46, 3 },
                { 47, 3 },
                { 48, 4 },
                { 49, 5 },
                { 50, 6 },
                { 51, 6 },
                { 52, 7 },
                { 53, 8 },
                { 54, 9 },
                { 55, 11 },
                { 56, 12 },
                { 57, 13 },
                { 58, 14 },
                { 59, 15 },
                { 60, 17 },
                { 61, 18 },
                { 62, 20 },
                { 63, 21 },
                { 64, 23 },
                { 65, 24 },
                { 66, 26 },
                { 67, 27 },
                { 68, 29 },
                { 69, 30 },
                { 70, 32 },
                { 71, 34 },
                { 72, 35 },
                { 73, 37 },
                { 74, 39 },
                { 75, 40 },
                { 76, 42 },
                { 77, 44 },
                { 78, 45 },
                { 79, 47 },
                { 80, 49 },
                { 81, 50 },
                { 82, 52 },
                { 83, 53 },
                { 84, 55 },
                { 85, 56 },
                { 86, 58 },
                { 87, 59 },
                { 88, 61 },
                { 89, 62 },
                { 90, 64 },
                { 91, 65 },
                { 92, 66 },
                { 93, 67 },
                { 94, 68 },
                { 95, 70 },
                { 96, 71 },
                { 97, 72 },
                { 98, 73 },
                { 99, 73 },
                { 100, 74 },
                { 101, 75 },
                { 102, 76 },
                { 103, 76 },
                { 104, 77 },
                { 105, 77 },
                { 106, 78 },
                { 107, 78 },
                { 108, 79 },
                { 109, 79 },
                { 110, 79 },
                { 111, 79 },
                { 112, 79 },
                { 113, 79 },
                { 114, 79 },
                { 115, 79 },
                { 116, 78 },
                { 117, 78 },
                { 118, 78 },
                { 119, 77 },
                { 120, 77 },
                { 121, 76 },
                { 122, 75 },
                { 123, 75 },
                { 124, 74 },
                { 125, 73 },
                { 126, 72 },
                { 127, 71 },
                { 128, 70 },
                { 129, 69 },
                { 130, 68 },
                { 131, 67 },
                { 132, 65 },
                { 133, 64 },
                { 134, 63 },
                { 135, 61 },
                { 136, 60 },
                { 137, 59 },
                { 138, 57 },
                { 139, 56 },
                { 140, 54 },
                { 141, 53 },
                { 142, 51 },
                { 143, 49 },
                { 144, 48 },
                { 145, 46 },
                { 146, 44 },
                { 147, 43 },
                { 148, 41 },
                { 149, 40 }
            };
            lv_line_set_points(obj, line_points, 150);
            add_style_waveform_line_style(obj);
        }
        {
            // waveform_saw
            lv_obj_t *obj = lv_line_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
            lv_obj_set_pos(obj, 0, 27);
            lv_obj_set_size(obj, 160, 93);
            static lv_point_precise_t line_points[] = {
                { 0, 79 },
                { 1, 78 },
                { 2, 77 },
                { 3, 76 },
                { 4, 75 },
                { 5, 74 },
                { 6, 73 },
                { 7, 72 },
                { 8, 70 },
                { 9, 69 },
                { 10, 68 },
                { 11, 67 },
                { 12, 66 },
                { 13, 65 },
                { 14, 64 },
                { 15, 63 },
                { 16, 62 },
                { 17, 61 },
                { 18, 60 },
                { 19, 59 },
                { 20, 58 },
                { 21, 57 },
                { 22, 56 },
                { 23, 54 },
                { 24, 53 },
                { 25, 52 },
                { 26, 51 },
                { 27, 50 },
                { 28, 49 },
                { 29, 48 },
                { 30, 47 },
                { 31, 46 },
                { 32, 45 },
                { 33, 44 },
                { 34, 43 },
                { 35, 42 },
                { 36, 41 },
                { 37, 40 },
                { 38, 38 },
                { 39, 37 },
                { 40, 36 },
                { 41, 35 },
                { 42, 34 },
                { 43, 33 },
                { 44, 32 },
                { 45, 31 },
                { 46, 30 },
                { 47, 29 },
                { 48, 28 },
                { 49, 27 },
                { 50, 26 },
                { 51, 25 },
                { 52, 23 },
                { 53, 22 },
                { 54, 21 },
                { 55, 20 },
                { 56, 19 },
                { 57, 18 },
                { 58, 17 },
                { 59, 16 },
                { 60, 15 },
                { 61, 14 },
                { 62, 13 },
                { 63, 12 },
                { 64, 11 },
                { 65, 10 },
                { 66, 9 },
                { 67, 7 },
                { 68, 6 },
                { 69, 5 },
                { 70, 4 },
                { 71, 3 },
                { 72, 2 },
                { 73, 1 },
                { 74, 0 },
                { 75, 79 },
                { 76, 78 },
                { 77, 77 },
                { 78, 76 },
                { 79, 75 },
                { 80, 74 },
                { 81, 73 },
                { 82, 72 },
                { 83, 70 },
                { 84, 69 },
                { 85, 68 },
                { 86, 67 },
                { 87, 66 },
                { 88, 65 },
                { 89, 64 },
                { 90, 63 },
                { 91, 62 },
                { 92, 61 },
                { 93, 60 },
                { 94, 59 },
                { 95, 58 },
                { 96, 57 },
                { 97, 56 },
                { 98, 54 },
                { 99, 53 },
                { 100, 52 },
                { 101, 51 },
                { 102, 50 },
                { 103, 49 },
                { 104, 48 },
                { 105, 47 },
                { 106, 46 },
                { 107, 45 },
                { 108, 44 },
                { 109, 43 },
                { 110, 42 },
                { 111, 41 },
                { 112, 40 },
                { 113, 38 },
                { 114, 37 },
                { 115, 36 },
                { 116, 35 },
                { 117, 34 },
                { 118, 33 },
                { 119, 32 },
                { 120, 31 },
                { 121, 30 },
                { 122, 29 },
                { 123, 28 },
                { 124, 27 },
                { 125, 26 },
                { 126, 25 },
                { 127, 23 },
                { 128, 22 },
                { 129, 21 },
                { 130, 20 },
                { 131, 19 },
                { 132, 18 },
                { 133, 17 },
                { 134, 16 },
                { 135, 14 },
                { 136, 13 },
                { 137, 12 },
                { 138, 11 },
                { 139, 10 },
                { 140, 9 },
                { 141, 8 },
                { 142, 7 },
                { 143, 6 },
                { 144, 5 },
                { 145, 4 },
                { 146, 3 },
                { 147, 2 },
                { 148, 1 },
                { 149, 0 }
            };
            lv_line_set_points(obj, line_points, 150);
            add_style_waveform_line_style(obj);
        }
        {
            // waveform_triangle
            lv_obj_t *obj = lv_line_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
            lv_obj_set_pos(obj, 0, 27);
            lv_obj_set_size(obj, 160, 93);
            static lv_point_precise_t line_points[] = {
                { 0, 79 },
                { 1, 77 },
                { 2, 75 },
                { 3, 73 },
                { 4, 70 },
                { 5, 68 },
                { 6, 66 },
                { 7, 64 },
                { 8, 62 },
                { 9, 60 },
                { 10, 58 },
                { 11, 56 },
                { 12, 53 },
                { 13, 51 },
                { 14, 49 },
                { 15, 47 },
                { 16, 45 },
                { 17, 43 },
                { 18, 41 },
                { 19, 38 },
                { 20, 36 },
                { 21, 34 },
                { 22, 32 },
                { 23, 30 },
                { 24, 28 },
                { 25, 26 },
                { 26, 23 },
                { 27, 21 },
                { 28, 19 },
                { 29, 17 },
                { 30, 15 },
                { 31, 13 },
                { 32, 11 },
                { 33, 9 },
                { 34, 6 },
                { 35, 4 },
                { 36, 2 },
                { 37, 0 },
                { 38, 2 },
                { 39, 4 },
                { 40, 6 },
                { 41, 9 },
                { 42, 11 },
                { 43, 13 },
                { 44, 15 },
                { 45, 17 },
                { 46, 19 },
                { 47, 21 },
                { 48, 23 },
                { 49, 26 },
                { 50, 28 },
                { 51, 30 },
                { 52, 32 },
                { 53, 34 },
                { 54, 36 },
                { 55, 38 },
                { 56, 41 },
                { 57, 43 },
                { 58, 45 },
                { 59, 47 },
                { 60, 49 },
                { 61, 51 },
                { 62, 53 },
                { 63, 56 },
                { 64, 58 },
                { 65, 60 },
                { 66, 62 },
                { 67, 64 },
                { 68, 66 },
                { 69, 68 },
                { 70, 70 },
                { 71, 73 },
                { 72, 75 },
                { 73, 77 },
                { 74, 79 },
                { 75, 79 },
                { 76, 77 },
                { 77, 75 },
                { 78, 73 },
                { 79, 70 },
                { 80, 68 },
                { 81, 66 },
                { 82, 64 },
                { 83, 62 },
                { 84, 60 },
                { 85, 58 },
                { 86, 56 },
                { 87, 53 },
                { 88, 51 },
                { 89, 49 },
                { 90, 47 },
                { 91, 45 },
                { 92, 43 },
                { 93, 41 },
                { 94, 38 },
                { 95, 36 },
                { 96, 34 },
                { 97, 32 },
                { 98, 30 },
                { 99, 28 },
                { 100, 26 },
                { 101, 23 },
                { 102, 21 },
                { 103, 19 },
                { 104, 17 },
                { 105, 15 },
                { 106, 13 },
                { 107, 11 },
                { 108, 9 },
                { 109, 6 },
                { 110, 4 },
                { 111, 2 },
                { 112, 0 },
                { 113, 2 },
                { 114, 4 },
                { 115, 6 },
                { 116, 9 },
                { 117, 11 },
                { 118, 13 },
                { 119, 15 },
                { 120, 17 },
                { 121, 19 },
                { 122, 21 },
                { 123, 23 },
                { 124, 26 },
                { 125, 28 },
                { 126, 30 },
                { 127, 32 },
                { 128, 34 },
                { 129, 36 },
                { 130, 38 },
                { 131, 41 },
                { 132, 43 },
                { 133, 45 },
                { 134, 47 },
                { 135, 49 },
                { 136, 51 },
                { 137, 53 },
                { 138, 56 },
                { 139, 58 },
                { 140, 60 },
                { 141, 62 },
                { 142, 64 },
                { 143, 66 },
                { 144, 68 },
                { 145, 70 },
                { 146, 73 },
                { 147, 75 },
                { 148, 77 },
                { 149, 79 }
            };
            lv_line_set_points(obj, line_points, 150);
            add_style_waveform_line_style(obj);
        }
        {
            // waveform_square
            lv_obj_t *obj = lv_line_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
            lv_obj_set_pos(obj, 0, 27);
            lv_obj_set_size(obj, 160, 90);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 1, 0 },
                { 2, 0 },
                { 3, 0 },
                { 4, 0 },
                { 5, 0 },
                { 6, 0 },
                { 7, 0 },
                { 8, 0 },
                { 9, 0 },
                { 10, 0 },
                { 11, 0 },
                { 12, 0 },
                { 13, 0 },
                { 14, 0 },
                { 15, 0 },
                { 16, 0 },
                { 17, 0 },
                { 18, 0 },
                { 19, 0 },
                { 20, 0 },
                { 21, 0 },
                { 22, 0 },
                { 23, 0 },
                { 24, 0 },
                { 25, 0 },
                { 26, 0 },
                { 27, 0 },
                { 28, 0 },
                { 29, 0 },
                { 30, 0 },
                { 31, 0 },
                { 32, 0 },
                { 33, 0 },
                { 34, 0 },
                { 35, 0 },
                { 36, 0 },
                { 37, 0 },
                { 38, 79 },
                { 39, 79 },
                { 40, 79 },
                { 41, 79 },
                { 42, 79 },
                { 43, 79 },
                { 44, 79 },
                { 45, 79 },
                { 46, 79 },
                { 47, 79 },
                { 48, 79 },
                { 49, 79 },
                { 50, 79 },
                { 51, 79 },
                { 52, 79 },
                { 53, 79 },
                { 54, 79 },
                { 55, 79 },
                { 56, 79 },
                { 57, 79 },
                { 58, 79 },
                { 59, 79 },
                { 60, 79 },
                { 61, 79 },
                { 62, 79 },
                { 63, 79 },
                { 64, 79 },
                { 65, 79 },
                { 66, 79 },
                { 67, 79 },
                { 68, 79 },
                { 69, 79 },
                { 70, 79 },
                { 71, 79 },
                { 72, 79 },
                { 73, 79 },
                { 74, 79 },
                { 75, 0 },
                { 76, 0 },
                { 77, 0 },
                { 78, 0 },
                { 79, 0 },
                { 80, 0 },
                { 81, 0 },
                { 82, 0 },
                { 83, 0 },
                { 84, 0 },
                { 85, 0 },
                { 86, 0 },
                { 87, 0 },
                { 88, 0 },
                { 89, 0 },
                { 90, 0 },
                { 91, 0 },
                { 92, 0 },
                { 93, 0 },
                { 94, 0 },
                { 95, 0 },
                { 96, 0 },
                { 97, 0 },
                { 98, 0 },
                { 99, 0 },
                { 100, 0 },
                { 101, 0 },
                { 102, 0 },
                { 103, 0 },
                { 104, 0 },
                { 105, 0 },
                { 106, 0 },
                { 107, 0 },
                { 108, 0 },
                { 109, 0 },
                { 110, 0 },
                { 111, 0 },
                { 112, 0 },
                { 113, 79 },
                { 114, 79 },
                { 115, 79 },
                { 116, 79 },
                { 117, 79 },
                { 118, 79 },
                { 119, 79 },
                { 120, 79 },
                { 121, 79 },
                { 122, 79 },
                { 123, 79 },
                { 124, 79 },
                { 125, 79 },
                { 126, 79 },
                { 127, 79 },
                { 128, 79 },
                { 129, 79 },
                { 130, 79 },
                { 131, 79 },
                { 132, 79 },
                { 133, 79 },
                { 134, 79 },
                { 135, 79 },
                { 136, 79 },
                { 137, 79 },
                { 138, 79 },
                { 139, 79 },
                { 140, 79 },
                { 141, 79 },
                { 142, 79 },
                { 143, 79 },
                { 144, 79 },
                { 145, 79 },
                { 146, 79 },
                { 147, 79 },
                { 148, 79 },
                { 149, 79 }
            };
            lv_line_set_points(obj, line_points, 150);
            add_style_waveform_line_style(obj);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
            lv_obj_set_pos(obj, 69, 68);
            lv_obj_set_size(obj, 86, 10);
            lv_bar_set_range(obj, -600, 600);
            lv_bar_set_mode(obj, LV_BAR_MODE_SYMMETRICAL);
            add_style_bar_style(obj);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
            lv_obj_set_pos(obj, 69, 94);
            lv_obj_set_size(obj, 87, 10);
            add_style_bar_style(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 4, 65);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_default_label_style(obj);
            lv_label_set_text_static(obj, "Detune");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 4, 91);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_default_label_style(obj);
            lv_label_set_text_static(obj, "Volume");
        }
    }
}

void tick_user_widget_oscillator(int startWidgetIndex) {
    (void)startWidgetIndex;
    {
        const char *new_val = get_var_dco_number();
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 0]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 0];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 0], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_dco_1_waveform();
        bool cur_val = lv_obj_has_flag(((lv_obj_t **)&objects)[startWidgetIndex + 1], LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 1];
            if (new_val) {
                lv_obj_add_flag(((lv_obj_t **)&objects)[startWidgetIndex + 1], LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_remove_flag(((lv_obj_t **)&objects)[startWidgetIndex + 1], LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_dco_1_waveform();
        bool cur_val = lv_obj_has_flag(((lv_obj_t **)&objects)[startWidgetIndex + 2], LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 2];
            if (new_val) {
                lv_obj_add_flag(((lv_obj_t **)&objects)[startWidgetIndex + 2], LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_remove_flag(((lv_obj_t **)&objects)[startWidgetIndex + 2], LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_dco_1_waveform();
        bool cur_val = lv_obj_has_flag(((lv_obj_t **)&objects)[startWidgetIndex + 3], LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 3];
            if (new_val) {
                lv_obj_add_flag(((lv_obj_t **)&objects)[startWidgetIndex + 3], LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_remove_flag(((lv_obj_t **)&objects)[startWidgetIndex + 3], LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_dco_1_waveform();
        bool cur_val = lv_obj_has_flag(((lv_obj_t **)&objects)[startWidgetIndex + 4], LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 4];
            if (new_val) {
                lv_obj_add_flag(((lv_obj_t **)&objects)[startWidgetIndex + 4], LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_remove_flag(((lv_obj_t **)&objects)[startWidgetIndex + 4], LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_dco_1_detune();
        int32_t cur_val = lv_bar_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 5]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 5];
            lv_bar_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 5], new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_dco_1_volume();
        int32_t cur_val = lv_bar_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 6]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 6];
            lv_bar_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 6], new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
}

void create_user_widget_adsr(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 11, 10);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_header_label_style(obj);
            lv_label_set_text_static(obj, "Envelope");
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 13, 43);
            lv_obj_set_size(obj, 14, 59);
            lv_bar_set_range(obj, 0, 127);
            add_style_bar_style(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 15, 102);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_default_label_style(obj);
            lv_label_set_text_static(obj, "A");
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
            lv_obj_set_pos(obj, 128, 44);
            lv_obj_set_size(obj, 14, 59);
            lv_bar_set_range(obj, 0, 127);
            add_style_bar_style(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 130, 103);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_default_label_style(obj);
            lv_label_set_text_static(obj, "R");
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
            lv_obj_set_pos(obj, 52, 44);
            lv_obj_set_size(obj, 14, 59);
            lv_bar_set_range(obj, 0, 127);
            add_style_bar_style(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 54, 103);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_default_label_style(obj);
            lv_label_set_text_static(obj, "D");
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
            lv_obj_set_pos(obj, 93, 44);
            lv_obj_set_size(obj, 14, 59);
            lv_bar_set_range(obj, 0, 127);
            add_style_bar_style(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 95, 103);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_default_label_style(obj);
            lv_label_set_text_static(obj, "S");
        }
    }
}

void tick_user_widget_adsr(int startWidgetIndex) {
    (void)startWidgetIndex;
    {
        int32_t new_val = get_var_envelop_attack();
        int32_t cur_val = lv_bar_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 0]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 0];
            lv_bar_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 0], new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_envelope_release();
        int32_t cur_val = lv_bar_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 1]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 1];
            lv_bar_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 1], new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_envelope_decay();
        int32_t cur_val = lv_bar_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 2]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 2];
            lv_bar_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 2], new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_envelope_sustain();
        int32_t cur_val = lv_bar_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 3]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 3];
            lv_bar_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 3], new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_bootup,
    tick_screen_dashboard,
    tick_screen_patches,
    tick_screen_visualization,
    tick_screen_settings,
    tick_screen_gif_visualization,
    tick_screen_fft_visualization,
    tick_screen_patch_edit,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 8) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
    { "RubikGlitch_20", &ui_font_rubik_glitch_20 },
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
// Groups
//

groups_t groups;
static bool groups_created = false;
void ui_create_groups() {
    if (!groups_created) {
        groups.MainGroup = lv_group_create();
        groups_created = true;
    }
}

//
//
//

void create_screens() {
    
    // Initialize groups
    ui_create_groups();
    
    // Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_bootup();
    create_screen_dashboard();
    create_screen_patches();
    create_screen_visualization();
    create_screen_settings();
    create_screen_gif_visualization();
    create_screen_fft_visualization();
    create_screen_patch_edit();
}