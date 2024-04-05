#include "displayDriver.h"

#ifdef ESP32_64x32px_Matrix
#include "version.h"
#include "monitor.h"
#include <Adafruit_GFX.h>
#include <PxMatrix.h>

#define P_LAT 22
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_E 15
#define P_OE 0
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

//#define matrix_width 64
//#define matrix_height 32
#define WIDTH 64
#define HEIGHT 32

PxMATRIX display(64, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D, P_E);

uint8_t display_draw_time = 60; // 30-70 is usually fine

// Some standard colors
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);

uint16_t myCOLORS[8] = {myRED, myGREEN, myBLUE, myWHITE, myYELLOW, myCYAN, myMAGENTA, myBLACK};

void IRAM_ATTR display_updater()
{
  // Increment the counter and set the time of ISR
  portENTER_CRITICAL_ISR(&timerMux);
  display.display(display_draw_time);
  portEXIT_CRITICAL_ISR(&timerMux);
}

void display_update_enable(bool is_enable)
{

#ifdef ESP32
  if (is_enable)
  {
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &display_updater, true);
    timerAlarmWrite(timer, 4000, true);
    timerAlarmEnable(timer);
  }
  else
  {
    timerDetachInterrupt(timer);
    timerAlarmDisable(timer);
  }
#endif
}

void esp32_64x32px_Matrix_Init(void)
{
  Serial.println("SSD1306 ... display init");



}

void esp32_64x32px_Matrix_AlternateScreenState(void)
{
  // tbd
}

void esp32_64x32px_Matrix_AlternateRotation(void)
{
  display.setRotation((display.getRotation() + 2) % 4);
}

void esp32_64x32px_Matrix_MinerScreen(unsigned long mElapsed)
{
  mining_data data = getMiningData(mElapsed);
/*
  // Print background screen
  display.clearDisplay(); // paint it black :-)

  Serial.printf(">>> Completed %s share(s), %s Khashes, avg. hashrate %s KH/s\n",
                data.completedShares.c_str(), data.totalKHashes.c_str(), data.currentHashRate.c_str());

  // Hashrate
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);
  // render.setFontColor(TFT_BLACK);

  display.print(data.currentHashRate.c_str());
  display.println(F(" kH/s"));
  display.setTextSize(1);
  display.println();

  // Valid Blocks
  display.setTextSize(2);
  display.print(data.valids.c_str());
  // display.setTextSize(1);
  display.println(F(" Blocks"));

  // Mining Time
  char timeMining[15];
  unsigned long secElapsed = millis() / 1000;
  int days = secElapsed / 86400;
  int hours = (secElapsed - (days * 86400)) / 3600;               // Number of seconds in an hour
  int mins = (secElapsed - (days * 86400) - (hours * 3600)) / 60; // Remove the number of hours and calculate the minutes.
  int secs = secElapsed - (days * 86400) - (hours * 3600) - (mins * 60);
  sprintf(timeMining, "%01d d %02d:%02d:%02d h", days, hours, mins, secs);
  display.setTextSize(1);
  display.println();
  display.println(String(timeMining).c_str());
  display.display();
*/
}

// uint16_t osx=64, osy=64, omx=64, omy=64, ohx=64, ohy=64;  // Saved H, M, S x & y coords
void esp32_64x32px_Matrix_ClockScreen(unsigned long mElapsed)
{
  clock_data_t data = getClockData_t(mElapsed);
/*
  char clocktimeNow[8];
  uint8_t secs = data.currentSeconds;
  uint8_t mins = data.currentMinutes;
  uint8_t hours = data.currentHours;

  sprintf(clocktimeNow, "%02d:%02d:%02d", hours, mins, secs);

  display.clearDisplay();

  display.setTextSize(2);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);             // Start at top-left corner

  display.println(F(String(clocktimeNow).c_str()));

  display.display();
*/
}

void esp32_64x32px_Matrix_GlobalHashScreen(unsigned long mElapsed)
{
  Serial.println("SSD1306 ... no global hash screen");
}

void esp32_64x32px_Matrix_LoadingScreen(void)
{

  Serial.println("SSD1306 ... no loading screen");
  // tft.fillScreen(TFT_BLACK);
  // tft.pushImage(0, 0, initWidth, initHeight, initScreen);
  // tft.setTextColor(TFT_GOLD);
  // tft.drawString(CURRENT_VERSION, 2, 100, FONT2);
}

void esp32_64x32px_Matrix_SetupScreen(void)
{

  Serial.println("SSD1306 ... no setup screen");
  // tft.pushImage(0, 0, setupModeWidth, setupModeHeight, setupModeScreen);
}

void esp32_64x32px_Matrix_AnimateCurrentScreen(unsigned long frame)
{
}

void esp32_64x32px_Matrix_DoLedStuff(unsigned long frame)
{
}

CyclicScreenFunction esp32_64x32px_MatrixCyclicScreens[] = {esp32_64x32px_Matrix_MinerScreen, esp32_64x32px_Matrix_ClockScreen};

DisplayDriver esp32_64x32px_matrix_driver = {
    esp32_64x32px_Matrix_Init,
    esp32_64x32px_Matrix_AlternateScreenState,
    esp32_64x32px_Matrix_AlternateRotation,
    esp32_64x32px_Matrix_LoadingScreen,
    esp32_64x32px_Matrix_SetupScreen,
    esp32_64x32px_MatrixCyclicScreens,
    esp32_64x32px_Matrix_AnimateCurrentScreen,
    esp32_64x32px_Matrix_DoLedStuff,
    SCREENS_ARRAY_SIZE(esp32_64x32px_MatrixCyclicScreens),
    0,
    WIDTH,
    HEIGHT};
#endif
