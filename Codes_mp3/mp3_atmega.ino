#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "LiquidCrystal_I2C.h"

SoftwareSerial mySoftwareSerial(13, 12); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

LiquidCrystal_I2C LCDku(0x27,20,4);
int buttonNext = 2;
int buttonPause = 3;
int buttonPrevious = 4;
int index = 1;

bool isPlaying = false;

void setup() {
    pinMode(buttonPause, INPUT_PULLUP);
    pinMode(buttonNext, INPUT_PULLUP);
    pinMode(buttonPrevious, INPUT_PULLUP);
    LCDku.init();
    LCDku.backlight();
    mySoftwareSerial.begin(9600);
    Serial.begin(9600);

    delay(1000);

    Serial.println();
    Serial.println("MP3");
    Serial.println("Initializing MP3...");

    if (!myDFPlayer.begin(mySoftwareSerial)) {
        Serial.println("Unable to begin:");
        LCDku.clear();
        LCDku.setCursor(0,0);
        LCDku.println("Unable to begin");
        Serial.println("1.Please recheck the connection!");
        Serial.println("2.Please insert the SD card!");
        while (true);
    }
    Serial.println(F("MP3 online."));
    LCDku.clear();
    LCDku.setCursor(0,0);
    myDFPlayer.setTimeOut(500);

    //----Set volume----
    myDFPlayer.volume(10); //Set volume value (0~30).
    //myDFPlayer.volumeUp(); //Volume Up
    //myDFPlayer.volumeDown(); //Volume Down

    //----Set different EQ----
    myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
    //  myDFPlayer.EQ(DFPLAYER_EQ_POP);
    //  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
    //  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
    //  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
    //  myDFPlayer.EQ(DFPLAYER_EQ_BASS);

    myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

    myDFPlayer.play(1); //Play the first song
    isPlaying = true;
    Serial.println("Playing..");
   
}

void loop() {
  LCDku.clear();
  LCDku.setCursor(0,0);
  LCDku.print("track " );
  LCDku.println(index);
    if (digitalRead(buttonPause) == LOW) {
        if (isPlaying) {
            myDFPlayer.pause();
            isPlaying = false;
            LCDku.setCursor(0,1);
            LCDku.println("Paused");
            Serial.println("Paused..");
        } else {
            isPlaying = true;
            myDFPlayer.start();
            LCDku.setCursor(0,1);
            LCDku.println("Playing");
            Serial.println("Playing..");
        }
        delay(500);
    }
    if (digitalRead(buttonNext) == LOW) {
        if (isPlaying) {
            myDFPlayer.next();
            Serial.println("Next Song..");
            index = index + 1;
        }
        delay(500);
    }

    if (digitalRead(buttonPrevious) == LOW) {
        if (isPlaying) {
            myDFPlayer.previous();
            Serial.println("Previous Song..");
            index = index - 1;
        }
        delay(500);
    }
    if (index < 0){
      index = 0;
    }else{index = index;}
}
