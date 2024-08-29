#include "CableTesters.h"


void TestCable::begin(bool Display_Enable, uint8_t PinErrorLED, uint8_t PinPassLED)
{
  if (Display_Enable)
  {
    #ifdef USE_LEDS
    #undef USE_LEDS
    #endif
  }
  else
  {
    #ifndef USE_LEDS
    #define USE_LEDS
    #endif
  }
}

void TestCable::SetPinsPullUP(uint8_t* PinsToSet, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
    pinMode(PinsToSet[i],INPUT_PULLUP);
    }
}   

void TestCable::SetPinsPullDown(uint8_t* PinsToSet, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    pinMode(PinsToSet[i],INPUT_PULLDOWN);
  }
}

void TestCable::SetPinsOutput(uint8_t* PinsToSet, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    pinMode(PinsToSet[i],OUTPUT);
  }
}

void TestCable::SetPinsLOW(uint8_t* PinsToSet, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    digitalWrite(PinsToSet[i],LOW);
  }
}

void TestCable::SetPinsHIGH(uint8_t* PinsToSet, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    digitalWrite(PinsToSet[i],HIGH);
  }
}


void TestCable::BlinkLED_fast(uint8_t pinNo, int times)
{
  for(int j=0; j < times; j++)
  {
    digitalWrite(pinNo, 1);
    delay(70);
    digitalWrite(pinNo, 0);
    delay(70);
  }
} 

void TestCable::BlinkLED_slow(uint8_t pinNo, int times)
{
  for(int j=0; j < times; j++)
  {
    digitalWrite(pinNo, 1);
    delay(300);
    digitalWrite(pinNo, 0);
    delay(300);
  }
}

void TestCable::BlinkLED_fast_inv(uint8_t pinNo, int times)
{
  for(int j=0; j < times; j++)
  {
    digitalWrite(pinNo, 0);
    delay(70);
    digitalWrite(pinNo, 1);
    delay(70);
  }
}

void TestCable::BlinkLED_slow_inv(uint8_t pinNo, int times)
{
  for(int j=0; j < times; j++)
  {
    digitalWrite(pinNo, 0);
    delay(300);
    digitalWrite(pinNo, 1);
    delay(300);
  }
}

void TestCable::SetErrorLEDS(uint8_t PinErrorLED, uint8_t PinPassLED)
{
  digitalWrite(PinPassLED, LOW);
  digitalWrite(PinErrorLED, HIGH);
  while(1);
}


void TestCable::SetPassLEDS(uint8_t PinErrorLED, uint8_t PinPassLED)
{
  digitalWrite(PinErrorLED, LOW);
  for(int i=0; i<5; i++)
  {
    digitalWrite(PinPassLED, HIGH);
    delay(500);
    digitalWrite(PinPassLED, LOW);
    delay(500);
  }
}

uint8_t TestCable::ShortsConfirm(uint8_t* pins, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    pinMode(pins[i],OUTPUT);
    digitalWrite(pins[i],LOW);
    delay(1);
    for (size_t j = 0; j < size; j++)
    {
      if(j!=i)  pinMode(pins[j],INPUT_PULLUP);
    }
    delay(1);
    for (size_t j = 0; j < size; j++)
    {
      if(j==i) continue;
      if(digitalRead(pins[j]))
      {
        pinMode(pins[i],INPUT_PULLUP);
        delay(1);
        return 1; //Short not found
      }
    }
    pinMode(pins[i],INPUT_PULLUP);
    delay(1);
  }
  return 0; //No error
}

uint8_t TestCable::NCConfirm(uint8_t* pins, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    pinMode(pins[i],OUTPUT);
    digitalWrite(pins[i],LOW);
    delay(1);
    for (size_t j = 0; j < size; j++)
    {
      if(j!=i)  pinMode(pins[j],INPUT_PULLUP);
    }
    delay(1);
    for (size_t j = 0; j < size; j++)
    {
      if(j==i) continue;
      if(!digitalRead(pins[j]))
      {
        pinMode(pins[i],INPUT_PULLUP);
        delay(1);
        return 1; //Short found error
      }
    }
    digitalWrite(pins[i],HIGH);
    delay(1);
    pinMode(pins[i],INPUT_PULLUP);
    delay(1);
  }
  return 0; //No error
}

uint8_t TestCable::DiodeTest(uint8_t* Anode, size_t size_A, uint8_t* Cathode, size_t size_C)
{
  SetPinsPullDown(Anode, sizeof(size_A));
  SetPinsOutput(Cathode, sizeof(size_C));
  SetPinsHIGH(Cathode, sizeof(size_C));
  delay(1);
  if(digitalRead(Anode[0]))
  {
    Serial.print("Diode is reversed or shorted");  
    Serial.println();
    SetPinsPullUP(Anode, sizeof(size_A));
    SetPinsPullUP(Cathode, sizeof(size_C));
    return 1;
  }
  SetPinsPullDown(Cathode, sizeof(size_C));
  SetPinsOutput(Anode, sizeof(size_A));
  SetPinsLOW(Anode, sizeof(size_A));
  delay(1);
  if(digitalRead(Cathode[0]))
  {
    Serial.println("Diode error!");
    SetPinsPullUP(Anode, sizeof(size_A));
    SetPinsPullUP(Cathode, sizeof(size_C));
    return 1;
  }
  SetPinsHIGH(Anode, sizeof(size_A));
  delay(1);
  if(digitalRead(Cathode[0]))
  {
    Serial.print("Diode ok!");  
    Serial.println();
    SetPinsPullUP(Anode, sizeof(size_A));
    SetPinsPullUP(Cathode, sizeof(size_C));
    return 0;
  }
  else
  {
    Serial.print("Diode is open");  
    Serial.println();
    SetPinsPullUP(Anode, sizeof(size_A));
    SetPinsPullUP(Cathode, sizeof(size_C));
    return 1;
  }
  return 1;
} 

uint8_t TestCable::CableDetect(uint8_t SetDetection, uint8_t DetectionPin)
{
  pinMode(SetDetection, OUTPUT);
  pinMode(DetectionPin, INPUT_PULLUP);
  digitalWrite(SetDetection, LOW);
  if(!digitalRead(DetectionPin))
  {
    Serial.println("Cable detected");
    pinMode(SetDetection, INPUT_PULLUP);
    return 0;
  }
  else
  {
    return 1;
  }
}