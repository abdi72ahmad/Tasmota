#ifdef USE_BT_CONSOLE

#include "BluetoothSerial.h"

BluetoothSerial BtSerial;

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
        AddLog(LOG_LEVEL_INFO, PSTR("BT RX: %c"), c);
      }
      break;
  }

  return false;
}

#endif
