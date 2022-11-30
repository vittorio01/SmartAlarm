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
![main structure](/documentation/main_structure.png)

### Clock system (1 persona)
Questo layer rappresenta la base operativa del progetto e ha il compito di gestire tutte informazioni basilari tra cui data, ora, giorno della settimana, informazioni ambientali (temperatura e luce) implementare un sistema di sveglie che, oltre ad avere le stesse caratteristiche delle sveglie normali, permette di lanciare e monitorare i minigiochi tramite il Activity launch system. 

