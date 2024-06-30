#include "mySerialBT.hpp"

BluetoothSerial SerialBT;

uint8_t atomlite1_address[6]={0x00,0x00,0x00,0x00,0x00,0x00};

void bluetoothMasterBegin(uint8_t *address)
{
    SerialBT.begin("M5 ATOM master", true);
    Serial.println("begin connect");
    //SSD1306 表示------------------------------------
    canvas.startWrite();//通信を開始する。（ペリフェラルを占有する）
    canvas.fillScreen(TFT_BLACK);    // 背景塗り潰し
    canvas.setTextSize(1);
    canvas.setCursor(0,0, &Font2);
    canvas.printf("Now Search device");
    canvas.pushSprite(0,0);
    canvas.endWrite();//通信を終了する。（ペリフェラルの占有を終了する)

    //bluetoothデバイスサーチと接続
    //advertisingパケット受信。
    //ATOMLite側のアドバタイズは停止していない。
    int times=0;
    bool connected;
    int btConnectCounter;

    do
    {
        connected = SerialBT.connect(address);//10秒でタイムアウト
        Serial.printf("%d connected=%d ",times,connected);
        times++;
        if(times==30)
        {
        Serial.println("error:connect timeout");
        break;
        }
    }while(!connected);
    Serial.println("");
    delay(30);
    if (connected) 
    {//接続成功
        btConnectCounter++;
        Serial.printf("Connected Succesfully! %d\n\r",btConnectCounter);
    } else 
    {//接続失敗
        while (!SerialBT.connected(10000))
        {
            Serial.println("Failed to connect.");
        }
    }

}

void bluetoothReceiver(void)
{
    if(SerialBT.available()>10)
    {
        String str = SerialBT.readStringUntil('\n');
        uint length = str.length();
        Serial.print("echo=> ");
        Serial.print(str);
        Serial.printf("length=%d\r",length);
    }
}