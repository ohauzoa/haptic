#include <Arduino.h>
#include <Wire.h> //Include arduino Wire Library to enable to I2C
#include <SPI.h> //Include arduino Wire Library to enable to I2C

#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

#define I2C_SDA 4
#define I2C_SCL 5
#define I2C_CLK 100000



/*******************************************************************************
 * LVGL Benchmark
 * This is a benchmark demo for LVGL - Light and Versatile Graphics Library
 * import from: https://github.com/lvgl/lv_demos.git
 *
 * Dependent libraries:
 * LVGL: https://github.com/lvgl/lvgl.git
 *
 * LVGL Configuration file:
 * Copy your_arduino_path/libraries/lvgl/lv_conf_template.h
 * to your_arduino_path/libraries/lv_conf.h
 * Then find and set:
 * #define LV_COLOR_DEPTH     16
 * #define LV_TICK_CUSTOM     1
 *
 * For SPI display set color swap can be faster, parallel screen don't set!
 * #define LV_COLOR_16_SWAP   1
 *
 * Optional: Show CPU usage and FPS count
 * #define LV_USE_PERF_MONITOR 1
 ******************************************************************************/
#include <lvgl.h>
////////////////////////////////////////////////
#include "ui.h"
#define SCR_LOAD_ANIM_TIME 300 // ms
#define CHART_SERIAL_VALUE_COUNT 60

#define LEFT_BTN_PIN 6
#define RIGHT_BTN_PIN 7

#define GET_VALUE_INTERVAL 60000 // 1 minute

static int32_t  temp, humidity, pressure, gas;  // BME readings
static char     buf[16];                        // sprintf text buffer
static float    alt;                            // Temporary variable
static uint16_t loopCounter = 0;                // Display iterations

static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_color_t *disp_draw_buf2;
static lv_disp_drv_t disp_drv;
static lv_chart_series_t * ser_temps;
static lv_chart_series_t * ser_humid;
static lv_chart_series_t * ser_air_q;
static long last_value_ms = -GET_VALUE_INTERVAL;
static long last_point_ms = -GET_VALUE_INTERVAL;
static uint8_t current_screen = 1;
static long last_pressed = -GET_VALUE_INTERVAL;
static long chart_value_interval = GET_VALUE_INTERVAL; // initial interval is same as GET_VALUE_INTERVAL, double after each serials cycle

/////////////////////////////////////////////////
#include <Arduino_GFX_Library.h>

#define TFT_BLK 12
#define TFT_RES 9

#define TFT_CS 10
#define TFT_MOSI 13
#define TFT_MISO 12 // n/a
#define TFT_SCLK 14
#define TFT_DC 11

#define GFX_BL TFT_BLK

Arduino_ESP32SPI *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED, HSPI, true); // Constructor

Arduino_GFX *gfx = new Arduino_GC9A01(bus, TFT_RES, 0 /* rotation */, true /* IPS */);

/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

/* Change to your screen resolution */
//static uint32_t screenWidth;
//static uint32_t screenHeight;
//static lv_disp_draw_buf_t draw_buf;
//static lv_color_t *disp_draw_buf;
//static lv_disp_drv_t disp_drv;
static unsigned long last_ms;

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
   uint32_t w = (area->x2 - area->x1 + 1);
   uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
   gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
   gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

   lv_disp_flush_ready(disp);
}

void left_btn_pressed() {
  if ((millis() - last_pressed) >= SCR_LOAD_ANIM_TIME) {
    switch(current_screen) {
      case 1:
        lv_scr_load_anim(ui_Screen4, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SCR_LOAD_ANIM_TIME, 0, false);
        current_screen = 4;
        break;
      case 2:
        lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SCR_LOAD_ANIM_TIME, 0, false);
        current_screen = 1;
        break;
      case 3:
        lv_scr_load_anim(ui_Screen2, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SCR_LOAD_ANIM_TIME, 0, false);
        current_screen = 2;
        break;
      default:
        lv_scr_load_anim(ui_Screen3, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SCR_LOAD_ANIM_TIME, 0, false);
        current_screen = 3;
        break;
    }

    last_pressed = millis();
  }
}

void right_btn_pressed() {
  if ((millis() - last_pressed) >= SCR_LOAD_ANIM_TIME) {
    switch(current_screen) {
      case 1:
        lv_scr_load_anim(ui_Screen2, LV_SCR_LOAD_ANIM_MOVE_LEFT, SCR_LOAD_ANIM_TIME, 0, false);
        current_screen = 2;
        break;
      case 2:
        lv_scr_load_anim(ui_Screen3, LV_SCR_LOAD_ANIM_MOVE_LEFT, SCR_LOAD_ANIM_TIME, 0, false);
        current_screen = 3;
        break;
      case 3:
        lv_scr_load_anim(ui_Screen4, LV_SCR_LOAD_ANIM_MOVE_LEFT, SCR_LOAD_ANIM_TIME, 0, false);
        current_screen = 4;
        break;
      default:
        lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_LEFT, SCR_LOAD_ANIM_TIME, 0, false);
        current_screen = 1;
        break;
    }

    last_pressed = millis();
  }
}


/*
 * ERM_Basic : Arduino IDE LRA example for TI DRV2605
 * 
 * Overview:
 * --------- 
 * This simple example for the ERM actuator types runs through 
 * all the effects in sequence.
 * 
 * Requirements:
 * -------------
 * PatternAgents DRV2605 library : https://github.com/PatternAgents/Haptic_DRV2605
 * 
 * Instructions:
 * -------------
 * 1) compile and Upload the sketch
 * 2) open the Serial Monitor
 *       
 * 
 * DRV2605 :  Immersion Libs Patented Waveform Libraries (under License with DRV2605)
 *
 * 	Library #   = Type / Nom Volts / Max Volts / Rise Time (mS) / Brake Time (mS)
 * 	Library   0 = Empty
 * 	Library A/1 = ERM  /  1.3V / 3.0V /  40 -  60 / 20 - 40
 * 	Library B/2 = ERM  /  3.0V / 3.0V /  40 -  60 / 5  - 15
 * 	Library C/3 = ERM  /  3.0V / 3.0V /  60 -  80 / 10 - 25
 * 	Library D/4 = ERM  /  3.0V / 3.0V / 100 - 140 / 15 - 25
 * 	Library E/5 = ERM  /  3.0V / 3.0V / 140 -     / 30 -
 * 	Library   6 = LRA  /       /      /           /
 * 	Library F/7 = ERM  /  4.5V / 5.0V /  35 -  45 / 10 - 20
 * 
 * ****************************************************************************** 
 */
void Task_TFT(void *pvParameters);

void Task_LRA(void *pvParameters);


void setup() {
//    Wire.setPins(4,5);
    Wire.begin(I2C_SDA, I2C_SCL);
    Serial.begin(115200);
    Serial.println("DRV2605 Audio responsive test");
    Serial.println("Adafruit DRV2605 Basic test");
    if (! drv.begin()) {
        Serial.println("Could not find DRV2605");
        while (1) delay(10);
    }
 
    drv.selectLibrary(6);
    drv.useLRA();
    // I2C trigger by sending 'go' command 
    // default, internal trigger when sending GO command
    drv.setMode(DRV2605_MODE_INTTRIG); 



//////////////////////////////////////////////////////////////
    // Init Display
    gfx->begin();
    gfx->fillScreen(BLACK);

#ifdef GFX_BL
    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);
#endif

    lv_init();

    screenWidth = gfx->width();
    screenHeight = gfx->height();
#ifdef ESP32
    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 30, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
#else
    disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * screenWidth * 10);
#endif
    if (!disp_draw_buf)
    {
        Serial.println("LVGL disp_draw_buf allocate failed!");
    }
    else
    {
        lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 30);

        /* Initialize the display */
        lv_disp_drv_init(&disp_drv);
        /* Change the following line to your display resolution */
        disp_drv.hor_res = screenWidth;
        disp_drv.ver_res = screenHeight;
        disp_drv.flush_cb = my_disp_flush;
        disp_drv.draw_buf = &draw_buf;
        lv_disp_drv_register(&disp_drv);

        /* Initialize the (dummy) input device driver */
        static lv_indev_drv_t indev_drv;
        lv_indev_drv_init(&indev_drv);
        indev_drv.type = LV_INDEV_TYPE_POINTER;
        lv_indev_drv_register(&indev_drv);

        /* Init SquareLine prepared UI */
        ui_init();

        /* Init Charts */
        lv_chart_set_type(ui_Screen2_Chart1, LV_CHART_TYPE_LINE);
        lv_chart_set_type(ui_Screen3_Chart1, LV_CHART_TYPE_LINE);
        lv_chart_set_type(ui_Screen4_Chart1, LV_CHART_TYPE_LINE);

        lv_chart_set_range(ui_Screen2_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 50);
        lv_chart_set_range(ui_Screen3_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
        lv_chart_set_range(ui_Screen4_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 100);

        lv_chart_set_axis_tick(ui_Screen2_Chart1, LV_CHART_AXIS_PRIMARY_Y, 5, 5, 6, 1, true, 24);
        lv_chart_set_axis_tick(ui_Screen3_Chart1, LV_CHART_AXIS_PRIMARY_Y, 5, 2, 6, 2, true, 28);
        lv_chart_set_axis_tick(ui_Screen4_Chart1, LV_CHART_AXIS_PRIMARY_Y, 5, 2, 6, 2, true, 28);

        lv_chart_set_point_count(ui_Screen2_Chart1, CHART_SERIAL_VALUE_COUNT);
        lv_chart_set_point_count(ui_Screen3_Chart1, CHART_SERIAL_VALUE_COUNT);
        lv_chart_set_point_count(ui_Screen4_Chart1, CHART_SERIAL_VALUE_COUNT);

        lv_chart_set_update_mode(ui_Screen2_Chart1, LV_CHART_UPDATE_MODE_SHIFT);
        lv_chart_set_update_mode(ui_Screen3_Chart1, LV_CHART_UPDATE_MODE_SHIFT);
        lv_chart_set_update_mode(ui_Screen4_Chart1, LV_CHART_UPDATE_MODE_SHIFT);

        lv_obj_set_style_size(ui_Screen2_Chart1, 0, LV_PART_INDICATOR);
        lv_obj_set_style_size(ui_Screen3_Chart1, 0, LV_PART_INDICATOR);
        lv_obj_set_style_size(ui_Screen4_Chart1, 0, LV_PART_INDICATOR);

        /* Init data series */
        ser_temps = lv_chart_add_series(ui_Screen2_Chart1, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
        ser_humid = lv_chart_add_series(ui_Screen3_Chart1, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
        ser_air_q = lv_chart_add_series(ui_Screen4_Chart1, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);

        lv_chart_set_all_value(ui_Screen2_Chart1, ser_temps, 0);
        lv_chart_set_all_value(ui_Screen3_Chart1, ser_humid, 0);
        lv_chart_set_all_value(ui_Screen4_Chart1, ser_air_q, 0);

        Serial.println("Setup done");
    }
    last_ms = millis();

    /* Init buttons */
    pinMode(LEFT_BTN_PIN, INPUT_PULLUP);
    attachInterrupt(LEFT_BTN_PIN, left_btn_pressed, FALLING);
    pinMode(RIGHT_BTN_PIN, INPUT_PULLUP);
    attachInterrupt(RIGHT_BTN_PIN, right_btn_pressed, FALLING);

    xTaskCreatePinnedToCore(Task_TFT, "Task_TFT", 20480, NULL, 10, NULL, 0);
    xTaskCreatePinnedToCore(Task_LRA, "Task_touch", 10240, NULL, 12, NULL, 1);

}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    if ((millis() - last_value_ms) < GET_VALUE_INTERVAL){
        delay(5);
    }else{
        last_value_ms = millis();
    }
   
}

void Send_Temp(void)
{
    Serial1.write(17);
    Serial1.write(3);
    Serial1.write(1);
    Serial1.write(152);
}

void Task_TFT(void *pvParameters)
{
    char temp_buf[10];
    int dest_temp, body_temp, temp_cnt;
    long value_ms = -GET_VALUE_INTERVAL;
    long point_ms = -GET_VALUE_INTERVAL;
    Serial1.begin(19200,SERIAL_8N1, 18, 17);

    delay(200);
    Send_Temp();
    delay(200);
    Send_Temp();
    while (1){
        //시리얼 1번에 데이터가 들어오면
        if(Serial1.available()){
            temp_buf[temp_cnt] = Serial1.read();
            if(temp_buf[temp_cnt] == 0x9c){
                Serial.println("receive ok");
                dest_temp = 0;
                dest_temp += temp_buf[2] << 8;
                dest_temp += temp_buf[3] << 0;
                body_temp = 0;
                body_temp += temp_buf[4] << 8;
                body_temp += temp_buf[5] << 0;
    //          Serial.print(dest_temp);
    //          Serial.print(',');
    //          Serial.print(body_temp);
    //          Serial.println("---");

                sprintf(buf, "%2d",(int8_t)(dest_temp / 100));   // Temp in decidegrees
                lv_arc_set_value(ui_Screen1_Arc_Temps, dest_temp / 100);
                lv_label_set_text(ui_Screen1_Label_Temps, buf);

                sprintf(buf, "%2d", (int8_t)(body_temp / 100));  // Humidity milli-pct
                lv_arc_set_value(ui_Screen1_Arc_Humid, body_temp / 100);
                lv_label_set_text(ui_Screen1_Label_Humid, buf);

                sprintf(buf, "%2d.%02d\nhPa", (int16_t)(dest_temp / 100), (uint8_t)(dest_temp % 100));  // Pressure Pascals
                lv_label_set_text(ui_Screen1_Label_Pressu, buf);

                lv_chart_set_next_value(ui_Screen2_Chart1, ser_temps, dest_temp / 100);
                lv_chart_set_next_value(ui_Screen3_Chart1, ser_humid, body_temp / 100);
                lv_chart_set_next_value(ui_Screen4_Chart1, ser_air_q, gas / 10000);

                temp_cnt = 0;
                Send_Temp();          
            }
            else{
                temp_cnt++;
            }
        }
        delay(10); 
    }
}


void Task_LRA(void *pvParameters)
{
    uint8_t effect = 1;

    while (1){
    //  Serial.print("Effect #"); Serial.println(effect);

        if (effect == 1) {
            Serial.println("11.2 Waveform Library Effects List");
        }

        if (effect == 1) {
            Serial.println(F("1 − Strong Click - 100%"));
        }
        if (effect == 2) {
            Serial.println(F("2 − Strong Click - 60%"));
        }
        if (effect == 3) {
            Serial.println(F("3 − Strong Click - 30%"));
        }
        if (effect == 4) {
            Serial.println(F("4 − Sharp Click - 100%"));
        }
        if (effect == 5) {
            Serial.println(F("5 − Sharp Click - 60%"));
        }
        if (effect == 6) {
            Serial.println(F("6 − Sharp Click - 30%"));
        }
        if (effect == 7) {
            Serial.println(F("7 − Soft Bump - 100%"));
        }
        if (effect == 8) {
            Serial.println(F("8 − Soft Bump - 60%"));
        }
        if (effect == 9) {
            Serial.println(F("9 − Soft Bump - 30%"));
        }
        if (effect == 10) {
            Serial.println(F("10 − Double Click - 100%"));
        }
        if (effect == 11) {
            Serial.println(F("11 − Double Click - 60%"));
        }
        if (effect == 12) {
            Serial.println(F("12 − Triple Click - 100%"));
        }
        if (effect == 13) {
            Serial.println(F("13 − Soft Fuzz - 60%"));
        }
        if (effect == 14) {
            Serial.println(F("14 − Strong Buzz - 100%"));
        }
        if (effect == 15) {
            Serial.println(F("15 − 750 ms Alert 100%"));
        }
        if (effect == 16) {
            Serial.println(F("16 − 1000 ms Alert 100%"));
        }
        if (effect == 17) {
            Serial.println(F("17 − Strong Click 1 - 100%"));
        }
        if (effect == 18) {
            Serial.println(F("18 − Strong Click 2 - 80%"));
        }
        if (effect == 19) {
            Serial.println(F("19 − Strong Click 3 - 60%"));
        }
        if (effect == 20) {
            Serial.println(F("20 − Strong Click 4 - 30%"));
        }
        if (effect == 21) {
            Serial.println(F("21 − Medium Click 1 - 100%"));
        }
        if (effect == 22) {
            Serial.println(F("22 − Medium Click 2 - 80%"));
        }
        if (effect == 23) {
            Serial.println(F("23 − Medium Click 3 - 60%"));
        }
        if (effect == 24) {
            Serial.println(F("24 − Sharp Tick 1 - 100%"));
        }
        if (effect == 25) {
            Serial.println(F("25 − Sharp Tick 2 - 80%"));
        }
        if (effect == 26) {
            Serial.println(F("26 − Sharp Tick 3 – 60%"));
        }
        if (effect == 27) {
            Serial.println(F("27 − Short Double Click Strong 1 – 100%"));
        }
        if (effect == 28) {
            Serial.println(F("28 − Short Double Click Strong 2 – 80%"));
        }
        if (effect == 29) {
            Serial.println(F("29 − Short Double Click Strong 3 – 60%"));
        }
        if (effect == 30) {
            Serial.println(F("30 − Short Double Click Strong 4 – 30%"));
        }
        if (effect == 31) {
            Serial.println(F("31 − Short Double Click Medium 1 – 100%"));
        }
        if (effect == 32) {
            Serial.println(F("32 − Short Double Click Medium 2 – 80%"));
        }
        if (effect == 33) {
            Serial.println(F("33 − Short Double Click Medium 3 – 60%"));
        }
        if (effect == 34) {
            Serial.println(F("34 − Short Double Sharp Tick 1 – 100%"));
        }
        if (effect == 35) {
            Serial.println(F("35 − Short Double Sharp Tick 2 – 80%"));
        }
        if (effect == 36) {
            Serial.println(F("36 − Short Double Sharp Tick 3 – 60%"));
        }
        if (effect == 37) {
            Serial.println(F("37 − Long Double Sharp Click Strong 1 – 100%"));
        }
        if (effect == 38) {
            Serial.println(F("38 − Long Double Sharp Click Strong 2 – 80%"));
        }
        if (effect == 39) {
            Serial.println(F("39 − Long Double Sharp Click Strong 3 – 60%"));
        }
        if (effect == 40) {
            Serial.println(F("40 − Long Double Sharp Click Strong 4 – 30%"));
        }
        if (effect == 41) {
            Serial.println(F("41 − Long Double Sharp Click Medium 1 – 100%"));
        }
        if (effect == 42) {
            Serial.println(F("42 − Long Double Sharp Click Medium 2 – 80%"));
        }
        if (effect == 43) {
            Serial.println(F("43 − Long Double Sharp Click Medium 3 – 60%"));
        }
        if (effect == 44) {
            Serial.println(F("44 − Long Double Sharp Tick 1 – 100%"));
        }
        if (effect == 45) {
            Serial.println(F("45 − Long Double Sharp Tick 2 – 80%"));
        }
        if (effect == 46) {
            Serial.println(F("46 − Long Double Sharp Tick 3 – 60%"));
        }
        if (effect == 47) {
            Serial.println(F("47 − Buzz 1 – 100%"));
        }
        if (effect == 48) {
            Serial.println(F("48 − Buzz 2 – 80%"));
        }
        if (effect == 49) {
            Serial.println(F("49 − Buzz 3 – 60%"));
        }
        if (effect == 50) {
            Serial.println(F("50 − Buzz 4 – 40%"));
        }
        if (effect == 51) {
            Serial.println(F("51 − Buzz 5 – 20%"));
        }
        if (effect == 52) {
            Serial.println(F("52 − Pulsing Strong 1 – 100%"));
        }
        if (effect == 53) {
            Serial.println(F("53 − Pulsing Strong 2 – 60%"));
        }
        if (effect == 54) {
            Serial.println(F("54 − Pulsing Medium 1 – 100%"));
        }
        if (effect == 55) {
            Serial.println(F("55 − Pulsing Medium 2 – 60%"));
        }
        if (effect == 56) {
            Serial.println(F("56 − Pulsing Sharp 1 – 100%"));
        }
        if (effect == 57) {
            Serial.println(F("57 − Pulsing Sharp 2 – 60%"));
        }
        if (effect == 58) {
            Serial.println(F("58 − Transition Click 1 – 100%"));
        }
        if (effect == 59) {
            Serial.println(F("59 − Transition Click 2 – 80%"));
        }
        if (effect == 60) {
            Serial.println(F("60 − Transition Click 3 – 60%"));
        }
        if (effect == 61) {
            Serial.println(F("61 − Transition Click 4 – 40%"));
        }
        if (effect == 62) {
            Serial.println(F("62 − Transition Click 5 – 20%"));
        }
        if (effect == 63) {
            Serial.println(F("63 − Transition Click 6 – 10%"));
        }
        if (effect == 64) {
            Serial.println(F("64 − Transition Hum 1 – 100%"));
        }
        if (effect == 65) {
            Serial.println(F("65 − Transition Hum 2 – 80%"));
        }
        if (effect == 66) {
            Serial.println(F("66 − Transition Hum 3 – 60%"));
        }
        if (effect == 67) {
            Serial.println(F("67 − Transition Hum 4 – 40%"));
        }
        if (effect == 68) {
            Serial.println(F("68 − Transition Hum 5 – 20%"));
        }
        if (effect == 69) {
            Serial.println(F("69 − Transition Hum 6 – 10%"));
        }
        if (effect == 70) {
            Serial.println(F("70 − Transition Ramp Down Long Smooth 1 – 100 to 0%"));
        }
        if (effect == 71) {
            Serial.println(F("71 − Transition Ramp Down Long Smooth 2 – 100 to 0%"));
        }
        if (effect == 72) {
            Serial.println(F("72 − Transition Ramp Down Medium Smooth 1 – 100 to 0%"));
        }
        if (effect == 73) {
            Serial.println(F("73 − Transition Ramp Down Medium Smooth 2 – 100 to 0%"));
        }
        if (effect == 74) {
            Serial.println(F("74 − Transition Ramp Down Short Smooth 1 – 100 to 0%"));
        }
        if (effect == 75) {
            Serial.println(F("75 − Transition Ramp Down Short Smooth 2 – 100 to 0%"));
        }
        if (effect == 76) {
            Serial.println(F("76 − Transition Ramp Down Long Sharp 1 – 100 to 0%"));
        }
        if (effect == 77) {
            Serial.println(F("77 − Transition Ramp Down Long Sharp 2 – 100 to 0%"));
        }
        if (effect == 78) {
            Serial.println(F("78 − Transition Ramp Down Medium Sharp 1 – 100 to 0%"));
        }
        if (effect == 79) {
            Serial.println(F("79 − Transition Ramp Down Medium Sharp 2 – 100 to 0%"));
        }
        if (effect == 80) {
            Serial.println(F("80 − Transition Ramp Down Short Sharp 1 – 100 to 0%"));
        }
        if (effect == 81) {
            Serial.println(F("81 − Transition Ramp Down Short Sharp 2 – 100 to 0%"));
        }
        if (effect == 82) {
            Serial.println(F("82 − Transition Ramp Up Long Smooth 1 – 0 to 100%"));
        }
        if (effect == 83) {
            Serial.println(F("83 − Transition Ramp Up Long Smooth 2 – 0 to 100%"));
        }
        if (effect == 84) {
            Serial.println(F("84 − Transition Ramp Up Medium Smooth 1 – 0 to 100%"));
        }
        if (effect == 85) {
            Serial.println(F("85 − Transition Ramp Up Medium Smooth 2 – 0 to 100%"));
        }
        if (effect == 86) {
            Serial.println(F("86 − Transition Ramp Up Short Smooth 1 – 0 to 100%"));
        }
        if (effect == 87) {
            Serial.println(F("87 − Transition Ramp Up Short Smooth 2 – 0 to 100%"));
        }
        if (effect == 88) {
            Serial.println(F("88 − Transition Ramp Up Long Sharp 1 – 0 to 100%"));
        }
        if (effect == 89) {
            Serial.println(F("89 − Transition Ramp Up Long Sharp 2 – 0 to 100%"));
        }
        if (effect == 90) {
        Serial.println(F("90 − Transition Ramp Up Medium Sharp 1 – 0 to 100%"));
        }
        if (effect == 91) {
            Serial.println(F("91 − Transition Ramp Up Medium Sharp 2 – 0 to 100%"));
        }
        if (effect == 92) {
            Serial.println(F("92 − Transition Ramp Up Short Sharp 1 – 0 to 100%"));
        }
        if (effect == 93) {
            Serial.println(F("93 − Transition Ramp Up Short Sharp 2 – 0 to 100%"));
        }
        if (effect == 94) {
            Serial.println(F("94 − Transition Ramp Down Long Smooth 1 – 50 to 0%"));
        }
        if (effect == 95) {
            Serial.println(F("95 − Transition Ramp Down Long Smooth 2 – 50 to 0%"));
        }
        if (effect == 96) {
            Serial.println(F("96 − Transition Ramp Down Medium Smooth 1 – 50 to 0%"));
        }
        if (effect == 97) {
            Serial.println(F("97 − Transition Ramp Down Medium Smooth 2 – 50 to 0%"));
        }
        if (effect == 98) {
            Serial.println(F("98 − Transition Ramp Down Short Smooth 1 – 50 to 0%"));
        }
        if (effect == 99) {
            Serial.println(F("99 − Transition Ramp Down Short Smooth 2 – 50 to 0%"));
        }
        if (effect == 100) {
            Serial.println(F("100 − Transition Ramp Down Long Sharp 1 – 50 to 0%"));
        }
        if (effect == 101) {
            Serial.println(F("101 − Transition Ramp Down Long Sharp 2 – 50 to 0%"));
        }
        if (effect == 102) {
            Serial.println(F("102 − Transition Ramp Down Medium Sharp 1 – 50 to 0%"));
        }
        if (effect == 103) {
            Serial.println(F("103 − Transition Ramp Down Medium Sharp 2 – 50 to 0%"));
        }
        if (effect == 104) {
            Serial.println(F("104 − Transition Ramp Down Short Sharp 1 – 50 to 0%"));
        }
        if (effect == 105) {
            Serial.println(F("105 − Transition Ramp Down Short Sharp 2 – 50 to 0%"));
        }
        if (effect == 106) {
            Serial.println(F("106 − Transition Ramp Up Long Smooth 1 – 0 to 50%"));
        }
        if (effect == 107) {
            Serial.println(F("107 − Transition Ramp Up Long Smooth 2 – 0 to 50%"));
        }
        if (effect == 108) {
            Serial.println(F("108 − Transition Ramp Up Medium Smooth 1 – 0 to 50%"));
        }
        if (effect == 109) {
            Serial.println(F("109 − Transition Ramp Up Medium Smooth 2 – 0 to 50%"));
        }
        if (effect == 110) {
            Serial.println(F("110 − Transition Ramp Up Short Smooth 1 – 0 to 50%"));
        }
        if (effect == 111) {
            Serial.println(F("111 − Transition Ramp Up Short Smooth 2 – 0 to 50%"));
        }
        if (effect == 112) {
            Serial.println(F("112 − Transition Ramp Up Long Sharp 1 – 0 to 50%"));
        }
        if (effect == 113) {
            Serial.println(F("113 − Transition Ramp Up Long Sharp 2 – 0 to 50%"));
        }
        if (effect == 114) {
            Serial.println(F("114 − Transition Ramp Up Medium Sharp 1 – 0 to 50%"));
        }
        if (effect == 115) {
            Serial.println(F("115 − Transition Ramp Up Medium Sharp 2 – 0 to 50%"));
        }
        if (effect == 116) {
            Serial.println(F("116 − Transition Ramp Up Short Sharp 1 – 0 to 50%"));
        }
        if (effect == 117) {
            Serial.println(F("117 − Transition Ramp Up Short Sharp 2 – 0 to 50%"));
        }
        if (effect == 118) {
            Serial.println(F("118 − Long buzz for programmatic stopping – 100%"));
        }
        if (effect == 119) {
            Serial.println(F("119 − Smooth Hum 1 (No kick or brake pulse) – 50%"));
        }
        if (effect == 120) {
            Serial.println(F("120 − Smooth Hum 2 (No kick or brake pulse) – 40%"));
        }
        if (effect == 121) {
            Serial.println(F("121 − Smooth Hum 3 (No kick or brake pulse) – 30%"));
        }
        if (effect == 122) {
            Serial.println(F("122 − Smooth Hum 4 (No kick or brake pulse) – 20%"));
        }
        if (effect == 123) {
            Serial.println(F("123 − Smooth Hum 5 (No kick or brake pulse) – 10%"));
        }

        // set the effect to play
        drv.setWaveform(0, effect);  // play effect 
        drv.setWaveform(1, 0);       // end waveform

        // play the effect!
        drv.go();

        // wait a bit
        delay(500);

        effect++;

        if (effect > 117) effect = 1;
        
    }

}

