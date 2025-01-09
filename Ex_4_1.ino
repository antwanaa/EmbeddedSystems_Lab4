#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "loopTimer.h"
#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
//#define LEDPIN 6
//#define BUZZER 5

SemaphoreHandle_t xSemaphore = NULL;

// define two tasks for Blink & AnalogRead
void ledTask( void *pvParameters );
void buzzTask( void *pvParameters );
void messageTask( void *pvParameters );
void serialTask( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  
  xSemaphore = xSemaphoreCreateBinary();
  if (xSemaphore == NULL) { 
    Serial.println("Mutex can not be created"); 
  }else{
    Serial.println("mutex created successfully");
    xSemaphoreGive(xSemaphore);
  }
  // Now set up two tasks to run independently.
  xTaskCreate(serialTask, "serial Task", 90, NULL, 2, NULL);
  xTaskCreate(ledTask, "Led Task", 48,  NULL, 2, NULL );
  xTaskCreate(buzzTask, "buzzerTask", 48, NULL, 2, NULL);
  xTaskCreate(messageTask, "Screen Task", 96, NULL, 2, NULL);
  


  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void ledTask(void *pvParameters)
{
  (void) pvParameters;

  pinMode(6, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    if(xSemaphoreTake(xSemaphore, ( TickType_t ) 10) == pdTRUE){
      Serial.println("Turning on the LED");
      xSemaphoreGive(xSemaphore);
    }
    digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay(500 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay(1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}
void buzzTask(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  pinMode(5, OUTPUT);

  for(;;){
    if(xSemaphoreTake(xSemaphore, ( TickType_t ) 10) == pdTRUE){
      Serial.println("Stopping to buzz");
      xSemaphoreGive(xSemaphore);
    }
    noTone(5); //Sets the voltage to low and makes no noise
    vTaskDelay(500 / portTICK_PERIOD_MS);
    tone(5, 100); //Set the voltage to high and makes a noise
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void messageTask(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  // initialize the display
  u8x8.begin(); // to start using the screen
  u8x8.setFlipMode(1);


  for(;;){
//    Serial.println("Task 3 Running");
    u8x8.clear();
    vTaskDelay(500 / portTICK_PERIOD_MS);
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.setCursor(0, 4);   //defining the starting point for the cursor
    u8x8.print("Hello World");  // Print "Hello World" on the display
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void serialTask(void *pvParameters)
{
  (void) pvParameters;
  
//  Serial.begin(9600);
  for(;;){
    if(xSemaphoreTake(xSemaphore, ( TickType_t ) 10) == pdTRUE){
      loopTimer.check(Serial);
      xSemaphoreGive(xSemaphore);
    }
    
  }
}
