// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: gui

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Screen1_Arc_Temps;
lv_obj_t * ui_Screen1_Arc_Body;
lv_obj_t * ui_Temp_Bg;
lv_obj_t * ui_Temp_Num_Bg;
lv_obj_t * ui_Label_Temp_1;
lv_obj_t * ui_Label_Skin;
lv_obj_t * ui_Label_Temp_2;
lv_obj_t * ui_Label_Air;
lv_obj_t * ui_Screen2;
lv_obj_t * ui_Chart2;
lv_obj_t * ui_Screen3;
lv_obj_t * ui_Screen4;

lv_chart_series_t * ui_Chart2_series_1;
lv_chart_series_t * ui_Chart2_series_2;
///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen1_Arc_Temps = lv_arc_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Arc_Temps, 240);
    lv_obj_set_height(ui_Screen1_Arc_Temps, 240);
    lv_obj_set_align(ui_Screen1_Arc_Temps, LV_ALIGN_CENTER);
    lv_arc_set_range(ui_Screen1_Arc_Temps, -1, 50);
    lv_arc_set_value(ui_Screen1_Arc_Temps, 30);
    lv_arc_set_bg_angles(ui_Screen1_Arc_Temps, 120, 360);
    lv_obj_set_style_radius(ui_Screen1_Arc_Temps, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Arc_Temps, lv_color_hex(0x1E1E2D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Arc_Temps, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen1_Arc_Temps, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen1_Arc_Temps, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen1_Arc_Temps, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen1_Arc_Temps, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_Screen1_Arc_Temps, lv_color_hex(0x0F1419), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Screen1_Arc_Temps, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_Screen1_Arc_Temps, 12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_Screen1_Arc_Temps, lv_color_hex(0xC8F00A), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Screen1_Arc_Temps, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_Screen1_Arc_Temps, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Screen1_Arc_Temps, lv_color_hex(0xFF6464), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Arc_Temps, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Screen1_Arc_Body = lv_arc_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Arc_Body, 200);
    lv_obj_set_height(ui_Screen1_Arc_Body, 200);
    lv_obj_set_align(ui_Screen1_Arc_Body, LV_ALIGN_CENTER);
    lv_arc_set_range(ui_Screen1_Arc_Body, -1, 50);
    lv_arc_set_value(ui_Screen1_Arc_Body, 20);
    lv_arc_set_bg_angles(ui_Screen1_Arc_Body, 120, 360);
    lv_obj_set_style_radius(ui_Screen1_Arc_Body, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Arc_Body, lv_color_hex(0x1E1E2D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Arc_Body, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen1_Arc_Body, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen1_Arc_Body, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen1_Arc_Body, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen1_Arc_Body, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_Screen1_Arc_Body, lv_color_hex(0x0F1419), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Screen1_Arc_Body, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_Screen1_Arc_Body, 12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_Screen1_Arc_Body, lv_color_hex(0xF0B40A), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Screen1_Arc_Body, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_Screen1_Arc_Body, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Screen1_Arc_Body, lv_color_hex(0xFF6464), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Arc_Body, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Temp_Bg = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Temp_Bg, 162);
    lv_obj_set_height(ui_Temp_Bg, 162);
    lv_obj_set_align(ui_Temp_Bg, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Temp_Bg, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Temp_Bg, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Temp_Bg, lv_color_hex(0xC8C8FA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Temp_Bg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Temp_Bg, lv_color_hex(0x323241), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Temp_Bg, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Temp_Bg, lv_color_hex(0x050A0F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Temp_Bg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Temp_Bg, lv_color_hex(0x050A0F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Temp_Bg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Temp_Bg, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Temp_Bg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Temp_Bg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Temp_Bg, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Temp_Num_Bg = lv_obj_create(ui_Temp_Bg);
    lv_obj_set_width(ui_Temp_Num_Bg, 125);
    lv_obj_set_height(ui_Temp_Num_Bg, 125);
    lv_obj_set_align(ui_Temp_Num_Bg, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Temp_Num_Bg, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Temp_Num_Bg, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Temp_Num_Bg, lv_color_hex(0x0C0F1E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Temp_Num_Bg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Temp_Num_Bg, lv_color_hex(0x191E28), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Temp_Num_Bg, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Temp_Num_Bg, lv_color_hex(0x5A646E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Temp_Num_Bg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label_Temp_1 = lv_label_create(ui_Temp_Num_Bg);
    lv_obj_set_width(ui_Label_Temp_1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label_Temp_1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label_Temp_1, -38);
    lv_obj_set_y(ui_Label_Temp_1, -8);
    lv_obj_set_align(ui_Label_Temp_1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label_Temp_1, "Skin");
    lv_obj_set_style_text_color(ui_Label_Temp_1, lv_color_hex(0x7878BE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label_Temp_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label_Temp_1, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label_Skin = lv_label_create(ui_Temp_Num_Bg);
    lv_obj_set_width(ui_Label_Skin, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label_Skin, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label_Skin, 14);
    lv_obj_set_y(ui_Label_Skin, -16);
    lv_obj_set_align(ui_Label_Skin, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label_Skin, "34.5");
    lv_obj_set_style_text_color(ui_Label_Skin, lv_color_hex(0xC8F00A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label_Skin, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label_Skin, &ui_font_Digital3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label_Temp_2 = lv_label_create(ui_Temp_Num_Bg);
    lv_obj_set_width(ui_Label_Temp_2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label_Temp_2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label_Temp_2, -39);
    lv_obj_set_y(ui_Label_Temp_2, 12);
    lv_obj_set_align(ui_Label_Temp_2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label_Temp_2, "Air");
    lv_obj_set_style_text_color(ui_Label_Temp_2, lv_color_hex(0x7878BE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label_Temp_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label_Temp_2, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label_Air = lv_label_create(ui_Temp_Num_Bg);
    lv_obj_set_width(ui_Label_Air, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label_Air, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label_Air, 14);
    lv_obj_set_y(ui_Label_Air, 20);
    lv_obj_set_align(ui_Label_Air, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label_Air, "22.7");
    lv_obj_set_style_text_color(ui_Label_Air, lv_color_hex(0xF0B40A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label_Air, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label_Air, &ui_font_Digital3, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Chart2 = lv_chart_create(ui_Screen2);
    lv_obj_set_width(ui_Chart2, 150);
    lv_obj_set_height(ui_Chart2, 150);
    lv_obj_set_x(ui_Chart2, 10);
    lv_obj_set_y(ui_Chart2, 0);
    lv_obj_set_align(ui_Chart2, LV_ALIGN_CENTER);
    lv_chart_set_type(ui_Chart2, LV_CHART_TYPE_LINE);
    lv_chart_set_range(ui_Chart2, LV_CHART_AXIS_PRIMARY_Y, 10, 50);
    lv_chart_set_range(ui_Chart2, LV_CHART_AXIS_SECONDARY_Y, 0, 0);
    lv_chart_set_div_line_count(ui_Chart2, 10, 10);
    lv_chart_set_axis_tick(ui_Chart2, LV_CHART_AXIS_PRIMARY_X, 0, 0, 0, 0, false, 0);
    lv_chart_set_axis_tick(ui_Chart2, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
    ui_Chart2_series_1 = lv_chart_add_series(ui_Chart2, lv_color_hex(0xC8F00A),
                                                                 LV_CHART_AXIS_PRIMARY_Y);
    static lv_coord_t ui_Chart2_series_1_array[] = { 0, 10, 20, 40, 45, 48, 40, 20, 10, 0 };
    lv_chart_set_ext_y_array(ui_Chart2, ui_Chart2_series_1, ui_Chart2_series_1_array);
    ui_Chart2_series_2 = lv_chart_add_series(ui_Chart2, lv_color_hex(0xF0B40A),
                                                                 LV_CHART_AXIS_PRIMARY_Y);
    static lv_coord_t ui_Chart2_series_2_array[] = { 10, 15, 18, 20, 23, 18, 16, 20, 15, 13 };
    lv_chart_set_ext_y_array(ui_Chart2, ui_Chart2_series_2, ui_Chart2_series_2_array);
    lv_obj_set_style_bg_color(ui_Chart2, lv_color_hex(0x0C0F1E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Chart2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Screen3_screen_init(void)
{
    ui_Screen3 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

}
void ui_Screen4_screen_init(void)
{
    ui_Screen4 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    ui_Screen3_screen_init();
    ui_Screen4_screen_init();
    lv_disp_load_scr(ui_Screen1);
}
