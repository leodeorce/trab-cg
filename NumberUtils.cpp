/*
 * NumberUtils.cpp
 *
 * Utility functions for number manipulation.
 *
 *  Created on: Jul 10, 2014
 *      Author: Vítor E. Silva Souza (vitorsouza@gmail.com)
 */

/*
 * Modificado por: Leonardo Oliveira
 */

#include <iomanip>
#include <sstream>

using namespace std;

/* Converts decimal numbers from textual format to float, following a locale configuration. */
float parseFloat(const string& str, const locale& loc) {
	
	float num;

	// Creates a stream with the given string and applies the specified locale to it.
	stringstream stream(str);
	stream.imbue(loc);

	// Uses the >> operator to read the the float value from the stream and returns.
	stream >> num;
	return num;
}
