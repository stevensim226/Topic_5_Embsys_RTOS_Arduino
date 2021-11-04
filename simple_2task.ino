
#include <Arduino_FreeRTOS.h>
TaskHandle_t taskPrintOneHandle;
TaskHandle_t taskPrintTwoHandle;

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

}

void loop() {}

void TaskPrintOne(void *pvParameters)
{
  (void) pvParameters;

  while (true)
  {
    Serial.println("Task one trigger");
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
