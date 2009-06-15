/**
\file
\author lcs09

\brief Rappresentazione dei permessi e degli intervalli temporali

 */


#ifndef __INTERVALS__H
#define __INTERVALS__H

/**include aggiunti*/
#include <time.h>

/** Lunghezza di un record restituito dalla ctime*/
#define CTIMELENGTH 26
/** Formato di un record time_t (per la stampa) */
#define FORMATO_TIME "%02d/%02d/%04d-%02d:%02d"
/** Formato di una targa*/
#define FORMATO_TARGA "AADDDAA"


/** Lunghezza di una stringa che rappresenta una targa */
#define LTARGA 7
/** Lunghezza di una stringa che rappresenta un estremo di un intervallo temporale */
#define LESTREMO 16
/** Lunghezza di una stringa che rappesenta un permesso (targa + estremi intervallo)*/
#define LRECORD (LTARGA+2*(LESTREMO)+1+1)

/** Rappresentazione di un intervallo di tempo

per il tipo 'time_t' vedi "man asctime". L'inizio e la fine sono compresi fra il 01/01/200 ed il 01/01/2020 */

typedef struct {
  /** inizio intervallo di tempo */
    time_t inizio;
  /** fine intervallo di tempo */
    time_t fine;
} intervallo_t;

void printIntervallo(intervallo_t in,char out[]);

int compIntervalli(intervallo_t *a,intervallo_t *b);

/** rappresentazione di un permesso ZTL come coppia targa intervallo */
typedef struct
{
  /** targa veicolo */
  char targa[LTARGA + 1];
  /** intervallo di tempo permesso*/
  intervallo_t in;
} permesso_t;

/** Trasforma una stringa

     XXXXXXX gg/mm/aaaa-hh:mm gg/mm/aaaa-hh:mm

    (che rappresenta un intervallo di permesso per la targa XXXXXXX
    in una struttura di tipo permesso_t - notare che c'e' un
    SINGOLO SPAZIO fra targa e primo estremo e fra primo e secondo estremo)

    L'implementazione e' utilizzabile in un ambiente multithreaded
    (quindi ad esempio usa ctime_r/localtime_r invece che ctime/localtime etc).

  \retval p (puntatore alla nuova struttura)
  \retval NULL se si e' verificato un errore (setta errno)
 */
permesso_t* convertiRecord(char r[]);



/** Trasforma una struttura di tipo permesso in una stringa r nel formato

    XXXXXXX gg/mm/aaaa-hh:mm gg/mm/aaaa-hh:mm

    \param r  la stringa da riempire (conterra' il record secondo il formato)
    \param pp permesso da convertire

    \retval  0 se tutto e' andato a buon fine
    \retval -1 altrimenti (setta errno)
             in questo caso il contenuto di r non viene modificato
*/

int convertiPermesso(permesso_t* pp ,char r[]) ;



/** Effettua la stampa su stdout di un intervallo in formato ctime/ctime_r

\param inter l'intervallo da stampare
 */
void stampaIntervallo(intervallo_t* inter);

/** Effettua la stampa su stdout di un permesso (targa,intervallo)

\param pr la struttura permesso da stampare
 */
void stampaPermesso(permesso_t* pr);
#endif