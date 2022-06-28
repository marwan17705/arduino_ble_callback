#include "stdio.h"

#include "freertos/FreeRTOS.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_timer.h"


#ifdef __cplusplus
extern "C" {
#endif


#define BLE_LEN                      60      // number of times the task iterates
#define TASK_ITERATIONS_COUNT        10      // number of times the task iterates
#define TASK_PERIOD                  500     // period of the task loop in milliseconds

ESP_EVENT_DECLARE_BASE(MW_TASK_EVENTS);         // declaration of the task events family

enum {
    MW_BLE_EVET                     // raised during an iteration of the loop within the task
};

enum {
    MW_BLE_GET_DATA,
    MW_BLE_START,
    MW_BLE_STOP_ADVERTISE,
    MW_BLE_RESTART_ADVERTISE,

};


typedef struct 
{
  char data[BLE_LEN];
  int even_id;
} ev_data;

esp_err_t mw_event_init(esp_event_loop_handle_t * event);
esp_err_t mw_add_event(esp_event_loop_handle_t event,esp_event_handler_t cb);
esp_err_t mw_event_start(esp_event_loop_handle_t * event,esp_event_handler_t cb);
// esp_err_t mw_event_init();


#ifdef __cplusplus
}
#endif