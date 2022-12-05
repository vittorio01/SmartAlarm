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
