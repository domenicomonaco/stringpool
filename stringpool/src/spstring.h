/**
 * \file spstring.h
 * \brief Header spstring
 *
 * Contiene i prototipi e le strutture della libreria "spstring"
 *
 */

#ifndef SPSTRING_H_
#define SPSTRING_H_

#define MAX_DIM_STRING_POOL 10

#define UNUSED_SLOT 0

#define USED_SLOT 1

typedef struct {
	//La libreria stringpool prevede la creazione di due strutture. La prima struttura, denominata string, contiene: (1) un vettore di caratteri; (2) un intero che definisce la dimensione fisica massima allocata dinamicamente per il vettore di caratteri.

	char* char_array; /*< Il campo char_array è un vettore di caratteri da allocare dinamicamente.*/
	//La dimensione del vettore sarà specificata da un intero dinamico in fase di allocazione della struttura. Tale numero sarà salvato nel campo allocated_size della struttura.

	int allocated_size; //Il campo allocated_size è un intero che indica la dimensione massima del vettore.
//In altre parole se allocated_size è pari a N>0, allora char_array potrà al più contenere una stringa lunga N-1 caratteri più il terminatore ‘\0’.

} string;

typedef struct {
	//La seconda struttura, denominata stringpool, contiene:
	// (1) un vettore statico di puntatori a stringhe (string*) per il contenimento degli elementi;
	// (2) un contatore degli elementi presenti nel vettore;
	// (3) un vettore di interi indicante per ciascuna posizione lo stato libero o occupato.

	string* strings; //Il campo strings è un vettore di puntatori a stringhe. La dimensione del vettore è specificata come costante MAX_DIM_STRING_POOL (10), in modo statico, nella dichiarazione.

	int used_counter; //Il campo used_counter conta il numero di elementi presenti nel vettore strings. In fase di inizializzazione, il contatore è posto a 0.

	int positions; //Il campo positions è un vettore di interi di dimensione pari a quello strings. Ciascun elemento in posizione i può valere 0 (UNUSED_SLOT) oppure 1 (USED_SLOT), e indicherà, rispettivamente, che nel vettore strings la posizione i è libera o già occupata. In fase di inizializzazione, il vettore positions è posto interamente a 0.

} stringpool;

//prototipi

string* sp_new_string(const char* str); //Crea una nuova stringa il cui contenuto è uguale a quello del parametro in ingresso str.

string* sp_new_string_as_struct(const string* str);//Crea una nuova stringa il cui contenuto è uguale a quello del parametro in ingresso str.

string* sp_new_empty_string(int len); //Crea una nuova stringa vuota (cioè “”) creata dinamicamente, la cui dimensione fisica è pari a len caratteri.

int sp_get_allocated_size(const string* str); //Restituisce la dimensione massima (fisica) allocata dinamicamente per la stringa.

string* sp_strcpy(string* copy, const char* original, int offset); //Copia il contenuto della stringa original in copy, a partire dal carattere in posizione offset di copy. Se offset è 0, allora la copia avviene dall’inizio della stringa copy. La dimensione di copy deve essere pari o maggiore di quella di original.

void sp_free(string* str); //Funzione per deallocare una stringa str allocata dinamicamente. Dopo la deallocazione str vale NULL

int sp_strlen(const string* str); //Funzione che calcola e restituisce la lunghezza logica della stringa in ingresso str.

boolean sp_strcmp(const string* str1, const char* str2); //Funzione che confronta due stringhe e restituisce il corrispettivo valore di verità.

string* sp_strcat(const char* str1, const char* str2); //La funzione crea una nuova stringa ottenuta dalla concatenazione delle due stringhe passate in ingresso, le quali non sono alterate dalla funzione.

string* sp_strcat_as_struct(const string* str1, const string* str2); //La funzione crea una nuova stringa ottenuta dalla concatenazione delle due stringhe passate in ingresso, le quali non sono alterate dalla funzione.

string* sp_lower_case(const string* str); //La funzione restituisce una nuova stringa ottenuta ponendo in minuscolo ciascun carattere della stringa in ingresso che non è alterata. Per esempio, se si passa come parametro in ingresso “Ciao”, allora la funzione restituirà una nuova stringa “ciao” in output.

string* sp_upper_case(const string* str); //La funzione restituisce una nuova stringa ottenuta ponendo in maiuscolo ciascun carattere della stringa in ingresso che non è alterata. Per esempio, se si passa come parametro in ingresso “Ciao”, allora la funzione restituirà una nuova stringa “CIAO” in output.

void sp_initialize_stringpool(stringpool* sp); //Inizializza la struttura stringpool. Pone il contatore di elementi a 0 e rende tutti gli slot disponibili.

void sp_free_stringpool(stringpool* sp); //Libera la memoria per tutte le stringhe salvate in strings e re-inizializza la struttura stringpool (positions e used_counter azzerati).

int sp_sizeof(const stringpool* sp); //Restituisce il numero di stringhe in sp. Restituisce 0 se lo stringpool è vuoto; -1 se sp è NULL

boolean sp_isempty(const stringpool* sp); //Restituisce un valore booleno stante a indicare se lo stringpool è vuoto o contiene uno o più elementi.

boolean sp_isfull(const stringpool* sp); //Restituisce un valore booleno stante a indicare se lo stringpool contiene già il massimo numero di elementi consentiti oppure no.

int sp_find_string(const stringpool* sp, const string* str); //Cerca la stringa str all’interno dello stringpool e ne restituisce la posizione, nel caso sia presente.

string* sp_get_string(const stringpool* sp, int pos); //Restituisce il puntatore alla stringa str che occupa la posizione pos all’interno dello stringpool.

boolean sp_add_string(stringpool* sp, string* str); //Aggiunge la stringa puntata da str all’interno dello stringpool. Nessuna operazione è compiuta se str e/o sp sono nulli, oppure se sp è pieno.

boolean sp_add_string_pos(stringpool* sp, string* str, int pos); //Aggiunge la stringa str all’interno dello stringpool in posizione pos. Nessuna operazione è compiuta se str e/o sp sono nulli, se pos è fuori dall’intervallo 0<= pos < MAX_DIM_STRING_POOL

string* sp_remove_string(stringpool* sp, int pos); //Rimuove e restituisce la stringa str all’interno dello stringpool in posizione pos. Nessuna operazione è compiuta se sp è nullo, oppure se pos è fuori dall’intervallo pos, MAX_DIM_STRING_POOL[

boolean sp_replace_string(stringpool* sp, int pos, string* newstr); //Sostituisce la stringa all’interno dello stringpool in posizione pos, rimpiazzandola con str. Nessuna operazione è compiuta se str e/o sp sono nulli, oppure se pos è fuori dall’intervallo [pos, MAX_DIM_STRING_POOL[

int sp_save_to_file(stringpool* sp, const string fname); //Salva il contenuto dello stringpool in un file di testo, con il nome specificato dal secondo paramentro fname. Ogni elemento sarà salvato su una riga diversa.

int sp_load_from_file(stringpool* sp, const string fname); //Carica il contenuto del file di test fname nello o stringpool. L’intera stringa letta su una riga sarà un elemento dello stringpool.

void bubble_sort(stringpool* sp); //Ordina alfabeticamente gli elementi dello stringpool, applicando l’algoritmo di bubble sort.

int bin_search(const stringpool* sp, const string str); //Cerca la stringa str all’interno dello stringpool ordinato attraverso l’algoritmo di ricerca binaria. Ne restituisce la posizione, nel caso in cui str sia presente.

#endif /* SPSTRING_H_ */
