#define ledPin 13 //LED는 디지털 핀 13에 연결됨
#define LINE_DETECT_WHITE 1

int linesensor_data[5] = {0,0,0,0,0}; // 읽은 값을 저장할 변수
int linesensor_pin[5] = {2,3,4,5,6}; // int 형 배열

int read_digital_line_sensor(void)
{
  int i;
  int sum = 0;
  for(i=0;i<5;i++)
  {
    if(LINE_DETECT_WHITE == 0) //흰색 바탕에 검정색 라인
    {
      linesensor_data[1] = 1 - digitalRead(linesensor_pin[i]);
    }
    else
    {
      linesensor_data[i] =      digitalRead(linesensor_pin[i]);
    }
  sum += linesensor_data[i];
  }
  if(sum == 5)
  {
    return sum;
  }
  else if(sum == 2)
  {
    if( (linesensor_data[3] == 1) && (linesensor_data[4] == 1) ) return 3;
    if( (linesensor_data[2] == 1) && (linesensor_data[3] == 1) ) return 1;
    if( (linesensor_data[1] == 1) && (linesensor_data[2] == 1) ) return -1;
    if( (linesensor_data[0] == 1) && (linesensor_data[1] == 1) ) return -3;
  }
  else if(sum == 1)
  {
    if(linesensor_data[0] == 1) return -4;
    if(linesensor_data[1] == 1) return -2;
    if(linesensor_data[2] == 1) return 0;
    if(linesensor_data[3] == 1) return 2;
    if(linesensor_data[4] == 1) return 4;
  }
  else if(sum == 3)
  {
    return -10;
  }
  else
  {
    return -5;
  }

}

void setup() {
  int i;
  pinMode(ledPin, OUTPUT);      //디지털 핀 13을 출력
  for(i=0;i<5;i++)
  {
    pinMode(linesensor_pin[i], INPUT);    // 디지털 linesensor_pin들을 입력으로 설정
  }
  Serial.begin(9600);
}

void loop() {
  int i;
  int sum =0;
  sum = read_digital_line_sensor();       // line read 함수 실행

  Serial.print("Input data = ");
  for(i=0;i<5;i++)
  {
    Serial.print(linesensor_data[i]);
    Serial.print("  ");
  }
  Serial.print(sum);          //sum 값 출력
  Serial.println("  ");       // 줄 바꿈
  
}