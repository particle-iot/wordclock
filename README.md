# Word Clock

### Introduction:
This repo belongs to the word clock made by Jordy Moors. This should contain the required code to get this up and running, along with the steps on how to do this.

It makes use of the RGB pixel clock which is included in the kit. More information about that can be found on the respective Github page, which can be found over [here](http://github.com/spark/rgb-pixel-clock). 

![Word Clock](https://github.com/spark/wordclock/blob/master/images/word-clock-front.jpg)

### Parts List:

- RGB matrix panel
- RGB matrix shield
- 5A power supply
- Acrylic enclosure
- Micro SD card
- Particle Photon

What else do I need:
- Sheet of white paper, vellum paper, or photogel. Something to diffuse the light with. Printer paper works well and was used in the demo, though other might look even better.

Tools needed:
-	Scissors or knife to cut the diffuser to size.
-	Tape or (hot) glue (no instant glue!) to hold the enclosure together. Doesn't have to be super strong, it’s just so it won't come apart on its own.


### Assembly Guide:

First off, start by peeling all the protective paper off the acrylic. Especially with the lettering plate care should be taken to avoid damaging the letters. Puts the parts aside, and familiarize yourself with what parts you've got.

![Step 1](https://github.com/spark/wordclock/blob/master/images/step1.jpg)

Lay the LED matrix face down on the table, with the arrow pointing upwards. Then put the small slim acrylic pieces on the two sides, notches pointing outwards.

![Step 1b](https://github.com/spark/wordclock/blob/master/images/step1b.jpg) 

Put the sides on, making sure to keep the one with the small hole on the bottom, and with the longer notches pointing towards the table. Attach this with tape temporarily.

![Step 2](https://github.com/spark/wordclock/blob/master/images/step2.jpg)

Turn the whole thing over, keeping the arrow still pointing upwards. Now, put the raster plate in. then, cut a piece of paper (or diffuser of choice) to size to fit in over the raster. The size would be 7.56” square (192mm). Once thats cut, put it over the raster. Then lay in the letter plate so it’s actually readable (top left should say “ITS…”). Attach this with a piece of tape to hold it in place.

![Step 3](https://github.com/spark/wordclock/blob/master/images/step3.jpg)

![Step 4](https://github.com/spark/wordclock/blob/master/images/step4.jpg)

![Step 4b](https://github.com/spark/wordclock/blob/master/images/step4b.jpg)

![Step 5](https://github.com/spark/wordclock/blob/master/images/step5.jpg)

![Step 6](https://github.com/spark/wordclock/blob/master/images/step6.jpg)

 
 Put the Photon in the shield that came with the kit, aligning it with the outline on the board. Then, screw in the wired connector to the board, taking care you use the red wires for positive and the black ones for negative. Place the board on the panel, making sure the connector is in the middle of the left receptor:

![Step 7](https://github.com/spark/wordclock/blob/master/images/step7.jpg)

![Step 7b](https://github.com/spark/wordclock/blob/master/images/rgb-clock-back.jpg)
 
Then put the back cover on the case and secure it with some tape. Insert the power cable while you're at it: 

![Step 8](https://github.com/spark/wordclock/blob/master/images/step8.jpg)


### Setup (programming guide):

Get the Photon up and running by following the instructions as laid out in the “getting started” section of the Particle documentation. Once it’s breathing cyan, play around with the Tinker application for a bit, toggling the D7 LED, making sure the cloud connection is working, and you can control it properly. If something fails, don’t hesitate to ask in the community, since they will go out of their way to help people out.
As soon as you've got the Photon running happily and want to get the clock code on there, head over to the web IDE. The actual code for the lamp can be found in this repo. There are three files of interest which you’ll need to get this working properly: main.ino, snake.h and snake.cpp. Create a new project, then add the following libraries to that newly created project:
"SparkIntervalTimer/SparkIntervalTimer.h"
"Adafruit_mfGFX/Adafruit_mfGFX.h"
"RGBmatrixPanel/RGBmatrixPanel.h"
When doing this, the following lines will automatically be added to the project:
```
// This #include statement was automatically added by the Particle IDE.
#include "SparkIntervalTimer/SparkIntervalTimer.h"
// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_mfGFX/Adafruit_mfGFX.h"
// This #include statement was automatically added by the Particle IDE.
#include "RGBmatrixPanel/RGBmatrixPanel.h"
```
Then, click the little ‘+’ icon on the tabs bar, and enter “snake” when you can fill in a name for the new tabs. In there, paste the respective files from above. After that, copy the main.ino contents and paste it over everything you’ve got in your project by then.
Once that’s done, try compiling the project (while making sure you’ve got a Photon selected in the devices tab). If everything goes as planned it shouldn’t give you any errors and tell you the following:

 
If you get that far, go ahead, and flash it to your device.

If you turn it on, you should be good to go!


### Troubleshooting:

http://community.particle.io/t/word-clock-kit-maker-faire-2016/23048
