Samsung IR Remote assistant
===========================

This project aim to build an easy interface to send same misterious IR code to your Samsung TV.

Hardware
--------

The hardware needed for this project consisto of :
* 1 IR led
* 1 150ohm resistence
* 3 pushbutton
* 1 Arduino UNO
* 1 bredboard

The connection between these hardware :

Arduino | bredboard
--------|-----------
8| to 150 ohm resistor then to catode of IR led (anode is attached to +5V)
2| to the first button (the other end of button goes to GND)
3| to the second button (the other end of button goes to GND)
4| to the third button (the other end of button goes to GND)

Software
--------

According to [SamyGo Wiki](http://wiki.samygo.tv/index.php5/Key_codes) the three button aim to send (in order) these IR codes :
* POWER CICLE
* FACTORY + 3SPEED
* INFO + MENU + MUTE + POWER

Usage
-----

Once built the simple connection between Arduino and the breadboard you can go and send the sketch to Arduino. Now you are ready to point IR led towards your TV and try to press first button ..... tada your TV is ON ;)

