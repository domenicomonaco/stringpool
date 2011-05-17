/*
 * @filename: spstring.c
 * @author: macbook
 * @rev: 0.1
 * @license: GPLV2
 * @date: 16/mag/2011
 * @desc: 
 */

#include <stdio.h>
#include <stdlib.h>

#include "bool.h"
#include "spstring.h"

int main(void) {
	return EXIT_SUCCESS;
}

/**
 * \fn
 *
 * Inizializza la struttura stringpool. Pone il contatore di elementi a 0 e rende tutti gli slot disponibili.
 *
 */
void sp_initialize_stringpool(stringpool* sp){

	/**
	 * Indirizzo alla struttura stringpool
	 *
	 * Abbiamo solo l'indirizzo
	 */
	sp = (stringpool*) calloc(1, sizeof(stringpool));/**< sp, allocazione di una struct stringpool all'indirizzo passato */


}

/** \fn string* sp_new_string(const char* str)
 *
 * Crea una nuova stringa il cui contenuto è uguale a quello del parametro in ingresso str.
 *
 * 	\param [in] str
 */
string* sp_new_string(const char* str){

	string* new_string = (string*) calloc(1, sizeof(string));/**< inizializza una struct di tipo string*/

	(*new_string).allocated_size = sizeof(str); /** Salva in new_string->allocated size la lunghezza della stringa da allocare*/

	(*new_string).char_array = (char*) calloc((new_string.allocated_size+1), sizeof(char));

	return new_string;
}


//string* sp_new_string_as_struct(const string* str){}
//Crea una nuova stringa il cui contenuto è uguale a quello del parametro in ingresso str.

//string* sp_new_empty_string(int len){} //Crea una nuova stringa vuota (cioè “”) creata dinamicamente, la cui dimensione fisica è pari a len caratteri.

//int sp_get_allocated_size(const string* str){} //Restituisce la dimensione massima (fisica) allocata dinamicamente per la stringa.

//string* sp_strcpy(string* copy, const char* original, int offset){} //Copia il contenuto della stringa original in copy, a partire dal carattere in posizione offset di copy. Se offset è 0, allora la copia avviene dall’inizio della stringa copy. La dimensione di copy deve essere pari o maggiore di quella di original.

//void sp_free(string* str){} //Funzione per deallocare una stringa str allocata dinamicamente. Dopo la deallocazione str vale NULL

//int sp_strlen(const string* str){} //Funzione che calcola e restituisce la lunghezza logica della stringa in ingresso str.

//boolean sp_strcmp(const string* str1, const char* str2){} //Funzione che confronta due stringhe e restituisce il corrispettivo valore di verità.

//string* sp_strcat(const char* str1, const char* str2){} //La funzione crea una nuova stringa ottenuta dalla concatenazione delle due stringhe passate in ingresso, le quali non sono alterate dalla funzione.

//string* sp_strcat_as_struct(const string* str1, const string* str2){} //La funzione crea una nuova stringa ottenuta dalla concatenazione delle due stringhe passate in ingresso, le quali non sono alterate dalla funzione.

//string* sp_lower_case(const string* str){} //La funzione restituisce una nuova stringa ottenuta ponendo in minuscolo ciascun carattere della stringa in ingresso che non è alterata. Per esempio, se si passa come parametro in ingresso “Ciao”, allora la funzione restituirà una nuova stringa “ciao” in output.

//string* sp_upper_case(const string* str){} //La funzione restituisce una nuova stringa ottenuta ponendo in maiuscolo ciascun carattere della stringa in ingresso che non è alterata. Per esempio, se si passa come parametro in ingresso “Ciao”, allora la funzione restituirà una nuova stringa “CIAO” in output.

//void sp_initialize_stringpool(stringpool* sp){} //Inizializza la struttura stringpool. Pone il contatore di elementi a 0 e rende tutti gli slot disponibili.

//void sp_free_stringpool(stringpool* sp){} //Libera la memoria per tutte le stringhe salvate in strings e re-inizializza la struttura stringpool (positions e used_counter azzerati).

//int sp_sizeof(const stringpool* sp){} //Restituisce il numero di stringhe in sp. Restituisce 0 se lo stringpool è vuoto; -1 se sp è NULL

//boolean sp_isempty(const stringpool* sp){} //Restituisce un valore booleno stante a indicare se lo stringpool è vuoto o contiene uno o più elementi.

//boolean sp_isfull(const stringpool* sp){} //Restituisce un valore booleno stante a indicare se lo stringpool contiene già il massimo numero di elementi consentiti oppure no.

//int sp_find_string(const stringpool* sp, const string* str){} //Cerca la stringa str all’interno dello stringpool e ne restituisce la posizione, nel caso sia presente.

//string* sp_get_string(const stringpool* sp, int pos){} //Restituisce il puntatore alla stringa str che occupa la posizione pos all’interno dello stringpool.

//boolean sp_add_string(stringpool* sp, string* str){} //Aggiunge la stringa puntata da str all’interno dello stringpool. Nessuna operazione è compiuta se str e/o sp sono nulli, oppure se sp è pieno.

//boolean sp_add_string_pos(stringpool* sp, string* str, int pos){} //Aggiunge la stringa str all’interno dello stringpool in posizione pos. Nessuna operazione è compiuta se str e/o sp sono nulli, se pos è fuori dall’intervallo 0<= pos < MAX_DIM_STRING_POOL

//string* sp_remove_string(stringpool* sp, int pos){} //Rimuove e restituisce la stringa str all’interno dello stringpool in posizione pos. Nessuna operazione è compiuta se sp è nullo, oppure se pos è fuori dall’intervallo pos, MAX_DIM_STRING_POOL[

//boolean sp_replace_string(stringpool* sp, int pos, string* newstr){} //Sostituisce la stringa all’interno dello stringpool in posizione pos, rimpiazzandola con str. Nessuna operazione è compiuta se str e/o sp sono nulli, oppure se pos è fuori dall’intervallo [pos, MAX_DIM_STRING_POOL[

//int sp_save_to_file(stringpool* sp, const string fname){} //Salva il contenuto dello stringpool in un file di testo, con il nome specificato dal secondo paramentro fname. Ogni elemento sarà salvato su una riga diversa.

//int sp_load_from_file(stringpool* sp, const string fname){} //Carica il contenuto del file di test fname nello o stringpool. L’intera stringa letta su una riga sarà un elemento dello stringpool.

//void bubble_sort(stringpool* sp){} //Ordina alfabeticamente gli elementi dello stringpool, applicando l’algoritmo di bubble sort.

//int bin_search(const stringpool* sp, const string str){} //Cerca la stringa str all’interno dello stringpool ordinato attraverso l’algoritmo di ricerca binaria. Ne restituisce la posizione, nel caso in cui str sia presente.
