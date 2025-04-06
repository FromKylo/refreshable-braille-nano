// Braille pins for 3 cells
const int braillePins[3][6] = {
    {2, 3, 4, 5, 6, 7},       // Braille Cell 1
    {8, 9, 10, 11, 12, 13},   // Braille Cell 2
    {17, 18, 19, 20, 21, 22}  // Braille Cell 3
  };
  
  // Fast test patterns
  const byte testPatterns[][6] = {
    {1,0,0,0,0,0},    // 1
    {0,1,0,0,0,0},    // 1
    {0,0,1,0,0,0},    // 1
    {0,0,0,1,0,0},    // 1
    {1,0,0,0,1,0},    // 1
    {0,0,0,0,0,1},    // 1
    {1,1,0,0,0,0},    // 1
    {1,1,1,0,0,0},    // 1
    {1,1,1,1,1,0},    // 1
    {1,1,1,1,1,1},    // 1
  };
  
  const int numPatterns = sizeof(testPatterns) / sizeof(testPatterns[0]);
  const int rippleDelay = 100;  // Delay per dot in ms
  
  void setup() {
    Serial.begin(115200);
    Serial.println("Braille Cell Dot Test Starting...");
  
    for (int cell = 0; cell < 3; cell++) {
      for (int dot = 0; dot < 6; dot++) {
        pinMode(braillePins[cell][dot], OUTPUT);
      }
    }
  }
  
  void loop() {
    for (int p = 0; p < numPatterns; p++) {
      Serial.print("Pattern ");
      Serial.print(p + 1);
      Serial.print(": ");
      for (int d = 0; d < 6; d++) {
        Serial.print(testPatterns[p][d]);
      }
      Serial.println();
  
      // Raise dots with ripple effect
      for (int cell = 0; cell < 3; cell++) {
        for (int dot = 0; dot < 6; dot++) {
          digitalWrite(braillePins[cell][dot], testPatterns[p][dot]);
          Serial.print("Raise cell ");
          Serial.print(cell + 1);
          Serial.print(" dot ");
          Serial.print(dot + 1);
          Serial.print(" → pin ");
          Serial.print(braillePins[cell][dot]);
          Serial.print(" = ");
          Serial.println(testPatterns[p][dot]);
          delay(rippleDelay);
        }
      }
  
      delay(2000);  // Hold pattern
  
      // Lower dots with ripple effect
      for (int cell = 0; cell < 3; cell++) {
        for (int dot = 0; dot < 6; dot++) {
          digitalWrite(braillePins[cell][dot], LOW);
          Serial.print("Lower cell ");
          Serial.print(cell + 1);
          Serial.print(" dot ");
          Serial.print(dot + 1);
          Serial.print(" → pin ");
          Serial.print(braillePins[cell][dot]);
          Serial.println(" = 0");
          delay(rippleDelay);
        }
      }
  
      Serial.println("All dots cleared.\n");
      delay(1000);
    }
  }
  