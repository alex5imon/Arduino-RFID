 /*
 *  @file       two_readers.ino
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
 * RST       |  7/ICSP-5 (shared)                   
 * MOSI      |  ICSP-4   (shared)  
 * MISO      |  ICSP-1   (shared) 
 * SCK       |  ICSP-3   (shared) 
 * SDA1 (SS) |  9        (reader 1)
 * SDA2 (SS) |  10       (reader 2)
 */

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 9
#define SS_PIN2 10
#define RST_PIN 7
#define RST_PIN2 8

MFRC522 mfrc522(SS_PIN, RST_PIN);     // Create First MFRC522 instance.
MFRC522 mfrc522_2(SS_PIN2, RST_PIN2); // Create Second MFRC522 instance.

void setup() {
    Serial.begin(9600);  // Initialize serial communications with the PC
    while (!Serial);     // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    
    SPI.begin();           // Init SPI bus
    mfrc522.PCD_Init();    // Init First MFRC522 card
    mfrc522_2.PCD_Init();  // Init Second MFRC522 card
}

void loop() {   
    check_reader(mfrc522, 1);
    check_reader(mfrc522_2, 2);
    delay(50);
}

void check_reader(MFRC522 reader, int id) {
    // Look for cards
    if ( ! reader.PICC_IsNewCardPresent() || ! reader.PICC_ReadCardSerial() ) {
        return;
    }
    Serial.print(F("Card detected in reader: "));Serial.println(id);
    // A card has been detected        
    unsigned int hex_num;
    hex_num =  reader.uid.uidByte[0] << 24;
    hex_num += reader.uid.uidByte[1] << 16;
    hex_num += reader.uid.uidByte[2] <<  8;
    hex_num += reader.uid.uidByte[3];
    Serial.print(F("Card UID hex:"));Serial.println(hex_num);
}
