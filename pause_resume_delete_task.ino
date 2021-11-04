
#include <Arduino_FreeRTOS.h>
TaskHandle_t taskPrintOneHandle;
TaskHandle_t taskPrintTwoHandle;
TaskHandle_t taskPrintThreeHandle;

void setup() {
  Serial.begin(9600);
  xTaskCreate(TaskPrintOne, // Task function
              "PrintOne", // Task name
              128, // Stack size 
              NULL, 
              1, // Priority
              &taskPrintOneHandle); // Task handler
              
  xTaskCreate(TaskPrintTwo, // Task function
              "PrintTwo", // Task name
              128, // Stack size 
              NULL, 
              1, // Priority
              &taskPrintTwoHandle); // Task handler

  xTaskCreate(TaskPrintThree, // Task function
              "PrintThree", // Task name
              128, // Stack size 
              NULL, 
              1, // Priority
              &taskPrintThreeHandle); // Task handler

}

void loop() {}

void TaskPrintOne(void *pvParameters)
{
  (void) pvParameters;
  int counter = 0;

  while (true)
  {
    counter++;

    if (counter == 5) {
      Serial.println("Counter reached 5, pausing task 2");  
      vTaskSuspend(taskPrintTwoHandle);
    } else if (counter == 10) {
      Serial.println("Counter reached 10, deleting task 3");
      vTaskDelete(taskPrintThreeHandle);
    } else if (counter == 15) {
      Serial.println("Counter reached 15, resuming task 2");
      vTaskResume(taskPrintTwoHandle);
      Serial.println("Trying also resuming task 3");
      vTaskResume(taskPrintThreeHandle);
    }
    Serial.println("Task one trigger " + String(counter));
    vTaskDelay(1000 / portTICK_PERIOD_MS );
  }
}

void TaskPrintTwo(void *pvParameters)
{
  (void) pvParameters;

  while (true)
  {
    Serial.println("Task two trigger");
    vTaskDelay(1000 / portTICK_PERIOD_MS );
  }
}

void TaskPrintThree(void *pvParameters)
{
  (void) pvParameters;

  while (true)
  {
    Serial.println("Task three trigger");
    vTaskDelay(1000 / portTICK_PERIOD_MS );
  }
}
