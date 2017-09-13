/*
 * library.h
 *
 * Created: 11-Sept-17 12:37:59
 * Author : hydroflax
 */ 


#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "stdlib.h"

class tinyjsonpp {
public:
	//--------------------------------------------------------------------------------------------------------------------
	//         Variables
	//--------------------------------------------------------------------------------------------------------------------

	unsigned int location;     // The current location of the user. (Used by parse). (Enables user to insert K-V pairs 
	                           // into the current JSON string).
	char* json;                // The JSON string.
	unsigned int jsonSize;     // The size of the json string.

	char* key;                 // A pointer to the start of the key (ignoring quotation marks). This is used know where 
	                           // the user has read up to in the JSON string stored in memory. (next() uses this to the
	                           // next key-value pair).
	unsigned int keySize;      // The amount of characters the key has.
	char* keyParent;           // The parent of the key. (if it has one).

	char* value;               // A pointer to the start of the value (ignoring quotation marks).
	unsigned int valueSize;    // The amount of characters the value has.
	char valueType;            // The value type (int => 'i', string => 's', char => 'c', bool => 'b', array => 'a',
                                   // embedded JSON obj => 'e', null => 'n').

	//--------------------------------------------------------------------------------------------------------------------
	//         Methods
	//--------------------------------------------------------------------------------------------------------------------

	/**
	 * Constructor
	 *
	 * @param bool store                - Store in IRAM or in EEPROM (Depending on purpose). (1 = EEPROM, 0 = IRAM).
	 * @param unsigned int maxSize	    - Specify a maximum size that will be used by the JSON string (if known). If not 
	 *                                    chosen, the string will be of variable size (need to check to ensure string will
	 *                                    be stored in a row).
	 */
	tinyjsonpp(bool store, unsigned int maxSize);

	/**
	 * Full Constructor
	 *
	 * @param bool store                - Store in IRAM or in EEPROM (Depending on purpose). (1 = EEPROM, 0 = IRAM).
	 * @param bool ignoreQuotes         - Ignore quotation marks, saving space in memory. (To Be Implemented at a later 
	 *                                    date).
	 * @param unsigned int maxSize	    - Specify a maximum size that will be used by the JSON string (if known). If not 
	 *                                    chosen, the string will be of variable size (need to check to ensure string will
	 *                                    be stored in a row).
	 */
	tinyjsonpp(bool store, bool ignoreQuotes, unsigned int maxSize);
	
	/** 
	 * Construct New Object.
	 *
	 * @param size_t objsize            - The size of the tinyjsonpp object.
	 * @return void
	 */
	void* operator new(size_t objsize);

	/** 
	 * Delete Object.
	 *
	 * @param void* obj                 - The tinyjsonpp object to delete.
	 * @return void
	 */
	void operator delete(void* obj);

	/** 
	 * Empties the current JSON string.
	 *
	 * @return void
	 */
	void empty();

	/** 
	 * Resets the current JSON string to an empty JSON string.
	 *
	 * @return void
	 */
	void reset();

	/**
	 * Read from buffer and store JSON string in either IRAM or EEPROM.
	 * During the read, remove any whitespace, /r, /n characters to ensure the smallest possible stored JSON. (Potential 
	 * to remove the quotation marks as well). The character from the buffer will be added to the end of the JSON string.
	 *
	 * @param char* c                   - The character currently being passed by the buffer.
	 * @return void
	 */ 
	void parse(char c);

	/** 
	 * Gets the value from the JSON string provided a key.
	 * Only the first value in the complete JSON string with the matching key will be found and placed in the value 
	 * property. 
	 *
	 * @param char* key                 - The key to find the value of (without quotation marks).
	 * @param unsigned int keySize      - The length of the key to find. 
	 * @return void
	 */
	void getvalue(char* key, unsigned int keySize);

	/**
	 * Gets the value from the JSON string provided a key.
	 * Only the first value in the complete JSON string with the matching key will be found and placed in the value 
	 * property.
	 *
	 * @param char* key                 - The key to find the value of (without quotation marks).
	 * @param unsigned int keySize      - The length of the key to find. 
	 * @param char* parent              - The parent structure to find. This should be in form "<parent>/<parent>".
	 * @param unsigned int parentLength - The length of the parent string.
	 * @return void
	 */
	void getvalue(char* key, unsigned int keySize, char* parent, unsigned int parentLength);
	
	/**
	 * Inserts the key value pair into the JSON string in the root JSON object.
	 *
	 * @param char* key                 - The key to insert.
	 * @param unsigned int keySize      - The length of the key to insert.
	 * @param char* value               - The value to insert.
	 * @param unsigned int valueSize    - The length of the value to insert.	 
	 */
	void insert(char* key, unsigned int keySize, char* value, unsigned int valueSize);
	
	/**
	 * Inserts the key value pair into the JSON string in the JSON object provided a parent schema.
	 *
	 * @param char* key                 - The key to insert.
	 * @param unsigned int keySize      - The length of the key to insert.
	 * @param char* value               - The value to insert.
	 * @param unsigned int valueSize    - The length of the value to insert.
	 * @param char* parent              - The parent structure to insert in to. This should be in form "<parent>/<parent>".
	 * @param unsigned int parentLength - The length of the parent string.
	 */
	void insert(char* key, unsigned int keySize, char* value, unsigned int valueSize, 
		    char* parent, unsigned int parentLength);
	
	// User can also add key-value pairs to the JSON string after the current key-value pointer position (two variations,
	// one function accepts a char* and the other accepts a key char*, value char*). This allows for users to provide an
	// already formatted JSON key-value pair or just the key, value. (Unsure at this point as to how to handle array
	// values/embedded key-value pairs).

	// user will loop through the  (will return a 1 if there is still JSON to parse, else 0. 'tinyjson.next()' function 
	// until the end of the JSON string has been reached.

	// user can get current Key-Value Pair (depending on where next is) by looking at the 'tinyjsonpp.key' and 
	// 'tinyjsonpp.value' properties. They will also be able to look at the 'tinyjsonpp.valueType', which will indicate 
	// what type the characters represent. (int => 'i', string => 's', char => 'c', bool => 'b', array => 'a').

	// value will always return a char *. (A Pointer to the start of value in the stored JSON string).
	// There is also a function that will allow looping through the string one character at a time for use when 
	// transmitting UART
};

#endif /* LIBRARY_H_ */