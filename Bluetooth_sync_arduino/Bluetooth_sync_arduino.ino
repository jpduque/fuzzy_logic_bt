#include "SoftwareSerial.h"
#include "LiquidCrystal.h"

SoftwareSerial serial_connection(8, 9);//Create a serial connection with TX and RX on these pins
#define BUFFER_SIZE 64//This will prevent buffer overruns.
char inData[BUFFER_SIZE];//This is a character buffer where the data sent by the python script will go.
char inChar=-1;//Initialie the first character as nothing
int count=0;//This is the number of lines sent in from the python script
int i=0;//Arduinos are not the most capable chips in the world so I just create the looping variable once

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);//Initialize communications to the serial monitor in the Arduino IDE
  serial_connection.begin(9600);//Initialize communications with the bluetooth module
  serial_connection.println("Ready!!!");//Send something to just start comms. This will never be seen.
  Serial.println("Started");//Tell the serial monitor that the sketch has started.


  
  lcd.begin(16,2);
  lcd.print("C=");
  lcd.setCursor(0,1);
  lcd.print("Temperatura");

  
}

float centi()
{// Funcion para leer el dato analogico y convertirlo a digital:
  int dato;
  float c;
  dato=analogRead(A0);
  c = (500.0 * dato)/1023;
  return (c);
}

void loop()
{
  //This will prevent bufferoverrun errors
  byte byte_count=serial_connection.available();//This gets the number of bytes that were sent by the python script
  if(byte_count)//If there are any bytes then deal with them
  {
    Serial.println("Incoming Data");//Signal to the monitor that something is happening
    int first_bytes=byte_count;//initialize the number of bytes that we might handle. 
    int remaining_bytes=0;//Initialize the bytes that we may have to burn off to prevent a buffer overrun
    if(first_bytes>=BUFFER_SIZE-1)//If the incoming byte count is more than our buffer...
    {
      remaining_bytes=byte_count-(BUFFER_SIZE-1);//Reduce the bytes that we plan on handleing to below the buffer size
    }
    for(i=0;i<first_bytes;i++)//Handle the number of incoming bytes
    {
      inChar=serial_connection.read();//Read one byte
      inData[i]=inChar;//Put it into a character string(array)
    }
    inData[i]='\0';//This ends the character array with a null character. This signals the end of a string
    if(String(inData)=="BOOP 1")//Again this is an arbitrary choice. It would probably be something like: MOTOR_STOP
    {
      
      
      float Centigrados = centi();
  
      lcd.setCursor(2,0);
      lcd.print(Centigrados);
  

      
      //temperatura=random(300);
      Serial.print ("temperatura: ");
      Serial.print (Centigrados);
      Serial.println (" grados");
      serial_connection.println(Centigrados);//Then send an incrmented string back to the python script
    }
   
  }
  delay(50);//Pause for a moment 
}
