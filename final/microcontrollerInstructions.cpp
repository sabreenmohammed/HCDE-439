
int clockwise1 = D1;//hybrid yellow, in4
int clockwise2 = D4;//purple, in7    black sticker
int anticlockwise1 = D2;//grey, in6    gold sticker
int anticlockwise2 = D3;//green, in5
int run = D7; //controls power to whole relay board
int sheetLength = 5;
void setup() {
    Particle.function("makeBed2", makeBed); //registers function in particle cloud
    Particle.function("unmakeBed2", unmakeBed); 
    Particle.function("tuckIn2", tuckIn); 
    Particle.function("tweak", tweak); 
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    //digitalWrite(motor, LOW); //ensures motor is off during setup (neccessary?)
}

void loop() {
    
}

/**
 * Makes bed. 
 * @param status--is the bed already made?
 * @returns 0 if bed was successfully made, 
 * 2 if the bed was already made
 * 
 **/
int makeBed(String status){
    bool bedMade = status.equals("true"); 
    if (bedMade)
        return 2; 
    else{
        runClockwise(8000);
    }
    return 0;
}

/**
 * Unmakes bed. 
 * @param status--is the bed already made?
 * @returns 0 if bed was unmade, 
 * 3 if the bed was already unmade
 * 
 **/
int unmakeBed(String status){
    bool bedMade = status.equals("true");
    if (!bedMade)
        return 3; 
    else{
        runAntiClockwise(8000);
    }
    return 0;
}

/**
 * Tucks person in. 
 * @param status--is the bed already made?
 * @returns 0 if person was successfully tucked in,
 * 10 if the person was already tucked in. 
 * 
 **/
int tuckIn(String status){
    int outcome1 = makeBed(status); //tucks in 
    int outcome2 = unmakeBed(status); //allows for freely moving in sleep
    return (outcome1 + outcome2) * 5; 
}


void runClockwise(int time){
    digitalWrite(anticlockwise1, HIGH); //RELAY SWITCHES ARE INVERTED
    digitalWrite(anticlockwise2, HIGH);
    digitalWrite(clockwise1, LOW);
    digitalWrite(clockwise2, LOW);
    runBedMaker(time);
}

void runAntiClockwise(int time){
    digitalWrite(clockwise1, HIGH); 
    digitalWrite(clockwise2, HIGH);
    digitalWrite(anticlockwise1, LOW);
    digitalWrite(anticlockwise2, LOW);
    runBedMaker(time);
}

void runBedMaker(int time){
    int clicks = time/1000;
    for (int i = 0; i < clicks; i++){
        digitalWrite(run, HIGH); //NOT INVERTED
        delay(100);
        digitalWrite(run, LOW); 
        delay(900);
    }
}

int tweak(String parameters){
    String orientation  = parameters.substring(0, 1);
    int time = parameters.substring (2).toInt();
    if (orientation == "c"){
        runClockwise(time);
        return 0;
    }
    else if (orientation == "a"){
        runAntiClockwise(time);
        return 0;
    }
    return 1;
}
