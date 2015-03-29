 /*
 *  @file       print_uid.ino
 *  Project     RFID
 *  @version    1.0
 *  @author     Alejandro Simon
 *  @date       29/03/15
 *  @license    MIT - http://opensource.org/licenses/MIT
 *
 *  This sample uses the MFRC522 library created by Miguel Balboa (circuitito.com), Jan, 2012.
 *
 */

 /*
 * Pin layout
 * --------------------------
 * MFRC522   |  Arduino Uno
 * --------------------------
 * RST       |  9  / ICSP-5          
 * SDA(SS)   |  10          
 * MOSI      |  11 / ICSP-4 
 * MISO      |  12 / ICSP-1
 * SCK       |  13 / ICSP-3
 */

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

void setup() {
    Serial.begin(9600);  // Initialize serial communications with the PC 
    SPI.begin();         // Init SPI bus
    mfrc522.PCD_Init();  // Init MFRC522 reader
}

void loop() {
    // Look for cards
    if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
        delay(50);
        return;
    }
    // A card has been detected        
    unsigned int hex_num;
    hex_num =  mfrc522.uid.uidByte[0] << 24;
    hex_num += mfrc522.uid.uidByte[1] << 16;
    hex_num += mfrc522.uid.uidByte[2] <<  8;
    hex_num += mfrc522.uid.uidByte[3];
    Serial.print(F("Card UID hex:"));Serial.println(hex_num);
    delay(2000);
}
