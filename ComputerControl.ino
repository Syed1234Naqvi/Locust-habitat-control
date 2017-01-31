//This is the receiving end of the jeenode.
//should receive information from its counterpart
//and then send the information to the UI program
#include<Time.h>
#include<JeeLib.h>
#include<windows.h>

void setup() {
  //command line notifier
  Serial.println("Computer control module start");
  
  //activate the RF module
  rf12_initialize(12,RF12_915MHZ,212);

  //initialize time
  setTime(12,0,0,26,1,2017);
  //set autosync
  setSyncProvider(getTime());
  setsyncInterval(10);
}

void loop() {


  //current delay set as 0.1 second/s
  delay(100)
}

//function getTime gets the current time from the computer system
//its connected to
time_t getTime()
{
  //create TimeElements variabel
  tm total;

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

  return makeTime(total);
}

