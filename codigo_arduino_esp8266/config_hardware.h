//configuracion de pines de E/S
int sensor = 2;
int led=0;

//configuracion del keypad I2C
const uint8_t KEYPAD_ADDRESS = 0x38;
I2CKeyPad keyPad(KEYPAD_ADDRESS);
