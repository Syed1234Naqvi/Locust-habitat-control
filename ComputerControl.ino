//This is the receiving end of the jeenode.
//should receive information from its counterpart
//and then send the information to the UI program
//
//Note: BC = Bug Control

#include<TimeLib.h>
#include<JeeLib.h>

#define RF12_COMPAT 1


int identifier = 0;

void setup() {
  //command line notifier
  Serial.println("Computer control module start");
  
  //activate the RF module
  rf12_initialize(12,RF12_915MHZ,212);

  //initialize time
  setTime(12,0,0,26,1,2017);
  //set autosync
  setSyncProvider(getTime());
  setSyncInterval(10);
}

void loop() {

  
  if(rf12_recvDone())
  {
    memcpy(&identifier,(int*)rf12_data,sizeof(int));

    if(identifier == 1)
    {
      sendTime();
    }
  }
  


  //current delay set as 0.1 second/s
  delay(100);
}

//function getTime gets the current time from the computer system
//its connected to
time_t getTime()
{
  /*//create TimeElements variable
  TimeElements total;

  //get the current time from the computer
  //note: this is specifically for a windows computer
  //if it is running another OS, will need to be changed
  SYSTEMTIME st;
  GetSystemTime(&st);

  //placing current time into package
  total.Year = st.wYear;
  total.Month = st.wMonth;
  total.Day = st.wDay;
  total.Hour = st.wHour;
  total.Minute = st.wMinute;
  total.Second = st.wSecond;

  return makeTime(total);*/
}

//func sendTime tells sends the current time to BC
void sendTime()
{
  int i=0;
  bool c=true;
  
  while(c==true) 
  {
    if(rf12_canSend())
    {
      rf12_sendStart(0,&c,now());
    }
    rf12_recvDone();//reactivates reciever
  }
}

//func recData receives data from BC and checks if it is valid.
//if it is not, it attempts to get it again
// returns the data received
int recData(){
  bool c=true;
  int data =0;

  while(c==true)
  {
    if(rf12_recvDone())//waiting on receiving data from BC
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
}
