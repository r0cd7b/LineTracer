const unsigned int LEFT_PIN = 4;  // 왼쪽 조도 센서 핀
const unsigned int RIGHT_PIN = 5;  // 오른쪽 조도 센서 핀

// Control Motor 핀
const unsigned int ENA = 10;
const unsigned int IN1 = 6;
const unsigned int IN2 = 7;
const unsigned int IN3 = 8;
const unsigned int IN4 = 9;
const unsigned int ENB = 11;

const unsigned int TOP_SPEED = 255;  // 작동 가능한 최고 속력
const unsigned int MINIMUM_SPEED = 150;  // 작동 가능한 최저 속력

unsigned int horizontal_lines = 9;  // 중지선 개수

void setup()
{
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop()
{
  bool left_black = digitalRead(LEFT_PIN); // 왼쪽 센서가 검은 선을 판단
  bool right_black = digitalRead(RIGHT_PIN); // 오른쪽 센서가 검은 선을 판단

  if (horizontal_lines)  // 남은 중지선 개수를 확인
  {
    if (left_black && right_black)  // 왼쪽과 오른쪽 모두 검은 선일 경우
    {
      if (--horizontal_lines) {  // 아직 중지선이 남았다면 수행
        straight();  // 200ms 동안 직진.
        delay(200);
      }
    }
    else if (left_black && !right_black)  // 왼쪽은 검은 선이고 오른쪽은 흰 선일 경우
    {
      left();  // 좌회전 수행
    }
    else if (!left_black && right_black)  // 왼쪽은 흰 선이고 오른쪽은 검은 선일 경우
    {
      right();  // 우회전 수행
    }
    else  // 왼쪽과 오른쪽 모두 흰 선일 경우
    {
      straight();  // 직진 수행
    }
  }
  else  // 남은 중지선 개수가 0이면 정지
  {
    stop_driving();  // 운전 정지
  }
}

void stop_driving() {  // 정지 함수
  analogWrite(ENB, TOP_SPEED);
  analogWrite(ENA, TOP_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void straight() {  // 직진 함수
  analogWrite(ENB, MINIMUM_SPEED);
  analogWrite(ENA, MINIMUM_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void left() {  // 좌회전 함수
  analogWrite(ENB, MINIMUM_SPEED);
  analogWrite(ENA, TOP_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void right() {  // 우회전 함수
  analogWrite(ENB, TOP_SPEED);
  analogWrite(ENA, MINIMUM_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}
