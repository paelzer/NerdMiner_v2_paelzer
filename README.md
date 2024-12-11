# NerdSoloMiner on an RGB LED Matrix Panel

**The NerdSoloMiner v2**

This is a fork of the **free and open source project** called **The NerdSoloMiner V2** that let you try to reach a bitcoin block with a small piece of hardware.

The main aim of this project is to let you **learn more about minery** and to have a beautiful piece of hardware in your desktop.

Original project https://github.com/valerio-vaccaro/HAN

## Requirements

- 64x32 dot matrix 
##### I bought a "P4" version, which means a distance of 4mm between two RGB LED's
- ESP32 S3 DevKit Microcontroller
- 5 Volt power supply (mine is a 5A and works fine)
- USB cable to connect the ESP32 to the computer to flash the firmware
- Cable to wire up everything

### Project description

**ESP32 implementing Stratum protocol** to mine on solo pool. Pool can be changed but originally works with [public-pool.io](https://web.public-pool.io) (where Nerdminers are supported).

This variant of the project is currently only working with ESP32-S3, but will also be adapted to work with common ESP32 chips. It uses WifiManager to modify miner settings and save them to SPIFF memory.
Several screens are available:

- NerdMiner Screen > Mining speed of Nerdminer
- ClockMiner Screen > Clock miner
- Current Bitcoin value

This miner is multicore and multithreads, both cores are used to mine and several threads are used to implementing stratum work and wifi stuff.
Every time an stratum job notification is received miner update its current work to not create stale shares.

**IMPORTANT** Miner is not seen by all standard pools due to its low share difficulty. You can check miner work remotely using specific pools specified down or seeing logs via UART.


#### Boards currently supported

- ESP32-S3 Devkit ([Board Info](https://docs.platformio.org/en/latest/boards/espressif

\*Affiliate links

### Flash firmware

Flashing is currently only possible via PlatformIO

## NerdMiner configuration

After flashing, you will only need to setup your Wifi and BTC address.

Note: when BTC address of your selected wallet is not provided, mining will not be started.

#### Wifi Accesspoint

1. Connect to NerdMinerAP
   - AP: NerdMinerAP
   - PASS: MineYourCoins
1. Set up your Wifi Network
1. Add your BTC address
1. Change the password if needed

   - If you are using public-pool.io and you want to set a custom name to your worker you can append a string with format _.yourworkername_ to the address


#### Pool selection

Recommended low difficulty share pools:

| Pool URL          | Port  | Web URL                    | Status                                                             |
| ----------------- | ----- | -------------------------- | ------------------------------------------------------------------ |
| public-pool.io    | 21496 | https://web.public-pool.io | Open Source Solo Bitcoin Mining Pool supporting open source miners |
| nerdminers.org    |       | https://nerdminers.org     | Team domain for future pool - Currently pointing to public-pool.io |
| pool.nerdminer.io | 3333  | https://nerdminer.io       | Mantained by CHMEX                                                 |
| pool.vkbit.com    | 3333  | https://vkbit.com/         | Mantained by djerfy - public-pool fork                             |
| pool.pyblock.xyz  | 3333  | https://pool.pyblock.xyz/  | Mantained by curly60e                                              |
| pool.sethforprivacy.com  | 3333  | https://pool.sethforprivacy.com/  | Mantained by @sethforprivacy - public-pool fork      |

Other standard pools not compatible with low difficulty share:

| Pool URL                 | Port | Web URL                                   |
| ------------------------ | ---- | ----------------------------------------- |
| solo.ckpool.org          | 3333 | https://solo.ckpool.org/                  |
| btc.zsolo.bid            | 6057 | https://zsolo.bid/en/btc-solo-mining-pool |
| eu.stratum.slushpool.com | 3333 | https://braiins.com/pool                  |

### Button (if connected)

- One click > change screen.
- Double click > change screen orientation.
- Tripple click > turn the screen off and on again.
- Hold 5 seconds > **reset the configurations and reboot** your NerdMiner.

Enjoy
