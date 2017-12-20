//////////
/////////  All Serial Handling Code, 
/////////  It's Changeable with the 'serialVisual' variable
/////////  Set it to 'true' or 'false' when it's declared at start of code.  
/////////

#define BPMCount 3

void serialOutput(){   // Decide How To Output Serial. 
 if (serialVisual == true){  
     arduinoSerialMonitorVisual('-', Signal);   // goes to function that makes Serial Monitor Visualizer
 } else{
      sendDataToSerial('S', Signal);     // goes to sendDataToSerial function
 }        
}

//  Decides How To OutPut BPM and IBI Data
void serialOutputWhenBeatHappens(){    
 if (serialVisual == true){                                          //  Code to Make the Serial Monitor Visualizer Work
    Serial.print("*** Heart-Beat Happened *** ");                   //ASCII Art Madness
    Serial.print("BPM: ");                                          //
    Serial.print(BPM);                                              //
    Serial.print("  ");                                             //
    static int BPMS[BPMCount] = { 0 };                               //측정된 BPM 중 올바른 값을 추출하기 위해 배열을 만듬
    static int count = 0;                                            //측정된 BPM의 갯수를 체크
      if(BPM <= 160 && BPM >= 40 ){                                  //BPM의 범위가 40~160일때
        if(count == 0){                                              //배열의 처음 값일때
          BPMS[count++] = BPM;                                       //BPM대입
        }else if(abs(BPMS[count-1] - BPM) < 9  && count < BPMCount){ //이전에 측정한 BPM이 있을 때 이 두개의 오차가 +-9미만일때 그리고 갯수가 3개 미만일때
          BPMS[count++] = BPM;                                       //BPM에 대입
        }else{                                                       //다 아니면 초기화한 후 측정된 BPM을 대입
          memset(BPMS,0,sizeof(int)*BPMCount);                       //
          count = 0;                                                 //
          BPMS[count++] = BPM;                                       //
        }                                                            //
        if(count - 1 == BPMCount - 1){                               //값이 다 대입되었을때 평균을 구하고 값을 보내주는 부분
          int AvrBPM = 0;                                            //
          count = 0;                                                 //
          for(int i=0;i<BPMCount;i++){                               //
            AvrBPM += BPMS[i];                                       //
            Serial.print(BPMS[i]);                                  //
            Serial.print("  ");                                     //
          }                                                          //
          AvrBPM /= BPMCount;                                        //
          BTSerial.write((char)(AvrBPM-40));                         //AvrBPM이 값이 손실되는 것을 방지하기 위해 -40을 해줌
          delay(1);                                                  //
          Serial.print(AvrBPM);                                     //
          memset(BPMS,0,sizeof(int)*BPMCount);                       //평균 BPM을 보내주고 배열 초기화
          count = 0;                                                 //BPM갯수 초기화
        }
    }
 } else{
        sendDataToSerial('B',BPM);   // send heart rate with a 'B' prefix
        sendDataToSerial('Q',IBI);   // send time between beats with a 'Q' prefix
 }   
}



//  Sends Data to Pulse Sensor Processing App, Native Mac App, or Third-party Serial Readers. 
void sendDataToSerial(char symbol, int data ){
    Serial.print(symbol);
    Serial.println(data);                
  }


//  Code to Make the Serial Monitor Visualizer Work
void arduinoSerialMonitorVisual(char symbol, int data ){    
  const int sensorMin = 0;      // sensor minimum, discovered through experiment
  const int sensorMax = 1024;    // sensor maximum, discovered through experiment

  int sensorReading = data;
  // map the sensor range to a range of 12 options:
  int range = map(sensorReading, sensorMin, sensorMax, 0, 11);

  // do something different depending on the 
  // range value:
  switch (range) {
  case 0:     
    Serial.println("");     /////ASCII Art Madness
    break;
  case 1:   
    Serial.println("---");
    break;
  case 2:    
    Serial.println("------");
    break;
  case 3:    
    Serial.println("---------");
    break;
  case 4:   
    Serial.println("------------");
    break;
  case 5:   
    Serial.println("--------------|-");
    break;
  case 6:   
    Serial.println("--------------|---");
    break;
  case 7:   
    Serial.println("--------------|-------");
    break;
  case 8:  
    Serial.println("--------------|----------");
    break;
  case 9:    
    Serial.println("--------------|----------------");
    break;
  case 10:   
    Serial.println("--------------|-------------------");
    break;
  case 11:   
    Serial.println("--------------|-----------------------");
    break;
  } 
}


