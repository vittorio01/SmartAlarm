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
## Development guidelines 

Moving on to serious things, the whole project is based on a structure formed by three main layers: one for managing the main functions of the alarm clock, one that represents the minigames that can be activated by the alarm clock and one for the ringtones. /!\ 

<p align="center">
    <img src="/documentation/main_structure.png" alt="System structure">
</p>

# Clock system (1 person)

This layer represents the operational basis of the project and has the task of managing all basic information including date, time, day of the week, "" environmental information (temperature and light)"" implementing an alarm clock system which, in addition to having the same characteristics as normal alarm clocks , allows you to launch and monitor minigames via the Activity launch system. From the user's point of view, the clock system manages two main menus: one dedicated to displaying information and one for changing settings. 

## main screen

The main screen is displayed whenever the alarm clock does not have to do anything else. Like a normal alarm clock, this screen has to represent some necessary information (date, time, day of the week,...) ""and some optional ones to make it cooler (temperature, day/night,...)"". The design can be chosen freely by the assigned programmer (please make it nice and stylish).
<p align="center">
    <img width="200" src="/documentation/main.png" alt="Main panel">
</p>
<p align="center"> 
    Esempio Scemo
</p>
""Some ideas for making:
  
- The backlighting of the display could be annoying during the night and consume energy. It would be nice to find a system to keep the display backlight on only when the device understands how much it is being used, such as when a key is pressed or when a movement is received
  
- Some unintelligent people may leave the alarm clock upside down. Do you remember how the professor implemented the accelerometer? Well we understand each other 
""

## Settings menu

The settings menu is used for changing basic information and assigning alarms. From a graphical point of view, it is a simple menu accessible by pressing a key which contains a list of modifiable information (date and time) and a submenu for setting alarms.

""Ideas for making:
- It would be very satisfying to be able to scroll through the settings using the analog pad on the left and select the option using one of the two buttons on the right
- Some useful settings may change other aspects of the alarm such as the volume of ringtones
- When power fails the menu should be launched soon after next boot to set all lost information.""

### Alarm submenu
""
This submenu is entirely dedicated to alarm management. For the realization one could opt for a simple version that contains a predefined number of alarm clocks or a more complex version that gives the possibility of assigning an arbitrary number. 

Ideas for making:

- All alarm clocks could use the same ringtone but the result would be quite boring. It could therefore be the user himself who chooses the ringtones.
- An even more complex system could allow the user to choose one or more days of the week in which to activate (actually management could be too difficult)""


## Activity launch system

The activity launch system is an aspect of programming that deserves its own description. The idea is to create a small system capable of launching a minigame randomly, having a list of choices available. Launching activities corresponds to launching activity-specific functions and handling function return variables (see description).

Ideas for making:

- From a programming point of view, an efficient idea could be to insert an array of pointers to functions in which each field points to the function of a specific activity. In this way the interface has only to draw a random index of the array and launch the corresponding function.
- the activity, since it is launched immediately after an alarm is activated, must start once the user is ready to play. One idea might be to display a dedicated waiting screen and launch the game on a keypress. From a practical point of view, the random system for launching the activity should be implemented separately from the waiting screen.

<p align="center"> 
    <img width="200" src="/documentation/game_launch.png" alt="Game launch">
</p>

- The system should also check the outcome of the execution of the minigames and perform operations in case of a negative outcome. For example, launch another activity in case the previous one returns an inactive status.

## Ringtones system 
""
This layer simply deals with the management and triggering of ringtones. The ringtones are played cyclically via the built-in buzzer and can be of different lengths.

Ideas for implementation:

- There are many projects for playing ringtones on the internet. A good idea would be to represent ringtones as arrays containing tones, which are played back in series at pre-established intervals (like 100ms)

- Always on the internet there are many ringtones already created previously (ideal for not wasting time manually writing the tones)""

### Activities

Each activity is actually built and packaged as a function that is launched by the activity launch system. The functions can use all the hardware devices of the board with some restrictions (the RTC system and one of the timers must remain unchanged for the correct functioning of the clock system). The functions must return a predetermined value to tell the clock system how the task was performed:
 
- Complete Execution, in case the task was executed successfully
- Inactive, if the user does not react to the stimuli
- Canceled, in case the user doesn't like the game

Activities can be of any type (should cause the user to wake up completely instead of falling asleep again). Some ideas can be:

- snake
- solving algebraic operations
- ...
- I don't know, I don't have other ideas

# Project structure
La programmazione, dato che deve essere composta da più parti, deve essere separata in più files. Le cartelle ![activities](/modules/activities_launcher) e ![ringtones](/modules/ringtones_manager) contengono la programmazione dell'activities system launcher e del ringtones manager, che verranno implementati come delle librerie da aggiungere al programma principale.
Nel progetto Github si trovano diverse sottocartelle dedicate allo sviluppo delle varie sezioni:

- La cartella ![activities](/modules/activities_launcher) contiene tutti i minigiochi (un singolo file contiene un minigioco dedicato), che vengono registrati in un file games, che contiene tutti i riferimenti alle funzioni (ancora da perfezionare) e l'activity launch system in un file dedicato.

- La cartella ![ringtones](/modules/ringtones_manager) contiene il sistema per la gestione delle suonerie e le suonerie stesse

- La cartella ![lib](/lib) contiene eventuali librerie utilizzate dal clock system. Nelle cartelle ![ringtones](/modules/ringtones_manager) e ![activities](/modules/activities_launcher) sono presenti altre sottocartelle dedicate

- Il file ![main.c](/main.c) contiene l'intero layer dedicato alla gestione dell'intero sistema ed è il file che deve effettivamente essere mandato in compilazione (tutti i moduli hanno un file ".h", che devono essere aggiunti nel codice principale tramite #include)

- Il file ![activities.cpp](/modules/activities_launcher/activities.cpp) deve contenere l'implementazione delle seguenti funzioni:
    * `state` è un tipo di dato definito tramite 
        `typedef state enum {RUNNING, USER_INACTIVE, TASK_COMPLETED, TASK_CLOSED, UNDEFINED}`
    * `state launch_game()` per lanciare casualmente un minigioco. La funzione tiene occupato il microcontrollore fino al suo completamento e restituisce un esito.
- Il file ![ringtones.cpp](/modules/ringtones_manager/ringtones.cpp) deve contenere l'implementazione delle seguenti funzioni:
    * `void start_ringtone(unsigned int piezoPin)` per lanciare casualmente una suoneria. La funzione, una volta che viene lanciata, la suoneria viene riprodotta ciclicamente fino a quando non viene invocata la funzione `void start_ringtone(int ringtone)`.
    * `bool start_ringtone(unsigned int piezoPin,unsigned int ringtone)` per lanciare una suoneria specifica. L'esecuzione rimane la stessa di `void start_ringtone()` ma restituisce `false` in caso di errore
    * `void stop_ringtone()` per fermare a suoneria attualmente in riproduzione. 
    * `int get_ringtones_number()` restituisce il numero di suonerie registrate.
    * `char* get_ringtone_description(unsigned int ringtone)` restituisce una stringa con le informazioni della suoneria

Dato che CCS non permette di utilizzare `bool` come tipo di dato, nelle cartelle lib di tutte le sezioni del progetto è presente una libreria che definisce questo tipo di dato.

Il clock system, quando deve dialogare con gli altri moduli, richiama semplicemente le funzioni implementate nei files ![ringtones.cpp](/modules/ringtones_manager/ringtones.h) e ![activities.cpp](/modules/activities_launcher/activities.h). 
  
