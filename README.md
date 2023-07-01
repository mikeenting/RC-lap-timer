# RC-lap-timer
## Description
This projects uses an Arduino to track the lap times of an RC car. It times the lap, and keeps track of the fastest registered lap. It is portable and can be powered with a 9V battery. See [this link](https://www.thingiverse.com/thing:6049245) to find the project on Thingiverse.

## Demo
[![Demo](https://img.youtube.com/vi/-q12BmalPtk/0.jpg)](https://youtu.be/-q12BmalPtk)


## Required materials
See component list [here](https://github.com/mikeenting/RC-lap-timer/blob/main/laptimer_component_list.csv)

## Assembly
1. Download [this program](https://github.com/mikeenting/RC-lap-timer/blob/main/laptimer/laptimer.ino) and upload it to your Arduino
2. Download, slice and print all files in [this folder](https://github.com/mikeenting/RC-lap-timer/blob/main/3d_designs) (see suggested printer settings below)
3. Use M3 heat set insert to connect arduino to the floor
4. Connect ultrasonic sensor to middle bottom
5. Connect floor to middle bottom using M3 heat set inserts
6. Use hot glue to connect potentiometer to middle bottom
7. Connect LCD to middle top
8. Wire up Arduino with all parts, according to [this circuit view](https://github.com/mikeenting/RC-lap-timer/blob/main/laptimer_circuit_view.png)
9. Connect middle bottom and top using M3 heat set inserts
10. Attach the lid using M3 heat set inserts
11. Power up the Arduino and you're good to go!

## Printer Settings
I printed with a Creality Ender 3 V2, using 1.75mm PLA and the following settings:
- Floor:
    - Print regular side down
    - Profile: 0.2
    - Infill: 60%
    - No support required
- Middle Bottom:
    - Print upside down
    - Profile: 0.2
    - Infill: 60%
    - No support required
- Middle Top:
    - Print regular side down
    - Profile: 0.2
    - Infill: 60%
    - Print with support (optional: use support blocker to prevent unnecessary support to be printed in the holes)
- Lid:
    - Print regular side down
    - Profile: 0.2
    - Infill: 60%
    - No support required

------
### Inspiration from
- https://github.com/beaver-pc/RC-Lap-Timer/blob/master/Lap_Timer.ino
- https://create.arduino.cc/projecthub/abdularbi17
- https://www.thingiverse.com/thing:2813169
