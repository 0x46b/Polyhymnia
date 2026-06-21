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

//
// Screens
//

void create_screen_bootup() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.bootup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
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
            create_user_widget_oscillator(obj, 12);
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
            create_user_widget_oscillator(obj, 18);
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
            create_user_widget_oscillator(obj, 24);
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
            create_user_widget_adsr(obj, 30);
        }
    }
    
    tick_screen_dashboard();
}

void tick_screen_dashboard() {
    tick_user_widget_oscillator(12);
    tick_user_widget_oscillator(18);
    tick_user_widget_oscillator(24);
    tick_user_widget_adsr(30);
}

void create_screen_main_menu() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main_menu = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Menu
            lv_obj_t *obj = lv_menu_create(parent_obj);
            objects.menu = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, -470, 50);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_default_label_style(obj);
                    lv_label_set_text_static(obj, "Settings");
                }
            }
        }
    }
    
    tick_screen_main_menu();
}

void tick_screen_main_menu() {
}

void create_screen_patches() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.patches = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
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
            lv_obj_set_pos(obj, 10, 51);
            lv_obj_set_size(obj, 297, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "FFT\nWaveform\nGIF");
            lv_dropdown_set_selected(obj, 0);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 112, 154);
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
    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            lv_obj_set_pos(obj, 9, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text_static(obj, "Show Bootscreen");
            lv_obj_add_state(obj, LV_STATE_CHECKED);
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
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            lv_obj_set_pos(obj, 157, 82);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "Distorted\nNormal");
            lv_dropdown_set_selected(obj, 0);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 9, 146);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_default_label_style(obj);
            lv_label_set_text_static(obj, "MIDI Channel:");
        }
        {
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            lv_obj_set_pos(obj, 157, 136);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16");
            lv_dropdown_set_selected(obj, 0);
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
}

void create_screen_gif_visualization() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gif_visualization = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    
    tick_screen_gif_visualization();
}

void tick_screen_gif_visualization() {
}

void create_screen_fft_visualization() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.fft_visualization = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
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
            lv_label_set_text_static(obj, "1");
        }
        {
            // waveform_sine
            lv_obj_t *obj = lv_line_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(80));
            static lv_point_precise_t line_points[] = {
                { 0, 35 },
                { 8, 24 },
                { 17, 14 },
                { 25, 6 },
                { 34, 1 },
                { 42, 0 },
                { 51, 3 },
                { 59, 9 },
                { 67, 18 },
                { 76, 29 },
                { 84, 41 },
                { 93, 52 },
                { 101, 61 },
                { 109, 67 },
                { 118, 70 },
                { 126, 69 },
                { 135, 64 },
                { 143, 56 },
                { 152, 46 },
                { 160, 35 }
            };
            lv_line_set_points(obj, line_points, 20);
            add_style_waveform_line_style(obj);
        }
        {
            // waveform_saw
            lv_obj_t *obj = lv_line_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(80));
            static lv_point_precise_t line_points[] = {
                { 0, 35 },
                { 8, 32 },
                { 17, 28 },
                { 25, 24 },
                { 34, 21 },
                { 42, 18 },
                { 51, 14 },
                { 59, 10 },
                { 67, 7 },
                { 76, 4 },
                { 84, 70 },
                { 93, 66 },
                { 101, 63 },
                { 109, 60 },
                { 118, 56 },
                { 126, 52 },
                { 135, 49 },
                { 143, 46 },
                { 152, 42 },
                { 160, 35 }
            };
            lv_line_set_points(obj, line_points, 20);
            add_style_waveform_line_style(obj);
        }
        {
            // waveform_triangle
            lv_obj_t *obj = lv_line_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(80));
            static lv_point_precise_t line_points[] = {
                { 0, 35 },
                { 8, 28 },
                { 17, 20 },
                { 25, 13 },
                { 34, 6 },
                { 42, 2 },
                { 51, 9 },
                { 59, 17 },
                { 67, 24 },
                { 76, 31 },
                { 84, 39 },
                { 93, 46 },
                { 101, 53 },
                { 109, 61 },
                { 118, 68 },
                { 126, 64 },
                { 135, 57 },
                { 143, 50 },
                { 152, 42 },
                { 160, 35 }
            };
            lv_line_set_points(obj, line_points, 20);
            add_style_waveform_line_style(obj);
        }
        {
            // waveform_square
            lv_obj_t *obj = lv_line_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(80));
            static lv_point_precise_t line_points[] = {
                { 0, 35 },
                { 8, 0 },
                { 17, 0 },
                { 25, 0 },
                { 34, 0 },
                { 42, 0 },
                { 51, 0 },
                { 59, 0 },
                { 67, 0 },
                { 76, 0 },
                { 84, 70 },
                { 93, 70 },
                { 101, 70 },
                { 109, 70 },
                { 118, 70 },
                { 126, 70 },
                { 135, 70 },
                { 143, 70 },
                { 152, 70 },
                { 160, 35 }
            };
            lv_line_set_points(obj, line_points, 20);
            add_style_waveform_line_style(obj);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            lv_obj_set_pos(obj, 69, 68);
            lv_obj_set_size(obj, 86, 10);
            lv_bar_set_range(obj, -600, 600);
            lv_bar_set_mode(obj, LV_BAR_MODE_SYMMETRICAL);
            lv_bar_set_value(obj, 100, LV_ANIM_OFF);
            add_style_bar_style(obj);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            lv_obj_set_pos(obj, 69, 94);
            lv_obj_set_size(obj, 87, 10);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
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
            lv_obj_set_pos(obj, 128, 44);
            lv_obj_set_size(obj, 14, 59);
            lv_bar_set_range(obj, 0, 127);
            lv_bar_set_value(obj, 30, LV_ANIM_ON);
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
            lv_obj_set_pos(obj, 52, 44);
            lv_obj_set_size(obj, 14, 59);
            lv_bar_set_range(obj, 0, 127);
            lv_bar_set_value(obj, 25, LV_ANIM_ON);
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
            lv_obj_set_pos(obj, 93, 44);
            lv_obj_set_size(obj, 14, 59);
            lv_bar_set_range(obj, 0, 127);
            lv_bar_set_value(obj, 110, LV_ANIM_ON);
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
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_bootup,
    tick_screen_dashboard,
    tick_screen_main_menu,
    tick_screen_patches,
    tick_screen_visualization,
    tick_screen_settings,
    tick_screen_gif_visualization,
    tick_screen_fft_visualization,
    tick_screen_patch_edit,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 9) {
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
//
//

void create_screens() {

// Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_bootup();
    create_screen_dashboard();
    create_screen_main_menu();
    create_screen_patches();
    create_screen_visualization();
    create_screen_settings();
    create_screen_gif_visualization();
    create_screen_fft_visualization();
    create_screen_patch_edit();
}