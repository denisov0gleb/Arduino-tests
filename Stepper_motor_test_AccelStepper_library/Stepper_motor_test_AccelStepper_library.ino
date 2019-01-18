#include <AccelStepper.h>

AccelStepper Stepper1(1,7,6); //использует пин 12 и 13 для dir и step, 1 - режим "external driver" (A4988)

int dir = 1; //используется для смены направления

void setup()
{
  Stepper1.setSpeed(50);
  Stepper1.setMaxSpeed(100); //устанавливаем максимальную скорость вращения ротора двигателя (шагов/секунду)
  Stepper1.setAcceleration(150); //устанавливаем ускорение (шагов/секунду^2)
}

void loop()
{
  if(Stepper1.distanceToGo()==0)
  { //проверка, отработал ли двигатель предыдущее движение

    Stepper1.move(400);
    //dir = dir*(-1); //отрицательное значение dir, благодаря чему реализуется вращение в противоположном направлении
    delay(1000);
  }
  Stepper1.run();
}

