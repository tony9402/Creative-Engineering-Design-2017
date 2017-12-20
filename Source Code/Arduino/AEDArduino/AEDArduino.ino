#include<SoftwareSerial.h> //다른 핀에서 Serial통신을 하기 위해 불러오는 header파일
//삼색 LED를 아두이노에 연결한 핀 번호들
#define Red 9
#define Red2 11
#define Green 5
#define Green2 10
#define Blue 6
#define Blue2 3

SoftwareSerial BTSerial(8,7); // 7번과 8번에서 Tx, Rx로 사용하기 위해 선언하는 함수

int LED[2][3] = {Red,Green,Blue,Red2,Green2,Blue2}; //for문 제어 할 때 편하게 제어 하기 위한 2차원 배열

void setup()
{
  for(int i=0;i<2;i++){ //LED와 연결된 PIN을 OUTPUT으로 설정한 후 모든 LED가 꺼져 있는 상태로 설정    
    for(int j=0;j<3;j++){
      pinMode(LED[i][j], OUTPUT);
      digitalWrite(LED[i][j],LOW);
    }
  }
  Serial.begin(9600); //Serial통신 속도(라즈베리파이와 통신 속도)
  BTSerial.begin(9600); //7,8으로 쓰이는 핀 Serial 통신 속도(자두이노와 통신 속도)
}

void loop(){
  int num = 0; //Serial 통신으로 자두이노에서 받은 BPM을 저장하는 변수
  int chk = 0; //LED의 깜박거림을 제어하는 변수
  int light = 0; //PWM을 이용하여 LED 밝기 조절
  int checkColor=0; //색깔을 제어하기 위한 변수
  int countValue = 0; //노래가 틀어지는 동안 깜박이도록 범위를 설정해주는 변수
  if(BTSerial.available()){ //BTSerial통신에서 읽을 값이 있을때
    num = BTSerial.read() + 40; //BTSerial통신을 할 때 char형으로 통신을 하는데 값이 손실 되거나 꺠지는 것을 방지한 것을 복구 시키는 과정
    if(num < 150 && num > 40){ //측정된 BPM값이 40~150 사이일 때
      Serial.println(num); //라즈베리파이가 읽을 수 있게 Serial모니터에 출력
      countValue = num * 2; //노래가 끝날때 까지 LED가 깜밖거릴수 있게 하는 변수
      while(chk++ <= countValue){ //노래가 끝날때까지 반복
        while(light+=5<255){ //밝기 조절(0(off)에서 시작하여 255(on)까지 pwm을 이용)
          if(checkColor == 0){ //빨간색
            analogWrite(Red,light);
            analogWrite(Red2,light);
          }else if(checkColor == 1){ //초록색
            analogWrite(Green,light);
            analogWrite(Green2,light);
          }/*else if(checkColor == 2){ //파란색
            analogWrite(Blue,light);
            analogWrite(Blue2,light);
          }*/
          if(light+5>255){ //255보다 큰값은 없으므로 light+=5하기 전에 while문 탈출
                           //이때 탈출 못하면 오류 및 계속 돌게 됨
            break;
          }
          delay(4.69 * 60 / num); //BPM에 맞게 깜박거리도록 직접 실행해보면서 계산된 식
        }
        light = 0;//LED OFF 및 초기화
        
        checkColor = 1 - checkColor; //checkColor = 0이면 checkColor = 1으로 checkColor = 1이면 checkColor = 0으로 값을 바꿈
        //모든 LED OFF
        digitalWrite(Red,LOW); 
        digitalWrite(Red2,LOW);
        digitalWrite(Green,LOW);
        digitalWrite(Green2,LOW);
        digitalWrite(Blue,LOW);
        digitalWrite(Blue2,LOW);
      }
    }
  }
}
