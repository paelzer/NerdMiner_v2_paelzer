#include "displayDriver.h"

#ifdef ESP32_64x32px_Matrix
#include "version.h"
#include "monitor.h"
#include <Adafruit_GFX.h>
#include <PxMatrix.h>
#include "media/images_64_32.h"

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

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

bool hasChangedScreen = true;

void drawImage(int x, int y, const unsigned short matrix_image[])
{
  // #include "media/images_64_32.h"
  int imageHeight = 32;
  int imageWidth = 64;
  int counter = 0;
  for (int yy = 0; yy < imageHeight; yy++)
  {
    for (int xx = 0; xx < imageWidth; xx++)
    {
      display.drawPixel(xx + x, yy + y, matrix_image[counter]);
      counter++;
    }
  }
}

void IRAM_ATTR display_updater()
{
  // Increment the counter and set the time of ISR
  portENTER_CRITICAL_ISR(&timerMux);
  display.display(display_draw_time);
  portEXIT_CRITICAL_ISR(&timerMux);
}

void display_update_enable(bool is_enable)
{

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
}

void esp32_64x32px_Matrix_Init(void)
{
  Serial.println("SSD1306 ... display init");

  display.begin(16);
  display.clearDisplay();
  display.setTextColor(myCYAN);
  display.setCursor(2, 0);
  display.println("NerdMiner");
  display.setTextColor(myMAGENTA);
  display.println("V2");
  display_update_enable(true);
  delay(2000);
  display.clearDisplay();
  Serial.println("Display cleared...");
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

  // Print background screen
  // display.clearDisplay(); // paint it black :-)

  Serial.printf(">>> Completed %s share(s), %s Khashes, avg. hashrate %s KH/s\n",
                data.completedShares.c_str(), data.totalKHashes.c_str(), data.currentHashRate.c_str());

  // Hashrate
  display.setTextSize(1);
  drawImage(0, 0, miner_bg);
  display.setCursor(1, 24);
  display.setTextColor(myBLACK);
  display.print(data.currentHashRate);

  // Valid Blocks
  display.setCursor(54, 10);
  display.setTextColor(myRED);
  display.print(data.valids);

  // Mining Time
  // char timeMining[15];
  // unsigned long secElapsed = millis() / 1000;
  // int days = secElapsed / 86400;
  // int hours = (secElapsed - (days * 86400)) / 3600;               // Number of seconds in an hour
  // int mins = (secElapsed - (days * 86400) - (hours * 3600)) / 60; // Remove the number of hours and calculate the minutes.
  // int secs = secElapsed - (days * 86400) - (hours * 3600) - (mins * 60);
  // sprintf(timeMining, "%01d %02d:%02d:%02d", days, hours, mins, secs);
  // display.setTextColor(myWHITE);
  // display.setCursor(2, 22);
  // display.print(String(timeMining));
}

// uint16_t osx=64, osy=64, omx=64, omy=64, ohx=64, ohy=64;  // Saved H, M, S x & y coords
void esp32_64x32px_Matrix_ClockScreen(unsigned long mElapsed)
{
  clock_data_t data = getClockData_t(mElapsed);

  char clocktimeNow[8];
  // uint8_t secs = data.currentSeconds;
  uint8_t mins = data.currentMinutes;
  uint8_t hours = data.currentHours;

  sprintf(clocktimeNow, "%02d:%02d", hours, mins);

  if (hasChangedScreen)
    display.clearDisplay(); // paint it black :-)
  drawImage(0, 0, clock_bg);
  hasChangedScreen = false;

  // drawImage(0, 0, clock_bg);

  // display.setTextSize(2);              // Normal 1:1 pixel scale
  display.setTextColor(myRED);
  display.setCursor(32, 2);

  display.println(clocktimeNow);

  display.setCursor(1, 24);
  display.setTextColor(myBLACK);
  display.print(data.currentHashRate);
}

void esp32_64x32px_Matrix_BTCprice(unsigned long mElapsed)
{
  clock_data data = getClockData(mElapsed);

  // Print background screen
  // display.clearDisplay(); // paint it black :-)

  Serial.printf(">>> Completed %s share(s), %s Khashes, avg. hashrate %s KH/s\n",
                data.completedShares.c_str(), data.totalKHashes.c_str(), data.currentHashRate.c_str());

  // Hashrate
  // display.setTextSize(1);
  drawImage(0, 0, price_bg);
  display.setCursor(1, 24);
  display.setTextColor(myBLACK);
  display.print(data.currentHashRate);

  display.setTextColor(myRED);
  display.setCursor(24, 8); // Start at top-left corner
  display.println(data.btcPrice);
}

void esp32_64x32px_Matrix_uptime(unsigned long mElapsed)
{
  mining_data data = getMiningData(mElapsed);

  drawImage(0, 0, miner_uptime);
  display.setCursor(1, 8);
  display.setTextColor(myRED);
  display.print(data.timeMining);

  display.setCursor(1, 24);
  display.setTextColor(myBLACK);
  display.print(data.currentHashRate);
}

void esp32_64x32px_Matrix_GlobalHashScreen(unsigned long mElapsed)
{
}

void esp32_64x32px_Matrix_LoadingScreen(void)
{
}

void esp32_64x32px_Matrix_SetupScreen(void)
{
}

void esp32_64x32px_Matrix_AnimateCurrentScreen(unsigned long frame)
{
}

void esp32_64x32px_Matrix_DoLedStuff(unsigned long frame)
{
}

CyclicScreenFunction esp32_64x32px_MatrixCyclicScreens[] = {esp32_64x32px_Matrix_MinerScreen, esp32_64x32px_Matrix_uptime, esp32_64x32px_Matrix_BTCprice, esp32_64x32px_Matrix_ClockScreen};
// CyclicScreenFunction esp32_64x32px_MatrixCyclicScreens[] = {esp32_64x32px_Matrix_ClockScreen, esp32_64x32px_Matrix_MinerScreen};

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
