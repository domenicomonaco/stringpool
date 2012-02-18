/**
 * \file spstring.c
 * \brief Implementazione funzioni stringpool
 *
 * La libreria stringpool consente la gestione di un'insieme di dati di tipo string.
 * Due sono i tipi di dato gestiti: string, stringpool.
 *
 * \author Domenico Monaco, domenico.monaco@kiuz.it
 * \date 2011
 * \section license Licenza
 * GPLv2 http://www.softwarelibero.it/gnudoc/gpl.it.txt
 * Per maggiori informazioni visitare il link o visualizzare il file LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

#include "bool.h"
#include "stringpool.h"
#include "spstring.h"

/** \fn sp_initialize_stringpool(stringpool* sp)
 * \brief Inizializza una struttura Stringpool
 * \param sp puntatore a struttura stringpool
 * \return void
 */
void sp_initialize_stringpool(stringpool* sp) {

	/**Verifica se il puntatore sp non è NULL */
	if (sp != NULL) {

		/** Imposta il counter degli slot utilizzati al valore di EMPTY_STRING_POOL */
		sp->used_counter = EMPTY_STRING_POOL;

		/** Imposta le posizioni al valore di UNUSED_SLOT rendendole tutte libere*/memset(sp->positions, UNUSED_SLOT, MAX_DIM_STRING_POOL* sizeof(int));
	}
}

/** \fn sp_free(string* str)
 * \brief Dealloca lo spazio di memoria a cui sta puntando str
 * \param str puntatore a struttura string
 * \return void
 */
void sp_free(string* str) {

	/** Verifica che il puntatore str non sia NULL*/
	if (NULL != str) {

		/** Verifica che sia stato allocato dello spazio in corrispondenza
		 * all'area di memoria puntata da str->char_array
		 */
		if (str->char_array != NULL) {
			/** Libera lo spazio puntato da str->char_array */
			free(str->char_array);
		}
		/** Libera lo spazio puntato da str */
		free(str);

		/** Forza str a valere NULL dopo la deallocazione */
		str = NULL;
	}
}

/** \fn sp_free_stringpool(stringpool* sp)
 * \brief Libera la memoria e reinizializza la struct sringpool
 * \param sp puntatore a stringpool
 * \return void
 */
void sp_free_stringpool(stringpool* sp) {

	/** i - indice intero per ciclo for per la deallocazione delle stringe */
	int i;

	/** Verifica che sp non sia NULL */
	if (NULL != sp) {

		/** Iterazione per liberare la memoria delle stringe salvate */
		for (i = 0; i < MAX_DIM_STRING_POOL; i++) {

			/** Verifica che la posizione i-esima sia occupata da una stringa altrimenti evita istruzioni inutili*/
			if (sp->positions[i] == USED_SLOT) {

				/** Rimuove la stringa decrementando used_counter e ponendo a 0 position[i]
				 * Per ogni iterazione la struttura stringpool è consistente e coerente con le string rimosse e da rimuovere
				 */
				sp_remove_string(sp, i);
				/** Libero la memoria occupata dalla stringa i-esima*/
				sp_free(sp->strings[i]);
			}
		}

		/** Operazione non necessaria se sp_remove_string() e sp_free() operano correttamente */
		sp_initialize_stringpool(sp);
	}
}

/** \fn sp_new_empty_string(int len)
 * \brief Crea una string vuota di dimensione len
 *
 * Equivale alla stringa ""
 * \param len intero maggiore uguale a zero
 * \return new_empty_string puntatore a struttura di tipo stringa
 */
string* sp_new_empty_string(int len) {

	/** Variabile di output, puntatre a string, inzializzata a NULL nel caso len non è >= 0 */
	string* new_empty_string = NULL;

	/** Verifica che len sia maggiore uguale a zero*/
	if (len >= 0) {
		/** Alloca la memoria per il puntatore new_empty_string, di dimensione SIZE_STRING_STRUCT */
		new_empty_string = (string*) calloc(SIZE_STRING_STRUCT, sizeof(string));

		/** Imposta la memoria allocata al valore di len */
		new_empty_string->allocated_size = (len);

		/** Alloca lo spazio di dimensione len caratteria al puntatore char_array */
		new_empty_string->char_array = (char*) calloc((len), sizeof(char));

		/** Inserisce il carattere di terminazione nello spazio allocato */
		new_empty_string->char_array = strcpy(new_empty_string->char_array, "");
	}

	/** Ritorna l'indirizzo della struct string,
	 * è NULL solo se len < 0 altrimenti punta ad una locazione di memoria valida
	 */
	return new_empty_string;
}

/** \fn sp_new_string(const char* str)
 * \brief Crea una string con contenuto pari a quello in ingresso
 *
 * \param str puntatore costante a caratteri
 * \return new_string puntatore a string
 */
string* sp_new_string(const char* str) {
	/** Calcolo e salvo la lunghezza della stringa passata, essa non contiene conto del carattere di terminazione \0*/
	int len_str = strlen(str);

	/** Creo ed alloco una nuova stringa vuota di lunghezza (len_str+1)*/
	string* new_string = sp_new_empty_string(len_str + 1);

	/** Copio il contenuto di str in new_string->char_array */
	new_string = sp_strcpy(new_string, str, 0);

	/** Ritorno il puntatore alla struct string*/
	return new_string;
}

/** \fn sp_get_allocated_size(const string* str)
 * \brief Restituisce la dimensione massima allocata per la stringa.
 *
 * \param str puntatore a string
 * \return allocated_size dimensione fisica allocata per str; se str è 0, restituisce NULL
 */
int sp_get_allocated_size(const string* str) {

	/** Variabile allocated_size di output*/
	int allocated_size;

	/** Verifica che str e str->char_array non siano NULL*/
	if (NULL != str || str->char_array != NULL) {

		/** imposta allocated_size al valore di str->allocated_size */
		allocated_size = str->allocated_size;

		/** In caso allocated_size è 0 viene portato a NULL*/
		if (allocated_size == 0) {
			allocated_size = NULL;
		}
	}

	/** Ritorna allocated_size che sarà > 0 oppure NULL */
	return allocated_size;
}

/** \fn sp_strlen(const string* str)
 * \brief Calcola e restituisce la lunghezza logica di una string
 * \param str puntatore a string
 * \return strlen_current_str Intero n rappresentante la lunghezza con n>= 0; se str = NULL, allora n = 0
 */

int sp_strlen(const string* str) {

	/** Dichiaro ed inizializzo la variabile di output a 0*/
	int strlen_current_str = 0;

	/** Verifico che str e str->char_array non siano NULL e che la dimensione allocata non sia 0 */
	if (NULL != str && str->allocated_size != 0 && str->char_array != NULL) {

		/** Calcolo la lunghezza della stringa contenuta in str->char_array */
		strlen_current_str = strlen(str->char_array);
	}

	/** Ritorna la linghezza della stringa, sarà 0 str o str->char_arrat sono NULL */
	return strlen_current_str;
}

/** \fn sp_strcmp(const string* str1, const char* str2)
 * \brief Confronta due stringhe e restituisce il relativo valore di verità
 * \param str1 puntatore a string costante
 * \param str2 puntatore a carattere costante
 * \return ifequal che sarà TRUE se str1 == str2; FALSE altrimenti
 */
boolean sp_strcmp(const string* str1, const char* str2) {

	/** Dichiaro ed inizializzo variabile di output Booleana a FALSE*/
	boolean ifequal = FALSE;

	/** Dichiaro  le variabili per la lunghezza delle due stringhe  */
	int strlen_1, strlen_2;

	/** Controllo che str1 e str->char array non siano NULL, str2 sarà al massimo vuoto*/
	if (str1->char_array != NULL || str1 != NULL) {

		/** inizializzo la lunghezza delle due stringhe */
		strlen_1 = strlen(str1->char_array);
		strlen_2 = strlen(str2);

		/** Verifico se hanno la stessa lunghezza,
		 * se sono lunghe uguali potrebbero anche essere identiche,
		 * altrimenti sono sicuramente diverse.
		 * Evito quindi di richiamere strcmp
		 */
		if (strlen_1 == strlen_2) {
			/** Se sono lunghe uguali, verifico anche se sono identiche*/
			if (strcmp(str1->char_array, str2) == 0) {
				/** Se sono anche identiche imposto ifequal a TRUE*/
				ifequal = TRUE;
			} else {
				/** Se non sono identiche imposto ifequal a FALSE */
				ifequal = FALSE;
			}
		}
		/** Se non sono lunghe uguali sono anche diverse, non faccio niente altro avendo ifequal inizializzato a FALSE */
	}

	/** Ritorno il risultato che sarà TRUE solo nel caso siano identiche str1 e str2 altrimenti restuirà FALSE*/
	return ifequal;
}

/** \fn sp_new_string_as_struct(const string* str)
 * \brief Crea una nuova string il cui contenuto è uguale a quella in ingresso
 * \param str puntatore a string
 * \return string_as_struct puntatore a string
 */
string* sp_new_string_as_struct(const string* str) {
	/** inizializzo la variabile di ritorno */
	/** associo alla variabile di ritorno il l'indirizzo della nuova string creata con sp_new_string */
	string* string_as_struct = sp_new_string(str->char_array);

	/** Ritorno l'indirizzo della nuova string */
	return string_as_struct;
}

/** \fn sp_strcpy(string* copy, const char* original, int offset)
 * \brief Copia il contenuto della string original in copy
 *
 *  Copia la string partire dal carattere in posizione offset di copy. Se offset è 0, allora la copia avviene dall’inizio della stringa copy.
 *  La dimensione di copy deve essere pari o maggiore di quella di original.
 * \param copy
 * \param original
 * \param offset
 * \return copy puntatore a string che punga ad una copia della string original, assumendo che N >= M, a partire dalla posizione offset
 */
string* sp_strcpy(string* copy, const char* original, int offset) {
	/** Dichiaro la variabile per la lunghezza della stringa original */
	int original_len;

	/** Verifico che copy non sia NULL */
	if (copy != NULL) {
		/** controllo che offset sia minore della grandezza di copy e che original sia diverso da NULL */
		if (copy->allocated_size >= offset && (original != NULL)) {

			/** Ottengo la dimensione di original */
			original_len = strlen(original);

			/** Controllo che copy sia maggiore o uguale alla dimensione di original*/
			if ((copy->allocated_size >= original_len)) {
				/** Copio il contenuto di original in copy dalla posizione offset in poi */strcpy((copy->char_array+offset), original);
			}
		}
	}

	/** Ritorno l'indirizzo di string copy */
	return copy;
}

/** \fn sp_strcat(const char* str1, const char* str2)
 * \brief Crea una string ottenuta dalla concatenazione di due stringhe in ingresso
 * \param str1 puntatore a caratteri costante
 * \param str2 puntatore a caratteri costante
 * \return str_cat puntatore a string contenete una stringa equivalente a str1+str2
 */
string* sp_strcat(const char* str1, const char* str2) {
	/** Dichiarro la variabile di ritorno */
	string* str_cat;

	/** Dichiaro le variabili per le lunghezze rispettivamente di str2, str1 e string di output*/
	int str_len_str2, str_len_str1, str_cat_len;

	/** Verifico che entrambe le stringhe non siano NULL */
	if (str1 != NULL && str2 != NULL) {

		/** inizializzo le lunghezze di str1 e str2 */
		str_len_str1 = strlen(str1);
		str_len_str2 = strlen(str2);

		/** Dichiaro la lunghezza complessiva della string concatenata sommando le lunghezze logiche di str1 e str2*/
		str_cat_len = str_len_str1 + str_len_str2;

		/** Creo una nuova string vuota di lunghezza str_cat_len + 1 dato che sp_new_empty_string non tiene conto del carattere di terminazione*/
		str_cat = sp_new_empty_string(str_cat_len + 1);

		/** Copio in str_cat a partire dalla posizione 0 il contenuto di str1 */
		sp_strcpy(str_cat, str1, 0);

		/** Copio in str_cat a partire dalla posizione str_len_str1 la str2 **/
		sp_strcpy(str_cat, str2, str_len_str1);

		/** Caso in cui almeno uno delle due string è NULL ma non entrambe NULL */
	} else if ((str1 == NULL || str2 == NULL)
			&& !(str1 == NULL && str2 == NULL)) {
		/** Controllo quale delle due string è NULL */
		if (str1 == NULL) {
			/** Nel caso fosse NULL la str1, creiamo una nuova string con il solo contenuto della str2 */
			str_len_str2 = strlen(str2);
			str_cat = sp_new_empty_string(str_len_str2 + 1);
			sp_strcpy(str_cat, str2, 0);

		} else if (str2 == NULL) {

			/** Nel caso fosse NULL la str2, creiamo una nuova string con il solo contenuto della str1 */
			str_len_str1 = strlen(str1);
			str_cat = sp_new_empty_string(str_len_str1 + 1);
			sp_strcpy(str_cat, str1, 0);
		}
	}

	/** Ritorno il puntatore a string contenente le due stringhe concatenate*/
	return str_cat;
}

/** \fn sp_strcat_as_struct(const string* str1, const string* str2)
 * \brief Crea una string ottenuta dalla conctaenazione delle due string in ingresso
 * \param str1 puntatore a string costanti
 * \param str2 puntatore a string costanti
 * \return strcat_as_struct puntatore a string pari a str1+str2
 */
string* sp_strcat_as_struct(const string* str1, const string* str2) {
	/** Dichiaro la variabile di output */
	string* strcat_as_struct;

	/** Verifico che entrmabe str1 e str2 non siano NULL */
	if (str1 != NULL && str2 != NULL) {

		/** Controllo lo spazio allocato, se > 0 vuol dire che non sono vuote */
		if (str1->allocated_size > 0 && str2->allocated_size > 0) {

			/** Concateno le due stringhe utilizzando sp_strcat(){} */
			strcat_as_struct = sp_strcat(str1->char_array, str2->char_array);

			/** Caso in cui almeno una delle due ha dimensione 0 ma non entrambe di dimensione 0 */
		} else if ((str1->allocated_size == 0 || str2->allocated_size == 0)
				&& !((str1->allocated_size == 0 && str2->allocated_size == 0))) {
			/** Controllo quale delle due string è di dimensione 0*/
			if (str1->allocated_size == 0) {
				/** Nel caso str1 è di dimensione 0, creo una string con contenuto di str2 */
				strcat_as_struct = sp_new_string_as_struct(str2);
			} else if (str2->allocated_size == 0) {

				/** Nel caso str2 è di dimensione 0, creo una string con contenuto di str1 */
				strcat_as_struct = sp_new_string_as_struct(str1);
			}
		}

		/** Caso in cui str1 o str2 è NULL ma non entrambe NULL */
	} else if ((str1 == NULL || str2 == NULL)
			&& !(str1 == NULL && str2 == NULL)) {
		/** Verifico quale delle due è NULL*/
		if (str1 == NULL) {
			/** Nel caso fosse srt1 NULL e str2 sia di dimensione mazziore di 0, creo una stringa con il contenuto di str2 */
			if (str2->allocated_size > 0) {
				strcat_as_struct = sp_new_string_as_struct(str2);
			}
		} else if (str2 == NULL) {
			/** Nel caso fosse srt2 NULL e str1 sia di dimensione mazziore di 0, creo una stringa con il contenuto di str1 */
			if (str1->allocated_size > 0) {
				strcat_as_struct = sp_new_string_as_struct(str1);
			}
		}
	}

	/** Ritorno il valore di ritorno*/
	return strcat_as_struct;
}

/** \fn sp_lower_case(const string* str)
 * \brief Restituisce una nuova stringa ottenuta ponendo in minuscolo ciascun carattere della stringa in ingresso
 * \param str puntatore a string costante
 * \return lower_output Puntatore a string contenente caratteri in minuscolo
 */
string* sp_lower_case(const string* str) {

	/** Dichiaro variabile di output */
	string* lower_output = NULL;

	/** Variabile per lunghezza stringa */
	int str_len;

	/** Variabile temporanea per carattere da porre in minuscolo*/
	char tmp_lower;

	/** Variabile indice per ciclo for, per porre iterativamente tutti i caratteri in minuscolo*/
	int i;

	/** Controllo che str sia diverso da NULL */
	if (str != NULL) {

		/** Controllo che sia diverso da NULL anche char_array */
		if (str->char_array != NULL) {

			/** Calcolo la lungehzza della stringa, che potrebbe essere diversa dalla dimensione allocata per la stringa */
			str_len = sp_strlen(str);

			/** Creo una nuova stringa vuota di dimensione della stringa in ingresso */
			lower_output = sp_new_empty_string(str_len);

			/** Ciclo su tutta la lunghezza della stringa */
			for (i = 0; i < str_len; i++) {

				/** Passo alla funzione tolower il carattere iesimo copiandolo in tmp_lower*/
				tmp_lower = tolower((str->char_array[i]));

				/** Copio quindi tmp_lower nella posizione i-esima della string di output, passaggio inutile ma migliora la leggibilità */
				lower_output->char_array[i] = tmp_lower;
			}

			/** Salvo il carattere di terminazine stringa in ultima+1 posizione*/
			lower_output->char_array[str_len] = '\0';
		}
	}

	/** Ritorno la nuova stringa ottenuta ponendo in minuscolo ogni carattere */
	return lower_output;
}

/** \fn sp_upper_case(const string* str)
 * \brief Restituisce una nuova stringa ottenuta ponendo in maiuscolo ciascun carattere della stringa in ingresso
 * \param str puntatore a string costante
 * \return upper_output Puntatore a string contenente caratteri in maiuscolo
 */
string* sp_upper_case(const string* str) {

	/** Dichiaro la variabile di output */
	string* upper_output = NULL;

	/** Variabile per lunghezza string di output */
	int str_len;

	/** Variabile temporanea per carattere da porre in maiuscolo */
	char tmp_upper;

	/** Variabile indice per ciclo for, per trasformare in maiuscolo tutti i caratteri*/
	int i;

	/** Controllo che str nons ia NULL*/
	if (str != NULL) {

		/** Controllo che char_array non sia NULL*/
		if (str->char_array != NULL) {

			/** Ottengo la lunghezza di str e creo una nuova stringa vuota di lungehzza uguale a str */
			str_len = sp_strlen(str);
			upper_output = sp_new_empty_string(str_len);

			/** Ciclo su tutta la lungehzza si str*/
			for (i = 0; i < str_len; i++) {

				/** Ottengo i-esimo carattere di str e lo trasformo in maiuscolo */
				tmp_upper = toupper((str->char_array[i]));

				/** Salvo l'iesimo carattere maiuscolo nella string di output */
				upper_output->char_array[i] = tmp_upper;
			}

			/** Salvo il carattere di terminazine stringa in ultima+1 posizione*/
			upper_output->char_array[str_len] = '\0';
		}
	}

	/** Ritorno la string di output con tutti i caratteri di str in maiuscolo */
	return upper_output;
}

/** \fn sp_isempty(const stringpool* sp)
 * \brief Restituisce un valore booleno che indica se lo stringpool è vuoto
 * \param sp puntatore a struttura stringpool costante
 * \return isempty è TRUE se sp è vuoto, FALSE altrimenti; se sp è NULL, restituisce FALSE
 */

boolean sp_isempty(const stringpool* sp) {

	/** Dichiaro la variabile di output e la inizializzo a FALSE */
	boolean isempty = FALSE;

	/** Verifico che sp non sia NUL */
	if (sp != NULL) {
		/** Controllo se il numero di slot usati è EMPTY_STRING_POOL */
		if (sp->used_counter == EMPTY_STRING_POOL) {
			/** In caso affermativo, imposta isempty a TRUE, altrimenti rimane FALSE*/
			isempty = TRUE;
		}
	}

	/** Ritorno il valore di verità per sp VUOTO */
	return isempty;
}

/** \fn sp_isfull(const stringpool* sp)
 * \brief Restituisce un valore booleno che indica se stringpool contiene già il massimo numero di elementi consentiti
 * \param sp puntatore a struttura stringpool costante
 * \return isfull è TRUE se il numero di elementi presenti è == MAX_DIM_STRING_POOL, FALSE altrimenti; se sp è NULL, restituisce TRUE
 */
boolean sp_isfull(const stringpool* sp) {

	/** Dichiaro la variabile di output*/
	boolean isfull = FALSE;

	/** Controllo se sp è diverso da NULL */
	if (sp != NULL) {

		/** Controllo se il counter degli slot è impotato alla dimensione massima di stringpool */
		if (sp->used_counter == MAX_DIM_STRING_POOL) {
			/** Tutti gli slot sono usati, imposto isfull a TRUE*/
			isfull = TRUE;
		}

		/** Caso in cui sp == NULL*/
	} else {
		/** Imposto come da specifica isfull a TRUE*/
		isfull = TRUE;
	}

	/** Ritorno il valore di verita per sp PIENO */
	return isfull;
}

/** \fn sp_add_string_pos(stringpool* sp, string* str, int pos)
 * \brief Aggiunge una string all’interno dello stringpool in posizione pos.
 *
 * Nessuna operazione è compiuta se str e/o sp sono nulli, se pos è fuori dall’intervallo 0<= pos < MAX_DIM_STRING_POOL
 * \param sp puntatore a struttura stringpool
 * \param str puntatore a struttura string
 * \param pos intero che indica la posizione in cui aggiungere la string
 *
 * \return is_added vale TRUE se l’inserimento è andato a buon fine, FALSE altrimenti.
 */
boolean sp_add_string_pos(stringpool* sp, string* str, int pos) {

	/** Dichiaro la variabile di output inizializzandola a FALSE */
	boolean is_added = FALSE;

	/** Controllo che sp e str non siano null e controllo che la posizione richiesta esista nello stringpool */
	if (sp != NULL && str != NULL && pos >= 0 && pos < (MAX_DIM_STRING_POOL)) {

		/** Controllo che la posizione pos sia già occupata, in tal caso libero la memoria */
		if (sp->positions[pos] == USED_SLOT) {
			sp_free(sp_remove_string(sp, pos));
		}

		/** Inesrisco in strings[pos] il puntatore a str passata */
		sp->strings[pos] = str;

		/** positions e used_counter sono aggiornati solo se
		 * è realmente presente in strings[pos] l'indirizzo voluto,
		 * altrimenti non aggiorna le variabili
		 */
		if (sp->strings[pos] == str) {

			/** L'assocciazione è andata a buon fine, posso aggiornare le variabili positions, used_counter e is_added per l'output*/
			is_added = TRUE;
			sp->positions[pos] = USED_SLOT;
			sp->used_counter = sp->used_counter + 1;
		}
	}

	/** Ritorno la variabile di output */
	return is_added;
}

/** \fn sp_add_string(stringpool* sp, string* str)
 * \brief Aggiunge la stringa puntata da str all’interno dello stringpool
 *
 * Viene aggiunta nella prima posizione libera. Nessuna operazione è compiuta se str e/o sp sono nulli, oppure se sp è pieno.
 *
 * \param sp puntatore a struttura stringpool
 * \param str puntatore a struttura string
 * \return is_added TRUE se l’inserimento è andato a buon fine, FALSE altrimenti.
 */
boolean sp_add_string(stringpool* sp, string* str) {

	/** Dichiaro la variabile di outpu inizializzandola a FALSE */
	boolean is_added = FALSE;

	/** Dichiaro la varibile di verità per la posizione libera */
	int check_free = 0;

	/** Variabile indice per ciclo while per la ricerca della posizione libera */
	int i = 0;

	/** Variabile */
	int result_adding_pos;

	/** Controllo che sp ed str non siano NULL */
	if (sp != NULL && str != NULL) {

		/** Controllo se lo string pool non è pieno*/
		if (!(sp_isfull(sp))) {

			/** Ciclo per l'intero stringpool alla ricerca della prima posizione libera */
			/** Il ciclo continua finchè check_free è diverso da 1 e non abbiamo controllato tutte le posizini */
			while (check_free != 1 && i < MAX_DIM_STRING_POOL) {
				/** Per ogni ciclo controllo se l'i-esima posizione è libera */
				if (sp->positions[i] == UNUSED_SLOT) {

					/** In caso affermativo, imposto check_free a 1 */
					check_free = 1;

					/** Provo quindi ad aggiungere la string in ingresso nella posizione libera appena trovata */
					/** Memoriazando il risutlato di tale operazione */
					result_adding_pos = sp_add_string_pos(sp, str, i);

					/** Controllo se l'operazione di aggiunta della string in posizine iesima è andata a buon fine */
					if (result_adding_pos == TRUE) {
						/** In caso affermativo imposto la variabile di output a TRUE */
						is_added = TRUE;
					} else {
						/** In caso negativo, riporto check_free a 0 permettendo di continuare a cercare un'altra posizione */
						check_free = 0;
					}
				}

				/** Incremente il contatore iesimo */
				i++;
			}
		}
	}

	/** Ritorno il valore di verità per l'operazione di aggiunta string */
	return is_added;
}

/** \fn sp_sizeof(const stringpool* sp)
 * \brief Restituisce il numero di stringhe in sp.
 *
 * Restituisce 0 se lo stringpool è vuoto; -1 se sp è NULL
 * \param
 * \return size_of_sp intero contenente il numero di elementi n>=0 presenti nello stringpool
 */
int sp_sizeof(const stringpool* sp) {

	/** Dichiaro la variabile di output */
	int size_of_sp;

	/** Controllo che sp sia diverso da NULL */
	if (sp != NULL) {
		/** In tal caso, associo alla variabile di output il numero di rigeh utilizzate che sarà sempre n>=0 e 0 solo se sp è vuoto */
		size_of_sp = sp->used_counter;

	} else if (sp == NULL) {
		/** Nel caso sp sia NULL, associo alla variabile di output il valore -1 */
		size_of_sp = -1;
	}

	/** Ritorno il valore di Output */
	return size_of_sp;
}

/** \fn sp_get_string(const stringpool* sp, int pos)
 * \brief Restituisce il puntatore alla stringa str che occupa la posizione pos all’interno dello stringpool.
 *
 * Se pos è fuori da questo intervallo o se sp è nullo, allora la funzione restituisce restituisce NULL.
 *
 * \param sp puntatore costante a struttura string pull
 * \param pos intero positivo che indica la posizione da controllare
 * \return str_output puntatore a string in posizione pos, se 0<= pos < MAX_DIM_STRING_POOL;
 */
string* sp_get_string(const stringpool* sp, int pos) {

	/** Dichiaro la variabile di output e la inizializzo a NULL */
	string* str_output = NULL;

	/** Controllo come da specifica se sp è NULL, se la posizione è all'interno degli indici di stringpool */
	if (sp != NULL && pos >= 0 && pos < (MAX_DIM_STRING_POOL)) {

		/** Controllo se la posizione richiesta è utilizzata */
		if (sp->positions[pos] == USED_SLOT) {
			/** In tal caso assozio l'indirizzo a cui punta stirngs[pos] alla variabile di output */
			str_output = sp->strings[pos];
		}
	}

	/** Ritorno la variabile di output */
	return str_output;
}

/** \fn sp_remove_string(stringpool* sp, int pos)
 * \brief Rimuove e restituisce la stringa str all’interno dello stringpool in posizione pos.
 *
 * Nessuna operazione è compiuta se sp è nullo, oppure se pos è fuori dall’intervallo pos, MAX_DIM_STRING_POOL
 * \param sp puntatore a struttura stringpool
 * \param pos intero che indica una posizione in stringpool
 * \return removed_str puntatore alla stringa rimossa dallo stringpool, oppure NULL se nessuna stringa è presente in posizione pos
 */
string* sp_remove_string(stringpool* sp, int pos) {

	/** Dichiaro la variabile di output e la inzializzo a NULL */
	string* removed_str = NULL;

	/** Controllo se sp è NULL o se pos sia all'interno del range di inidici di stringpool */
	if (sp != NULL && pos >= 0 && pos < MAX_DIM_STRING_POOL) {

		/** Controllo se la posizione cercata contiene una Stringa
		 * Se la condizione è soddisfatta salvo il suo indirizzo
		 */
		if (sp->positions[pos] == USED_SLOT) {

			removed_str = sp->strings[pos];

			/** Una volta salvato l'indirizzo della string rimossa, imposto la posizione come DISPONIBILE */
			sp->positions[pos] = UNUSED_SLOT;

			/** Importo il counter degli slot utilizzati ad un valore inferiore */
			sp->used_counter = sp->used_counter - 1;
		}
	}

	/** Ritorno la variabile di ouput contenente l'indirizzo della string rimossa */
	return removed_str;
}

/** \fn sp_replace_string(stringpool* sp, int pos, string* newstr)
 * \brief Sostituisce la stringa all’interno dello stringpool in posizione pos, rimpiazzandola con str
 *
 * Nessuna operazione è compiuta se str e/o sp sono nulli, oppure se pos è fuori dall’intervallo [pos, MAX_DIM_STRING_POOL[
 * \param sp puntatore a struttura stringpool
 * \param newstr puntatore a struttura string
 * \return is_relpaced TRUE se la sostituzione è andata a buon fine, FALSE altrimenti
 */
boolean sp_replace_string(stringpool* sp, int pos, string* newstr) {
	/** Dichiaro la variabile di output */
	boolean is_replaced = FALSE;

	/** Controllo se sp è NULL oppure se la posizione richiesta è all'interno del range di indiici di stringpool */
	if (sp != NULL && pos >= 0 && pos < (MAX_DIM_STRING_POOL)) {

		/** Controllo se la posizone richiesta è utilizzata e se la nuova string è diverso da NULL */
		if (newstr != NULL && sp->positions[pos] == USED_SLOT) {

			/** Rimuvo la stringa richiesta in posizione POS, verranno decrementati il contatore ed impostato a libera la posizione pos */
			sp_remove_string(sp, pos);
			/** Aggiungo in posizionepos la nuova stringa, verrano reincrementati il contatore ed il valore di utilizzo dello slot*/
			/** Salvo com'è andata l'operazione nel valore di ritorno */

			is_replaced = sp_add_string_pos(sp, newstr, pos);
		}
	}

	/** Ritorno la variabile di output che indica se l'operazione è andata a buon fine */
	return is_replaced;
}

/** \fn sp_save_to_file(stringpool* sp, const string fname)
 * \brief Salva il contenuto dello stringpool in un file di testo
 *
 * Specificando il nome nel secondo paramentro fname. Ogni elemento sarà salvato su una riga diversa.
 *
 * \param sp puntatore a struttura stringpool
 * \param fname puntatore a struttura string costante
 * \return number_writed_line con il numero di elementi scritti nel file oppure -1 in caso di errore.
 */
int sp_save_to_file(stringpool* sp, const string fname) {
	/** Dichiaro la variabile di output e la inizializzo a -1 in caso sia possibile effettuare alcuna operazione */
	int number_writed_line = -1;

	/** Inizializzo la variabile indice per il ciclo di scruttura delle n linee */
	int i;

	/** Inizializzo il puntatore al file per la lettura */
	FILE* fp;

	/** Controllo che sp non sia null e che il nome del file su cui scrivere sia diverso da "" o " " */
	if (sp != NULL) {
		if (!sp_strcmp(&fname, "") && !sp_strcmp(&fname, " ")) {

			/** Credo il file richiesto e se l'operazione è andata a buon fine continuo*/
			if (_sp_file_create(&fname) == TRUE) {

				/** Apro il file appena creato e se l'operazione va a buon fine continuo */
				if ((fp = fopen(fname.char_array, "w")) != NULL) {

					fprintf(fp, PATTERN_READ_WRITE_INIT, sp_sizeof(sp));

					/** Imposto il numero di linee scritte a 0 dato che stiamo per scrivere un numero di righe >= 0 */
					number_writed_line = 0;

					/** Itero per l'intero numero massimo di posizione dell'array stringpool */
					for (i = 0; i < MAX_DIM_STRING_POOL; i++) {

						/** controllo che lo slot i-esimo sia occupato da una string */
						if (sp->positions[i] == USED_SLOT) {

							/** In caso sia passata la condizione precedente, scrivo la riga i-esima basandomi sul pattern di scrittura e lettura PATTERN_READ_WRITE_LINE */
							fprintf(fp, PATTERN_READ_WRITE_LINE, i,
									sp->strings[i]->allocated_size,
									sp->strings[i]->char_array);

							/** Incremento il contatore del numero di righe scritte */
							number_writed_line = number_writed_line + 1;
						}
					}
				} else {
					/** In caso la riapertura del file non è andata a buon fine imposto la variabile di output a -1 come da specifica */
					number_writed_line = -1;
				}

				/** Chiudo il file aperto */
				fclose(fp);
			}
		}
	}

	/** Ritorno il valore di output che sarà -1 se è stato incontrato qualche problema, altrimento sarò >= 0 ovvero il numero di linee scritte pari a sp_sizeof(<STRINPOOL>)*/
	return number_writed_line;
}

/** \fn sp_load_from_file(stringpool* sp, const string fname)
 * \brief Carica il contenuto del file di test fname nello o stringpool.
 *
 * L’intera stringa letta su una riga sarà un elemento dello stringpool. Inoltre conserva l'ordinamento ed il posizionamento originale delle stringhe pizzandole esattamene nella posizione originale.
 *
 * \param sp puntatore a struttura stringpool
 * \param fname struttura string contenente il nome del file da leggere
 * \return number_loaded_line il numero di righe lette e caricate
 */
int sp_load_from_file(stringpool* sp, const string fname) {

	/** Dichiaro la variabile di output, la inizializzo a -1 in caso si incontrano problemi nel caricamento */
	int number_loaded_line = -1;

	/** Variabile di indice per ciclo for per caricamento righe */
	int i;

	/** Dichiaro la variabile per la lettura "massima" di righe da file */
	int number_slot;

	/** Puntatore a file da leggere */
	FILE* fp;

	/** Variabile per l'i-esimo slot letto da file */
	int size_slot;

	/** Varibile della posizione dell'i-esimo slot lett da file */
	int pos;

	/** array temporanei */
	/** tmp_slot_start_line per contenere l'inizio della stringa */
	char* tmp_slot_start_line = (char*) calloc(
			(MAX_CHAR_STRING_LOAD_FROM_FILE), sizeof(char));

	/** tmp_slot_end_line per contenere la fine della riga, ovvero uno spazio un punto e virgola ed il carattere di nuova linea */
	char* tmp_slot_end_line = (char*) calloc(
			(strlen(PATTERN_READ_WRITE_END_LINE_SHORT)), sizeof(char));

	/** Controllo che sp non sia NULL, e che il nome del file richiesto non sia vuoto o pari al solo spazio*/
	if (sp != NULL && !sp_strcmp(&fname, "") && !sp_strcmp(&fname, " ")) {

		/** Controllo che il file richiesto esista */
		if (_sp_file_exist(&fname) == TRUE) {

			/** In caso esiste viene ri-aperto */
			if ((fp = fopen(fname.char_array, "r")) != NULL) {

				/** Imposto il numero di righe caricate a  0 */
				number_loaded_line = 0;

				/** Leggo la prima informazione del file che contiene il numero di stringhe salvate
				 * Ed imposto tale valore a number_slot.
				 */
				if (fscanf(fp, PATTERN_READ_WRITE_INIT, &number_slot) != NULL
						&& number_slot != NULL) {

					/** Effettuo una iterazione su number_slot in modo da leggere le righe e salvarle */
					for (i = 0; i < number_slot; i++) {

						/** Se il puntarore all'i-esima itezione non è NULL continuo*/
						if (fp != NULL) {
							/** Se il puntatore all'i-esima iterazione non è parti a EOF continuo */
							if (feof(fp) == NULL) {

								/** Effettuo una prima lettura della righa con fscanf prelevando posizione dello slot letto e la sua dimesione */
								if (fscanf(fp,
										PATTERN_READ_WRITE_START_LINE_SHORT,
										&pos, &size_slot) != NULL) {

									/** Effettuo una seconda lettura con fgets leggendo la parte restante del testo basandomi sulla dimensione appena letta */
									tmp_slot_start_line = fgets(
											tmp_slot_start_line, size_slot + 1,
											fp) + 1;

									/** Effettuo una terza lettura utile solo a far avanzare il puntatore, leggendo i 3 caratteri finali della stinga sufficenti a far trovare il puntare ad inizio riga alla prosssima iterazione */
									tmp_slot_end_line
											= fgets(
													tmp_slot_end_line,
													strlen(
															PATTERN_READ_WRITE_END_LINE_SHORT),
													fp);

									/** Aggiungo in sp lo slot lett con tmp_slot_start_line in posizione pos */
									sp_add_string_pos(sp,
											sp_new_string(tmp_slot_start_line),
											pos);
									/** Incremento la varibile che indica il numero di righe caricate */
									number_loaded_line = number_loaded_line + 1;

									/** Contollo di sicurezza in caso il valore letto da pos non sia compatibile
									 *  con la dimensione massima e minima contenibile in uno stringpool
									 */
									if (pos >= MAX_DIM_STRING_POOL && pos != 0) {
										i = number_slot;
									}
								}

							}
						}

					}
				}
			}
			/** Chiudo il file aperto */
			fclose(fp);
		}
	}
	/** Restituisco il valore di ritorno pari al numero di righe lette */
	return number_loaded_line;
}

/** \fn bubble_sort(stringpool* sp)
 * \brief Ordina alfabeticamente gli elementi dello stringpool, applicando l’algoritmo di bubble sort
 *
 * Ordina effettuando un controllo su ogni coppia di elementi, partendo dal basso sceglie minore del confronto e lo porta verso l'alto.
 * Ho usato la versione "corta" dell'algoritmo dover per ogni i-esimo ciclo assumiamo che l'elemento appena spostato è già in posizione corretta.
 * Ho dovuto applicare un piccolo hack per poter fare l'ordinamento anche su array con elementi non contiugui e lasciare invariate le posizione vuote, in altri termini l'algoritmo ordina gli elementi solo sulle posizione attualmente utilizzare senza alterare la posizione degli slot vuoti.
 *
 * \param sp puntatore a struttura stringpool
 * \return void
 */
void bubble_sort(stringpool* sp) {

	/** Dichiaro le variabili indici per i due cicli dell'algoritmo Bubble sort */
	int i, j;

	/** Dichiaro la variabile per identificare se nell'i-esimo controllo è necessario uno Switch degli slot */
	int ifswitch;

	/** Dichiaro la variabile per memorizzare temporaneamente la string da sostituire*/
	string* temp_swap;

	/** Dichiaro la variabile per mappare le posizioni degli slot */
	int* map_array;

	/** Controllo prima se sp non sia NULL ed in seguito se sp non è VUOTO altrimenti non faccio null */
	if (sp != NULL) {
		if (sp_isempty(sp) != TRUE) {

			/** Ottengo un array della mappa delle posizione dell'array.
			 * Dove ogni i-esima posione contiene la posizione reale dello slot.
			 * Ad esempio se esistono 4 elementi, ma il sp->position[3] è vuoto mentre il sp->position[4] è pieno
			 * il risultato sarà un arrai del tipo [0->0,1->1,2->2,3->4]
			 */
			map_array = _sp_map_array_stringpool(sp);

			/** Itero su due cicli for come da definizione dell'algoritmo*/
			/** Il primo ciclo itera da 0 alla dimensione di sp, incrementando il puntatore */
			for (i = 0; i < sp_sizeof(sp); i++) {

				/** Il secondo ciclo itera dalla dimensione di sp meno 1,fino ad i, decrementando l'indice. */
				/** Ad ogni iterazione del primo ciclo for, il secndo ciclo for effettuera un passaggio in meno evitando di controllare elementi sicuramente già in posizione corretta */
				for (j = sp_sizeof(sp) - 1; j >= i; j--) {

					/** La j esima posione è quella corrente e dipende anche da i.
					 * Controlliamo le poszioni (j) e (j-1), identificando se sono o meno in ordine alfabetico utilizzando strcmp.
					 * Quindi ifswitch sarà -1 l'elemento j deve essere spostato in posizione j-1 e viceversa
					 *
					 * In questi cicli non mi devo preoccupare dei "buchi" nell'array stringpool dato che
					 * le iterazioni sono fatte sulla mappa dele posizione che è un array continuo che
					 * ci permette di tradurre per ogni iterazione la reale posizione dello slot trattato
					 */

					ifswitch = strcmp(
							sp->strings[*(map_array + j)]->char_array,
							sp->strings[(*(map_array + j - 1))]->char_array);

					/** Controllo se bisogna scambiare gli elementi */
					if (ifswitch < 0) {
						/** Memorizzo temporanemente la stringa in posizione j*/
						temp_swap = sp_get_string(sp, *(map_array + j));

						/** Rimpiazzo in posizione j la strin j-1*/
						sp_replace_string(sp, *(map_array + j),
								sp->strings[*(map_array + j - 1)]);

						/** Rimpiazzo in posizione j-1 la stringa memorizzata precedentemente, ovvero quella in posizione j */
						sp_replace_string(sp, (*(map_array + j - 1)), temp_swap);
					}
				}
			}
		}
	}

}

/** \fn bin_search(const stringpool* sp, const string str)
 * \brief Cerca la stringa str all’interno dello stringpool ordinato attraverso l’algoritmo di ricerca binaria.
 *
 * Ne restituisce la posizione, nel caso in cui str sia presente.
 *
 * \param
 * \return iffound pari alla posizione p della stringa, con 0<= p < MAX_DIM_STRING_POOL se str è presente in sp; p=-1, altrimenti. Se sp o str sono nulli, restituisce -1.
 */
int bin_search(const stringpool* sp, const string str) {

	/** Dichiaro la variabile di output */
	int iffound = -1;

	/** Dichiaro la variabile indice per il ciclo while della ricerca binaria, rappresenta il numero di controll effettuati*/
	int i = 0;

	/** Variabile di controllo per la ricerca della stringa cercata */
	int str_cmp = -1;

	/** Variabili per il calcolo dell'i-esima posizione da controlla come da definizione del bin_search */
	int mid, low, hight, size_sp;

	/** Puntatore ad array di interi contenere la mappa delle posizioni degli slot in stringpool */
	int* map_array;

	/** Controllo che sp e str non siano NULL, altrimenti salta salta e restituisce valore di errore -1 */
	if (sp != NULL && (&str) != NULL) {

		/** Calcolo e salvo la dimensione di sp */
		size_sp = sp_sizeof(sp);

		/** Se ha dimensione diversa da 0 è possibile effettuare la ricerca */
		if (size_sp != 0) {

			/** Ottengo la mappa delle posizione degli slot di sp*/
			map_array = _sp_map_array_stringpool(sp);

			/** Imposto il parametro hight del binary serch alla dimensione di sp*/
			hight = size_sp;

			/** Imposoto il parametro low del binary search a 1 */
			low = 0;

			/** Itero finchè str_cmp non è 0 ovvero è stata identificata esattamente la stringa ricercata oppure se abbiamo già controllato tutto gli slot */
			while (str_cmp != 0 && i != size_sp) {

				/** Calcolo mid su base della formula binary search */
				mid = (low + hight) / 2;

				/** Controllo la strina in posizione mid, contrale rispetto [low, hight] */
				str_cmp = strcmp(str.char_array,
						sp->strings[*(map_array + mid)]->char_array);

				/** In base al risultato associo a low o hight un valore diverso ed incremento la variabile indice */
				if (str_cmp > 0 || sp_strcmp(&str, "") == TRUE) {
					low = mid + 1;
					i++;
				} else if (str_cmp < 0) {
					hight = mid - 1;
					i++;
				}

			}
		}
	}

	/** Alla fine dll'iterazione controllo controllo se sia stata identificata o meno la stringa righesta */
	if ((i == sp_sizeof(sp) && str_cmp != 0) || (i == 0 && str_cmp != 0)) {
		/** In caso sia concluso il ciclo senza trovare la stringa o non sia neanche iniziato, imposto il risultato a -1*/
		iffound = -1;
	} else {
		/** In caso invece sia stata identificata la stringa resituisco la sua posizione */
		iffound = *(map_array + mid);
	}

	/** Ritorno il valore di ritorno che può essere o la posizione p della strnga cercata o -1 in caso di errore */
	return iffound;
}

/** \fn sp_find_string(const stringpool* sp, const string* str)
 * \brief Cerca la stringa str all’interno dello stringpool e ne restituisce la posizione, nel caso sia presente.
 * \param sp puntatore a struttura stringpool
 * \param str puntatore a struttura string costante
 * \return position_find Posizione p della stringa, con 0<= p < MAX_DIM_STRING_POOL se str è presente in sp; p=-1, altrimenti. Se sp e/o str sono NULL, restituisce -1.
 */
int sp_find_string(const stringpool* sp, const string* str) {

	/** Dichiaro la varibile di output e la inizializzo a -1 in caso di problemi durante la computazione */
	int position_find = -1;

	/** Dichiaro la variabile per l'iterazione su tutto l'array */
	int i;

	/** Variabile di controllo per risultato comparazione */
	int strcmp_result;

	/** Controllo che sp ed str non siano NUL */
	if (sp != NULL && str != NULL) {

		/** Itero su tutta la dimensione possibile dell'array*/
		for (i = 0; i < MAX_DIM_STRING_POOL; i++) {

			/** Controllo se la posizione i-esima è utilizzata */
			if (sp->positions[i] == USED_SLOT) {

				/** Comparo le stringhe e salvo il risultato*/
				strcmp_result = strcmp(str->char_array,
						sp->strings[i]->char_array);

				/** Controllo il risultato della comparazione*/
				if (strcmp_result == 0) {
					/** Se è stata identificata la stringa salvo la posizione i-esima corrente */
					position_find = i;

					/** Forzo l'indice i a sforare sul valore di uscita dal ciclo for*/
					i = MAX_DIM_STRING_POOL;
				}

			}
		}
	}

	/** Resituisco il valore di output, -1 se ci sono stati problemi e/o non è stata trovata o >= pari alla posione della stringa cercata in sp */
	return position_find;
}

/** \fn _sp_file_exist(const string* fname)
 * \brief Controlla se il file richiesto esiste e ne restituisce il valore di verità
 * \param fname puntatore a struttura string costante
 * \return ifexist valore boolean FALSE se non esiste non è possibile aprirlo in modalità di lettura, TRUE se esiste ed è possibile aprirlo in modalità di lettura
 */
boolean _sp_file_exist(const string* fname) {

	/** Dichiaro la variabile di output inizializzandola a FAlSE */
	boolean ifexist = FALSE;

	/** Dichiaro il puntatore  a file */
	FILE* fp;

	/** Verifico che fname non sia nullo */
	if (fname != NULL) {

		/** Controllo se è possibile aprire il file richiesto in modalità di lettura */
		if ((fp = fopen(fname->char_array, "r")) == NULL) {

			/** Se non è possibile aprirlo imposto la variabile di output a FALSE */
			ifexist = FALSE;
		} else {

			/** Altrimenti se è possibile aprie il file imposto a TRUE la variabile di output */
			ifexist = TRUE;

		}

		/** Chiudo il file */
		fclose(fp);
	}

	/** Ritorno la variabile di output */
	return ifexist;
}

/** \fn _sp_file_create(const string* fname)
 * \brief Controlla se esiste già il file e se non esiste lo crea
 * \param fname puntatore a struttura string costante
 * \return ifcreated boolean valore di verità,
 * TRUE se è esiste già o se non esiste ed è stato Creato, FALSE se non esiste non è stato possibile crearlo
 */
boolean _sp_file_create(const string* fname) {

	/** Dichiaro la variabile di output */
	boolean ifcreated = FALSE;

	/** Dichiaro il puntatore a file */
	FILE* fp;

	/** Verifico che fname non sia nullo */
	if (fname != NULL) {

		/** Controllo se non esiste già il file */
		if (_sp_file_exist(fname) == FALSE) {

			/** Se non esiste cerco di crearlo */
			if ((fp = fopen(fname->char_array, "w")) == NULL) {

				/** Se non si riesce a a crearlo imposto la variabile di output a FALSE */
				ifcreated = FALSE;
			} else {

				/** Altrimenti se sono riuscito* a crerlo imposto la variabile di output a TRUE */
				ifcreated = TRUE;
			}

			/** Chiudo il file aperto */
			fclose(fp);

		} else {
			/** Se esiste già imposto la variabile outpt a TRUE */
			ifcreated = TRUE;
		}

	}
	/** Ritorno il valore di output */
	return ifcreated;
}

/** \fn _sp_map_array_stringpool(stringpool* sp)
 * \brief Crea un array contenente le posizioni dei soli slot pieni
 *
 * Se sp non è NULL e contiene alcune string l'array di output conterrà in
 * posizioni consecutive le posizioni degli n slot di sp, avendo così a disposizione
 * un array senza spazi vuoti di posizioni reali anche in posizioni non contigue
 * da utilizzare in algoritmi in cui si necessitano slot contigui.

 * \param sp puntatore a struttura stringpool
 * \return array_map puntatore a array di interi di della dimensione di sp, NULL se sp è NULL
 */
int* _sp_map_array_stringpool(const stringpool* sp) {

	/** Dichiaro l'array di output */
	int* array_map = NULL;

	/** Dichiaro la variabile indice per il ciclo for e la variabile di posizione */
	int i, map_pos = 0;

	/** Controllo che sp non sia NULL */
	if (sp != NULL) {

		/** Inizializzo lo spazio di memoria per l'array di outpu calcolato sulla dimensione di sp */
		array_map = (int*) calloc((sp_sizeof(sp)), sizeof(int));

		/** Itero su tutte le possibili posizioni potenzialmente occupate in sp*/
		for (i = 0; i < MAX_DIM_STRING_POOL; i++) {

			/** Controllo se la i-esima posizione è occupata*/
			if (sp->positions[i] == USED_SLOT) {

				/** In caso sia occupata salvo in posizioni consecutive la posizione i-esima */
				*(array_map + map_pos) = i;
				/** Incremento la posizione del vettore di output solo se è stato inserito qualcosa */
				map_pos = map_pos + 1;
			}
		}
	}

	/** Ritorno la varibile di ouput */
	return array_map;
}
