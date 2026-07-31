#ifdef USE_BT_CONSOLE

#include "BluetoothSerial.h"

BluetoothSerial BtSerial;

char BtBuffer[256];
uint16_t BtIndex = 0;

void BtConsoleSend(const char* msg)
{
  if (BtSerial.hasClient()) {
    BtSerial.println(msg);
  }
}

bool BtConsoleConnected(void)
{
  return BtSerial.hasClient();
}


bool Xdrv99(uint32_t function)
{
  switch (function)
  {
    case FUNC_INIT:
      BtSerial.begin("Tasmota-BT");
      AddLog(LOG_LEVEL_INFO, PSTR("BT: Started"));
      break;


    case FUNC_LOOP:

      while (BtSerial.available())
      {
        char c = BtSerial.read();

        // command finished
        if ((c == '\r') || (c == '\n'))
        {
          if (BtIndex > 0)
          {
            BtBuffer[BtIndex] = 0;

            AddLog(LOG_LEVEL_INFO, PSTR("BT CMD: %s"), BtBuffer);

            ExecuteCommand(BtBuffer, SRC_SERIAL);

            BtIndex = 0;
          }
        }

        // backspace
        else if (c == '\b')
        {
          if (BtIndex > 0) {
            BtIndex--;
          }
        }

        // store character
        else
        {
          if (BtIndex < sizeof(BtBuffer) - 1)
          {
            BtBuffer[BtIndex++] = c;
          }
        }
      }

      break;
  }

  return false;
}

#endif
