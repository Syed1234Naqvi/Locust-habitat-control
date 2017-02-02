/* This is the bug habitat control module.
 * List of functionality is as follows:
 * Track time
 * sync time with counterpart
 * change time (received from outside source)
 * 
 * 
 * note: CC = ComputerControl
 */

#include<TimeLib.h>
#include<JeeLib.h>

//lCount counts the current amount of times loop has passed
int lCount = 100;
int identifier = 0;

void setup() {
  int data = 0;
  int years,months,days;
  
  //initialize serial port
  Serial.begin(115200);
  //command line notifier
  Serial.println("Bug Habitat Control Start");
  
  //activate the RF module
  rf12_initialize(12,RF12_915MHZ,212);

  //initialize time
  setTime(12,0,0,24,01,2017);
  //initial sync
  //years
  sendData();
  data = recData();
  years = data;

  //months
  sendData();
  data = recData();
  months = data; 
   
  //days
  sendData();
  data = recData();
  days = data; 

  setTime(12,0,0,day,month,year);

  sync();
                           
}

void loop() {
  lCount++;
  
  //current time for sync set for every 10 seconds
  if(lCount==100)//heavily reliant on current loop, consider changing
  {
    lCount=0;
    sync();
  }

  //polling for signal
  if(rf12_recvDone())
  {
    memcpy(&identifier,(int*)rf12_data,sizeof(int));
    if(identifier == 1)
    {
      //change time up
      timeUp();
    }
    if(identifier == 2)
    {
      //change time down
      timeDown();
    }
    if(identifier == 3)
    {
      //possible something else?
    }
  }
  

  //delay set currently as 0.1 second/s
  delay(100);
}

//func sync will get the current time from its counterpart module
void sync(){
  int data = 0;
  int hours,minutes,seconds;
  
  //hours
  sendData();
  data = recData();
  hours = data;
  
  //minutes
  sendData();
  data = recData();
  minutes = data;

  //seconds
  sendData();
  data = recData();
  seconds = data;

  setTime(hours,minutes,seconds,day(),month(),year());
}

//func sendData tells CC to send their data
void sendData()
{
  bool c=true;
  
  while(c==true) 
  {
    if(rf12_canSend())
    {
      rf12_sendStart(0,&c,1);//tells CC to send time
      c=false;// turns off loop to exit
    }
    rf12_recvDone();//reactivates reciever
  }
}

//func recData receives data from CC and checks if it is valid.
//if it is not, it attempts to get it again
// returns the data received
int recData(){
  bool c=true;
  int data =0;

  while(c==true)
  {
    if(rf12_recvDone())//waiting on receiving data from CC
    {
      //output to serial for testing
      memcpy(&data,(int*)rf12_data,sizeof(int));
      Serial.println(data);
      
      if(rf12_crc!=0)//if the data isn't reliable
      {
        data = recData();
      }
      
      c=false;
    }
  }
  return data;
}

//func digitalClockDisplay display the current
//time of the arduino on the serial port.
void digitalClockDisplay(){
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

//func printDigits outputs a proper format for
//digital numbers to serial
void printDigits(int digits){
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


//func timeUp changes the hour of time up by 1 hour
//whenever called
void timeUp(){
  adjustTime(3600);
}

//func timeDown changes the hour of time down
//by 1 hour whenever called
void timeDown(){
  adjustTime(-3600);
}
