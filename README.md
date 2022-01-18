# baby-r2-sounds

This repo is a work in progress. I have printed and assembled one of [Mr. Baddeley's](https://www.patreon.com/mrbaddeley) Baby R2 droids. He has all of the instructions for getting the droid moving, but I wanted to add sounds as well. This guide will cover the modifications to the droid. For more info on how to build the droid itself check out his patreon.

Additional Hardware used:

- [Ardunio Nano](https://store-usa.arduino.cc/products/arduino-nano?selectedStore=us)
- [DF Mini Player](https://www.dfrobot.com/product-1121.html)
- SD Card
- 1K Resistor

## Setting up the Circuit

I wanted to keep as much of Mr. Baddeley's design in place as possible, so I decided to power my setup through the FS-iA6B.

You can also send commands to the arduino via the FS-iA6B by connecting the arduino to the iBus output. You will need to connect the Arduino to the iBus of the FS-iA6B as shown.

![Baby R2 Breadboard V1](https://user-images.githubusercontent.com/39142975/149836900-255352c2-a780-4506-a653-6cfbed98c6dc.png)

## Setting up the DF Mini Player
I formatted my micro SD card using FAT32.

All of the sound files are in the `MP3 Files` directory. You will need to copy these to your SD card. The order that they are copied onto the SD card matters. I started with the first file and copied them over one at a time.

If you are on a mac you may need to follow the directions [here](https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299#target_6) to clean up the dot files after copying everything over.

Once everything is copied over you can put it into the DF Mini Player

## Setting up the software

You should be able to place the `baby_r2_sounds.ino` file into a folder called `baby_r2_sounds` and then open that up in the [Arduino software](https://www.arduino.cc/en/software).

You will need to install the following libraries using the Arduino library manager:
- iBusBM
- AltSoftSerial
- DFRobotDFPlayerMini

Then open up that file and flash your board with it. You can find step-by-step directions for flashing by selecting your board [here](https://www.arduino.cc/en/Guide).

## Setting up the transmitter

This project assumes that you have all 10 channels enabled on your Flysky i6 or i6X transmitter. It also assumes that you have the channels 5-10 assigned as follows:

- Ch5: VAA
- Ch6: VAB
- Ch7: SWA
- Ch8: SWB
- Ch9: SWC
- Ch10: SWD

I found [this video](https://www.youtube.com/watch?v=ZwM_AoKfoj0) helpful in getting my tranmitter set up. The only difference is that I left my output mode in PWM. Switching to PPM doesn't seem necessary for getting channels 7-10 set up.

## Making it work

For whatever reason I've found that your FlySky transmitter (controller) has to be turned off when you power up the receiver in order for the code to execute properly.

1. Plug your battery into your FS-1A6B. This should power up your RC receiver, your servos, your nano, and your DF mini.
2. Power up your transmitter. (If you haven't paired the reciever to the transmitter you will need to do that. The steps for that are outside the scope of this repo.)

## Controls
![Baby R2 Sounds Controls](https://user-images.githubusercontent.com/39142975/149840752-1e6b11ea-07b3-4312-a17c-db5ac8ca2787.png)

