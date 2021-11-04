
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

TaskHandle_t concurrentTaskOneHandle;
TaskHandle_t concurrentTaskTwoHandle;
SemaphoreHandle_t critSemaphore;

void setup() {
  Serial.begin(9600);

  critSemaphore = xSemaphoreCreateMutex();
  
  xTaskCreate(ctOneFunction, // Task function
              "ct1", // Task name
              128, // Stack size 
              NULL, 
              1, // Priority
              &concurrentTaskOneHandle); // Task handler

  xTaskCreate(ctTwoFunction, // Task function
              "ct2", // Task name
              128, // Stack size 
              NULL, 
              1, // Priority
              &concurrentTaskTwoHandle); // Task handler
  //vTaskStartScheduler();
}

void loop() {}

void ctOneFunction(void *pvParameters)
{
  (void) pvParameters;
  int counter = 1;

  while (true)
  {
    if (counter % 10 == 0) {
      criticalSection("FROM CT ONE :D");
    } else {
      Serial.println("Doing task 1 at counter " + String(counter));
    }
    counter++;
    vTaskDelay(1000 / portTICK_PERIOD_MS );
  }
}

void ctTwoFunction(void *pvParameters)
{
  (void) pvParameters;
  int counter = 1;

  while (true)
  {
    if (counter % 10 == 0) {
      criticalSection("FROM CT TWO OwO");
    } else {
      Serial.println("Doing task 2 at counter " + String(counter));
    }
    counter++;
    vTaskDelay(1000 / portTICK_PERIOD_MS );
  }
}

void criticalSection(String parameter) {
  xSemaphoreTake(critSemaphore, portMAX_DELAY);
  Serial.println("Calling crit entered!");
  for (int i = 0; i < 5; i++) {
    
    Serial.println("Critical section from " + parameter + " loop number " + String(i));
    vTaskDelay(500 / portTICK_PERIOD_MS ); 
  }
  xSemaphoreGive(critSemaphore);
}
