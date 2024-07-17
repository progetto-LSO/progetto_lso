Lo studente dovrà realizzare la simulazione di un sistema che modella una libreria per un numero non precisato di utenti. 

- Gli utenti devono potersi registrare e loggare al server.
- Il libraio ha una lista di libri disponibili nella libreria, con il numero di copie disponibili, numero di copie prese in prestito, e per ognuno delle copie prese in prestito un nome o identificativo del cliente che le ha prese in prestito, un timestamp del giorno in cui è stato preso in prestito, e una data per la restituzione del libro.
- Gli utenti possono cercare un libro e possono prenderlo in prestito se ci sono ancora copie disponibili.
- Gli utenti possono prendere in prestito un numero K di libri, dove K è deciso dal libraio.
- Gli utenti mettono nel carrello tutti i libri presi in prestito e poi possono effettuare il check-out.

Se un altro utente nel frattempo ha preso l'ultima copia disponibile di quel libro, l'altro utente riceverà un messaggio. 

Il libraio dovrà contattare con un messaggio un cliente che non ha restituito il libro dopo la scadenza prevista per la restituzione.

- Registrazione può essere sviluppata tramite database sql o file
- I libri possono essere gestiti in un database, json, etc..
- Opzionale: La ricerca di un libro può essere fatta per genere, nome oppure da lista di quelli disponibili