#include "stdio.h"
#include "mw_arduino_gatt.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
// #include "mw_event.h"
esp_event_loop_handle_t loop_post_to;

BLEAdvertising *pAdvertising;


class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        /*
        Serial.println("*********");
        Serial.print("Received Value: ");
        Serial.println(rxValue.c_str());
        Serial.println();
        Serial.println("*********");
        */
        ev_data data_ev ;
        memcpy(data_ev.data,rxValue.c_str(),rxValue.length());
        data_ev.data[rxValue.length()] = '\0';
        data_ev.even_id = MW_BLE_GET_DATA;
        ESP_ERROR_CHECK(esp_event_post_to(loop_post_to, MW_TASK_EVENTS, MW_BLE_EVET, &data_ev, sizeof(data_ev), portMAX_DELAY));

      }
    }
    void onConnect(BLEServer* pserver) {
      Serial.println("Connected");
    }

    void onDisconnect(BLEServer* pserver) {
      Serial.println("Disconnected");
    }
};

void mw_arduino_gatt_setup(esp_event_handler_t cb) {
  esp_event_loop_handle_t loop_with_task;

  mw_event_start(&loop_with_task,cb);

  Serial.println("Starting BLE work!");
  loop_post_to  = loop_with_task;
  BLEDevice::init("FARM_KID");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE

                                       );
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("FARM_KID_BLE_CONFIGS_WIFI");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");


  ev_data data_ev ;
  data_ev.even_id = MW_BLE_START;
  ESP_ERROR_CHECK(esp_event_post_to(loop_post_to, MW_TASK_EVENTS, MW_BLE_EVET, &data_ev, sizeof(data_ev), portMAX_DELAY));
}



void mw_ble_stop()
{
  pAdvertising->stop();
  BLEDevice::getAdvertising()->stop();
  ev_data data_ev ;
  data_ev.even_id = MW_BLE_STOP_ADVERTISE;
  ESP_ERROR_CHECK(esp_event_post_to(loop_post_to, MW_TASK_EVENTS, MW_BLE_EVET, &data_ev, sizeof(data_ev), portMAX_DELAY));
  
}

void mw_ble_restart()
{
  pAdvertising->start();
  BLEDevice::getAdvertising()->start();
  ev_data data_ev ;
  data_ev.even_id = MW_BLE_RESTART_ADVERTISE;
  ESP_ERROR_CHECK(esp_event_post_to(loop_post_to, MW_TASK_EVENTS, MW_BLE_EVET, &data_ev, sizeof(data_ev), portMAX_DELAY));
  
}
