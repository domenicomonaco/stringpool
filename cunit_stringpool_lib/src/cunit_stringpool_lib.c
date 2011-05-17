#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "spstring.h"
#include "bool.h"


stringpool sp;
string* CONST_TEST_STRING_LOWER_CASE = NULL;
string* CONST_TEST_STRING_UPPER_CASE = NULL;
int CONST_TEST_STRING_LEN;

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int suite_void_init_func (void) {
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
int suite_init_func (void) {
/*    sp_initialize_stringpool(&sp);
    CONST_TEST_STRING_LOWER_CASE = sp_new_string("stringa costante di test");
    CONST_TEST_STRING_UPPER_CASE = sp_new_string("STRINGA COSTANTE DI TEST");
    CONST_TEST_STRING_LEN = sp_strlen(CONST_TEST_STRING_LOWER_CASE);*/
    return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int suite_cleanup_func(void) {
/*	sp_free(CONST_TEST_STRING_LOWER_CASE);
	sp_free(CONST_TEST_STRING_UPPER_CASE);
	CONST_TEST_STRING_LEN = 0;
    sp_free_stringpool(&sp);
    sp_initialize_stringpool(&sp);*/
    return 0;
}

void test_sp_initialize_stringpool() {
/*     stringpool sp;
     sp_initialize_stringpool(&sp);
     CU_ASSERT_EQUAL(sp.used_counter, 0);
	 CU_ASSERT(NULL != sp.strings);*/
}

void test_sp_new_empty_string() {
/*     string* s = sp_new_empty_string(10);
     CU_ASSERT(NULL != s);
     CU_ASSERT_EQUAL(sp_strlen(s), 0);
     sp_free(s);

     s = sp_new_empty_string(0);
     CU_ASSERT(NULL != s);
     s = sp_new_empty_string(-4);
     CU_ASSERT(NULL == s);*/
}

void test_sp_new_string() {
/*     string* s = sp_new_string("prova");
     CU_ASSERT(NULL != s);
     CU_ASSERT_EQUAL(sp_strlen(s), strlen("prova") );
     CU_ASSERT_TRUE(sp_strcmp(s, "prova"));

     string* copy = sp_new_string_as_struct(s);
     CU_ASSERT(NULL != copy);
     CU_ASSERT_EQUAL(sp_strlen(copy), sp_strlen(s));
     CU_ASSERT_STRING_EQUAL(copy->char_array, s->char_array);
     sp_free(s);
     sp_free(copy);*/
}

void test_sp_get_allocated_size() {
/*	string* s = sp_new_string("prova");
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
	sp_free(s1);*/
}

void test_sp_free() {
/*     string* s = sp_new_string("prova prova");
     CU_ASSERT_TRUE(sp_strcmp(s, "prova prova"));
     sp_free(s);
     CU_ASSERT_FALSE(sp_strcmp(s, "prova prova"));

     s = NULL;
     sp_free(s);
     CU_ASSERT_PTR_NULL(s);*/
}

void test_sp_strlen() {
/*     string* str = sp_new_empty_string(10);
     CU_ASSERT_EQUAL(sp_strlen(str), 0);
     sp_free(str);

     string* str1 = sp_new_string("Prova");
     CU_ASSERT_EQUAL(sp_strlen(str1), strlen("Prova"));
     sp_free(str1);

     string* str2 = sp_new_string("");
     CU_ASSERT_EQUAL(sp_strlen(str2), 0);
     sp_free(str2);

     string* str3 = NULL;
     CU_ASSERT_EQUAL(sp_strlen(str3), 0);*/
}

void test_sp_strcmp() {
/*     string* str = sp_new_empty_string(10);
     CU_ASSERT_TRUE(sp_strcmp(str, ""));
     sp_free(str);

     string* str1 = sp_new_string("test");
     CU_ASSERT_TRUE(sp_strcmp(str1, "test"));
     sp_free(str1);

     string* str2 = sp_new_string("");
     CU_ASSERT_TRUE(sp_strcmp(str2, ""));
     sp_free(str2);*/
}

void test_sp_strcpy() {
/*     string* str = sp_new_empty_string(100);
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
     CU_ASSERT(NULL == str);*/
}

void test_sp_strcat() {
/*     string* str = sp_strcat("parte A", " + parte B");
     CU_ASSERT_TRUE(sp_strcmp(str, "parte A + parte B"));
     sp_free(str);

     str = sp_strcat("parte A", "");
     CU_ASSERT_TRUE(sp_strcmp(str, "parte A"));
     sp_free(str);*/
}

void test_sp_lower_case() {
/*     string* str = sp_lower_case(CONST_TEST_STRING_UPPER_CASE );
     CU_ASSERT_STRING_EQUAL("stringa costante di test", str->char_array);
     sp_free(str);

     str = sp_lower_case(sp_new_empty_string(0));
     CU_ASSERT_STRING_EQUAL("", str->char_array);
     sp_free(str);

     str = sp_lower_case(NULL);
     CU_ASSERT(NULL == str);*/
}

void test_sp_upper_case() {
/*     string* str = sp_upper_case(CONST_TEST_STRING_LOWER_CASE);
     CU_ASSERT_STRING_EQUAL("STRINGA COSTANTE DI TEST", str->char_array);
     sp_free(str);

     str = sp_upper_case(sp_new_empty_string(0));
     CU_ASSERT_STRING_EQUAL("", str->char_array);
     sp_free(str);

     str = sp_upper_case(NULL);
     CU_ASSERT_PTR_NULL( str);*/
}

void test_sp_add_string(void) {
 /*        string* str1;
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
         sp_remove_string(&sp, MAX_DIM_STRING_POOL-1);
         CU_ASSERT_TRUE(sp_isempty(&sp));
         CU_ASSERT_FALSE( sp_add_string(&sp, NULL) );
         CU_ASSERT_EQUAL(sp_sizeof(&sp), 0);
         CU_ASSERT_TRUE(sp_isempty(&sp));

		 sp_free(str1);
         sp_free(str2);
         sp_free(str3);*/
    }

    void test_sp_get_string(void) {
/*         CU_ASSERT_TRUE( sp_isempty(&sp) );
         CU_ASSERT_PTR_NULL (sp_get_string(NULL, 0));

         sp_add_string(&sp, sp_new_string(" "));
         CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 0), " ") );
         sp_add_string_pos(&sp, sp_new_string("prova A"), 4);
         CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 4), "prova A") );
         sp_add_string(&sp, sp_new_string("prova B"));
         CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, 1), "prova B") );
         sp_add_string_pos(&sp, sp_new_string("prova C"), MAX_DIM_STRING_POOL-1);
         CU_ASSERT_TRUE(sp_strcmp( sp_get_string(&sp, MAX_DIM_STRING_POOL-1), "prova C") );

         CU_ASSERT_PTR_NULL (sp_get_string(&sp, 5));
         CU_ASSERT_PTR_NULL (sp_get_string(&sp, 3));
         CU_ASSERT_PTR_NULL (sp_get_string(&sp, MAX_DIM_STRING_POOL));
         CU_ASSERT_PTR_NULL (sp_get_string(&sp, 1000));
         CU_ASSERT_PTR_NULL (sp_get_string(&sp, -4));

         sp_remove_string(&sp, MAX_DIM_STRING_POOL-1);
         sp_remove_string(&sp, 0);
         sp_remove_string(&sp, 1);
         sp_remove_string(&sp, 4);
         CU_ASSERT_TRUE( sp_isempty(&sp) );*/
    }

    void test_sp_add_string_pos(void) {
/*         string* str1;
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
         sp_remove_string(&sp, MAX_DIM_STRING_POOL-1);
         CU_ASSERT_TRUE(sp_isempty(&sp));
         CU_ASSERT_FALSE( sp_add_string_pos(&sp, NULL, 0) );
         CU_ASSERT_EQUAL(sp_sizeof(&sp), 0);
         CU_ASSERT_TRUE(sp_isempty(&sp));

         sp_free(str1);
         sp_free(str2);
         sp_free(str3);
         sp_free(str4);*/
    }

    void test_sp_remove_string(void) {
/*         CU_ASSERT_TRUE( sp_isempty(&sp) );
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
         CU_ASSERT_TRUE( sp_isempty(&sp) );*/
    }

    void test_sp_replace_string(void) {
 /*        string* str1;
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
         sp_free(str7);*/
    }

    void test_sp_find_string(void) {
  /*       string* str0;
         string* str1;
         string* str2;
         string* str3;
         CU_ASSERT_TRUE( sp_isempty(&sp) );
         sp_add_string(&sp, str0 = sp_new_string(" "));
         sp_add_string(&sp, str1 = sp_new_string("prova A"));
         sp_add_string(&sp, str2 = sp_new_string("prova B"));
         sp_add_string(&sp, str3 = sp_new_string("prova C"));
         sp_add_string_pos(&sp, sp_new_empty_string(10), MAX_DIM_STRING_POOL-1);

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

         sp_remove_string(&sp, MAX_DIM_STRING_POOL-1);
         sp_remove_string(&sp, 0);
         sp_remove_string(&sp, 1);
         sp_remove_string(&sp, 2);
         sp_remove_string(&sp, 3);
         CU_ASSERT_TRUE( sp_isempty(&sp) );

         sp_free(str0);
         sp_free(str1);
         sp_free(str2);
         sp_free(str3);*/
    }

    void test_sp_isfull(void) {
 /*        CU_ASSERT_TRUE( sp_isempty(&sp) );
         CU_ASSERT_TRUE( sp_isfull(NULL) );
         register int i=0;
         while(i<MAX_DIM_STRING_POOL) {
             CU_ASSERT_EQUAL(sp_isfull(&sp), FALSE);
             sp_add_string(&sp, sp_new_string("prova"));
             i++;
         }
         CU_ASSERT_TRUE(sp_isfull(&sp));

         sp_free_stringpool(&sp);
         CU_ASSERT_TRUE( sp_isempty(&sp) );*/

    }

    void test_sp_isempty(void) {
 /*        string* str1;
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
         sp_free(str2);*/
    }

    void test_sp_sizeof(void) {
/*         string* str1;
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
         sp_free(str3);*/
    }

    void test_sp_free_stringpool(void) {
/*         CU_ASSERT_TRUE( sp_isempty(&sp));
         sp_add_string(&sp, sp_new_string(" "));
         sp_add_string_pos(&sp, sp_new_string("prova A"), 3);
         sp_add_string_pos(&sp, sp_new_string("prova B"), 5);
         sp_add_string_pos(&sp, sp_new_string("prova C"), 2);
         sp_add_string_pos(&sp, sp_new_empty_string(10), MAX_DIM_STRING_POOL-1);
         CU_ASSERT_FALSE( sp_isempty(&sp) );
         sp_free_stringpool(&sp);
         CU_ASSERT_TRUE(sp_isempty(&sp));*/
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
      { "test of sp_initialize_stringpool()", test_sp_initialize_stringpool },
      CU_TEST_INFO_NULL,
    };

   CU_TestInfo test_array_string_creation[] = {
      { "test of sp_new_empty_string()", test_sp_new_empty_string },
      { "test of sp_new_string()", test_sp_new_string },
      { "test of sp_get_allocated_size()", test_sp_get_allocated_size },
      { "test of sp_free()", test_sp_free },
      CU_TEST_INFO_NULL,
    };

    CU_TestInfo test_array_string_manipulation[] = {
      { "test of sp_strlen()", test_sp_strlen },
      { "test of sp_strcmp()", test_sp_strcmp },
      { "test of sp_strcat()", test_sp_strcat },
      { "test of sp_strcpy()", test_sp_strcpy },
      CU_TEST_INFO_NULL,
    };

    CU_TestInfo test_array_string_case[] = {
      { "test of sp_lower_case()", test_sp_lower_case },
      { "test of sp_upper_case()", test_sp_upper_case },
      CU_TEST_INFO_NULL,
    };

    CU_TestInfo test_array_stringpool_functions[] = {
      { "test of sp_add_string()", test_sp_add_string },
      { "test of sp_get_string()", test_sp_get_string },
      { "test of sp_add_string_pos()", test_sp_add_string_pos },
      { "test of sp_remove_string()", test_sp_remove_string },
      { "test of sp_replace_string()", test_sp_replace_string },
      { "test of sp_find_string()", test_sp_find_string },
      { "test of sp_isfull()", test_sp_isfull },
      { "test of sp_isempty()", test_sp_isempty },
      { "test of sp_sizeof()", test_sp_sizeof },
      { "test of sp_free_stringpool()", test_sp_free_stringpool },
      CU_TEST_INFO_NULL,
    };

    // create the suites & add the tests to the suite
    CU_SuiteInfo suites[] = {
      { "test suite for stringpool creation", suite_void_init_func, suite_void_cleanup_func, test_array_stringpool_creation },
      { "test suite for string creation", suite_void_init_func, suite_void_cleanup_func, test_array_string_creation },
      { "test suite for string manipulation", suite_void_init_func, suite_void_cleanup_func, test_array_string_manipulation },
      { "test suite for string font case change", suite_init_func, suite_cleanup_func, test_array_string_case },
      { "test suite for stringpool functions", suite_init_func, suite_cleanup_func, test_array_stringpool_functions },
      CU_SUITE_INFO_NULL,
    };

   // add the suites to the registry
   CU_ErrorCode error = CU_register_suites(suites);

   if (CUE_SUCCESS != error) {
      CU_cleanup_registry();
      CU_get_error();
      //system("PAUSE");
      return -1;
   }

   // Run all tests using the CUnit Basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   CU_get_error();
   //system("PAUSE");
   return 0;

}
