/** \file bool.h
 * \brief Header per valori Booleani
 *
 * \author Domenico Monaco, domenico.monaco@kiuz.it
 * \date 2011
 * \section license Licenza
 * GPLv2 http://www.softwarelibero.it/gnudoc/gpl.it.txt
 * Per maggiori informazioni visitare il link o visualizzare il file LICENSE
 */

#ifndef BOOLE_H_
#define BOOLE_H_ /**< Impedisce inclusioni multiple */

/** \typedef Definizione del tipo boolean
 * \brief Tipo di dato non primitivo boolean
 *
 * vale 1 se TRUE, 0 se FALSE
 */
typedef enum {
	FALSE = 0, /**< valore boolean FALSE = 0*/
	TRUE = 1 /**< valore boolean TRUE = 1*/
} boolean;

#endif /* END BOOLE_H_ */
