#include "myTask.hpp"
#include "mySerialBT.hpp"
#include "famicon.hpp"
#include "myGraphics.hpp"

void setupTask()
{
    xTaskCreate(my_task, "my_task", 2048, NULL, 1, NULL);
}

void my_task(void *arg) 
{
  String buttonName;
  String strbuttonState;
  uint16_t buttonState;

  while (1) 
  {
    if(SerialBT.available()>1)
    {
        String str = SerialBT.readStringUntil('\n');
        uint length = str.length();
        //Serial.print("echo=> ");
        //Serial.print(str);
        //Serial.printf("length=%d\r",length);
        //Serial1.printf("%s\n",str);
        char ch[length+1];
        str.toCharArray(ch,length+1,0);
        buttonState = strtol(ch,NULL,16);
        Serial1.printf("%04x\r\n",buttonState);
        buttonName = famiconGetButtonName(buttonState);
        //SSD1306 表示------------------------------------
        canvas.startWrite();//通信を開始する。（ペリフェラルを占有する）
        canvas.fillScreen(TFT_BLACK);    // 背景塗り潰し
        canvas.setTextSize(1);
        canvas.setCursor(0,0, &Font4);
        canvas.printf("%s\n",buttonName);
        canvas.pushSprite(0,0);
        canvas.endWrite();//通信を終了する。（ペリフェラルの占有を終了する)
    }
    vTaskDelay(INTERVAL_TASK / portTICK_RATE_MS);
  }
}