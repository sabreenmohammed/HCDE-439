int c0 = D3;
int c1 = D2;
int c2 = D1;
int c3 = D0;
int sheetLength = 5;
int delayTime = 5; 
int numLoops = calculateNumLoops(sheetLength);
void setup() {
    int pins [] = {c0, c1, c2, c3};
    for (int pin : pins){
        pinMode(pin, OUTPUT);
    }
    Particle.function("makeBed", makeBed); //registers function in particle cloud
    Particle.function("unmakeBed", unmakeBed); 
    Particle.function("tuckIn", tuckIn); 
    //digitalWrite(motor, LOW); //ensures motor is off during setup (neccessary?)
}

void loop() {
}

/**
 * Makes bed. 
 * paramater status--is the bed already made?
 * returns 0 if bed was successfully made, 
 * 2 if the bed was already made
 * 
 **/
int makeBed(String status){
    bool bedMade = status.equals("true"); 
    if (bedMade)
        return 2; 
    else{
        runClockwise();
    }
    return 0;
}

/**
 * Unmakes bed. 
 * parameter status--is the bed already made?
 * returns 0 if bed was unmade, 
 * 3 if the bed was already unmade
 * 
 **/
int unmakeBed(String status){
    bool bedMade = status.equals("true");
    if (!bedMade)
        return 3; 
    else{
        runAntiClockwise();
    }
    return 0;
}

/**
 * Tucks person in. 
 * parameter status--is the bed already made?
 * returns 0 if person was successfully tucked in,
 * 10 if the person was already tucked in. 
 * 
 **/
int tuckIn(String status){
    int outcome1 = makeBed(status); //tucks in 
    int outcome2 = unmakeBed(status); //allows for freely moving in sleep
    return (outcome1 + outcome2) * 5; 
}


int runClockwise(){
    for (int i = 0; i < numLoops; i++){
        for (int step = 3; step >= 0; step--)
            activateStep(step);
    }
}

int runAntiClockwise(){
  
    for (int i = 0; i < numLoops; i++){
        for (int step = 0; step < 4; step++)
            activateStep(step);
    }
}

int activateStep(int step){
    delay(5);
    digitalWrite(step, HIGH);
    digitalWrite((step + 1) % 4, HIGH);
    digitalWrite((step + 2) % 4, LOW);
    digitalWrite((step + 3) % 4, LOW);
   
}

/**
 * Calculates how many steps the motor needs to turn
 *  in order to move item across 
 * paramater distance is the distance motor pulls in cm
 * returns number of loops that must run to turn 
 * stepper motor the needed amount 
 * 
**/
int calculateNumLoops(int distance){
    return 1000;
}