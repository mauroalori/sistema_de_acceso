void ConectarEnSTA(bool useStaticIP = false)
{
   Serial.println("");
   Serial.print("Conectandose a ");
   Serial.println(ssid);
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   if(useStaticIP) 
     WiFi.config(ip, gateway, subnet);
   Serial.print("Conectando");
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(100);  
     Serial.print('.'); 
   }
   
   Serial.println("");
   Serial.print("Conectado exitosamente a ");
   Serial.println(WiFi.SSID());
   Serial.print("IP address:\t");
   Serial.println(WiFi.localIP());
}
