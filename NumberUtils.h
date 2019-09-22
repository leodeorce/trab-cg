/*
 * NumberUtils.h
 *
 * Utility functions for number manipulation.
 *
 *  Created on: Jul 10, 2014
 *      Author: Vítor E. Silva Souza (vitorsouza@gmail.com)
 */

/*
 * Modificado por: Leonardo Oliveira
 */

#ifndef NUMBERUTILS_H_
#define NUMBERUTILS_H_

#include <locale>
#include <string>

using namespace std;

/* Converts decimal numbers from textual format to float, following a locale configuration. */
float parseFloat(const string&, const locale&);

#endif
