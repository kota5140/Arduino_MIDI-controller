// long position1  = -999;
// long position2  = -999;
// long position3  = -999;
// long position4  = -999;
// int encVals[4] = {64, 64, 64, 64}; // set initial value of encoder (for four rotator) to mid range of 0-127

// int cVal = 0;

const int gain1 = A0;
const int gain2 = A1;
const int lowpot1 = A2;
const int lowpot2 = A3;
const int CFX1 = A4;
const int CFX2 = A5;

const int startButton1 = 2;
const int startButton2 = 3;
const int CUEButton1 = 4;
const int CUEButton2 = 5;

int previousStartButton1 = LOW;
int previousStartButton2 = LOW;
int previousCUEButton1 = LOW;
int previousCUEButton2 = LOW;

int lastGainVal1 = 0;
int lastGainVal2 = 0;
int lastLowPotVal1 = 0;
int lastLowPotVal2 = 0;
int lastCFXVal1 = 0;
int lastCFXVal2 = 0;


//void readEncoder();
void readButton();
void readPots();

void setup() {
  Serial.begin(115200);
  pinMode(startButton1, INPUT);
  pinMode(startButton2, INPUT);
  pinMode(CUEButton1, INPUT);
  pinMode(CUEButton2, INPUT);
  pinMode(gain1, INPUT);
  pinMode(gain2, INPUT);
  pinMode(lowpot1, INPUT);
  pinMode(lowpot2, INPUT);
  pinMode(CFX1, INPUT);
  pinMode(CFX2, INPUT);
}


void loop() {
  //readEncoder();
  readButton();
  readPots();
}

void readButton() { // ボタンの設定

  int kpc = 128;

  int currentstartButton1 = digitalRead(startButton1);
  int currentstartButton2 = digitalRead(startButton2);
  int currentCUEButton1 = digitalRead(CUEButton1);
  int currentCUEButton2 = digitalRead(CUEButton2);

  if (currentstartButton1 != previousStartButton1) {
    if (currentstartButton1 == HIGH) {
      MIDImessage(kpc, 11, 127);
    } else {
      MIDImessage(kpc, 11, 0);
    }
    previousStartButton1 = currentstartButton1;
  }

  if (currentstartButton2 != previousStartButton2) {
    if (currentstartButton2 == HIGH) {
      MIDImessage(kpc + 1, 11, 127);
    } else {
      MIDImessage(kpc + 1, 11, 0);
    }
    previousStartButton2 = currentstartButton2;
  }

  if (currentCUEButton1 != previousCUEButton1) {
    if (currentCUEButton1 == HIGH) {
      MIDImessage(kpc, 12, 127);
    } else {
      MIDImessage(kpc, 12, 0);
    }
    previousCUEButton1 = currentCUEButton1;
  }

  if (currentCUEButton2 != previousCUEButton2) {
    if (currentCUEButton2 == HIGH) {
      MIDImessage(kpc + 1, 12, 127);
    } else {
      MIDImessage(kpc + 1, 12, 0);
    }
    previousCUEButton2 = currentCUEButton2;
  }

}

void readPots() {

  int diff = 50;
  int kpc = 160; //A0

  int gainVal1 = analogRead(gain1);
  int gainVal2 = analogRead(gain2);
  int lowPotVal1 = analogRead(lowpot1);
  int lowPotVal2 = analogRead(lowpot2);
  int CFXVal1 = analogRead(CFX1);
  int CFXVal2 = analogRead(CFX2);

  if (abs(gainVal1 - lastGainVal1) > diff) {
    MIDImessage(kpc, 4, map(gainVal1, 0, 1023, 0, 127));
    lastGainVal1 = gainVal1;
  }

  if (abs(gainVal2 - lastGainVal2) > diff) {
    MIDImessage(kpc + 1, 4, map(gainVal2, 0, 1023, 0, 127));
    lastGainVal2 = gainVal2;
  }

  if (abs(lowPotVal1 - lastLowPotVal1) > diff) {
    MIDImessage(kpc, 15, map(lowPotVal1, 0, 1023, 0, 127));
    lastLowPotVal1 = lowPotVal1;
  }

  if (abs(lowPotVal2 - lastLowPotVal2) > diff) {
    MIDImessage(kpc + 1, 15, map(lowPotVal2, 0, 1023, 0, 127));
    lastLowPotVal2 = lowPotVal2;
  }

  if (abs(CFXVal1 - lastCFXVal1) > diff) {
    MIDImessage(166, 23, map(CFXVal1, 0, 1023, 0, 127));
    lastCFXVal1 = CFXVal1;
  }

  if (abs(CFXVal2 - lastCFXVal2) > diff) {
    MIDImessage(166, 24, map(CFXVal2, 0, 1023, 0, 127));
    lastCFXVal2 = CFXVal2;
  }

  delay(2);
  
}


void MIDImessage(byte status, byte data1, byte data2) {
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}