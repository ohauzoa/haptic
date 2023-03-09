// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: gui

#ifndef _GUI_UI_H
#define _GUI_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_Screen1_Arc_Temps;
extern lv_obj_t * ui_Screen1_Arc_Body;
extern lv_obj_t * ui_Temp_Bg;
extern lv_obj_t * ui_Temp_Num_Bg;
extern lv_obj_t * ui_Label_Temp_1;
extern lv_obj_t * ui_Label_Skin;
extern lv_obj_t * ui_Label_Temp_2;
extern lv_obj_t * ui_Label_Air;
extern lv_obj_t * ui_Screen2;
extern lv_obj_t * ui_Chart2;
extern lv_obj_t * ui_Screen3;
extern lv_obj_t * ui_Screen4;

extern lv_chart_series_t * ui_Chart2_series_1;
extern lv_chart_series_t * ui_Chart2_series_2;



LV_FONT_DECLARE(ui_font_Digital3);
LV_FONT_DECLARE(ui_font_Digital7);
LV_FONT_DECLARE(ui_font_ScoreBoard);
LV_FONT_DECLARE(ui_font_Small_Font);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
