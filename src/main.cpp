/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/
#include <Arduino.h>



#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#include "mw_arduino_gatt.h"
// #include "mw_event.h"


static void mw_ble_callback(void* handler_args, esp_event_base_t base, int32_t id, void* event_data)
{
    ev_data data = *(ev_data*)event_data;

    switch (data.even_id)
    {
    case MW_BLE_GET_DATA /* constant-expression */:
      printf("event MW_BLE_GET_DATA %s, even_id = %d\n",data.data,data.even_id);
      if(memcmp(data.data,"stop",4)==0)
        mw_ble_stop();
      if(memcmp(data.data,"start",5)==0)
        mw_ble_restart();
      /* code */
      break;
    case MW_BLE_START/* constant-expression */:
      printf("Ble MW_BLE_START, even_id = %d\n",data.even_id);
      /* code */
      break;
    case MW_BLE_STOP_ADVERTISE/* constant-expression */:
      printf("Ble MW_BLE_STOP_ADVERTISE, even_id = %d\n",data.even_id);
      /* code */
      break;
    case MW_BLE_RESTART_ADVERTISE/* constant-expression */:
      printf("Ble MW_BLE_RESTART_ADVERTISE, even_id = %d\n",data.even_id);
      /* code */
      break;
    default:

      break;
    }
    // printf( "\nhandling %s:%s from %s, iteration %d", base, "MW_BLE_TASK", loop, data.even_id);
    printf("end Task\n");
}







void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  mw_arduino_gatt_setup(mw_ble_callback) ;

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}