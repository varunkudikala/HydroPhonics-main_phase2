/****************************************************************************************************************************
  defines.h
  For ESP32 boards to run GSM/GPRS and WiFi simultaneously, using config portal feature
  
  Library to enable GSM/GPRS and WiFi running simultaneously , with WiFi config portal.
  Based on and modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/BlynkGSM_Manager
  Licensed under MIT license
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h
#include "GPIOConfig.h"
#ifndef ESP32
  #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_PRINT         Serial
#define BLYNK_HEARTBEAT     60

#define DOUBLERESETDETECTOR_DEBUG     true  //false
#define BLYNK_WM_DEBUG                1

// Not use #define USE_LITTLEFS and #define USE_SPIFFS  => using SPIFFS for configuration data in WiFiManager
// (USE_LITTLEFS == false) and (USE_SPIFFS == false)    => using EEPROM for configuration data in WiFiManager
// (USE_LITTLEFS == true) and (USE_SPIFFS == false)     => using LITTLEFS for configuration data in WiFiManager
// (USE_LITTLEFS == true) and (USE_SPIFFS == true)      => using LITTLEFS for configuration data in WiFiManager
// (USE_LITTLEFS == false) and (USE_SPIFFS == true)     => using SPIFFS for configuration data in WiFiManager
// Those above #define's must be placed before #include <BlynkSimpleEsp32_WFM.h>

//#define USE_LITTLEFS          true
#define USE_SPIFFS            false

#if USE_LITTLEFS
  #define CurrentFileFS     F("LittleFS")
#elif USE_SPIFFS
  #define CurrentFileFS     F("SPIFFS")
#else
  #define CurrentFileFS     F("EEPROM")

  // EEPROM_SIZE must be <= 2048 and >= CONFIG_DATA_SIZE (currently 172 bytes)
  #define EEPROM_SIZE    (2 * 1024)
  // EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
  #define EEPROM_START   0
#endif

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

// Config Timeout 120s (default 60s)
#define CONFIG_TIMEOUT                            120000L
// Those above #define's must be placed before #include <BlynkSimpleEsp8266_WM.h>

// TTGO T-Call pin definitions
#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23

#define MODEM_TX             MODEM_TX_PIN
#define MODEM_RX             MODEM_RX_PIN

#define I2C_SDA              21
#define I2C_SCL              22

// Select your modem:
//#define TINY_GSM_MODEM_SIM800
//#define TINY_GSM_MODEM_SIM808
//#define TINY_GSM_MODEM_SIM868
//#define TINY_GSM_MODEM_SIM900
//#define TINY_GSM_MODEM_SIM5300
//#define TINY_GSM_MODEM_SIM5320
//#define TINY_GSM_MODEM_SIM5360
//#define TINY_GSM_MODEM_SIM7000
//#define TINY_GSM_MODEM_SIM7100
//#define TINY_GSM_MODEM_SIM7500
#define TINY_GSM_MODEM_SIM7600
//#define TINY_GSM_MODEM_SIM7800
//#define TINY_GSM_MODEM_UBLOX
//#define TINY_GSM_MODEM_SARAR4
//#define TINY_GSM_MODEM_M95
//#define TINY_GSM_MODEM_BG96
//#define TINY_GSM_MODEM_A6
//#define TINY_GSM_MODEM_A7
//#define TINY_GSM_MODEM_M590
//#define TINY_GSM_MODEM_MC60
//#define TINY_GSM_MODEM_MC60E
//#define TINY_GSM_MODEM_XBEE
//#define TINY_GSM_MODEM_SEQUANS_MONARCH

// Increase RX buffer if needed
#define TINY_GSM_RX_BUFFER 1024

#include <TinyGsmClient.h>

#define USE_BLYNK_WM      false
//#define USE_BLYNK_WM      true

#include <BlynkSimpleTinyGSM_M.h>

#if USE_BLYNK_WM
  #define USE_DYNAMIC_PARAMETERS                    true

  #include <BlynkSimpleEsp32_GSM_WFM.h>

#else
  #include <BlynkSimpleEsp32_GSM_WF.h>
  
  // Your WiFi credentials.
  #define ssid  "MrMrsChippada"
  #define pass  "mayukh13m"
  
  //#define USE_LOCAL_SERVER      true
  #define USE_LOCAL_SERVER      false
  
  #if USE_LOCAL_SERVER
    #define wifi_blynk_tok        "****"
    #define gsm_blynk_tok         "****"
    //#define blynk_server          "account.duckdns.org"
    // Use direct IPAddress in case GPRS can't use DDNS fast enough and can't connect
    #define blynk_server          "xxx.xxx.xxx.xxx"
  #else
    #define wifi_blynk_tok        "vuv-YwKPQJEhKtiWpDC2NURwEJSnNlnc"
    #define gsm_blynk_tok         "KfiVZb8uwkWXuf0f8-ZFkZCrIyRkKISt"//"vuv-YwKPQJEhKtiWpDC2NURwEJSnNlnc"
    #define blynk_server          "blynk.cloud"
    //#define BLYNK_TEMPLATE_ID "TMPL-hClCSGR"
    //#define BLYNK_DEVICE_NAME "Demo"
    //#define BLYNK_AUTH_TOKEN "KfiVZb8uwkWXuf0f8-ZFkZCrIyRkKISt"
  #endif
  
  #define apn         "airtelgprs.com"
  #define gprsUser    ""    //"wapuser1"
  #define gprsPass    ""    //"wap"

#endif    //USE_BLYNK_WM

#define BLYNK_HARDWARE_PORT       80

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

#define RXD2      16
#define TXD2      17

// Use ESP32 Serial2 for GSM
#define SerialAT  Serial1

// Uncomment this if you want to see all AT commands
#define DUMP_AT_COMMANDS      true

#if DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, SerialMon);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif

#define HOST_NAME   "ESP32-GSM-WiFi"

#endif      //defines_h