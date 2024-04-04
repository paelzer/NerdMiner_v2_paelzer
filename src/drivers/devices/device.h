#ifndef __DEVICE_H__
#define __DEVICE_H__

#if defined(NERDMINERV2)
#include "nerdMinerV2.h"
#elif defined(M5STICK_C)
#include "M5Stick-C.h"
#elif defined(DEVKITV1)
#include "esp32DevKit.h"
#elif defined(TDISPLAY)
#include "lilygoS3TDisplay.h"
#elif defined(NERMINER_S3_AMOLED)
#include "lilygoS3Amoled.h"
#elif defined(NERMINER_S3_DONGLE)
#include "lilygoS3Dongle.h"
#elif defined(LILYGO_S3_T_EMBED)
#include "lilygoS3TEmbed.h"
#elif defined(ESP32_2432S028R)
#include "esp322432s028r.h"
#elif defined(ESP32_2432S028_2USB) // For another type of ESP32_2432S028 version with 2 USB connectors
#include "esp322432s028r.h"
#elif defined(NERMINER_T_QT)
#include "lilygoT_QT.h"
#elif defined(NERDMINER_T_DISPLAY_V1)
#include "lilygoV1TDisplay.h"
#elif defined(ESP32_CAM)
#include "esp32CAM.h"
#elif defined(ESP32RGB)
#include "esp32RGB.h"
#elif defined(ESP32_ST7735)
#include "esp32_st7735.h"
#elif defined(ESP32_SSD1306)
#include "esp32_ssd1306.h"
#elif defined(ESP32_super_mini_SSD1306)
#include "esp32_super_mini_SSD1306.h"


#else
#error "No device defined"
#endif

#endif // __DEVICE_H__
