# Super Famicom Controller to Channel F

The goal of this project was to connect a Nintendo SNES / Super Famicom controller to the Fairchild Channel F console. Both these devices use different protocols/connections for their respective controllers, so to translate and connect the two I used an Arduino Due. It's overkill for a simple project like this, but it's what I had on hand at the time. Note that both system's controllers use active low data.

## Super Famicom Controller

<img src="https://user-images.githubusercontent.com/44975876/155827176-da1adc80-9e00-4f97-bf77-bcbb8899ecbe.png" align="right" width="30%" />

The Super Famicom uses a serial connection with 3 wires. *Latch* captures the button states in that moment. Then *Clock* is toggled 16 times to pull 16-bits (though only 12 are used) from the controllers internal shift register through *Data*. The Super Famicom console will poll the controller about 60 times a second.

| Pin  | Description       | Color of wire |
| ---- | ----------------- | ------------- |
| 1    | 5V                | White         |
| 2    | Clock             | Blue          |
| 3    | Latch             | Yellow        |
| 4    | Data              | Red           |
| 7    | Ground            | Brown         |


#### Super Famicom Timing Diagram

![image](https://user-images.githubusercontent.com/44975876/155824923-c4a5b9ad-d9db-47a8-9dc3-ba889e904e70.png)



## Channel F Controller

<img src="https://user-images.githubusercontent.com/44975876/155827105-ee87fd83-5722-4dc9-9ef0-5f88691cc5ed.png" align="right" width="30%" />

The Channel F uses a parallel connection with 9 wires for each controller. 1 for ground, and 8 floating, pulled to +5V, that each represent a movement on the controller as shown in the table below. When a movement is made, its corresponding wire is shorted to ground.

| Pin  | Description       | Color of wire |
| ---- | ----------------- | ------------- |
| 1    | Push down         | Black         |
| 2    | Pull up           | Brown         |
| 3    | Clockwise         | Red           |
| 4    | Counter-clockwise | Orange        |
| 5    | Forward           | Yellow        |
| 6    | Backward          | Green         |
| 7    | Left              | Blue          |
| 8    | Right             | Grey          |
| 10   | Ground            | White         |



## Controller Mapping

I settled on mapping the 4 extra buttons in a way that allows NES / Famicom controllers to be connected too. Of course one could also use these extra buttons to perform more interesting actions. But for now it works just fine.

<p align="center">
    <img src="https://user-images.githubusercontent.com/44975876/155828164-dbdc2ab8-5b65-4bcd-abc6-e1fd5aa4944f.png" align="center" width="70%" />
</p>



## Final Design

Here's what it looks like all hooked up, along with a simplified schematic. Note that I used a Super Famicom extension cable, as I didn't want to cut the cable from an actual controller, both because I don't want to destroy vintage hardware (even though the one shown here isn't genuine), and because I still want it to work with my Super Famicom.

<p align="center">
    <img src="https://user-images.githubusercontent.com/44975876/155828416-97023b8b-77b9-4e35-8c3c-c095a32c9541.png" align="center" width="90%" />
</p>

# Useful Links / Sources

[Nintenduino - Controller Reference](https://nintenduino.wordpress.com/documentation/controller-reference/)

[Ves Wiki - Channel F Pinouts](https://channelf.se/veswiki/index.php?title=Pinouts)

[Gamepaduino - SNES Controller Interface](https://github.com/marcosassis/gamepaduino/wiki/SNES-controller-interface)

[The Nerd Mag - Nintendo Super Famicom...](https://www.thenerdmag.com/nintendo-super-famicom-buttons-trademark-hints-at-wireless-super-famicom-controller/)

[Repair FAQ - SNES](https://www.repairfaq.org/REPAIR/F_SNES.html)

