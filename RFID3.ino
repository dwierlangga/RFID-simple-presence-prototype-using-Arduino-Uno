#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27,16,2);
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Kode Kartu yang terbaca");
  Serial.println();
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Akses diterima");
    Serial.println();
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Terima kasih");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sudah Absensi");
    lcd.setCursor(0,1);
    lcd.print("Tepat Waktu");
    delay(3000);
    lcd.clear();
    layarAwal();
  }
 
 else{
    Serial.println(" Akses ditolak !");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Maaf, Kartu Anda");
    lcd.setCursor(0,1);
    lcd.print("Tidak Terdaftar!");
    delay(3000);
    lcd.clear();
    layarAwal();
  }
}

void layarAwal(){
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello....");
  lcd.setCursor(0,1);
  lcd.print("Tempelkan kartu");
}
