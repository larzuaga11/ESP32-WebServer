# ESP32-WebServer

This project is based on four ultrasonic sensor that measure the distant of the car and the parking bumpers. Using the two microcontroller called Arduino and ESP32 we can take that information given by the sensors and send it to a website to track live time the disponibility of the parking slot. The Webpage will represent the Occupied mode with Red and the Free mode with green. 

# How it Works? 

Using the information given by the ultrasonic, the Arduino using the libraries NewPing that give use function that manipulate the signal of the ultrasonic sensor calculate the distance and send to the ESP32 the stage of the parking. When the signal is receive by the ESP32 it will convert the input in a JSON to give it to the script in JavaScritp and then change the stage of the parking in the webpage.

