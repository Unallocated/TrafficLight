#include <Bridge.h>

#define one 6; //light 1
#define two 7;
#define three 8;
#define four 9;

int pins[4] = {6, 7, 8, 9};

char lights[4];

void setup()
{
  Bridge.begin();
  Serial.begin(9600);
}

void loop()
{
  int y;
  y = Bridge.get("stoplight", lights, 4);
  
  for (int i=0; i<=3; i++)
  {
    if (lights[i] == char('1'))
    {
      digitalWrite (13, HIGH);
      Serial.println ('1');
    }
    else if (lights[i] == char('0'))
    {
      digitalWrite (13, LOW);
      Serial.println ('0');
    }
  }
  Serial.println("---------------------");

  delay(200);  
}
