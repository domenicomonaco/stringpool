/**
 * \fn
 *
 * Inizializza la struttura stringpool. Pone il contatore di elementi a 0 e rende tutti gli slot disponibili.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "bool.h"
#include "spstring.h"

int main(void) {
	return EXIT_SUCCESS;
}

void sp_initialize_stringpool(stringpool* sp) {

	/**
	 * Indirizzo alla struttura stringpool
	 *
	 * Abbiamo solo l'indirizzo
	 */
	sp = (stringpool*) calloc(1, sizeof(stringpool));/**r< sp, allocazione di una struct stringpool all'indirizzo passato */
	(*sp).positions = 0;
	(*sp).used_counter = 0;

}

/**
 * Libera la memoria per tutte le stringhe salvate in strings e re-inizializza la struttura stringpool (positions e used_counter azzerati).
 *
 */
void sp_free_stringpool(stringpool* sp){
 free(sp);
}


/**
 * Crea una nuova stringa vuota (cioè “”) creata dinamicamente, la cui dimensione fisica è pari a len caratteri.
 *
 */
string* sp_new_empty_string(int len) {
	/**
	 * Inizializza st come puntatore a string
	 */
	string* st;

	/**
	 * Verifica se len maggiore di 0
	 */
	if (len > 0) {
		/**
		 * Se len maggiore di 0 alloca all'indirizzo st una struct string di dimensione len
		 */
		string* st = (string*) calloc(1, sizeof(string));
		(*st).allocated_size = len;
		(*st).char_array = (char*) calloc(len, sizeof(char));
	} else {
		/**
		 * Altrimenti associa a st NULL
		 */
		st = NULL;
	}

	return st;
}

/** \fn string* sp_new_string(const char* str)
 *
 * Crea una nuova stringa il cui contenuto è uguale a quello del parametro in ingresso str.
 *
 * 	\param [in] str
 */
string* sp_new_string(const char* str) {

	int len = strlen(str);

	string* new_string = sp_new_empty_string(len);/**< inizializza una struct di tipo string*/

	(*new_string).allocated_size = len; /** Salva in new_string->allocated size la lunghezza della stringa da allocare*/

	(*new_string).char_array = (char*) calloc(len+1,
			sizeof(char));

	return new_string;
}

/**
 * Restituisce la dimensione massima (fisica) allocata dinamicamente per la stringa.
 *
 */
int sp_get_allocated_size(const string* str) {
	int allocated_size = 0;

	allocated_size = (*str).allocated_size;

	return allocated_size;
}

/**
 * Funzione per deallocare una stringa str allocata dinamicamente. Dopo la deallocazione str vale NULL
 *
 */
void sp_free(string* str) {
	free(str);
}

/*
 * Funzione che calcola e restituisce la lunghezza logica della stringa in ingresso str.
 *
 */
int sp_strlen(const string* str) {
	int current_strlen = strlen(str);
	return current_strlen;
}

/*
 * Funzione che confronta due stringhe e restituisce il corrispettivo valore di verità.
 *
 */
boolean sp_strcmp(const string* str1, const char* str2){
	boolean is_equal = FALSE;

	return is_equal;
}

//Crea una nuova stringa il cui contenuto è uguale a quello del parametro in ingresso str.
string* sp_new_string_as_struct(const string* str){
	return str;
}

//Copia il contenuto della stringa original in copy, a partire dal carattere in posizione offset di copy. Se offset è 0, allora la copia avviene dall’inizio della stringa copy. La dimensione di copy deve essere pari o maggiore di quella di original.
string* sp_strcpy(string* copy, const char* original, int offset){
	return copy;
}

//La funzione crea una nuova stringa ottenuta dalla concatenazione delle due stringhe passate in ingresso, le quali non sono alterate dalla funzione.
string* sp_strcat(const char* str1, const char* str2){
	string* str;

	return str;
}

//La funzione crea una nuova stringa ottenuta dalla concatenazione delle due stringhe passate in ingresso, le quali non sono alterate dalla funzione.
string* sp_strcat_as_struct(const string* str1, const string* str2){
	return str1;
}

string* sp_lower_case(const string* str){
	return str;

} //La funzione restituisce una nuova stringa ottenuta ponendo in minuscolo ciascun carattere della stringa in ingresso che non è alterata. Per esempio, se si passa come parametro in ingresso “Ciao”, allora la funzione restituirà una nuova stringa “ciao” in output.

string* sp_upper_case(const string* str){
	return str;
} //La funzione restituisce una nuova stringa ottenuta ponendo in maiuscolo ciascun carattere della stringa in ingresso che non è alterata. Per esempio, se si passa come parametro in ingresso “Ciao”, allora la funzione restituirà una nuova stringa “CIAO” in output.

int sp_sizeof(const stringpool* sp){
	int size;

	return size;
} //Restituisce il numero di stringhe in sp. Restituisce 0 se lo stringpool è vuoto; -1 se sp è NULL

boolean sp_isempty(const stringpool* sp){
	boolean a=TRUE;

	return TRUE;

} //Restituisce un valore booleno stante a indicare se lo stringpool è vuoto o contiene uno o più elementi.

boolean sp_isfull(const stringpool* sp){
	boolean a=TRUE;

	return TRUE;


} //Restituisce un valore booleno stante a indicare se lo stringpool contiene già il massimo numero di elementi consentiti oppure no.


int sp_find_string(const stringpool* sp, const string* str){
	int a;

	return a;

} //Cerca la stringa str all’interno dello stringpool e ne restituisce la posizione, nel caso sia presente.

string* sp_get_string(const stringpool* sp, int pos){

	string* a;
	return a;

} //Restituisce il puntatore alla stringa str che occupa la posizione pos all’interno dello stringpool.

boolean sp_add_string(stringpool* sp, string* str){
	boolean a=TRUE;

	return TRUE;

} //Aggiunge la stringa puntata da str all’interno dello stringpool. Nessuna operazione è compiuta se str e/o sp sono nulli, oppure se sp è pieno.

boolean sp_add_string_pos(stringpool* sp, string* str, int pos){
	boolean a=TRUE;

	return TRUE;


} //Aggiunge la stringa str all’interno dello stringpool in posizione pos. Nessuna operazione è compiuta se str e/o sp sono nulli, se pos è fuori dall’intervallo 0<= pos < MAX_DIM_STRING_POOL

string* sp_remove_string(stringpool* sp, int pos){
	string* a;
	return a;
} //Rimuove e restituisce la stringa str all’interno dello stringpool in posizione pos. Nessuna operazione è compiuta se sp è nullo, oppure se pos è fuori dall’intervallo pos, MAX_DIM_STRING_POOL[

boolean sp_replace_string(stringpool* sp, int pos, string* newstr){
	boolean a=TRUE;

	return TRUE;

} //Sostituisce la stringa all’interno dello stringpool in posizione pos, rimpiazzandola con str. Nessuna operazione è compiuta se str e/o sp sono nulli, oppure se pos è fuori dall’intervallo [pos, MAX_DIM_STRING_POOL[

int sp_save_to_file(stringpool* sp, const string fname){
	return 1;
} //Salva il contenuto dello stringpool in un file di testo, con il nome specificato dal secondo paramentro fname. Ogni elemento sarà salvato su una riga diversa.

int sp_load_from_file(stringpool* sp, const string fname){
	return 1;
} //Carica il contenuto del file di test fname nello o stringpool. L’intera stringa letta su una riga sarà un elemento dello stringpool.


void bubble_sort(stringpool* sp){
	boolean a=TRUE;
} //Ordina alfabeticamente gli elementi dello stringpool, applicando l’algoritmo di bubble sort.

int bin_search(const stringpool* sp, const string str){
	return 1;
} //Cerca la stringa str all’interno dello stringpool ordinato attraverso l’algoritmo di ricerca binaria. Ne restituisce la posizione, nel caso in cui str sia presente.
