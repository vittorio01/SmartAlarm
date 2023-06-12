**Power Point Presentation** -> https://docs.google.com/presentation/d/10k4tyO-IFauvRD4opIbPKDKe18_IUEi6HgjZJo3L0wQ/edit?usp=sharing

**Video demonstration** -> https://youtu.be/sSwYLoQlOco

# SmartAlarm

SmartAlarm is a project that involves the development of an intelligent alarm clock capable of awakening, in the least annoying way possible, even the people most resistant to traditional methods including:
- The smartest ones who unconsciously turn off their alarm clocks in their sleep (including me too).
- The sleepiest ones, who can't wake up even with an atomic bomb, who set 50 alarms every 5 minutes capable of disturbing anyone within a radius of 20 meters.
- The laziest who, once awake, can't get out of bed and fall asleep again after a few seconds.


The project is being developed to run on a Ti MSP432 development board, equipped with an Arm Cortex M4 microcontroller, with its BoosterPack. The original idea is to implement in the alarm clock, in addition to the basic functions of a normal alarm clock, mini-games / activities capable of reactivating the brain activity of the user as quick as possible. 
## Usage Warnings 

The SmartAlarm alarm clock may lead to the development of the following symptoms:
- Puffy and pale face
- Long-term drowsiness
- Bad mood
- Mood swings and aggression
- Loss of interest in life (in the most extreme cases)

To avoid these symptoms, we strongly recommend that you set your alarm to get a minimum of 8 hours of sleep per night in order not to endanger the product, the individual and the community.
## Development

Moving on to serious things, the whole project is based on a structure formed by four main layers: one for managing the main functions of the alarm clock, one that represents the minigames that can be activated by the alarm clock, one for the ringtones system and one for all hardware management.

The diagram shows that the Hardware layer is the base of other layers and the clock system controls others projects parts (dotted nets represents dependency relations and arrows represent control relations).
<p align="center">
    <img src="/documentation/main_structure.png" alt="System structure">
</p>


# Hardware (Filippo, Vittorio)
The Hardware layers contains all functions dedicated for the hardware management. It contains:
- Initialization functions for all features (led, RTC clock, timers, buttons, joypad ADC and display).
- An autonomus timer system (PWM, delays and timer interrupts).
- Button state functions, dedicated for reading the state of the Two main BoosterPack buttons A and B.
- Joypad state function, dedicated for reading the joypad current position

The autonomus timer system is a small code dedicated for sharing 16bit timer and PWM buzzer resources in rutime. Contains:
- Two PWM dedicated functions, which used a fixed timer (Timer0) for tones generation. In particular, there is one function for the tone activation and one function for the deactivation.
- Four delay functions, which are used for controlling all the three timer left. 

In particular, all three delay functions verifies if there is one free timer and configures it in base of the right operation:
- Delay, which is a blocking delay function that stop the normal CPU activity for the specified time.
- Wait, which is a function that calls automatically an handler after a specified time and doesn't block the CPU activity.
- Rate, which is a function that calls multiple times a specific handler with a specified delay (like a repeated Wait function).
The fourth function is used for deactivate the timer choosen by the Rate function.

The display is the only hardware resource that in only initialized and not managed by the Hardware layer, because every layer has to program it in different ways.

# Clock system (Filippo)

This layer represents the operational basis of the project and has the task of managing all basic information including date, time and day of the week implementing an alarm clock system which, in addition to having the same characteristics as normal alarm clocks , allows you to launch and monitor minigames via the Activity launch system. From the user's point of view, the clock system manages two main menus: one dedicated to displaying information and one for changing settings. 

## Main screen

The main screen is displayed whenever the alarm clock does not have to do anything else. Like a normal alarm clock, this screen has to represent some necessary information.

Some ideas for future improvements:

- The backlighting of the display could be annoying during the night and consume energy. It would be nice to find a system to keep the display backlight on only when the device understands how much it is being used, such as when a key is pressed or when a movement is received
  
- Some people may leave the alarm clock upside down. A future implementation may use the giroscope to recognize the right position and rotate the screen automatically. 


## Settings menu

The settings menu is used for changing basic information and assigning alarms. From a graphical point of view, it is a simple menu accessible by pressing a key which contains a list of modifiable information (date and time) and a submenu for setting alarms.

Ideas for future upgrades:
- Implement a system which allows the user to select different ringtones at different times
- Some useful settings may change other aspects of the alarm such as the volume of ringtones and a specific ringtone
- An even more complex system could allow the user to choose one or more days of the week in which to activate a single ringtone (actually management could be too difficult)


# Activity launch system (Ennio)

The activity launch system is an aspect of programming that deserves its own description. The idea is to create a small system capable of launching a minigame randomly, having a list of choices available. Launching activities corresponds to launching activity-specific functions and handling function return different results.

Ideas for future upgrades:
- the clock system might show a specific screen image when the alarm occours ,until the user is ready to play. One idea might be to display a dedicated waiting screen and launch the game on a keypress.

### Activities (Ennio, Vittorio)

Each activity is actually built and packaged as a function that is launched by the activity launch system. The functions can use all the hardware devices managed in the Hardware layer. The functions must return a predetermined value to tell the clock system how the task was performed:
 
- Complete Execution, in case the task was executed successfully
- Inactive, if the user does not react to the stimuli

Activities can be of any type (should cause the user to wake up completely instead of falling asleep again). Two minigames already developed are:
- Combo Master. The user has to repeat all exact five given combinations with buttons (A and B) and joypad (for arrows). If the user doesn't respect the given order, the level will be resetted.
- Treasure hunt. The user has to move the pointer with the joypad to find the hidden area.

Ideas for future upgrades:
- Add one more activity state Canceled, triggered when the user doesn't like the current game.

# Ringtones system (Vittorio)

This layer simply deals with the management and triggering of ringtones. The ringtones are played cyclically via the built-in buzzer and can be of different lengths.

The ringtone system uses timers and buzzer without blocking the normal execution of the clock system.

Ideas for future upgrades:
- Add one function to turn on a specific ringtones instead using a random system which choose automatically ones.

# Project structure
The file ![main.c](/main.c) contains the basic code for initialize all hardware and ttart the clock system, which set up the main screen and provide all the features of the alarm.

The folder ![modules](/modules) contain all four system layers in four different dedicated subfolders. Each layer is programmed as a library (*.h and *.c files) and can contains other resources like images or other libraries:

- The folder ![activities_launcher](/modules/activities_launcher) contains the activity launcher and all minigames in the subfolder ![activities](/modules/activities_launcher/activities). Each minigame is structured and packed as a sublibrary.
- The folder ![ringtones_manager](/modules/ringtones_manager) contains the ringtones system and all ringtones packed with a *.h files in the ![ringtones](/modules/ringtones_manager/ringtones) subfolder.
- The folder ![hardware](/modules/ringtones_manager) contains the hardware layer.

# Compiling the project
SmartAlarm ia a project for MSP432 development kit with booster Pack. 

This project contains necessary files to be compiled and loaded with Code Composer Studio.

For the correct compilation, the main folder of the project must be completed by adding the driverlib folder, which is excluded from the GitHub project. It can be downloaded directly from the official board site, unpacked, renamed and putted directly in the project.

# Acknowledgements

![https://www.unitn.it/](https://www.unitn.it/sites/www.unitn.it/themes/unitn_theme/images/newlogo_unitn_it.png)
