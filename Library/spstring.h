/** \file spstring.h
 * \brief Header per funzioni stringpool
 *
 * Protitpi di funzioni per la manipolazione dei dati gestiti dalla libreria stringpool
 *
 * \author Domenico Monaco, domenico.monaco@kiuz.it
 * \date 2011
 * \section license Licenza
 * GPLv2 http://www.softwarelibero.it/gnudoc/gpl.it.txt
 * Per maggiori informazioni visitare il link o visualizzare il file LICENSE
 */

#ifndef SPSTRING_H_
#define SPSTRING_H_ /**< Impedisce inclusioni multiple */

/** \include bool.h
 * Importa tipi di dato boolean */
#include "bool.h"

/** \include stringpool.h
 * Importa tipi di dato string e stringpool */
#include "stringpool.h"

void sp_initialize_stringpool(stringpool* sp);
void sp_free_stringpool(stringpool* sp);
string* sp_new_string(const char* str);
string* sp_new_empty_string(int len);
int sp_get_allocated_size(const string* str);
void sp_free(string* str);
int sp_strlen(const string* str);
boolean sp_strcmp(const string* str1, const char* str2);
string* sp_new_string_as_struct(const string* str);
string* sp_strcpy(string* copy, const char* original, int offset);
string* sp_strcat(const char* str1, const char* str2);
string* sp_strcat_as_struct(const string* str1, const string* str2);
string* sp_lower_case(const string* str);
string* sp_upper_case(const string* str);
int sp_sizeof(const stringpool* sp);
boolean sp_isempty(const stringpool* sp);
boolean sp_isfull(const stringpool* sp);
int sp_find_string(const stringpool* sp, const string* str);
string* sp_get_string(const stringpool* sp, int pos);
boolean sp_add_string(stringpool* sp, string* str);
boolean sp_add_string_pos(stringpool* sp, string* str, int pos);
string* sp_remove_string(stringpool* sp, int pos);
boolean sp_replace_string(stringpool* sp, int pos, string* newstr);
int sp_save_to_file(stringpool* sp, const string fname);
int sp_load_from_file(stringpool* sp, const string fname);
void bubble_sort(stringpool* sp);
int bin_search(const stringpool* sp, const string str);

boolean _sp_file_create(const string* fname);
boolean _sp_file_exist(const string* fname);
int* _sp_map_array_stringpool(const stringpool* sp);

#endif /* END SPSTRING_H_ */
