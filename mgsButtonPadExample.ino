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
  blank();  
  digitalWrite(_SCK_Pin, HIGH);
  digitalWrite(_CS_Pin, HIGH);
  delay(240);

  // Set lights: 3 x 16 bytes
  setLights();

  if (!ready) {
    wait = true;
    ready = true;
  }

  if(ready)readButtons();
  handleButtonPress();
  
  digitalWrite(_CS_Pin, LOW);

  // After the second cycle, get ready to read new button presses.
  if (wait) {
    delay(500);
    wait = false;
    ready = true;
  }

  //delayMicroseconds(400);
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

void handleButtonPress(){
  switch(currentButton){
    case 0:
      // Do Stuff For Button 0
      
    break;
    case 1:
      // Do Stuff For Button 1
      
    break;
    case 2:
      // Do Stuff For Button 2
      
    break;
    case 3:
      // Do Stuff For Button 3
      
    break;
    case 4:
      // Do Stuff For Button 4
      
    break;
    case 5:
      // Do Stuff For Button 5
      
    break;
    case 6:
      // Do Stuff For Button 6
      
    break;
    case 7:
      // Do Stuff For Button 7
      
    break;
    case 8:
      // Do Stuff For Button 8
      
    break;
    case 9:
      // Do Stuff For Button 9
      
    break;
    case 10:
      // Do Stuff For Button 10
      
    break;
    case 11:
      // Do Stuff For Button 11
      
    break;
    case 12:
      // Do Stuff For Button 12
      
    break;
    case 13:
      // Do Stuff For Button 13
      
    break;
    case 14:
      // Do Stuff For Button 14
      
    break;
    case 15:
      // Do Stuff For Button 15
      
    break;
  }

