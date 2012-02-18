/**
 * \file cunit_stringpool_lib.c
 * \brief File per il testing della libreria stringpool
 *
 * \date 2011
 * \section license Licenza
 * GPLv2 http://www.softwarelibero.it/gnudoc/gpl.it.txt
 * Per maggiori informazioni visitare il link o visualizzare il file LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "CUnit/Basic.h"

#include "bool.h"
#include "stringpool.h"
#include "spstring.h"

stringpool sp;
string* CONST_TEST_STRING_LOWER_CASE = NULL;
string* CONST_TEST_STRING_UPPER_CASE = NULL;

int CONST_TEST_STRING_LEN;

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 *
 */

int suite_void_init_func(void) {
	return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int suite_void_cleanup_func(void) {
	return 0;
}

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int suite_init_func(void) {
	sp_initialize_stringpool(&sp);
	CONST_TEST_STRING_LOWER_CASE = sp_new_string("stringa costante di test");
	CONST_TEST_STRING_UPPER_CASE = sp_new_string("STRINGA COSTANTE DI TEST");
	CONST_TEST_STRING_LEN = sp_strlen(CONST_TEST_STRING_LOWER_CASE);
	return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int suite_cleanup_func(void) {
	sp_free(CONST_TEST_STRING_LOWER_CASE);
	sp_free(CONST_TEST_STRING_UPPER_CASE);
	CONST_TEST_STRING_LEN = 0;
	sp_free_stringpool(&sp);
	sp_initialize_stringpool(&sp);
	return 0;
}

void test_sp_initialize_stringpool() {
	stringpool sp;
	sp_initialize_stringpool(&sp);

	CU_ASSERT_EQUAL(sp.used_counter, 0);
	CU_ASSERT(NULL != sp.strings);
}

void test_sp_new_empty_string() {
	string* s = sp_new_empty_string(10);
	CU_ASSERT(NULL != s);
	CU_ASSERT_EQUAL(sp_strlen(s), 0);
	sp_free(s);

	s = sp_new_empty_string(0);
	CU_ASSERT(NULL != s);
	s = sp_new_empty_string(-4);
	CU_ASSERT(NULL == s);
}

void test_sp_new_string() {
	string* s = sp_new_string("prova");
	CU_ASSERT(NULL != s);
	CU_ASSERT_EQUAL(sp_strlen(s), strlen("prova") );
	CU_ASSERT_TRUE(sp_strcmp(s, "prova"));

	string* copy = sp_new_string_as_struct(s);
	CU_ASSERT(NULL != copy);
	CU_ASSERT_EQUAL(sp_strlen(copy), sp_strlen(s));
	CU_ASSERT_STRING_EQUAL(copy->char_array, s->char_array);
	sp_free(s);
	sp_free(copy);
}

void test_sp_get_allocated_size() {
	string* s = sp_new_string("prova");
	CU_ASSERT_EQUAL(sp_get_allocated_size(s), 5+1);
	sp_free(s);

	s = sp_new_string("");
	CU_ASSERT_EQUAL(sp_get_allocated_size(s), 0+1);
	sp_free(s);

	string* s1 = sp_new_empty_string(10);
	CU_ASSERT_EQUAL(sp_get_allocated_size(s1), 10);
	sp_strcpy(s1, "prova", 0);
	CU_ASSERT_EQUAL(sp_strlen(s1), 5);
	CU_ASSERT_EQUAL(sp_get_allocated_size(s1), 10);
	sp_free(s1);
}

void test_sp_free() {
	string* s = sp_new_string("prova prova");
	CU_ASSERT_TRUE(sp_strcmp(s, "prova prova"));
	sp_free(s);
	CU_ASSERT_FALSE(sp_strcmp(s, "prova prova"));

	s = NULL;
	sp_free(s);
	CU_ASSERT_PTR_NULL(s);
}

void test_sp_strlen() {
	string* str = sp_new_empty_string(10);
	CU_ASSERT_EQUAL(sp_strlen(str), 0);
	sp_free(str);

	string* str1 = sp_new_string("Prova");
	CU_ASSERT_EQUAL(sp_strlen(str1), strlen("Prova"));
	sp_free(str1);

	string* str2 = sp_new_string("");
	CU_ASSERT_EQUAL(sp_strlen(str2), 0);
	sp_free(str2);

	string* str3 = NULL;
	CU_ASSERT_EQUAL(sp_strlen(str3), 0);
}

void test_sp_strcmp() {
	string* str = sp_new_empty_string(10);
	CU_ASSERT_TRUE(sp_strcmp(str, ""));
	sp_free(str);

	string* str1 = sp_new_string("test");
	CU_ASSERT_TRUE(sp_strcmp(str1, "test"));
	sp_free(str1);

	string* str2 = sp_new_string("");
	CU_ASSERT_TRUE(sp_strcmp(str2, ""));
	sp_free(str2);
}

void test_sp_strcpy() {
	string* str = sp_new_empty_string(100);
	CU_ASSERT_TRUE(sp_strcmp(str, ""));

	str = sp_strcpy(str, NULL, 0);
	CU_ASSERT_TRUE(sp_strcmp(str, ""));

	str = sp_strcpy(str, "parte A", 0);
	CU_ASSERT_TRUE(sp_strcmp(str, "parte A"));

	str = sp_strcpy(str, "", strlen("parte A"));
	CU_ASSERT_TRUE(sp_strcmp(str, "parte A"));

	str = sp_strcpy(str, " + parte B", strlen("parte A"));
	CU_ASSERT_TRUE(sp_strcmp(str, "parte A + parte B"));
	sp_free(str);

	str = sp_new_empty_string(20);
	CU_ASSERT_TRUE(sp_strcmp(str, ""));
	str = sp_strcpy(str, "parte A", 600);
	CU_ASSERT_TRUE(sp_strcmp(str, ""));

	str = NULL;
	str = sp_strcpy(str, "parte A", 0);
	CU_ASSERT(NULL == str);
}

void test_sp_strcat() {
	string* str = sp_strcat("parte A", " + parte B");
	CU_ASSERT_TRUE(sp_strcmp(str, "parte A + parte B"));
	sp_free(str);

	str = sp_strcat("parte A", "");
	CU_ASSERT_TRUE(sp_strcmp(str, "parte A"));
	sp_free(str);
}

void test_sp_lower_case() {
	string* str = sp_lower_case(CONST_TEST_STRING_UPPER_CASE);
	CU_ASSERT_STRING_EQUAL("stringa costante di test", str->char_array);
	sp_free(str);

	str = sp_lower_case(sp_new_empty_string(0));
	CU_ASSERT_STRING_EQUAL("", str->char_array);
	sp_free(str);

	str = sp_lower_case(NULL);
	CU_ASSERT(NULL == str);
}

void test_sp_upper_case() {
	string* str = sp_upper_case(CONST_TEST_STRING_LOWER_CASE);
	CU_ASSERT_STRING_EQUAL("STRINGA COSTANTE DI TEST", str->char_array);
	sp_free(str);

	str = sp_upper_case(sp_new_empty_string(0));
	CU_ASSERT_STRING_EQUAL("", str->char_array);
	sp_free(str);

	str = sp_upper_case(NULL);
	CU_ASSERT_PTR_NULL( str);
}

void test_sp_add_string(void) {
	string* str1;
	string* str2;
	string* str3;
	CU_ASSERT_TRUE( sp_isempty(&sp) );
	CU_ASSERT_TRUE( sp_add_string(&sp, sp_new_string(" ")) );
	CU_ASSERT_TRUE( sp_strcmp( sp_get_string(&sp, 0), " ") );
	CU_ASSERT_TRUE( sp_add_string_pos(&sp, str1 = sp_new_string("prova A"), 2) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 2), "prova A") );
	CU_ASSERT_TRUE( sp_add_string(&sp, str2 = sp_new_string("prova B")) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 1), "prova B") );
	sp_remove_string(&sp, 0);
	sp_remove_string(&sp, 1);
	sp_remove_string(&sp, 2);
	CU_ASSERT_TRUE( sp_add_string_pos(&sp, str3 = sp_new_empty_string(10), MAX_DIM_STRING_POOL-1) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, MAX_DIM_STRING_POOL-1), "") );
	sp_remove_string(&sp, MAX_DIM_STRING_POOL - 1);
	CU_ASSERT_TRUE(sp_isempty(&sp));
	CU_ASSERT_FALSE( sp_add_string(&sp, NULL) );
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 0);
	CU_ASSERT_TRUE(sp_isempty(&sp));

	sp_free(str1);
	sp_free(str2);
	sp_free(str3);
}

void test_sp_get_string(void) {
	CU_ASSERT_TRUE( sp_isempty(&sp) );
	CU_ASSERT_PTR_NULL (sp_get_string(NULL, 0));

	sp_add_string(&sp, sp_new_string(" "));
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 0), " ") );
	sp_add_string_pos(&sp, sp_new_string("prova A"), 4);
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 4), "prova A") );
	sp_add_string(&sp, sp_new_string("prova B"));
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 1), "prova B") );
	sp_add_string_pos(&sp, sp_new_string("prova C"), MAX_DIM_STRING_POOL - 1);
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, MAX_DIM_STRING_POOL-1), "prova C") );

	CU_ASSERT_PTR_NULL (sp_get_string(&sp, 5));
	CU_ASSERT_PTR_NULL (sp_get_string(&sp, 3));
	CU_ASSERT_PTR_NULL (sp_get_string(&sp, MAX_DIM_STRING_POOL));
	CU_ASSERT_PTR_NULL (sp_get_string(&sp, 1000));
	CU_ASSERT_PTR_NULL (sp_get_string(&sp, -4));

	sp_remove_string(&sp, MAX_DIM_STRING_POOL - 1);
	sp_remove_string(&sp, 0);
	sp_remove_string(&sp, 1);
	sp_remove_string(&sp, 4);
	CU_ASSERT_TRUE( sp_isempty(&sp) );
}

void test_sp_add_string_pos(void) {
	string* str1;
	string* str2;
	string* str3;
	string* str4;
	CU_ASSERT_TRUE(sp_isempty(&sp));
	CU_ASSERT_FALSE( sp_add_string_pos(&sp, CONST_TEST_STRING_LOWER_CASE, 1000) );
	CU_ASSERT_FALSE( sp_add_string_pos(&sp, CONST_TEST_STRING_LOWER_CASE, -33) );
	CU_ASSERT_TRUE( sp_isempty(&sp));
	CU_ASSERT_TRUE( sp_add_string_pos(&sp, sp_new_string(" ") , 3) );
	CU_ASSERT_TRUE( sp_strcmp( sp_get_string(&sp, 3), " ") );
	CU_ASSERT_TRUE( sp_add_string_pos(&sp, str1 = sp_new_string("prova A"), 7) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 7), "prova A") );
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 2);
	CU_ASSERT_FALSE( sp_add_string_pos(&sp, str2 = sp_new_string("prova B"), 100) );
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 2);
	CU_ASSERT_TRUE( sp_add_string_pos(&sp, str3 = sp_new_string("prova B"), 8) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 8), "prova B") );
	sp_remove_string(&sp, 3);
	sp_remove_string(&sp, 7);
	sp_remove_string(&sp, 8);
	CU_ASSERT_TRUE( sp_add_string_pos(&sp, str4 = sp_new_empty_string(10), MAX_DIM_STRING_POOL-1) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, MAX_DIM_STRING_POOL-1), "") );
	sp_remove_string(&sp, MAX_DIM_STRING_POOL - 1);
	CU_ASSERT_TRUE(sp_isempty(&sp));
	CU_ASSERT_FALSE( sp_add_string_pos(&sp, NULL, 0) );
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 0);
	CU_ASSERT_TRUE(sp_isempty(&sp));

	sp_free(str1);
	sp_free(str2);
	sp_free(str3);
	sp_free(str4);
}

void test_sp_remove_string(void) {
	CU_ASSERT_TRUE( sp_isempty(&sp) );
	sp_add_string(&sp, sp_new_string(" "));
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 0), " ") );
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 1);
	sp_remove_string(&sp, MAX_DIM_STRING_POOL);
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 1);
	sp_remove_string(&sp, -1);
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 1);
	sp_remove_string(&sp, 100);
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 1);
	sp_remove_string(&sp, 0);
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 0);
	CU_ASSERT_TRUE( sp_isempty(&sp) );
}

void test_sp_replace_string(void) {
	string* str1;
	string* str2;
	string* str3;
	string* str4;
	string* str5;
	string* str6;
	string* str7;
	CU_ASSERT_TRUE( sp_isempty(&sp) );
	CU_ASSERT_TRUE( sp_add_string(&sp, sp_new_string(" ")) );
	CU_ASSERT_FALSE( sp_replace_string(&sp, 0, NULL) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 0), " ") );
	CU_ASSERT_TRUE( sp_add_string_pos(&sp, str1 = sp_new_string("prova A"), 2) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 2), "prova A") );
	CU_ASSERT_TRUE( sp_add_string(&sp, str2 = sp_new_string("prova B")) );
	CU_ASSERT_TRUE( sp_strcmp( sp_get_string(&sp, 1), "prova B") );
	CU_ASSERT_FALSE( sp_replace_string(&sp, 100, str3 = sp_new_string("prova C")) );
	CU_ASSERT_FALSE( sp_replace_string(&sp, -78, str4 = sp_new_string("prova C")) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 1), "prova B") );
	CU_ASSERT_TRUE( sp_replace_string(&sp, 1, str5 = sp_new_string("prova C")) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 1), "prova C") );
	CU_ASSERT_TRUE( sp_add_string_pos(&sp, str6 = sp_new_empty_string(10), MAX_DIM_STRING_POOL-1) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, MAX_DIM_STRING_POOL-1), "") );
	CU_ASSERT_TRUE( sp_replace_string(&sp, MAX_DIM_STRING_POOL-1, str7 = sp_new_string("prova D")) );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, MAX_DIM_STRING_POOL-1), "prova D") );

	CU_ASSERT_PTR_NOT_NULL( sp_remove_string(&sp, MAX_DIM_STRING_POOL-1) );
	CU_ASSERT_PTR_NOT_NULL( sp_remove_string(&sp, 0) );
	CU_ASSERT_PTR_NOT_NULL( sp_remove_string(&sp, 1) );
	CU_ASSERT_PTR_NOT_NULL( sp_remove_string(&sp, 2) );
	CU_ASSERT_TRUE(sp_isempty(&sp));

	// replace rilascia le stringhe
	// queste free non devono cmq fallire
	sp_free(str1);
	sp_free(str2);
	sp_free(str3);
	sp_free(str4);
	sp_free(str5);
	sp_free(str6);
	sp_free(str7);
}

void test_sp_find_string(void) {
	string* str0;
	string* str1;
	string* str2;
	string* str3;
	CU_ASSERT_TRUE( sp_isempty(&sp) );
	sp_add_string(&sp, str0 = sp_new_string(" "));
	sp_add_string(&sp, str1 = sp_new_string("prova A"));
	sp_add_string(&sp, str2 = sp_new_string("prova B"));
	sp_add_string(&sp, str3 = sp_new_string("prova C"));
	sp_add_string_pos(&sp, sp_new_empty_string(10), MAX_DIM_STRING_POOL - 1);

	int pos = sp_find_string(&sp, str0);
	CU_ASSERT_EQUAL(pos, 0);
	pos = sp_find_string(&sp, str1);
	CU_ASSERT_EQUAL(pos, 1);
	pos = sp_find_string(&sp, str2);
	CU_ASSERT_EQUAL(pos, 2);
	pos = sp_find_string(&sp, str3);
	CU_ASSERT_EQUAL(pos, 3);
	pos = sp_find_string(&sp, sp_new_empty_string(0));
	CU_ASSERT_EQUAL(pos, MAX_DIM_STRING_POOL-1);
	pos = sp_find_string(&sp, NULL);
	CU_ASSERT_EQUAL(pos, -1);
	pos = sp_find_string(&sp, sp_new_string("stringa non presente"));
	CU_ASSERT_EQUAL(pos, -1);

	sp_remove_string(&sp, MAX_DIM_STRING_POOL - 1);
	sp_remove_string(&sp, 0);
	sp_remove_string(&sp, 1);
	sp_remove_string(&sp, 2);
	sp_remove_string(&sp, 3);
	CU_ASSERT_TRUE( sp_isempty(&sp) );

	sp_free(str0);
	sp_free(str1);
	sp_free(str2);
	sp_free(str3);
}

void test_sp_isfull(void) {
	CU_ASSERT_TRUE( sp_isempty(&sp) );
	CU_ASSERT_TRUE( sp_isfull(NULL) );
	register int i = 0;
	while (i < MAX_DIM_STRING_POOL) {
		CU_ASSERT_EQUAL(sp_isfull(&sp), FALSE);
		sp_add_string(&sp, sp_new_string("prova"));
		i++;
	}
	CU_ASSERT_TRUE(sp_isfull(&sp));

	sp_free_stringpool(&sp);
	CU_ASSERT_TRUE( sp_isempty(&sp) );

}

void test_sp_isempty(void) {
	string* str1;
	string* str2;
	CU_ASSERT_TRUE(sp_isempty(&sp));
	CU_ASSERT_EQUAL(sp_isempty(NULL), FALSE);
	sp_add_string(&sp, str1 = sp_new_string("prova 1"));
	CU_ASSERT_EQUAL(sp_isempty(&sp), FALSE);
	sp_add_string(&sp, str2 = sp_new_string("prova 2"));
	CU_ASSERT_EQUAL(sp_isempty(&sp), FALSE);
	sp_remove_string(&sp, 1);
	CU_ASSERT_EQUAL(sp_isempty(&sp), FALSE);
	sp_remove_string(&sp, 0);
	CU_ASSERT_TRUE( sp_isempty(&sp));

	sp_free(str1);
	sp_free(str2);
}

void test_sp_sizeof(void) {
	string* str1;
	string* str2;
	string* str3;
	CU_ASSERT_TRUE( sp_isempty(&sp) );
	CU_ASSERT_EQUAL(sp_sizeof(NULL), -1);
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 0);
	sp_add_string(&sp, str1 = sp_new_string("prova 1"));
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 1);
	sp_add_string(&sp, str2 = sp_new_string("prova 2"));
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 2);
	sp_replace_string(&sp, 2, str3 = sp_new_string("prova 3"));
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 2);
	sp_remove_string(&sp, 1);
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 1);
	sp_remove_string(&sp, 2);
	sp_remove_string(&sp, 0);
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 0);
	CU_ASSERT_TRUE( sp_isempty(&sp));

	sp_free(str1);
	sp_free(str2);
	sp_free(str3);
}

void test_sp_free_stringpool(void) {
	CU_ASSERT_TRUE( sp_isempty(&sp));
	sp_add_string(&sp, sp_new_string(" "));
	sp_add_string_pos(&sp, sp_new_string("prova A"), 3);
	sp_add_string_pos(&sp, sp_new_string("prova B"), 5);
	sp_add_string_pos(&sp, sp_new_string("prova C"), 2);
	sp_add_string_pos(&sp, sp_new_empty_string(10), MAX_DIM_STRING_POOL - 1);
	CU_ASSERT_FALSE( sp_isempty(&sp) );
	sp_free_stringpool(&sp);
	CU_ASSERT_TRUE(sp_isempty(&sp));
}

/** \fn test_sp_strcat_as_struct()
 * \brief Test per sp_strcat_as_struct
 *
 * Caso di test aggiunto in string_manipulation
 * \param void
 * \return void
 */
void test_sp_strcat_as_struct() {

	string* str1 = sp_strcat("parte A", " + parte B");
	CU_ASSERT_TRUE(sp_strcmp(str1, "parte A + parte B"));

	string* str2 = sp_strcat(" + parte C", "");
	CU_ASSERT_TRUE(sp_strcmp(str2, " + parte C"));

	string* str3 = sp_strcat_as_struct(str1, str2);
	CU_ASSERT_TRUE(sp_strcmp(str3, "parte A + parte B + parte C"));

	str1 = sp_strcat("Primo", NULL);
	CU_ASSERT_TRUE(sp_strcmp(str1, "Primo"));
	str2 = sp_strcat(NULL, "Terzo");
	CU_ASSERT_TRUE(sp_strcmp(str2, "Terzo"));

	str3 = sp_strcat_as_struct(str1, str2);
	CU_ASSERT_TRUE(sp_strcmp(str3, "PrimoTerzo"));

	str3 = sp_strcat_as_struct(str1, NULL);
	CU_ASSERT_TRUE(sp_strcmp(str3, "Primo"));

	str3 = sp_strcat_as_struct(NULL, str2);
	CU_ASSERT_TRUE(sp_strcmp(str3, "Terzo"));

	sp_free(str1);
	sp_free(str2);
	sp_free(str3);

}

/** \fn test_sp_save_to_file(void)
 * \brief Test per sp_save_to_file
 *
 * Caso di test aggiunto per testare il salvataggio su file
 * \param void
 * \return void
 */
void test_sp_save_to_file(void) {

	/** Dichiaro il puntare a string per il nome dle file */
	string* fname;

	/** Ci assicuriamo che sia vuoto sp */CU_ASSERT_TRUE(sp_isempty(&sp));

	/** Aggiungiamo 5 string a sp, possibilmente con spazi per verificare se la scrittura di frasi con spazi funziona */
	sp_add_string(&sp, fname = sp_new_string("Internet.csv"));
	sp_add_string(&sp, sp_new_string("Facebook il social network"));
	sp_add_string(&sp, sp_new_string("Google il motore di ricerca"));

	sp_add_string(&sp, sp_new_string(""));
	sp_add_string(&sp,
			sp_new_string("Flickr il social network per le fotografie"));

	/** Creiamo uno spazio vuoto eliminando la string in posizione 3 */
	sp_remove_string(&sp, 3);

	/** Controlliamo se in prima posizine abbimo il nome del file */CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 0), "Internet.csv") );

	/** Controlliamo che sia di dimensione 4 */CU_ASSERT_EQUAL(sp_sizeof(&sp), 4);

	/** Controlliamo che la dimensione di sp corrisponda al numero di righe scritte */CU_ASSERT_EQUAL(sp_save_to_file(&sp,*fname), sp_sizeof(&sp));

	/** Rimuoviamo le stringhe scritte*/
	sp_remove_string(&sp, 0);
	sp_remove_string(&sp, 1);
	sp_remove_string(&sp, 2);
	sp_remove_string(&sp, 4);

	/** Controlliamo che sp sia vuoto */CU_ASSERT_TRUE(sp_isempty(&sp));

	/** Creiamo una stringa con il nome del file senza metterlo in sp */
	fname = sp_new_string("Indirizzo_Disney.csv");

	/** Aggiungiamo le stringhe in sp, miste con spazi, numeri e simboli speciali */
	sp_add_string(&sp, sp_new_string("Pippo Pluto"));
	sp_add_string(&sp, sp_new_string("Via Paperino n¡5"));
	sp_add_string(&sp, sp_new_string("Disneyland Paris #27364"));

	/** Verifichiamo la dimensione di sp*/CU_ASSERT_EQUAL(sp_sizeof(&sp), 3);
	/** Verifichiamo che la dimensioni di sp corrisponda al numero di righe scritte*/CU_ASSERT_EQUAL(sp_save_to_file(&sp,*fname), sp_sizeof(&sp));

	/** Liberiamo sp dalle righe scritte, svuotandolo*/
	sp_remove_string(&sp, 0);
	sp_remove_string(&sp, 1);
	sp_remove_string(&sp, 2);

	/** Verifichiamo che sia vuoto*/CU_ASSERT_TRUE(sp_isempty(&sp));

	/** Scriviamo un file vuoto */
	fname = sp_new_string("Zero_Righe.csv");
	CU_ASSERT_EQUAL(sp_save_to_file(&sp,*fname), sp_sizeof(&sp));

	/** Non dovrebbe scrivere nessun file e ritornare errore -1 a causa del nome sbagliato del file*/
	fname = sp_new_string(" ");
	CU_ASSERT_EQUAL(sp_save_to_file(&sp,*fname), -1);

	/** Non dovrebbe scrivere nessun file e ritornare errore -1 a causa del nome sbagliato del file*/
	fname = sp_new_string("");
	CU_ASSERT_EQUAL(sp_save_to_file(&sp,*fname), -1);

	/** Non dovrebbe scrivere nessun file e ritornare errore -1 a causa del puntatore a sp NULL */
	stringpool* sp_void = NULL;
	fname = sp_new_string("nome.csv");
	CU_ASSERT_EQUAL(sp_save_to_file(sp_void,*fname), -1);

}

/** \fn test_sp_load_from_file(void)
 * \brief Test per sp_load_from_file
 *
 * Caso di test aggiunto per testare il caricamento da file
 *
 * \param void
 * \return void
 */
void test_sp_load_from_file(void) {

	/** Credo la string con il nome del file da caricare,  stato creato nel test precedente */
	string* fname = sp_new_string("Indirizzo_Disney.csv");

	/** Controlliamo che sp sia vuoto, riceverˆ in ingresso le righe del file letto */CU_ASSERT_TRUE(sp_isempty(&sp));

	/** Controlliamo che il caricamento ritorni il numero di righe della dimensione di sp*/CU_ASSERT_EQUAL(sp_load_from_file(&sp,*fname), sp_sizeof(&sp));
	CU_ASSERT_EQUAL(sp_sizeof(&sp), 3);

	/** Controllo se le stringhe caricate sono esattamente quelle che avevo scritto su file e nella loro posizione*/CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 0), "Pippo Pluto") );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 2), "Disneyland Paris #27364") );

	/** Rimuovo le stringhe da sp*/
	sp_remove_string(&sp, 0);
	sp_remove_string(&sp, 1);
	sp_remove_string(&sp, 2);

	/** Controllo che sp sia vuoto */CU_ASSERT_TRUE(sp_isempty(&sp));

	/** Dichiaro ed inizializzo un nuovo nome di file da leggere, sempre che esista */
	fname = sp_new_string("Internet.csv");

	/** Carichiamo da file e controlliamo che il numero di righe caricate corrisponda alla dimensione di sp e che sp sia della dimensione che ci aspettiamo*/CU_ASSERT_EQUAL(sp_load_from_file(&sp,*fname), sp_sizeof(&sp));
	CU_ASSERT_EQUAL(sp_sizeof(&sp),4);

	/** Controlliamo che il caricamento in posizioni non contigue sia andato a buon fine */CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 1), "Facebook il social network") );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 4), "Flickr il social network per le fotografie") );

	/** Ci aspettiam che la posizione 3 sia NULL */CU_ASSERT_PTR_NULL (sp_get_string(&sp, 3));

}

/** \fn test_sp_bubble_sort(void)
 * \brief Test per sp_bubble_sor
 *
 * Caso di test aggiunto per testare l'ordinamento con bubble sort conservando posizioni vuote/piene
 *
 * \param void
 * \return void
 */
void test_sp_bubble_sort(void) {

	string* fname;

	sp_free_stringpool(&sp);
	CU_ASSERT_TRUE(sp_isempty(&sp));

	/** Dichiaro ed inizializzo un nuovo nome di file da leggere, sempre che esista */
	fname = sp_new_string("Internet.csv");

	/** Carichiamo da file e controlliamo che il numero di righe caricate corrisponda alla dimensione di sp e che sp sia della dimensione che ci aspettiamo*/CU_ASSERT_EQUAL(sp_load_from_file(&sp,*fname), sp_sizeof(&sp));
	CU_ASSERT_EQUAL(sp_sizeof(&sp),4);

	bubble_sort(&sp);

	/** Ho ordinato le 4 frasi con gEdit e mi aspetto che esse siano nel seguente ordine*/CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 0), "Facebook il social network") );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 1), "Flickr il social network per le fotografie") );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 2), "Google il motore di ricerca") );

	/** Ci aspettiamo che anche dopo l'ordinamente la posizione 3 sia NULL */CU_ASSERT_PTR_NULL (sp_get_string(&sp, 3));

	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 4), "Internet.csv") );

}

/** \fn test_sp_bin_search(void)
 * \brief Test per sp_bin_search
 *
 * Caso di test aggiunto per testare la ricerca binaria in concomitanza del bubble sort
 *
 * \param void
 * \return void
 */
void test_sp_bin_search(void) {

	string* pattern;
	string* fname;

	/** Controllo che sp sia vuoto*/CU_ASSERT_TRUE(sp_isempty(&sp));

	/** Inserisco in ordine casuale 6 stringhe */
	sp_add_string(&sp, sp_new_string("Domenico"));
	sp_add_string(&sp, sp_new_string("Google"));
	sp_add_string(&sp, sp_new_string("Flickr"));
	sp_add_string(&sp, sp_new_string("Ragusa"));
	sp_add_string(&sp, sp_new_string("Colombo"));
	sp_add_string(&sp, sp_new_string("Monaco"));

	/** Ne rimuovo una in posizione 3, Ragusa*/
	sp_remove_string(&sp, 3);

	/** Ricontrollo la dimensione */CU_ASSERT_EQUAL(sp_sizeof(&sp), 5);

	/** Ordino l'array,  una specifica per il binary search */
	bubble_sort(&sp);

	/**Dopo l'ordinamento  mi aspetto che sp sia ordinato in questo modo:
	 * Colombo
	 * Domenico
	 * Flickr
	 * Google
	 * Monaco
	 */

	/** Effettuo una prima ricerca sul valore elimnato e mi aspetto di riceve errore*/
	pattern = sp_new_string("Ragusa");
	CU_ASSERT_EQUAL(bin_search(&sp, *pattern), -1);

	/** Controllo che le posizioni degli elementi sia quella che mi aspetto */
	pattern = sp_new_string("Domenico");
	CU_ASSERT_EQUAL(bin_search(&sp, *pattern), 1);

	pattern = sp_new_string("Flickr");
	CU_ASSERT_EQUAL(bin_search(&sp, *pattern), 2);

	pattern = sp_new_string("Google");
	CU_ASSERT_EQUAL(bin_search(&sp, *pattern), 4);

	pattern = sp_new_string("Monaco");
	CU_ASSERT_EQUAL(bin_search(&sp, *pattern), 5);
}

/** \fn test_sp_file_exist_create(void)
 * \brief Test per _sp_file_exist _sp_file_create
 *
 * Caso di test aggiunto per testare le funzioni per creare file e controllare se esite giˆ il file
 *
 * \param void
 * \return void
 */

void test_sp_file_exist_create(void) {

	/** Dichiaro e creo la variabile per il nome del file */
	string* fname;
	fname = sp_new_string("nomefile.csv");

	/** Controllo se esiste */CU_ASSERT_FALSE(_sp_file_exist(fname));

	/** Cerco di crearlo */CU_ASSERT_TRUE(_sp_file_create(fname));

	/** Ricontrollo se esiste*/CU_ASSERT_TRUE(_sp_file_exist(fname));

	/** Rimuovo il file */
	remove("nomefile.csv");

	/** Rimuovo il file */

	sp_free(fname);
	fname = NULL;

	/** Controllo se esiste un file NULL */CU_ASSERT_FALSE(_sp_file_exist(fname));

	/** Dichiaro un nome di file pre-esistenbte*/
	fname = sp_new_string("Indirizzo_Disney.csv");

	/** Controlliamo se esiste*/CU_ASSERT_TRUE(_sp_file_exist(fname));

	/** Controlliamo se possiamo sovrascriverlo */CU_ASSERT_TRUE(_sp_file_create(fname));

	sp_free(fname);
}

/** \fn test_sp_map_array_stringpool(void)
 * \brief Test per _sp_map_array_stringpool
 *
 * Caso di test aggiunto per testare la creazione della mappa di stringpool
 *
 * \param void
 * \return void
 */

void test_sp_map_array_stringpool(void) {

	//sp_free(&sp);

	int* map_array = NULL;
	/** Controllo che sp sia vuoto*/
	CU_ASSERT_TRUE(sp_isempty(&sp));

	/** Inseriamo a salti alcuni elemnti in sp*/
	sp_add_string_pos(&sp, sp_new_string("Drupal"), 0);
	sp_add_string_pos(&sp, sp_new_string("Django"), 2);
	sp_add_string_pos(&sp, sp_new_string("Wordpress"), 3);
	sp_add_string_pos(&sp, sp_new_string("Php"), 5);
	sp_add_string_pos(&sp, sp_new_string("Magento"), 7);
	sp_add_string_pos(&sp, sp_new_string("Python"), 8);

	/** Ricontrollo la dimensione */CU_ASSERT_EQUAL(sp_sizeof(&sp), 6);

	map_array = _sp_map_array_stringpool(&sp);

	CU_ASSERT_PTR_NULL(!map_array);

	/** Controlleremo in modo "consecutivo" le posizioni sp ignorando le posizoni reali,
	 * Controllando passo per passo elementi consecuitivi, il primo elemento, il secondo ecc...
	 */

	/** Il termine Drupal  in posizione reale 0 ed in posizione virtuale map_array 0.
	 * In entrambi i casi  il primo elemento.
	 */
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, *(map_array+0)), "Drupal") );

	/** Il termine Django  in posizione reale 2 ed in posizione virtuale map_array 1.
	 * In entrambi i casi  il Secondo elemento.
	 */
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, *(map_array+1)), "Django") );

	/** Il termine Wordpress  in posizione reale 3 ed in posizione virtuale map_array 2.
	 * In entrambi i casi  il Terzo elemento.
	 */
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, *(map_array+2)), "Wordpress") );

	/** Il termine Php  in posizione reale 5 ed in posizione virtuale map_array 3.
	 * In entrambi i casi  il Quarto elemento.
	 */
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, *(map_array+3)), "Php") );

	/** Il termine Magento  in posizione reale 7 ed in posizione virtuale map_array 4.
	 * In entrambi i casi  il Quinto elemento.
	 */
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, *(map_array+4)), "Magento") );

	/** Il termine Python  in posizione reale 8 ed in posizione virtuale map_array 5.
	 * In entrambi i casi  il Sesto elemento.
	 */
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, *(map_array+5)), "Python") );

	/** Controlliamo immettendo direttamente le posizioni reali */
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 2), "Django") );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 0), "Drupal") );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 3), "Wordpress") );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 5), "Php") );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 7), "Magento") );
	CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 8), "Python") );

	sp_free_stringpool(&sp);

}

int main(int argc, char *argv[]) {
	// initialize the CUnit test registry
	if (CUE_SUCCESS != CU_initialize_registry()) {
		CU_get_error();
		system("PAUSE");
		return -1;
	}

	// create the test arrays
	CU_TestInfo test_array_stringpool_creation[] = {
			{ "test of sp_initialize_stringpool()",
					test_sp_initialize_stringpool }, CU_TEST_INFO_NULL, };

	CU_TestInfo test_array_string_creation[] = { {
			"test of sp_new_empty_string()", test_sp_new_empty_string }, {
			"test of sp_new_string()", test_sp_new_string }, {
			"test of sp_get_allocated_size()", test_sp_get_allocated_size }, {
			"test of sp_free()", test_sp_free }, CU_TEST_INFO_NULL, };

	CU_TestInfo test_array_string_manipulation[] = { { "test of sp_strlen()",
			test_sp_strlen }, { "test of sp_strcmp()", test_sp_strcmp }, {
			"test of sp_strcat()", test_sp_strcat }, { "test of sp_strcpy()",
			test_sp_strcpy }, { "test of sp_strcat_as_struct()",
			test_sp_strcat_as_struct }, CU_TEST_INFO_NULL, };

	CU_TestInfo test_array_string_case[] = { { "test of sp_lower_case()",
			test_sp_lower_case }, { "test of sp_upper_case()",
			test_sp_upper_case }, CU_TEST_INFO_NULL, };

	CU_TestInfo test_array_stringpool_functions[] = { {
			"test of sp_add_string()", test_sp_add_string }, {
			"test of sp_get_string()", test_sp_get_string }, {
			"test of sp_add_string_pos()", test_sp_add_string_pos }, {
			"test of sp_remove_string()", test_sp_remove_string }, {
			"test of sp_replace_string()", test_sp_replace_string }, {
			"test of sp_find_string()", test_sp_find_string }, {
			"test of sp_isfull()", test_sp_isfull }, { "test of sp_isempty()",
			test_sp_isempty }, { "test of sp_sizeof()", test_sp_sizeof }, {
			"test of sp_free_stringpool()", test_sp_free_stringpool },
			CU_TEST_INFO_NULL, };

	CU_TestInfo test_array_file[] = { { "test of sp_save_to_file()",
			test_sp_save_to_file }, { "test of sp_load_from_file()",
			test_sp_load_from_file }, CU_TEST_INFO_NULL, };

	CU_TestInfo test_array_sp_bubble_sort[] = { { "test of bubble_sort()",
			test_sp_bubble_sort }, CU_TEST_INFO_NULL, };

	CU_TestInfo test_array_sp_bin_search[] = { { "test of bin_search()",
			test_sp_bin_search }, CU_TEST_INFO_NULL, };

	CU_TestInfo test_array_extra_file[] = { {
			"test of _sp_file_exist() e _sp_file_create() ",
			test_sp_file_exist_create }, CU_TEST_INFO_NULL, };

	CU_TestInfo test_array_extra_stringpool[] =
			{ { "test of _sp_map_array_stringpool ",
					test_sp_map_array_stringpool }, CU_TEST_INFO_NULL, };

	// create the suites & add the tests to the suite
	CU_SuiteInfo suites[] = { { "test suite for stringpool creation",
			suite_void_init_func, suite_void_cleanup_func,
			test_array_stringpool_creation }, {
			"test suite for string creation", suite_void_init_func,
			suite_void_cleanup_func, test_array_string_creation }, {
			"test suite for string manipulation", suite_void_init_func,
			suite_void_cleanup_func, test_array_string_manipulation }, {
			"test suite for string font case change", suite_init_func,
			suite_cleanup_func, test_array_string_case }, {
			"test suite for stringpool functions", suite_init_func,
			suite_cleanup_func, test_array_stringpool_functions }, {
			"test suite for file functions", suite_init_func,
			suite_cleanup_func, test_array_file }, {
			"test suite for bubble sort", suite_init_func, suite_cleanup_func,
			test_array_sp_bubble_sort }, { "test suite for binary search",
			suite_init_func, suite_cleanup_func, test_array_sp_bin_search }, {
			"test suite for extra function file", suite_init_func,
			suite_cleanup_func, test_array_extra_file }, {
			"test suite for extra stringpool function", suite_init_func,
			suite_cleanup_func, test_array_extra_stringpool },

	CU_SUITE_INFO_NULL, };

	// add the suites to the registry
	CU_ErrorCode error = CU_register_suites(suites);

	if (CUE_SUCCESS != error) {
		CU_cleanup_registry();
		CU_get_error();
		system("PAUSE");
		return -1;
	}

	// Run all tests using the CUnit Basic interface
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	CU_get_error();
	system("PAUSE");
	return 0;

}
