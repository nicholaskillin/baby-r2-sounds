# baby-r2-sounds

This repo is a work in progress. I have printed and assembled one of [Mr. Baddeley's](https://www.patreon.com/mrbaddeley) Baby R2 droids. He has all of the instructions for getting the droid moving, but I wanted to add sounds as well. This guide will cover the modifications to the droid. For more info on how to build the droid itself check out his patreon.

Additional Hardware used:

- Ardunio Mega2560
- LED

## Setting up the Circuit

I wanted to keep as much of Mr. Baddeley's design in place as possible, so I decided to power my arduino through the FS-iA6B.

You can also send commands to the arduino via the FS-iA6B by connecting the arduino to the iBus output. You will need to connect the Arduino to the iBus of the FS-iA6B as shown.

![BabyR2 Sound Test 2022-01-13 at 1 48 48 PM](https://user-images.githubusercontent.com/39142975/149513009-72999688-93f0-42d4-bf98-009dc90dc068.jpg)

## Setting up the software

You should be able to place the `baby_r2_sounds.ino` file into a folder called `baby_r2_sounds` and then open that up in the [Arduino software](https://www.arduino.cc/en/software).

You will need to install the `iBusBM` library which can be found in the Library Manager in the Arduino IDE.

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

1. Plug your battery into your FS-1A6B. This should power up your RC receiver, your servos, and your Mega2650
2. Power up your transmitter. (If you haven't paired the reciever to the transmitter you will need to do that. The steps for that are outside the scope of this repo.)
3. Now SWD should be able to turn on/off the LED light you have connected.

## I thought this was about making sounds, not turning a light on/off

Well yes, it is. But before I could do that I had to figure out how to send commands to an arduino via my RC receiver.

Now that I have that part figured out I plan to update this in the future. Future plans include:

- Actually making sounds instead of turning on/off an LED
- Swapping out the Mega2560 for a much smaller board
