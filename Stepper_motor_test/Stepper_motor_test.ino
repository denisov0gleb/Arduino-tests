int stp = 13; //подключите 13 пин к step

int dir = 12; //подключите 12 пин к dir

int a = 0;

void setup()

{
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
}

void loop()

{
  if (a < 200) // вращение на 200 шагов в направлении 1
  {
    a++;
    digitalWrite(stp, HIGH);
    delay(10);
    digitalWrite(stp, LOW);
    delay(10);
  }
  else
  {
    digitalWrite(dir, HIGH);
    a++;
    digitalWrite(stp, HIGH);
    delay(10);
    digitalWrite(stp, LOW);
    delay(10);
    if (a>400) // вращение на 200 шагов в направлении 2
    {
      a = 0;
      digitalWrite(dir, LOW);
    }
  }
}
