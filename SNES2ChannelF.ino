// From https://gamefaqs.gamespot.com/snes/916396-super-nintendo/faqs/5395
//       ----------------------------- ---------------------
//      |                             |                      \
//      | (1)     (2)     (3)     (4) |  (X)     (X)      (7) |
//      |                             |                      /
//       ----------------------------- ---------------------
//
//        Pin     Description             Color of wire in cable
//        ===     ===========             ======================
//         1      +5v                     White
//         2      Data clock              Yellow
//         3      Data latch              Orange
//         4      Serial data             Red
//         7      Ground                  Brown

constexpr uint8_t SNES_CLOCK = 6;
constexpr uint8_t SNES_LATCH = 7;
constexpr uint8_t SNES_DATA = 12;

// From https://channelf.se/veswiki/index.php?title=Pinouts
//       ------------------------------------------
//      |                                          |
//      | (1) (2) (3) (4) (5) (6) (7) (8) (X) (10) |
//      |                                          |
//       ------------------------------------------
//
//        Pin     Description             Color of wire in cable
//        ===     =================       ======================
//         1      Push down               Black
//         2      Pull up                 Brown
//         3      Clockwise               Red
//         4      Counter-clockwise       Orange
//         5      Forward                 Yellow
//         6      Backward                Green
//         7      Left                    Blue
//         8      Right                   Grey
//        10      Ground                  White

constexpr uint8_t CHANF_PUSH_PIN = 25;
constexpr uint8_t CHANF_PULL_PIN = 27;
constexpr uint8_t CHANF_CW_PIN = 29;
constexpr uint8_t CHANF_CCW_PIN = 31;
constexpr uint8_t CHANF_FORWARD_PIN = 33;
constexpr uint8_t CHANF_BACKWARD_PIN = 35;
constexpr uint8_t CHANF_LEFT_PIN = 37;
constexpr uint8_t CHANF_RIGHT_PIN = 39;

constexpr uint8_t ChannelFPins[8] = {
    CHANF_PUSH_PIN, CHANF_PULL_PIN, CHANF_CW_PIN, CHANF_CCW_PIN, CHANF_FORWARD_PIN, CHANF_BACKWARD_PIN, CHANF_LEFT_PIN, CHANF_RIGHT_PIN,
};

// From https://github.com/marcosassis/gamepaduino/wiki/SNES-controller-interface
//              _______ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ _______________________
//  serial data        |_B_|_Y_|___|___|___|___|___|___|_A_|_X_|_L_|_R_| ?   ?   ?   ?  
//                       0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
//  button name/id              /   /    |    \   \   \
//                          select start up down left right 

enum {
    CHANF_PUSH, CHANF_PULL, CHANF_CW, CHANF_CCW, CHANF_FORWARD, CHANF_BACKWARD, CHANF_LEFT, CHANF_RIGHT,
} SNES2Fairchild[12] = {
    CHANF_PUSH, CHANF_PULL, CHANF_CCW, CHANF_CW, CHANF_FORWARD, CHANF_BACKWARD, CHANF_LEFT, CHANF_RIGHT, 
    CHANF_PUSH, CHANF_PULL, CHANF_CCW, CHANF_CW,
};
uint16_t SNESButtonStates;

void setup(){
    // Initialize SNES controller
    digitalWrite(SNES_CLOCK, HIGH);
    pinMode(SNES_CLOCK, OUTPUT);

    digitalWrite(SNES_LATCH, LOW);
    pinMode(SNES_LATCH, OUTPUT);

    pinMode(SNES_DATA, INPUT_PULLUP); 
}

void loop(){
    getControllerData();
    setChannelFData();
}

// Read button states from SNES controller
void getControllerData(void){
    // Latch button states
    digitalWrite(SNES_LATCH, HIGH);
    delayMicroseconds(12);
    digitalWrite(SNES_LATCH, LOW);
    delayMicroseconds(6);
    
    // Retrieve button states from shift register
    for(uint8_t i = 0; i < 16; i++){
        digitalWrite(SNES_CLOCK, LOW);
        delayMicroseconds(6);
        bitWrite(SNESButtonStates, i, digitalRead(SNES_DATA));
        digitalWrite(SNES_CLOCK, HIGH);
        delayMicroseconds(6);
    }
}

// Set the Channel F pins according to the SNES button states
void setChannelFData() {
    // Convert SNES button states to Channel F button states
    uint8_t ChannelFButtonStates = 0xFF;
    for (uint8_t i = 0; i < 12; i++){
        if (bitRead(SNESButtonStates, i) == 0) {
            bitClear(ChannelFButtonStates, SNES2Fairchild[i]);
        }
    }

    // Set Channel F pins to floating(1) or ground(0)
    for (uint8_t i = 0; i < 8; i++){
        uint8_t pin = ChannelFPins[i];
        if (bitRead(ChannelFButtonStates, i)) { // Float
            pinMode(pin, INPUT);
        } else { // Ground
            digitalWrite(pin, LOW);
            pinMode(pin, OUTPUT);
        }
    }
}
