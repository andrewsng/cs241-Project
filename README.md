# Shooting Timelapses with an Arduino Intervalometer

The purpose of this project was to get an Arduino connected to a DSLR camera, and to be able to programmatically control the camera's shutter release. The shutter release is
essentially the mechanism that will capture a photo once activated. Being able to remotely control the shutter release can help remove camera shake that results from physically
pushing the camera button down. It also allows the possibility of operating your camera from a distance, which might help with security surveillance, wildlife photography, etc.
However, the main reason I wanted to do this was to shoot timelapse by having the Arduino handle time intervals between photos.

This use of the Arduino is possible because many DSLR cameras come with a 2.5mm audio jack that offers an interface to some of the camera's functions, namely the auto focus and
the shutter release. These are typically used for intervalometers, external devices with time controls for shooting timelapses, which is exactly what I wanted to emulate.
Connecting an audio plug gives three lines out of the camera's internal circuit: auto focus (white), shutter release (red), and ground (black). Closing the circuit between ground
and the other two activate their given functions, but I ended up never using the auto focus feature since it's unnecessary for timelapses.

![](https://user-images.githubusercontent.com/54720199/116506575-093e2700-a86a-11eb-8470-311344070418.jpg)
![](https://user-images.githubusercontent.com/54720199/116506610-18bd7000-a86a-11eb-9cf0-a78f890be411.jpg)

Finally, I needed a switching element to control the shutter release circuit. I ended up using an opto-isolator, which allowed me to switch the camera's internal circuit from an
entirely isolated circuit. I chose this mostly because of the extra protection barrier it gives to the camera's circuit. The final circuit was straightforward, with the switching
side of the opto-isolator hooked up to the audio cable, and the other side wired to an Arduino logic pin. Having the switching element on a breadboard separated from the Arduino
was difficult to handle and not very portable, so I attached a prototyping shield from the lab kit that allowed the small breadboard to be stuck onto the device.

![](https://user-images.githubusercontent.com/54720199/116506778-75b92600-a86a-11eb-9e67-6c2e2cac38df.jpg)

# Demo Video

Here is a video that shows the device working, as well as some of the timelapses I managed to capture with it: 
https://www.youtube.com/watch?v=kEHigyjwOHY
