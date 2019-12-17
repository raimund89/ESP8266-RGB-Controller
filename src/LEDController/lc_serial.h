#ifndef LC_SERIAL
#define LC_SERIAL

void InitSerial()
{
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println("Skynet LED Controller");
  Serial.println("Starting...");
}

#endif
