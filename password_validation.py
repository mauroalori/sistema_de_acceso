import requests
import json
from datetime import datetime

ruta_pass="password.txt"
ruta_valid_registro="registros.txt"

url_esp="http://192.168.0.25/"

while(1):
    print("+Esperando solicitud de validacion")
    response = requests.get(url_esp)
    print("-Se recibio la solicitud")
    response_json = response.json()

    with open(ruta_pass,"rt") as fpass:
        if(response_json['pass_ingresada']==fpass.read()):
            try:
                requests.post(url_esp,params={'pass':'correcta'})
            except:
                print("No se pudo establecer la conexión con el servidor")
                quit()
            print("intento exitoso")
            intento="exitoso"
        else:
            try:
                requests.post(url_esp,params={'pass':'incorrect'})
            except:
                print("No se pudo establecer la conexión con el servidor")
                quit()
            intento="fallido"
            print("intento fallido")

    #fecha y hora con datetime
    dt = datetime.now()
    fecha_y_hora=str(dt)

    fecha=""
    hora=""
    i=0
    segundos=0
    for c in fecha_y_hora:
        if(i==0 and c!=' '):
            fecha+=c
        if(i==1 and c!=' '):
            if(c==':'):
                segundos+=1
            if(segundos!=2):
                hora+=c
        if(c==' '):
            i+=1
            
    with open(ruta_valid_registro,"at") as registros:
        datos_validacion="Se realizó un ingreso de contraseña " + intento + " a las " + hora + " con fecha " + fecha + '\n' 
        registros.write(datos_validacion)
