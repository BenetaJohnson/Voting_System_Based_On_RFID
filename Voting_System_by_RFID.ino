#include <LiquidCrystal.h>

#include <LiquidCrystal.h>

#include <SPI.h>
#include <LiquidCrystal.h>

#include <MFRC522.h>
 LiquidCrystal lcd(12,11,5,4,3,2);
 MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)
 int vote1=0, vote2=0, vote3=0;
 String tagUID[] = {"45 65 8D 30", "75 06 00 5C","A1 C8 D9 DF"}; // String to store UID of tag. Change it with your tag's UID
 #define sw1 15
 #define sw2 16
 #define sw3 17
 #define rsw 18
 void setup() {
  lcd.begin(16,2); // LCD screen
  SPI.begin(); // Init SPI bus
  Serial.begin(9600);
  mfrc522.PCD_Init(); // Init MFRC522
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
  pinMode(sw3,INPUT_PULLUP);
  pinMode(rsw,INPUT_PULLUP);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Voting System");
  lcd.setCursor(0, 1);
  lcd.print(" based on RFID");
  delay(1000);
 }
 void loop() {
  /*lcd.setCursor(0, 0);
  lcd.print(" Voting System");
  lcd.setCursor(0, 1);
  lcd.print(" based on RFID");
  delay(1000);*/
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press vote");
  lcd.setCursor(0, 1);
  lcd.print("or Result");
  sample();
 }
 void sample(){
  while(1){
    Serial.println(digitalRead(sw1));
    if(digitalRead(sw1)!=0 || digitalRead(sw2)!=0 || digitalRead(sw3)!=0){
      Serial.println("Button pressed");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Show Your");
      lcd.setCursor(0,1);
      lcd.print("Tag");
      delay(7000);
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
      }
      // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
      }
      
      //Reading from the card
      String tag = "";
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        tag.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      tag.toUpperCase();
      
      //Checking the card
      int count=0;
      for(int j=0;j<3;j++){
        if (tag.substring(1) == tagUID[j]) //change here the UID of the card/cards that you want to give access
        {
          // If UID of tag is matched.
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Please Place");
          lcd.setCursor(0,1);
          lcd.print("Your Vote");
          vote();
          count=1;
        }
      }
      if(count==0)
      {
        // If UID of tag is not matched.
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wrong Tag Shown");
        lcd.setCursor(0, 1);
        lcd.print("Access Denied");
        delay(3000);
        lcd.clear();
      }
      return;
    }
    else if(digitalRead(rsw)==1){
      result();
      return;
    }
  }
 }
 void vote(){
  while(1){
    if(digitalRead(sw1)==1){
      vote1++;
      while(digitalRead(sw1)==1);
      return;
    }
    else if(digitalRead(sw2)==1){
      vote2++;
      while(digitalRead(sw2)==1);
      return;
    }
    else if(digitalRead(sw3)==1){
      vote3++;
      while(digitalRead(sw3)==1);
      return;
    }
  }
 }

 void result(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Can1");
    lcd.setCursor(6,0);
    lcd.print("Can2");
    lcd.setCursor(12,0);
    lcd.print("Can3");
    lcd.setCursor(0,1);
    lcd.print(vote1);
    lcd.setCursor(6,1);
    lcd.print(vote2);
    lcd.setCursor(12,1);
    lcd.print(vote3);
    delay(4000);
    lcd.clear();
 }