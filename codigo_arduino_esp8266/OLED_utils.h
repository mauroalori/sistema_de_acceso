void displayPassword(String pass_ingresada) {
  String pass_muestreo="";
  unsigned long largo_string;
  
  display.clearDisplay();
  display.display();

  //armo el string de la contraseña para el muestreo
  largo_string=pass_ingresada.length();
  if(largo_string<6){
    for(int i=0;i<largo_string;i++)
      pass_muestreo += pass_ingresada[i];
  }
  else{
    for(int i=largo_string-6;i<largo_string;i++)
      pass_muestreo += pass_ingresada[i];
  }
  
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Ingrese contrase");display.print((char)164);display.println("a:");
  display.println("-------------------");
  display.setCursor(0,27);
  display.setTextSize(3);
  display.print(pass_muestreo);
  display.display();
}

void displayPassStatus(String estado) {  
  display.clearDisplay();
  display.display();
  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,15);
  display.print("Contrase");display.print((char)164);display.println("a");
  display.println(estado);
  
  display.display();
}
