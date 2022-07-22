// Direccion I2C del Keypad
#define KEYPAD_ADDRESS 0x20

// Defino una estructura para obtener datos relacionados a la última tecla presionada
struct lastKeyPressed{
  uint32_t time;
  unsigned char last;
};

// String con los caracteres del keypad
char keys[] = "123A456B789C*0#DNF";  // N = NoKey, F = Fail
