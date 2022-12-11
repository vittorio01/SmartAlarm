# SmartAlarm

SmartAlarm è un progetto che prevede lo sviluppo di una sveglia intelligente in grado di risvegliare, nel modo meno brusco possibile, anche le persone più resistenti ai metodi tradizionali tra cui:
- I più furbi che spengono le sveglie inconsciamente nel sonno (tra cui anche me).
- I più sonnolenti, che non riescono a svegliarsi neanche con una bomba atomica, che mettono 50 sveglie a distanza di 5 minuti in grado di disturbare qualsiasi persona nel raggio di 20 metri.
- I più pigri che, una volta svegli, non riescono ad alzarsi dal letto e si riaddormentano dopo qualche secondo.

Il progetto viene sviluppato per funzionare su una scheda di sviluppo Ti MSP432, dotata di un microcontrollore Arm Cortex M4, con il relativo BoosterPack.
L'idea originale è quella di implementare nella sveglia, oltre le funzioni base di una normale sveglia, dei minigiochi/attività in grado di riattivare il più velocemente possibile l'attività cerebrale del mal capitato. 
## Avvertenze sull'utilizzo 

La sveglia SmartAlarm potrebbe indurre allo sviluppo dei seguenti sintomi:
- Viso gonfio e pallido
- Sonnolenza a lungo termine
- Cattivo umore
- Sbalzi d'umore e aggressività 
- Perdita di interesse nella vita (nei casi più estremi)

Per evitare questi sintomi consigliamo caldamente di impostare la sveglia in modo da dormire un minimo di 8 ore per notte per non mettere in pericolo il prodotto, l'individuo e la comunità.
## Linee guida per lo sviluppo 

Passando alle cose serie, l'intero progetto si basa su una struttura formata da due layer principali: uno per la gestione delle funzioni principali della sveglia e uno che rappresenta i minigiochi che possono essere attivati dalla sveglia. 

<p align="center">
    <img src="/documentation/main_structure.png" alt="System structure">
</p>

# Clock system (1 persona)

Questo layer rappresenta la base operativa del progetto e ha il compito di gestire tutte informazioni basilari tra cui data, ora, giorno della settimana, informazioni ambientali (temperatura e luce) implementare un sistema di sveglie che, oltre ad avere le stesse caratteristiche delle sveglie normali, permette di lanciare e monitorare i minigiochi tramite l'Activity launch system. Il clock system gestisce, dal punto di vista dell'utente, due menu principali: uno dedicato alla visualizzazione delle informazioni e uno per la modifica delle impostazioni. 

## Schermata principale

La schermata principale viene visualizzata ogni volta che la sveglia non deve eseguire altre operazioni. Come una normale sveglia, questa schermata deve rappresentare alcune informazioni necessarie (data, ora, giorno della settimana,...) e alcune opzionali per rendere il tutto più figo (temperatura, giorno/notte,...). Il desing può essere scelto liberamente dal programmatore assegnato (per favore fallo bello e stiloso).
<p align="center">
    <img width="200" src="/documentation/main.png" alt="Main panel">
</p>
<p align="center"> 
    Esempio Scemo
</p>
Alcune idee per la realizzazione:
  
- La retroilluminazione del display potrebbe dare fastidio durante i periodi notturni e consumare energia. Sarebbe carino trovare un sistema per tenere accesa la retroilluminazione del display solo quando il dispositivo capisce quanto viene utilizzato, tipo alla pressione di un tasto o alla ricezione di un  movimento
  
- Qualche persona poco intelligente potrebbe lasciare la sveglia sottosopra. Ricordate come il professore ha implementato l'accellerometro? Bene ci siamo capiti

## Menù impostazioni

Il menù impostazioni viene utilizzato per la modifica delle informazioni base e l'assegnazione delle sveglie. Dal punto di vista grafico è un semplice menù accessibile tramite la pressione di un tasto che contiene una lista di informazioni modificabili (data e ora) e un sottomenù per impostare le sveglie.

Idee per la realizzazione:
- Sarebbe molto soddisfacente poter scorrere fra le impostazioni utilizzanto il pad analogico a sinistra e selezionare l'opzione tramite uno dei due tasti a destra 
- Alcune impostazioni utili potrebbero modificare altri aspetti della sveglia come il volume delle suonerie
- Quando l'alimentazione viene a mancare il menu dovrebbe essere lanciato subito dopo all'avvio successivo per impostare tutte le informazioni perse.
### Sottomenù sveglie 

Questo sottomenu viene dedicato interamente alla gestione delle sveglie. Per la realizzazione si potrebbe optare per una versione semplice che contiene un numero predefinito di sveglie oppure una versione più complessa che da la possibilità di assegnarne un numero arbitrario.

Idee per la realizzazione:

- Tutte le sveglie potrebbero utilizzare la stessa suoneria ma i risultato sarebbe alquanto noioso. Potrebbe quindi essere l'utente stesso a scegliere le suonerie.
- Un sistema ancora più complesso potrebbe permettere all'utente di scegliere uno o più giorni della settimana in cui attivarsi (effettivamente la gestione potrebbe risultare troppo difficile)

## Activity launch system 

L'activity launch system è un aspetto della programmazione che merita una sua descrizione a parte. L'idea è quella di creare un piccolo sistema in grado di lanciare un minigioco in modo casuale, avendo una lista di scelte disponibili.
Il lancio delle attività corrisponde effettivamente all'avvio delle funzioni specifiche delle attività e alla gestione delle variabili di ritorno della funzione (vedi la descrizione).

Idee per la realizzazione:

- Dal punto di vista della programmazione un'idea efficente potrebbe essere quella di inserire un array di puntatori a funzioni in cui ogni campo punta ala funzione di un'attività specifica. In questo modo l'interfaccia deve solamente sorteggiare un indice casuale dell'array e lanciare la funzione corrispondente. 
- l'attività, dato che viene lanciata subito dopo all'attivazione di una sveglia, deve avviarsi una volta che l'utente è pronto per giocare. Un'idea potrebbe essere quella di visualizzare una schermata di attesa dedicata e di avviare il gioco alla pressione di un tasto.

<p align="center"> 
    <img width="200" src="/documentation/game_launch.png" alt="Game launch">
</p>

- Il sistema dovrebbe inoltre verificare l'esito dell'esecuzione dei minigames ed eseguire operazioni in caso di esito negativo. Ad esempio, lanciare un altra attività nel caso in cui quella precedente restituisca uno stato di inattività .

## Ringtones system 

Questo layer si occupa semplicemente della gestione e dell'avvio delle suonerie. Le suonerie vengono ripodotte tramite il buzzer integrato e possono essere di diversa durata.

Idee per l'implementazione:

- Su internet si trovano molti progetti per la riproduzione di suonerie. Una buona idea sarebbe quella di rappresentare le suonerie come array contenenti toni, che vengono riporodotti in serie ad intervalli prestabiliti (tipo 100ms)

- Sempre su internet si trovano moltissime suonerie già create precedentemente (l'ideale per non perdere tempo a scrivere manualmente i toni)

### Activities

Ogni attività viene concretamente realizzata e impacchettata come una funzione che viene lanciata dall'activity launch system. Le funzioni possono utilizzare tutti i disositivi hardware della scheda con alcune restrizioni (il sistema RTC e uno dei timer devono rimanere inalterati per il corretto funzionamento del clock system). Le funzioni devono ritornare un valore prestabilito per segnalare al clock system come è stata eseguita l'attività:
 
- Completa esecuzione, nel caso in cui l'attività è stata eseguita correttamente 
- Inattivo, nel caso l'utente non reagisce agli stimoli
- Annullato, nel caso in cui all'utente non piace il gioco

Le attività possono essere di qualunque tipo (devono portare l'utente a svegliarsi completamente invece di farlo riaddormentare di nuovo). Alcune idee possono essere:

- snake 
- risoluzione di operazioni algebriche 
- ...
- Non lo so non mi vengono alte idee

# Struttura del progetto (ancora da perfezionare)
La programmazione, dato che deve essere composta da più parti, deve essere separata in più files. Nel progetto Github si trovano diverse sottocartelle dedicate allo sviluppo delle varie sezioni:

- La cartella ![activities](/src/activities) contiene tutti i minigiochi (un singolo file contiene un minigioco dedicato), che vengono registrati in un file games, che contiene tutti i riferimenti alle funzioni (ancora da perfezionare) e l'activity launch system in un file dedicato.

- La cartella ![ringtones](/src/ringtones) contiene il sistema per la gestione delle suonerie e le suonerie stesse

- La cartella ![Libraries](/src/Libraries) contiene eventuali librerie utilizzate dal clock system. Nelle cartelle ![ringtones](/src/ringtones) e ![activities](/activities) sono presenti altre sottocartelle dedicate

- Il file ![SmartAlarm.ino](/SmartAlarm.ino) contiene l'intero layer dedicato alla gestione dell'intero sistema ed è il file che deve effettivamente essere mandato in compilazione (tutti i moduli hanno un file ".h", che devono essere aggiunti nel codice principale tramite #import)

- Il file ![activity_system_launcher.cpp](/src/activities/activity_system_launcher.cpp) deve contenere l'implementazione delle seguenti funzioni:
    * `state` è un tipo di dato definito tramite 
        `typedef state enum {RUNNING, USER_INACTIVE, TASK_COMPLETED, TASK_CLOSED, UNDEFINED}`
    * `state launch_game()` per lanciare casualmente un minigioco. La funzione tiene occupato il microcontrollore fino al suo completamento e restituisce un esito.
- Il file ![ringtones.cpp](/ringtones/ringtones.cpp) deve contenere l'implementazione delle seguenti funzioni:
    * `void start_ringtone(unsigned int piezoPin)` per lanciare casualmente una suoneria. La funzione, una volta che viene lanciata, la suoneria viene riprodotta ciclicamente fino a quando non viene invocata la funzione `void start_ringtone(int ringtone)`.
    * `bool start_ringtone(unsigned int piezoPin,unsigned int ringtone)` per lanciare una suoneria specifica. L'esecuzione rimane la stessa di `void start_ringtone()` ma restituisce `false` in caso di errore
    * `void stop_ringtone()` per fermare a suoneria attualmente in riproduzione. 
    * `int get_ringtones_number()` restituisce il numero di suonerie registrate.
    * `char* get_ringtone_description(unsigned int ringtone)` restituisce una stringa con le informazioni della suoneria
    
Il clock system, quando deve dialogare con gli altri moduli, richiama semplicemente le funzioni implementate nei files ![ringtones.cpp](/src/ringtones/ringtones.cpp) e ![activity_system_launcher.cpp](/src/activities/activity_system_launcher.cpp). 
  
