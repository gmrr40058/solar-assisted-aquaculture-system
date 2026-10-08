#include <Servo.h>

Servo servohori; //horizontal servo(BOTTOM SERVO)
int servoh = 0; //assign servo at 0 degree
int servohLimitHigh = 180; //maximum range of servo is 180 degree(it is variable you can also change)
int servohLimitLow = 0;   //minimum range of servo is 10 degree(it is variable you can also change)

Servo servoverti; //vertical servo(TOP SERVO)
int servov = 0;
int servovLimitHigh = 180;
int servovLimitLow = 0;

int ldrtopr = 1; //top right LDR A1 pin
int ldrtopl = 2; //top left LDR A2 pin

int ldrbotr = 0; // bottom right LDR A0 pin
int ldrbotl = 3; // bottom left LDR A3 pin

int flag = 0;


void setup ()
{
  servohori.attach(10); //horizontal servo connected to arduino pin 10
  servohori.write(90);

  servoverti.attach(9); //vertical servo connected to arduino pin 9
  servoverti.write(90);
  delay(500); //delay
  Serial.begin(9600);
}

void loop()
{
  servoh = servohori.read();
  servov = servoverti.read();


  int topl = analogRead(ldrtopl); //read analog values from top left LDR
  int topr = analogRead(ldrtopr); //read analog values from top right LDR
  int botl = analogRead(ldrbotl); //read analog values from bottom left LDR
  int botr = analogRead(ldrbotr); //read analog values from bottom right LDR


  Serial.print("Top left:");
  Serial.println(topl);
  Serial.print("Top Right:");
  Serial.println(topr);

  Serial.print("bottom left:");
  Serial.println(botl);
  Serial.print("bottom Right:");
  Serial.println(botr);

  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs







  if (avgtop > avgbot)
  {
    servoverti.write(servov - 1);
    if (servov > servovLimitHigh)
    {
      servov = servovLimitHigh;
    }
    delay(8);
  }
  else if (avgbot > avgtop)
  {
    servoverti.write(servov + 1);
    if (servov < servovLimitLow)
    {
      servov = servovLimitLow;
    }
    delay(8);
  }
  else
  {
    servoverti.write(servov);
  }


  //  Serial.print("\nhori posi:");
  //  Serial.println(servoh);
  //  Serial.print("verti posi:");
  //  Serial.println(servov);
  Serial.print("Flag:");
  Serial.println(flag);



  //  Serial.print("\nTop-Left:");
  //  Serial.println(topl);
  //    Serial.print("Bottom-Left:");
  //  Serial.println(botl);
  //  Serial.print("Top-Right:");
  //  Serial.println(topr);
  //    Serial.print("Bottom-Right:");
  //  Serial.println(botr);



  ////flagggggggggggggggggggggggggggggggg
  if (flag == 1) {

    if (avgleft < avgright)
    {
      servohori.write(servoh - 1);
      if (servoh <= servohLimitLow)
      {
        servoh = servohLimitLow;
        flag = 0;

      }
      delay(8);
    }
    else if (avgright < avgleft)
    {
      servohori.write(servoh + 1);
      if (servoh >= servohLimitHigh)
      {
        servoh = servohLimitHigh;
        flag = 0;
        //        delay(1000);

      }
      delay(8);
    }
    else
    {
      servohori.write(servoh); // write means run servo
    }
    delay(50);

  }
  //new
  if (flag == 0) {

    if (avgleft < avgright)
    {
      servohori.write(servoh + 1);
      if (servoh >= servohLimitHigh)
      {
        servoh = servohLimitHigh;
        //        servohori.write(5);
        //        servoverti.write(60);
        flag = 1;
      }
      delay(8);
    }
    else if (avgright < avgleft)
    {
      servohori.write(servoh - 1);
      if (servoh <= servohLimitLow)
      {
        servoh = servohLimitLow;
        //        servohori.write(175);
        //        servoverti.write(140);
        flag = 1;
      }
      delay(8);
    }
    else
    {
      servohori.write(servoh); // write means run servo
    }
    delay(50);

  }








}
