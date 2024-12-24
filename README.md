# Weather_Station
This Arduino code snippet demonstrates how to interface with the BME280 sensor using the Adafruit BME280 library. The sensor provides temperature, pressure, altitude, and humidity data. The setup initializes the sensor and checks its status, ensuring proper connection via I2C. The main loop continuously reads sensor values and prints them to the Serial Monitor every second. Functions include reading temperature in Celsius, pressure in hectopascals (hPa), altitude relative to sea level pressure, and humidity as a percentage. This setup is ideal for applications requiring precise environmental monitoring and data logging.
Connect the circuit in the following way:

ESP32                    Breadboard
3.3V-                      BME280 VCC
GND-	                    BME280 GND
D21-	                    BME280 SDA
D22-	                    BME280 SCL

Make the necessary connections and upload the code onto the ESP32 DEVKIT V1 board.
paste the IP address generated in the serial monitor onto an internet browser. 

To graph the data

Connect the circuit in the following way:

ESP32                    Breadboard
3.3V-                      BME280 VCC
GND-	                    BME280 GND
D21-	                    BME280 SDA
D22-	                    BME280 SCL

Make the necessary connections and upload the code onto the ESP32 DEVKIT V1 board.
paste the IP address generated in the serial monitor onto an internet browser. 






