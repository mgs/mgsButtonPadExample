// The wires
int _CS_Pin = 10;
int _MISO_Pin = 11;
int _MOSI_Pin = 12;
int _SCK_Pin = 13;

int currentButton = -1;
// Frame buffer for lights
int lights = 16;
int depth = 3;
byte buf[16][3];

boolean wait = false;
boolean ready = true;

int red = 0;
int green = 1;
int blue = 1;

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
  //  setColor(light1Counter, random(red), random(green), random(blue));
  //  setColor(random(red), random(green), random(blue), 1);
  Serial.println("X: " + String(xCounter) + "\n" + "Y: " + String(yCounter) + "\n");
  delay(240);

  // Set lights: 3 x 16 bytes
  setLights();

  if (!ready) {
    wait = true;
    ready = true;
  }

  if(ready)readButtons();

  digitalWrite(_CS_Pin, LOW);

  // After the second cycle, get ready to read new button presses.
  if (wait) {
    delay(500);
    wait = false;
    ready = true;
  }

  delayMicroseconds(400);
}

void setLights(){
  for (int d = 0; d < depth; d++) {
    for (int l = 0; l < lights; l++) {
      writeByte(buf[l][d]);
    }
  }
}

void readButtons(){
  // Read the buttons: 16 bytes.
  for (int l = 0; l < lights; l++) {
    // readByte returns a non-zero value when a button is pressed.
    byte b = readByte();
    currentButton = int(l);
    // If a button is pressed, change the color.
    Serial.print("Button ");
    Serial.print(l);
    Serial.print(": ");
    Serial.println(int(b));

    ready = false;
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


