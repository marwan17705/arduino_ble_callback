#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "event_source.h"
#include "esp_event_base.h"
#include "mw_event.h"
#include "stdint.h"


static const char* TAG = "mw_event";




esp_event_loop_handle_t loop_with_task;
ESP_EVENT_DEFINE_BASE(MW_TASK_EVENTS);


// static void task_iteration_handler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data)
// {

//     int iteration = *((int*) event_data);

//     char* loop;

//     if (handler_args == loop_with_task) {
//         loop = "loop_with_task";
//     } else {
//         loop = "loop_without_task";
//     }

//     printf( "\nhandling %s:%s from %s, iteration %d", base, "MW_BLE_EVET", loop, iteration);
//     printf("\n");
// }


esp_err_t mw_event_init(esp_event_loop_handle_t * event)
{
    esp_err_t res = ESP_OK;
    esp_event_loop_args_t loop_with_task_args = {
        .queue_size = 5,
        .task_name = "loop_task", // task will be created
        .task_priority = 4,//uxTaskPriorityGet(NULL),
        .task_stack_size = 1024 * 3,
        .task_core_id = tskNO_AFFINITY
    };
    res=(esp_event_loop_create(&loop_with_task_args, &loop_with_task));
    if(res)
      goto END_LABEL;
    else  
      *event = loop_with_task;

    // res=(esp_event_handler_instance_register_with(loop_with_task, MW_TASK_EVENTS, MW_BLE_EVET,task_iteration_handler, loop_with_task, NULL));
    // if(res)
    //   goto END_LABEL;


    END_LABEL:
    {
      *event = loop_with_task;
      printf("%s\n",esp_err_to_name(res));
      return res;
    }
}


esp_err_t mw_add_event(esp_event_loop_handle_t event,esp_event_handler_t cb)
{

  return esp_event_handler_instance_register_with(loop_with_task, MW_TASK_EVENTS,MW_BLE_EVET,cb, loop_with_task, NULL);
}




esp_err_t mw_event_start(esp_event_loop_handle_t * event,esp_event_handler_t cb)
{
  esp_err_t res  =  mw_event_init(event);
  if(res)
    goto END_LABEL;
  res  =  mw_add_event(*event,cb);
  if(res)
    goto END_LABEL;
  END_LABEL:
  {
    printf("%s\n",esp_err_to_name(res));
    return res;
  }

}
