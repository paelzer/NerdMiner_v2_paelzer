#ifndef __DEVICE_H__
#define __DEVICE_H__

#if defined(ESP32_64x32px_Matrix)
#include "esp32_64x32px_matrix.h"


#else
#error "No device defined"
#endif

#endif // __DEVICE_H__
