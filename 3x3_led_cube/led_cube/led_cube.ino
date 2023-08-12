/*************************************************************************************************
 *  PROJECT: LED CUBE 3X3X3                                                                      *
 *  COURSE: ELECTRONIC CIRCUITS                                                                  *
 *  AUTHORS: ARTURO HUNG, ANGELO DI MARTINO, JESÚS PÉREZ & ALEJANDRO SENIOR                      *
 *  REFERENCES: ADAPTED PROJECT FROM JHIMMY ASTORAQUE DURÁN (https://www.youtube.com/c/jadsatv)  *
 *  ©  ANDRÉS BELLO CATHOLIC UNIVERSITY - ACADEMIC SEMESTER APR-AUG 2022                         *
 *************************************************************************************************/


// Constants and variables
  // Q# - Arduino pins for LED - CUBE columns
      const byte Q0 = 2; 
      const byte Q1 = 3;
      const byte Q2 = 4;
      const byte Q3 = 5;
      const byte Q4 = 6;
      const byte Q5 = 7;
      const byte Q6 = 8;
      const byte Q7 = 9;
      const byte Q8 = 10;
      const byte Q[9] = {Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8};

  // floor# - Arduino pins for LED - CUBE rows
      const byte floor0 = 11; 
      const byte floor1 = 12;
      const byte floor2 = 13;
      const byte FLOORS[3] = {floor0, floor1, floor2};

// setup
void setup() {

    Serial.begin(115200);

    // Pins setup
    for (int k = 0; k < 3; k++) {
      pinMode(FLOORS[k], OUTPUT);
    }

    for (int k = 0; k < 9; k++) {
      pinMode(Q[k], OUTPUT);
    }
    cubeOff();  // LED-CUBE OFF
    delay(350); 

  } // End of setup function

void loop() {
  // To prevent possible issues, you might want to execute cubeOff() function every after any other animation.
  blinkCube(8, 500);
  columnBeam(true, 450);
  delay(500);

  for (int i = 0; i < 15; i++){
    xFactor(18);
  }

  cubeOff();
  delay(500);
  testLeds(5, 60);
  delay(500);

  for (byte i = 0; i < 3; i++){
    cubeFadeInOut(true, 27);
  }

  delay(500);
  columnBeam(false, 450);
  delay(500);
  upDownFloor(true, 7, 120);
  rightLeftSide(true, 7, 120);
  upDownFloor(false, 7, 120);
  rightLeftSide(false, 7, 120);
  delay(500);
  tornado(25, 180);
  delay(500);
  curtains(20, 100);
  delay(500);

} // End of the loop


/* Functions */

void cubeOff() {

  for (int k = 0; k < 3; k++) {
    digitalWrite(FLOORS[k], LOW);
  }

  for (int k = 0; k < 9; k++) {
    digitalWrite(Q[k], LOW);
  }
}


void cubeOn() {
  // all layers and cols ON
  for (int k = 0; k < 3; k++) {
    // pinMode(FLOORS[k], OUTPUT);
    digitalWrite(FLOORS[k], HIGH);
  }

  for (int k = 0; k < 9; k++) {
    digitalWrite(Q[k], HIGH);
  }
} // EOF cubeOn

void setVoxel(uint8_t row, uint8_t col) {
  // A pretty archaic implementation of setting up a voxel
  digitalWrite(FLOORS[row], HIGH);
  digitalWrite(Q[col], HIGH);
} // EOF setVoxel


void fullRow(uint8_t row) {
  for (int i = 0;  i < 9; i++) {
    digitalWrite(Q[i], HIGH);
  }
  digitalWrite(FLOORS[row], HIGH);
} // EOF fullRow


void fullCol(uint8_t col) {

  digitalWrite(Q[col], HIGH);

  digitalWrite(FLOORS[0], HIGH);
  digitalWrite(FLOORS[1], HIGH);
  digitalWrite(FLOORS[2], HIGH);

} // EOF fullCol


void fullLaterall(uint8_t lat) {
  // lat 0, 1, 2
  for (int i = 0; i < 9; i++) {
    if (i % 3 == lat) {
      fullCol(i);
    }
  }
} // EOF fullSide

void blinkCube(byte repetitions, int speed) {
  // suggested default speed 1000ms
  for (int i = 0; i < repetitions; i++) {
    cubeOn();
    delay(speed);
    cubeOff();
    delay(speed);
  }
} // EOF blinkCube


void testLeds(byte repetitions, int speed) {
  // speed 150 ms
  for (int c = 0; c < repetitions; c++) {
    for (int k = 0; k < 3; k++) {
      for (int i = 0; i < 9; i++) {
        setVoxel(k, i);
        delay(speed);
        cubeOff();
        // delay(150);
      }
    }
  }
} // EOF testLeds


void upDownFloor(bool isUp, byte repetitions, int speed) {
  // 200 ms nice default
  if (isUp) {
    for (int i = 0; i < repetitions; i++) {
      fullRow(0);
      delay(speed);
      cubeOff();
      fullRow(1);
      delay(speed);
      cubeOff();
      fullRow(2);
      delay(speed);
      cubeOff();
    }
  }
  else {
    for (int i = repetitions; i > 0 ; i--) {
      fullRow(2);
      delay(speed);
      cubeOff();
      fullRow(1);
      delay(speed);
      cubeOff();
      fullRow(0);
      delay(speed);
      cubeOff();
    }
  }
} // EOF upFloor


void rightLeftSide(bool isRight, byte repetitions, int speed ) {
  // 250 ms speed nice default
  if (isRight) {
    for (int i = 0; i < repetitions; i++) {
      fullLaterall(0);
      delay(speed);
      cubeOff();
      fullLaterall(1);
      delay(speed);
      cubeOff();
      fullLaterall(2);
      delay(speed);
      cubeOff();
    }
  }
  else {
    for (int i = 0; i < repetitions; i++) {
      fullLaterall(2);
      delay(speed);
      cubeOff();
      fullLaterall(1);
      delay(speed);
      cubeOff();
      fullLaterall(0);
      delay(speed);
      cubeOff();
    }
  }
} // EOF rightLeftSide


void cross(bool isFull, int timeShown) {
  // timeShown = 80 aprox 1 sec

  for (int i = 0; i < timeShown; i++)
  {
    fullCol(1);
    if (isFull) {
      fullCol(4);
      fullCol(7);
    }
    delay(7);
    cubeOff();
    setVoxel(1, 0);
    setVoxel(1, 2);
    if (isFull) {
      setVoxel(1, 3);
      setVoxel(1, 5);
      setVoxel(1, 6);
      setVoxel(1, 8);
    }
    delay(7);
    cubeOff();
  }
} // EOF cross

void X(bool isFull, int timeShown) {
  // timeShown = 80 aprox 1 sec
  for (int i = 0; i < timeShown; i++)
  {
    setVoxel(2, 0);
    setVoxel(2, 2);
    setVoxel(0, 0);
    setVoxel(0, 2);
    if (isFull) {
      setVoxel(2, 3);
      setVoxel(2, 5);
      setVoxel(2, 6);
      setVoxel(2, 8);
      setVoxel(0, 3);
      setVoxel(0, 5);
      setVoxel(0, 6);
      setVoxel(0, 8);
    }
    delay(7);
    cubeOff();
    setVoxel(1, 1);
    if (isFull) {
      setVoxel(1, 4);
      setVoxel(1, 7);
    }
    delay(7);
    cubeOff();
  }
} // EOF cross

void xFactor(int charHoldTime) {
  X(true, charHoldTime);
  cross(true, charHoldTime);
  X(true, charHoldTime);
  cross(true, charHoldTime);
} // EOF xFactor

void columnBeam(bool isRight, int speed) {
  byte colPattern[8] = {0, 1, 2, 5, 8, 7, 6, 3};
  if (isRight) {
    for (byte k = 1; k <= 12; k++) // 12 levels of acceleration
    {
      for (byte i = 0; i < 8; i++)
      {
        fullCol(colPattern[i]);
        delay(speed / k);
        cubeOff();
      }
      if (k == 12) {
        for (int c = 0; c < 7; c++) { // 7 laps at full speed
          for (byte i = 0; i < 8; i++)
          {
            fullCol(colPattern[i]);
            delay(speed / k);
            cubeOff();
          }
        }
      }
    }
  }
  else {
    for (byte k = 1; k <= 12; k++) // 12 levels of acceleration
    {
      for (int i = 7; i >= 0; i--)
      {
        fullCol(colPattern[i]);
        delay(speed / k);
        cubeOff();
      }
      if (k == 12) {
        for (int c = 0; c < 7; c++) { // 7 laps at full speed
          for (int i = 7; i >= 0; i--)
          {
            fullCol(colPattern[i]);
            delay(speed / k);
            cubeOff();
          }
        }
      }
    }
  }

} // EOF columnBeam

void cubeFadeInOut(bool alsoOut, int timeVoxel) {
  // Extremely nice function fades in with a random sequency always
  byte cube[27][2] = { //row col
    {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8},
    {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8},
    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8},
  };

  int array[27] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
  randomSeed(micros() +  analogRead(A1));

  // Randomize array order
  for (int i = 0; i < 27; i++)
  {
    int pos = random(27);
    int t = array[i];
    array[i] = array[pos];
    array[pos] = t;
  }

  /***** Start Fade IN ******/
  int progresiveCounter = 0;
  int adaptiveDelay = 2200;
  for (int i = 0; i < 27; i++) {
    progresiveCounter++;
    if (progresiveCounter > 24) {
      adaptiveDelay = 90;
    }
    else if (progresiveCounter > 21) {
      adaptiveDelay = 110;
    }
    else if (progresiveCounter > 17) {
      adaptiveDelay = 145;
    }
    else if (progresiveCounter > 12) {
      adaptiveDelay = 190;
    }
    else if (progresiveCounter > 9) {
      adaptiveDelay = 350;
    }
    else if (progresiveCounter > 7) {
      adaptiveDelay = 455;
    }
    else if (progresiveCounter > 5) {
      adaptiveDelay = 700;
    }
    else if (progresiveCounter > 3) {
      adaptiveDelay = 1265;
    }
    for (int y = 0; y < timeVoxel; y++) {
      for (int z = 0; z < progresiveCounter; z++) {
        setVoxel(cube[array[z]][0], cube[array[z]][1]);
        delayMicroseconds(adaptiveDelay); // 7 with 4 voxels, 1 with 26 voxels
        cubeOff();
      }
      // Holds the full cube On with same contrast
      if (progresiveCounter == 27) {
        for (int a = 0; a < 2; a++)
        {
          for (int x = 0; x < 27; x++) {
            setVoxel(cube[array[x]][0], cube[array[x]][1]);
            delayMicroseconds(750); // 7 with 4 voxels, 1 with 26 voxels
            cubeOff();
          }
        }
      }
    } // eof for timeVoxel
  }

  /***** Starts Fade OUT ******/
  if (alsoOut) {
    randomSeed(micros() +  analogRead(A1));

    // Randomize array order
    for (int i = 0; i < 27; i++)
    {
      int pos = random(27);
      int t = array[i];
      array[i] = array[pos];
      array[pos] = t;
    }

    adaptiveDelay = 90;
    for (int i = 0; i < 27; i++) {
      progresiveCounter--;
      if (progresiveCounter > 24) {
        adaptiveDelay = 95;
      }
      else if (progresiveCounter > 21) {
        adaptiveDelay = 110;
      }
      else if (progresiveCounter > 17) {
        adaptiveDelay = 145;
      }
      else if (progresiveCounter > 12) {
        adaptiveDelay = 190;
      }
      else if (progresiveCounter > 9) {
        adaptiveDelay = 350;
      }
      else if (progresiveCounter > 7) {
        adaptiveDelay = 455;
      }
      else if (progresiveCounter > 5) {
        adaptiveDelay = 700;
      }
      else if (progresiveCounter > 3) {
        adaptiveDelay = 1265;
      }
      for (int y = 0; y < timeVoxel; y++) {
        for (int z = progresiveCounter; z >= 0; z--) {
          setVoxel(cube[array[z]][0], cube[array[z]][1]);
          delayMicroseconds(adaptiveDelay); // 7 with 4 voxels, 1 with 26 voxels
          cubeOff();
        }
      } // eof for timeVoxel
    }
    delay(200);
  }
} // EOF cubeFadeInOut

void tornado(byte repetitions, int speed) {
  // 200 ms default nice
  for (byte i = 0; i < repetitions; i++) {
    fullCol(0);
    fullCol(2);
    fullCol(4);
    fullCol(6);
    fullCol(8);
    delay(speed);
    cubeOff();
    fullCol(1);
    fullCol(3);
    fullCol(4);
    fullCol(5);
    fullCol(7);
    delay(speed);
    cubeOff();
  }
} // eof tornado

void curtains(byte repetitions, int speed) {
  // nice 150ms
  for (int j = 0; j < repetitions; j++) {
    // Front animation
    for (int i = 2; i >= 0; i--) {
      for (int k = 0; k < 3; k++) {
        setVoxel(i, k);
        setVoxel(i, k + 6);
      }
      delay(speed);
    }
    cubeOff();
    for (int i = 2; i >= 1; i--) {
      for (int k = 0; k < 3; k++) {
        setVoxel(i, k);
        setVoxel(i, k + 6);
      }
    }
    delay(speed);
    cubeOff();

    for (int i = 2; i >= 2; i--) {
      for (int k = 0; k < 3; k++) {
        setVoxel(i, k);
        setVoxel(i, k + 6);
      }
    }
    delay(speed);
    cubeOff();
    delay(speed * 1.1);

    // sides animation
    for (int i = 2; i >= 0; i--) {
      for (int k = 0; k < 9; k = k + 3) {
        setVoxel(i, k);
        setVoxel(i, k + 2);
      }
      delay(speed);
    }
    cubeOff();
    for (int i = 2; i >= 1; i--) {
      for (int k = 0; k < 9; k = k + 3) {
        setVoxel(i, k);
        setVoxel(i, k + 2);
      }
    }
    delay(speed);
    cubeOff();
    for (int i = 2; i >= 2; i--) {
      for (int k = 0; k < 9; k = k + 3) {
        setVoxel(i, k);
        setVoxel(i, k + 2);
      }
    }
    delay(speed);
    cubeOff();
    delay(speed * 1.1);
  } // eof for repetitions
  
} // EOF curtains
