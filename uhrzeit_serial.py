import serial
import time

ser = serial.Serial('COM9', 9600)  # COM9 durch den entsprechenden COM-Port ersetzen

try:
    while True:
        # Warte auf Anfrage vom Mbed-Gerät
        if ser.read() == b'?':
            current_time = time.strftime("%H:%M:%S")  # Aktuelle Uhrzeit als String erhalten, z.B. '17:48:30'
            ser.write(current_time.encode())  # Die Uhrzeit als Zeichen an das Mbed-Gerät senden
            print(current_time)
        time.sleep(0.01)  # Eine kurze Pause, um den Code nicht zu schnell auszuführen

except KeyboardInterrupt:
    pass

ser.close()  # Die serielle Verbindung schließen
