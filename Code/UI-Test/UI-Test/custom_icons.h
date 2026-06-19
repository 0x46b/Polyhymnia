/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Opts: --bpp 1 --size 8 --no-compress --stride 1 --align 1 --font fa-solid-900.woff --range 63360,63166,57649,63176,62752,58611,63202,63198,63494,63315,63100,62206,62796 --format lvgl -o custom_icons.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef CUSTOM_ICONS
#define CUSTOM_ICONS 1
#endif

#if CUSTOM_ICONS

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST PROGMEM const uint8_t glyph_bitmap[] = {
    /* U+E131 "" */
    0xf7, 0xff, 0xff, 0xff, 0xff,

    /* U+E4F3 "" */
    0xff, 0xbd, 0x4f, 0x53, 0xd4, 0xf5, 0x3b, 0xe6,
    0xf8, 0x3e,

    /* U+F2FE "" */
    0x8, 0xc, 0x3c, 0x3c, 0x7e, 0x7e, 0xe7, 0xff,

    /* U+F520 "" */
    0x3, 0x80, 0xb0, 0x78, 0x3e, 0x1f, 0x1f, 0x8c,
    0xa0, 0x18,

    /* U+F54C "" */
    0x3c, 0x7e, 0xff, 0xcb, 0xcb, 0x7e, 0x3c, 0x2c,

    /* U+F67C "" */
    0x3e, 0x35, 0xb2, 0x71, 0x19, 0xcf, 0x5d, 0xac,
    0x7c,

    /* U+F6BE "" */
    0x7, 0x87, 0x47, 0x78, 0x7e, 0x7a, 0x7a,

    /* U+F6C8 "" */
    0x7f, 0x30, 0xce, 0x7f, 0xff, 0x7f, 0xd9, 0xb0,

    /* U+F6DE "" */
    0x22, 0xeb, 0xf9, 0x9f, 0xf7, 0x9e,

    /* U+F6E2 "" */
    0x7b, 0xff, 0xff, 0xff, 0xff, 0xd4,

    /* U+F753 "" */
    0x0, 0x1f, 0x3e, 0x7e, 0xa6, 0xa6, 0x94, 0x4c,
    0x38,

    /* U+F780 "" */
    0x14, 0x11, 0xa, 0x8f, 0xcf, 0x75, 0xf4, 0x20,
    0xee,

    /* U+F806 "" */
    0x10, 0x20, 0x41, 0xcb, 0xff, 0xff, 0x3e
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 160, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 15, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 23, .adv_w = 160, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 33, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 41, .adv_w = 128, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 50, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 57, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 71, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 77, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 86, .adv_w = 144, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 95, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x3c2, 0x11cd, 0x13ef, 0x141b, 0x154b, 0x158d, 0x1597,
    0x15ad, 0x15b1, 0x1622, 0x164f, 0x16d5
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 57649, .range_length = 5846, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 13, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t custom_icons = {
#else
lv_font_t custom_icons = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 9,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    //.static_bitmap = 0,
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};

#endif /*#if CUSTOM_ICONS*/
