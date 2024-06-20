/**
* @file Arduino_Mega.ino
* @author Angel G. Fonseca y Luis R. Arzuaga
* @brief This code is in charge of controlling the
ultrasonic sensors and sending the info to the ESP32.
* @date 2024-05-09
*
* @copyright Copyright (c) 2024
*
*/
///@brief Trigger pin for sensor 1.
#define trig_pk1 3
///@brief Echo pin for sensor 1.
#define echo_pk1 4
///@brief Trigger pin for sensor 2.
#define trig_pk2 5
///@brief Echo pin for sensor 2.
#define echo_pk2 6
///@brief Trigger pin for sensor 3.
#define trig_pk3 42
///@brief Echo pin for sensor 3.
#define echo_pk3 43
///@brief Trigger pin for sensor 4.
#define trig_pk4 50
///@brief Echo pin for sensor 4.
#define echo_pk4 51
///@brief Library to simplify ultrasonic sensors.
///@link
https://www.arduino.cc/reference/en/libraries/newping/
#include <NewPing.h>
/**
* @brief Max is going to save the maximum distance we
want the sensors to detect in centimeters.
*/
#define max 7
/// @brief Pins for the led in parking 1.
#define ledpin1 10
/// @brief Pins for the led in parking 2.
#define ledpin2 12
/// @brief Saves the distance of the right sensor.
int distance_left;
/// @brief Saves the distance of the left sensor.
int distance_right;
/// @brief Bool that saves true or false if the parking 1 is
occuppied.
bool park1;
/// @brief Bool that saves true or false if the parking 2 is
occuppied.
bool park2;
/**
* @brief Funtion to verify if the parking is occuppied.
*
* @return true
* @return false
*/
bool verify_parking(NewPing, NewPing);
/**
* @brief Create an object of type NewPing named sonar1,
with the pins and the maximum distance.
*/
NewPing sonar1(trig_pk1, echo_pk1, max);
/**
* @brief Create an object of type NewPing named sonar2,
with the pins and the maximum distance.
*/
NewPing sonar2(trig_pk2, echo_pk2, max);
/**
* @brief Create an object of type NewPing named sonar3,
with the pins and the maximum distance.
*/
NewPing sonar3(trig_pk3, echo_pk3, max);
/**
* @brief Create an object of type NewPing named sonar4,
with the pins and the maximum distance.
*/
NewPing sonar4(trig_pk4, echo_pk4, max);
/**
* @brief Here the Seria.begin is done and also initialize
the pins for the leds as output pins.
*/
void setup()
{
Serial.begin(9600);
pinMode(ledpin1, OUTPUT);
pinMode(ledpin2, OUTPUT);
}
/**
* @brief void loop of the code codigo
*
* In the main loop of the code, the function
verify_parking() is called and the respective sonar objects
representing the parking are passed to it.
* This function then returns a boolean which is stored in
park1 and park2, which respectively symbolize parking
spots 1 and 2.
*These boolean variables are inserted into if statements
that will print "P1 OCa" or "P1 Fa", which are then passed
through UART ports to the ESP32 and also turn on or off
LEDs indicating whether the parking spot is occupied.
*This process is repeated once more for the second
boolean to decide whether to print "P2 OCb" or "P2 Fb"
on the serial port.
*These printed strings have the letters 'a' and 'b' at the end
so that the ESP32 has reference as to where exactly it
needs to read the received string.
*/
void loop()
{
park1 = verify_Parking(sonar1, sonar2);
park2 = verify_Parking(sonar3, sonar4);
if(park1)
{
Serial.print("P1 OCa");
digitalWrite(ledpin1, HIGH);
}
else
{
Serial.print("P1 Fa");
digitalWrite(ledpin1, LOW);
}
if(park2)
{
Serial.print("P2 OCb");
digitalWrite(ledpin2, HIGH);
}
else
{
Serial.print("P2 Fb");
digitalWrite(ledpin2, LOW);
}
delay(3000);
}
/**
* @brief Boolean function that verifies if both sensors are
activated.
*
* @param s1 Represents the first ultrasonic sensor.
* @param s2 Represents the second ultrasonic sensor.
* @return true Returns true if both sensors are activated
at the same time.
* @return false Retunr false if at least one of the sensors
is not active.
*
*
*This function receives the two NewPing objects, which
are the ultrasonic sensors, and creates a boolean variable
called 'temperera' to return it as the result.
*Using the global integers 'distance_left' and
'distance_right', we store the result of the .ping_cm()
function from the NewPing library, which gives us the
calculated distance in centimeters that the sensor has
detected.
*These values are then stored to be compared later in an
if statement, where both distances must be true to enter.
For this, both distances must be less than or equal to the
maximum distance and greater than zero.
*If this is the case, the parking space is considered
occupied.
*/
bool verify_Parking(NewPing s1, NewPing s2)
{
bool tmp;
distance_left = s1.ping_cm(max);
distance_right = s2.ping_cm(max);
if(distance_left <= max && distance_left > 0 &&
distance_right <= max && distance_right > 0 )
{
tmp = true;
}
else
{
tmp = false;
}
return tmp;
}