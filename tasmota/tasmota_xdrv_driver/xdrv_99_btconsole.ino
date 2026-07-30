#ifdef USE_BT_CONSOLE

#include "BluetoothSerial.h"

BluetoothSerial BtSerial;

bool Xdrv99(uint32_t function)
{
  switch (function)
  {
    case FUNC_INIT:
      BtSerial.begin("Tasmota-BT");
      break;

    case FUNC_LOOP:
      if (BtSerial.available())
      {
        char c = BtSerial.read();
        AddLog(LOG_LEVEL_INFO, PSTR("BT: %c"), c);
      }
      break;
  }

  return false;
}

#endif
