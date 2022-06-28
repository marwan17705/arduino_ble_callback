#include <Arduino.h>
#include "mw_event.h"

#ifdef __cplusplus
extern "C" {
#endif
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"


void mw_arduino_gatt_setup(esp_event_handler_t cb) ;
void mw_ble_stop();
void mw_ble_restart();
#ifdef __cplusplus
}
#endif