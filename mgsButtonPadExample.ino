// The wires
int _CS_Pin = 10;
int _MISO_Pin = 11;
int _MOSI_Pin = 12;
int _SCK_Pin = 13;

int red = 0;
int green = 1;
int blue = 255;

// Frame buffer for lights
int lights = 16;
int depth = 3;
byte buf[16][3];

int yCounter = 0;
int xCounter = 0;

int light1Counter = 0;
int light2Counter = 15;
int light3Counter = 4;
int light4Counter = 11;

int maxX = 16;
int maxY = 3;

int mainMode = 1;
int mode = 1;

boolean wait = false;
boolean ready = true;

void setup() {
  pinMode(_CS_Pin, OUTPUT);
  pinMode(_MISO_Pin, OUTPUT);
  pinMode(_MOSI_Pin, INPUT);
  pinMode(_SCK_Pin, OUTPUT);

  digitalWrite(_CS_Pin, LOW);
  delay(500);

  blank();

  Serial.begin(9600);
}

void blank() {
  // init frame buffer
  for (int l = 0; l < lights; l++) {
    for (int d = 0; d < depth; d++) {
      buf[l][d] = 0;
    }
  }
}

void setColor(int l, int r, int g, int b) {
  buf[l][0] = r;
  buf[l][1] = g;
  buf[l][2] = b;
}

void loop() {
  //if (ready)
  //Serial.print(digitalRead(7));
  blank();
  mode = random(2);
  digitalWrite(_SCK_Pin, HIGH);
  digitalWrite(_CS_Pin, HIGH);
  setColor(light1Counter, random(red), random(green), random(blue));
  switch (mainMode) {
    case 0:
      if (light1Counter < 15) {
        light1Counter++;
      } else {
        light1Counter = 0;
      }
    case 1:
      switch (mode) {
        case 0:
          if (millis() % 20 != 0) {
            tone(9   , random(1000, 1100), 2);
            green = 255;
            blue = 0;
            red = 0;
          } else {
            blue = 255;
            green = 255;
            red = 255;
            for (int i = 0; i < 10; i++) {
              tone(9   , random(800, 900), 10);
              delay(1);
            }
          }
          if (light1Counter < 15) {
            light1Counter++;
          } else {
            light1Counter = 0;
          }
          break;
        case 1:
          if (millis() % 10 == 0) {
            tone(9   , random(1000, 1100), 2);
            green = 255;
            blue = 0;
            red = 0;
          } else {
            blue = 255;
            green = 0;
            red = 0;
            tone(9   , random(800, 900), 1);
          }
          if (light1Counter > 0) {
            light1Counter--;
          } else {
            light1Counter = 15;
          }
          break;
      }
      if (random(100) > 50) {
        setColor(light3Counter, random(red), random(green), random(blue));
        switch (mode) {
          case 0:
            if (millis() % random(20) != 0) {
              tone(9   , random(1000, 1100), 2);
              green = 255;
              blue = 0;
              red = 0;
            } else {
              blue = 255;
              green = 255;
              red = 255;
              for (int i = 0; i < 10; i++) {
                tone(9   , random(800, 900), 10);
                delay(1);
              }
            }
            if (light3Counter < 15) {
              light3Counter++;
            } else {
              light3Counter = 0;
            }
            break;
          case 1:
            if (millis() % random(10) == 0) {
              tone(9   , random(1000, 1100), 2);
              green = 255;
              blue = 0;
              red = 0;
            } else {
              blue = 255;
              green = 0;
              red = 0;
              tone(9   , random(800, 900), 1);
            }
            if (light3Counter > 0) {
              light3Counter--;
            } else {
              light3Counter = 15;
            }
            break;
        }
      }
      if (random(100) > 50) {
        switch (mode) {
          case 0:
            if (millis() % random(20) != 0) {
              tone(9   , random(100, 400), 20);
              green = 255;
              blue = 0;
              red = 0;
            } else {
              blue = 255;
              green = 255;
              red = 255;
              for (int i = 0; i < 10; i++) {
                tone(9   , random(400, 800), 20);
                delay(1);
              }
            }
            if (light4Counter < 15) {
              light4Counter++;
            } else {
              light4Counter = 0;
            }
            break;
          case 1:
            if (millis() % random(10) == 0) {
              tone(9   , random(1000, 1100), 2);
              green = 255;
              blue = 0;
              red = 0;
            } else {
              blue = 255;
              green = 0;
              red = 0;
              tone(9   , random(800, 900), 1);
            }
            if (light4Counter > 0) {
              light4Counter--;
            } else {
              light4Counter = 15;
            }
            break;
        }
        
      }
      //setColor(light2Counter, random(red), random(green), random(blue));
      switch (mode) {
        case 0:
          if (millis() % 2 == 0) {
            tone(9   , random(100, 200), 1000);
            green = 255;
            blue = 0;
            red = 0;

          } else {
            tone(9   , random(200, 300), 1);
            blue = 255;
            green = 0;
            red = 0;

          }
          if (light2Counter > 0) {
            light2Counter--;
          } else {
            light2Counter = 15;
          }
          break;
        case 1:
          if (millis() % 2 == 0) {
            tone(9   , random(0, 100), 1000);
            green = 0;
            blue = 255;
            red = 0;

          } else {
            tone(9   , random(400, 500), 1);
            blue = 255;
            green = 0;
            red = 0;

          }
          if (light2Counter < 15) {
            light2Counter++;
          } else {
            light2Counter = 0;
          }
          break;
      }
      setColor(light2Counter, random(red), random(green), random(blue));
      break;
  }
  Serial.println("X: " + String(xCounter) + "\n" + "Y: " + String(yCounter) + "\n");
  delay(240);
    if (random(10) > 5) {
      for (int i = 0; i < random(10); i++) {
        //setColor(random(4), random(13), random(red), random(green), random(blue));
  
        //      tone(9, random(880, 1340), 1);
        //      delay(50);
        //      tone(9, random(880, 1340), 1);
        //      delay(50);
  
        delay(random(90));
      }
    } else {
      for (int i = 0; i < random(10); i++) {
        //setColor(random(4), random(13), random(red), random(green), random(blue));
        delay(random(90));
      }
    }

  // Set lights: 3 x 16 bytes
  for (int d = 0; d < depth; d++) {
    for (int l = 0; l < lights; l++) {
      writeByte(buf[l][d]);
    }
  }

  if (!ready) {
    wait = true;
    ready = true;
  }

  if(ready)readButtons();

  digitalWrite(_CS_Pin, LOW);

  // After the second cycle, get ready to read new button clicks.
  if (wait) {
    delay(500);
    wait = false;
    ready = true;
  }

  delayMicroseconds(400);
}

void readButtons(){
    // Read the buttons: 16 bytes.
  for (int l = 0; l < lights; l++) {
    // readByte returns a non-zero value when a button is pressed.
    byte b = readByte();

    // If a button is pressed, change the color.
    if (b > 0 && ready && !wait) {
      if      (buf[l][2] > 0) {
        buf[l][2] = 0;
        tone(9, random(220, 440), 1);
        delay(50);
        tone(9   , random(440, 880), 1);
        delay(50);
      } else if (buf[l][1] > 0) {
        buf[l][1] = 0;
        buf[l][2] = 255;
        tone(9, random(440, 880), 1);
        delay(50);
        tone(9, random(220, 440), 1);
        delay(50);
      } else if (buf[l][0] > 0) {
        buf[l][0] = 0;
        buf[l][1] = 255;
        tone(9, random(880, 1340), 1);
        delay(50);
        tone(9, random(880, 1340), 1);
        delay(50);
      } else {
        buf[l][0] = 255;
        tone(9, random(880, 1340), 1);
        delay(50);
        tone(9, random(880, 1340), 1);
        delay(50);
      }

      Serial.print("Button ");
      Serial.print(l);
      Serial.print(": ");
      Serial.print((int)b);
      Serial.println();

      // Change colours slowly.
      ready = false;
    }
  }
}

// Write out a byte.
// This is for a single colour channel, for a single button.
void writeByte(byte data) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(_SCK_Pin, LOW);
    delayMicroseconds(5);

    digitalWrite(_MISO_Pin, (data & (1 << i)) >> i);
    delayMicroseconds(5);

    digitalWrite(_SCK_Pin, HIGH);
    delayMicroseconds(10);
  }
}

// Read a byte.
// Returns the value for a single button.
// Non-zero if it is pressed, or 0 otherwise.
byte readByte() {
  byte result = 0;
  for (int i = 0; i < 8; i++) {
    digitalWrite(_SCK_Pin, LOW);
    delayMicroseconds(5);

    result += (!digitalRead(_MOSI_Pin)) * i;
    delayMicroseconds(5);

    digitalWrite(_SCK_Pin, HIGH);
    delayMicroseconds(10);
  }

  return result;
}
