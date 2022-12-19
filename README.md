# Esonero Reti UDP DNS 22 23
 
    Il client è avviato passando come parametri di input il nome e il numero di porta del server UDP da contattare, rispettando il seguente formato : srv.di.uniba.it:56700.

    Il client legge la scelta dell'operazione da compiere (usando i caratteri +, x, -, /, rispettivamente per Addizione, Moltiplicazione, Sottrazione e Divisione) e due numeri interi dallo standard input, rispettando il seguente formato: + 23 45

    Il client invia al server quanto letto da tastiera.
    
    Ricevuti i dati dal client, il server visualizza sullo std output un messaggio contenente sia il nome sia l’indirizzo dell’host del client e l'operazione da eseguire (Esempio: Richiesta operazione '+ 23 45' dal client pippo.di.uniba.it, ip 193.204.187.154).

    Il server segue l'operazione richiesta e invia il risultato al client nell'esatto formato indicato negli esempi riportati di seguito:
        23 + 45 = 68 per l'addizione;
        23 / 45 = 0.51 per la divisione;
        23 * 45 = 1035 per il prodotto;
        23 - 45 = -22 per la sottrazione.

    Il client legge la risposta inviata dal server e visualizza la risposta sullo std output (Esempio: Ricevuto risultato dal server srv.di.uniba.it, ip 193.204.187.166: 23 + 45 = 68).

    Il client legge dallo standard input la successiva operazione da compiere.

    Se invece di un'operazione è inserito il carattere =, il client termina qui il suo processo; altrimenti, torna al punto 2.
    
    Il server non termina mai il suo processo.
