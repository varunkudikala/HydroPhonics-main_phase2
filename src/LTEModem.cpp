#include "LTEModem.h"
//#include "Adafruit_FONA.h"
#include "defines.h"
#include "GPIOConfig.h"

namespace ModemInterface
{
    TinyGsmClient client(modem);
    BlynkTimer timer; // Create a Timer object called "timer"!
    bool GSM_CONNECT_OK = false;

    //PH,EC,temp,motor status,on time,motor off time
    //Lights status,on time,off time
    void sendUptime()
    {
        Serial.println("Send sensor values");
        Serial.print(measParams.f_ECValue);        
        Serial.print(measParams.f_TempValue);
        Serial.print(measParams.f_PHValue);
        Serial.println();

        Blynk_GSM.virtualWrite(V0, measParams.f_ECValue);
        Blynk_GSM.virtualWrite(V1, measParams.f_TempValue);
        Blynk_GSM.virtualWrite(V2, measParams.f_PHValue);
        Blynk_GSM.virtualWrite(V3, measParams.waterPumpOnStatus);
        Blynk_GSM.virtualWrite(V4, measParams.waterPumpOnTime);
        Blynk_GSM.virtualWrite(V5, measParams.waterPumpOffTime);
        Blynk_GSM.virtualWrite(V6, measParams.lightPumpOnStatus);
        Blynk_GSM.virtualWrite(V7, measParams.lightPumpOnTime);
        Blynk_GSM.virtualWrite(V8, measParams.lightPumpOffTime);
        Blynk_GSM.virtualWrite(V9, measParams.waterLevelInCm);
        //Alert yet to be defined
    }

    void Modem::init()
    {
        SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
        delay(3000);
        timer.setInterval(4000L, sendUptime);
        //modem.init(); //modem.restart(); 
        //modem.setBaud(9600);
        //SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);
        Blynk_GSM.config(modem, gsm_blynk_tok, blynk_server, BLYNK_HARDWARE_PORT);
        GSM_CONNECT_OK = Blynk_GSM.connectNetwork(apn, gprsUser, gprsPass);
        
        if (GSM_CONNECT_OK)
            Blynk_GSM.connect();
    }

    void Modem::sendIOTServer(void)
    {    
        static uint32_t time2SCount;
        
        if (GSM_CONNECT_OK)
        {
            Blynk_GSM.run();
            time2SCount++;
            if( time2SCount>= 450 )
            {
                Blynk_GSM.disconnect();                
                modem.gprsDisconnect();                
                GSM_CONNECT_OK = Blynk_GSM.connectNetwork(apn, gprsUser, gprsPass);        
                if (GSM_CONNECT_OK)
                    Blynk_GSM.connect();
                time2SCount = 0;
              }              
        }
        timer.run();

        /*
        static uint8_t clientconnected = false;
        if (clientconnected == false)
        {
            if (modem.isNetworkConnected())
            {
                //modem.waitForNetwork(600000L);
                modem.gprsConnect("airtelgprs.com", "", "");
                client.connect("169.55.61.243", 9012);
                delay(2000);
            }
        }
        if (!client.connected())
        {
            // Print available data
            clientconnected = true;
        }
        */
    }
    void Modem::sendSMSAlert(char *phnum)
    {
    }
}