/*
 * This is my first own teensy 4.1 programm with sd card.
 * This programm will calculate some stuff an write it to the sd card 
 * 
 *  created   Nov 2022
 *  by Niko Eller
 * 
 */

#include <SD.h>
#include <SPI.h>

File myFile;
const int chipSelect = BUILTIN_SDCARD;
const int buildInLEDPin = 13;


const String fileName = "data.txt";
int i = 0;

void setup() {
  // Setup on board LED
  pinMode(buildInLEDPin, OUTPUT);

  
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  SD.remove("data.txt");


}

void loop() {
  // put your main code here, to run repeatedly:
  if( i < 5){
    saveData(i+1);
    i++;
  }
  if ( i == 5) {
    readData();
    i++;
  }
}



void saveData(String data){
  //open the file
  myFile = SD.open("data.txt", FILE_WRITE);

  //if there was no problem opening the file => wirte to it
  if (myFile) {
    Serial.print("writing to");
    Serial.println(fileName);
    myFile.println(data);
    //colse the file
    myFile.close();
  } else {
    //if the file couldn't be opend => print error message
    Serial.print("error oppening the file :");
    Serial.println(fileName); 
  }
}

void readData(){
  //open the file
  myFile = SD.open("data.txt", FILE_READ);

  if(myFile){
     //read the context of the file starting from the top
    while(myFile.available()){
    Serial.write(myFile.read());
    }
    //after reading the complete file, close the file
    myFile.close();
  } else {
    //if the file couldn't be opend => print error message
    Serial.print("error oppening the file :");
    Serial.println(fileName); 
  }

}




  
