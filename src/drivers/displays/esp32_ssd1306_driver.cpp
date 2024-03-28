#include "displayDriver.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifdef ESP32_SSD1306

#define WIDTH 128
#define HEIGHT 64

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);

#include "version.h"
#include "monitor.h"

/*
OpenFontRender render;
TFT_eSPI tft = TFT_eSPI();                  // Invoke library, pins defined in User_Setup.h
TFT_eSprite background = TFT_eSprite(&tft); // Invoke library sprite
*/

void t_qtDisplay_Init(void)
{
  Serial.println("SSD1306 ... display init");
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner

  display.println("Nerd");
  display.println("MinerV2");

  display.display();

  //tft.init();
  //tft.setRotation(1);
  //tft.setSwapBytes(true);                 // Swap the colour byte order when rendering
  //background.createSprite(WIDTH, HEIGHT); // Background Sprite
  //background.setSwapBytes(true);
  //render.setDrawer(background);  // Link drawing object to background instance (so font will be rendered on background)
  //render.setLineSpaceRatio(0.9); // Espaciado entre texto

  // Load the font and check it can be read OK
  // if (render.loadFont(NotoSans_Bold, sizeof(NotoSans_Bold))) {
  //if (render.loadFont(DigitalNumbers, sizeof(DigitalNumbers)))
  //{
  //  Serial.println("Initialise error");
  //  return;
  //}
}

void t_qtDisplay_AlternateScreenState(void)
{
  //int screen_state = digitalRead(TFT_BL);
  Serial.println("Nothing to do.... ");
  //digitalWrite(TFT_BL, !screen_state);
}

void t_qtDisplay_AlternateRotation(void)
{
  Serial.println("SSD1306 ... no rotation");
  //tft.setRotation((tft.getRotation()+1) % 4);
}

void t_qtDisplay_MinerScreen(unsigned long mElapsed)
{
  mining_data data = getMiningData(mElapsed);


  // Print background screen
  display.clearDisplay(); // paint it black :-)


  Serial.printf(">>> Completed %s share(s), %s Khashes, avg. hashrate %s KH/s\n",
                data.completedShares.c_str(), data.totalKHashes.c_str(), data.currentHashRate.c_str());

    //Hashrate
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0, 0);
    //render.setFontColor(TFT_BLACK);  

    display.print(data.currentHashRate.c_str());
    display.println(F(" kH/s"));
    display.setTextSize(1);
    display.println();

    //Valid Blocks
    display.setTextSize(2);
    display.print(data.valids.c_str());
    //display.setTextSize(1);
    display.println(F(" Blocks"));

    //Mining Time
    char timeMining[15]; 
    unsigned long secElapsed = millis() / 1000;
    int days = secElapsed / 86400; 
    int hours = (secElapsed - (days * 86400)) / 3600;                                                        //Number of seconds in an hour
    int mins = (secElapsed - (days * 86400) - (hours * 3600)) / 60;                                              //Remove the number of hours and calculate the minutes.
    int secs = secElapsed - (days * 86400) - (hours * 3600) - (mins * 60);   
    sprintf(timeMining, "%01d d %02d:%02d:%02d h", days, hours, mins, secs);
    display.setTextSize(1);
    display.println();
    display.println(String(timeMining).c_str());        
    display.display();
}

uint16_t osx=64, osy=64, omx=64, omy=64, ohx=64, ohy=64;  // Saved H, M, S x & y coords
void t_qtDisplay_ClockScreen(unsigned long mElapsed)
{
    clock_data_t data = getClockData_t(mElapsed);

    // Print background screen
    //background.pushImage(0, 0, minerClockWidth, minerClockHeight, minerClockScreen);

    // Serial.printf(">>> Completed %s share(s), %s Khashes, avg. hashrate %s KH/s\n",
    //             data.completedShares.c_str(), data.totalKHashes.c_str(), data.currentHashRate.c_str());

    //render.setCursor(0, 0);

    //Hashrate
    //render.setFontSize(18);
    //render.setFontColor(TFT_BLACK);    
    //render.cdrawString(data.currentHashRate.c_str(), 75, 74, TFT_DARKGREY);

    //Valid Blocks
    //render.setFontSize(15);
    //render.rdrawString(data.valids.c_str(), 96, 54, TFT_BLACK);

    if (data.currentHours > 12)
        data.currentHours -= 12;
    float sdeg = data.currentSeconds*6;                  // 0-59 -> 0-354
    float mdeg = data.currentMinutes*6+sdeg*0.01666667;  // 0-59 -> 0-360 - includes seconds
    float hdeg = data.currentHours*30+mdeg*0.0833333;  // 0-11 -> 0-360 - includes minutes and seconds

    float hx = cos((hdeg-90)*0.0174532925);    
    float hy = sin((hdeg-90)*0.0174532925);
    float mx = cos((mdeg-90)*0.0174532925);    
    float my = sin((mdeg-90)*0.0174532925);
    float sx = cos((sdeg-90)*0.0174532925);    
    float sy = sin((sdeg-90)*0.0174532925);    

    ohx = hx*33+60;    
    ohy = hy*33+60;
    omx = mx*44+60;    
    omy = my*44+60;    
    // Redraw new hand positions, hour and minute hands not erased here to avoid flicker
    //background.drawLine(ohx, ohy, 65, 65, TFT_BLACK);
    //background.drawLine(omx, omy, 65, 65, TFT_BLACK);
    osx = sx*47+60;    
    osy = sy*47+60;
    //background.drawLine(osx, osy, 65, 65, TFT_RED);   

    //background.fillCircle(65, 65, 3, TFT_RED);

    //Push prepared background to screen
    //background.pushSprite(0,0);      
}

void t_qtDisplay_GlobalHashScreen(unsigned long mElapsed)
{
  Serial.println("SSD1306 ... no global hash screen");
}

void t_qtDisplay_LoadingScreen(void)
{
  
  Serial.println("SSD1306 ... no loading screen");
  //tft.fillScreen(TFT_BLACK);
  //tft.pushImage(0, 0, initWidth, initHeight, initScreen);
  //tft.setTextColor(TFT_GOLD);
  //tft.drawString(CURRENT_VERSION, 2, 100, FONT2); 
}

void t_qtDisplay_SetupScreen(void)
{
  
  Serial.println("SSD1306 ... no setup screen");
  //tft.pushImage(0, 0, setupModeWidth, setupModeHeight, setupModeScreen);
}

void t_qtDisplay_AnimateCurrentScreen(unsigned long frame)
{
}

void t_qtDisplay_DoLedStuff(unsigned long frame)
{
}

CyclicScreenFunction t_qtDisplayCyclicScreens[] = {t_qtDisplay_MinerScreen, t_qtDisplay_ClockScreen};

DisplayDriver esp32_ssd1306_driver = {
    t_qtDisplay_Init,
    t_qtDisplay_AlternateScreenState,
    t_qtDisplay_AlternateRotation,
    t_qtDisplay_LoadingScreen,
    t_qtDisplay_SetupScreen,
    t_qtDisplayCyclicScreens,
    t_qtDisplay_AnimateCurrentScreen,
    t_qtDisplay_DoLedStuff,
    SCREENS_ARRAY_SIZE(t_qtDisplayCyclicScreens),
    0,
    WIDTH,
    HEIGHT};
#endif
