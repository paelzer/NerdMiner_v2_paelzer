# NerdSoloMiner on an RGB LED Matrix Panel

**The NerdSoloMiner v2**

This is a fork of the **free and open source project** called **The NerdSoloMiner V2** that let you try to reach a bitcoin block with a small piece of hardware.

The main aim of this project is to let you **learn more about minery** and to have a beautiful piece of hardware in your desktop.

Original project https://github.com/valerio-vaccaro/HAN

## Requirements

- 64x32 dot matrix - I bought a "P4" version, which means a distance of 4mm between two RGB LED's
- ESP32 S3 DevKit Microcontroller
- 5 Volt power supply (mine is a 5A and works fine)
- USB cable to connect the ESP32 to the computer to flash the firmware
- Cable to wire up everything

### Project description

**For details to the NerdMinerV2 software implementation, please visit the original project page**
This repo only provides additional information to get the NerdMinerV2 on a 64x32 RGB matrix panel and the features 

This variant of the project is currently only working with ESP32-S3, but will also be adapted to work with common ESP32 chips.

These views are available:

- NerdMiner Screen > Mining speed of Nerdminer
- ClockMiner Screen > Clock miner
- Current Bitcoin value


#### Boards currently supported

- ESP32-S3 Devkit ([Board Info](https://docs.platformio.org/en/latest/boards/espressif


### Flash firmware

Flashing is currently only possible via PlatformIO.

## NerdMiner configuration

After flashing, you just need to setup your Wifi credentials and BTC address.

Note: when BTC address of your selected wallet is not provided, mining will not be started.

#### Wifi Accesspoint

1. Connect your WiFi device to:
   - Accesspoint: **NerdMinerAP**
   - Password: **MineYourCoins**
1. Set up your Wifi Network
1. Add your BTC address
1. Change the password if needed

   - If you are using public-pool.io and you want to set a custom name to your worker you can append a string with format _.yourworkername_ to the address


#### Pool selection

Visit the original NerdMinerV2 project page about details to mining pool selection. 


### Button (if connected)

- One click > change screen.
- Hold 5 seconds > **reset the configurations and reboot** your NerdMiner.

Have fun!
