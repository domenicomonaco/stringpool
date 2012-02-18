/** \file stringpool.h
 * \brief Header per tipi di dati stringpool
 *
 * Definizioni di variabili e tipi di dato per la libreria stringpool
 *
 * \author Domenico Monaco, domenico.monaco@kiuz.it
 * \date 2011
 * \section license Licenza
 * GPLv2 http://www.softwarelibero.it/gnudoc/gpl.it.txt
 * Per maggiori informazioni visitare il link o visualizzare il file LICENSE
 */

#ifndef STRINGPOOL_H_
#define STRINGPOOL_H_/**< Impedisce inclusioni multiple */

/** \def UNUSED_SLOT
 * Standard per l'identificazione degli slot Liberi
 * Deve contenere interi, si consiglia UNUSED_SLOT 0
 */
#define UNUSED_SLOT 0

/** \def USED_SLOT
 * Standard per l'identificazione degli slot Occupati
 * Deve contenere interi, si consiglia USED_SLOT 1
 */
#define USED_SLOT 1

/** \def EMPTY_STRING_POOL
 * Standard per l'identificazione del numero di stringhe contenute in stringpool per identificarlo come Vuoto.
 * Deve contenere interi, si consiglia EMPTY_STRING_POOL 0.
 */
#define EMPTY_STRING_POOL 0

/** \def MAX_DIM_STRING_POOL
 * Numero massimo di stringhe che stringpool può contenere. Identifica anche lo stato di stringpool Pieno.
 * Deve contenere un'intero maggiore di 0, si consiglia MAX_DIM_STRING_POOL 10.
 */
#define MAX_DIM_STRING_POOL 10

/** \def SIZE_STRING_STRUCT
 * Dimensione di base per l'allocazione della struttura string
 */
#define SIZE_STRING_STRUCT 1

/** \def MAX_CHAR_STRING_LOAD_FROM_FILE
 * Valore massimo per l'allocazione dell'array di memorizzazione della stringa da file
 */
#define MAX_CHAR_STRING_LOAD_FROM_FILE 255

/** \def PATTERN_READ_WRITE_LINE
 * Pattern completo per la lettura/scrittura su file
 */
#define PATTERN_READ_WRITE_LINE "%d , %d , %s ;\n"

/** \def PATTERN_READ_WRITE_START_LINE_SHORT
 * Pattern parziale iniziale per la scrittura su file
 */
#define PATTERN_READ_WRITE_START_LINE_SHORT "%d , %d ,"

/** \def PATTERN_READ_WRITE_END_LINE_SHORT
 * Pattern parziale finale per la scirttura su file
 */
#define PATTERN_READ_WRITE_END_LINE_SHORT " ;\n"

/** \def PATTERN_READ_WRITE_INIT
 * Pattern completo per la lettura/scrittura della riga iniziale su file
 */
#define PATTERN_READ_WRITE_INIT "%d ;\n"

/** \struct string
 * Tipo di dato non primitivo string
 * Insieme di caratteri da allocare dinamicamente, contiene anche un contatore della sua dimensione
 */
typedef struct {
	char* char_array; /**< Vettore a caratteri caratteri tramite puntatore a caratteri, rappresenta il contenuto della stringa */
	int allocated_size; /**< Contiene la dimensione massima allocata per tale string, se N>0 allora è possibile inserire N-1 Caratteri con  carattere  di terminazione \0 in posizione N. */
} string;

/** \struct stringpool
 * Tipo di dato non primitivo stringpool
 * Insieme dinamico di elementi di tipo string, contiene anche il numero e la posizione degli slot occupati.
 * Il numero di slot che stringpool può contenere è definito da MAX_DIM_STRING_POOL.
 */
typedef struct {
	string* strings[MAX_DIM_STRING_POOL]; /**< Array a puntatori di tipo stringa, rappresentano gli slot di stringpool */
	int used_counter; /**< Contatore delle locazioni utilizzate */
	int positions[MAX_DIM_STRING_POOL]; /**< Array per identificare quali posizioni sono occupati o libere */
} stringpool;

#endif /* END STRINGPOOL_H_ */
