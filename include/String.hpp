//!
//! @file				String.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-08-12
//! @last-modified		2014-08-22
//! @brief				Contains the declarations for the String class.
//! @details
//!						See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef STRING_CPP_STRING_H
#define STRING_CPP_STRING_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace mNinja
{
	class String;
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// System headers
#include <cstdint>		// int8_t, int32_t e.t.c

// User libraries
// none

// User headers
// none

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace mNinja
{
	//! @brief		Enumerates the possible ends to trim a string from when calling String::Trim().
	enum class EndsToTrim
	{
		LEFT,		//!< Trim from the left-side of the string only.
		RIGHT,		//!< Trim from the right-side of the string only.
		BOTH		//!< Trim from both sides of the string.
	};

	//! @brief		The default characters to trim from a string if none are provided as
	//!				an argument to String::Trim().
	static const char * defCharsToMatch = " \r\n\t";

	//! @brief		String class designed for embedded applications.
	//! @details	Exceptions are not used.
	class String
	{	
		
		public:

			//======================================================================================//
			//==================================== PUBLIC METHODS ==================================//
			//======================================================================================//
					
			//! @brief		Constructor.
			//! @details	Allocates memory for the string and copies the provided cString into this memory.
			//! @param		cString		C-style string to populate string with.
			//! @note
			String(const char * cString);

			//! @brief		Simplified constructor.
			//! @details	Creates string object that only contains one character, the null char.
			String();

			//! @brief		Copy constructor.
			//! @details	Delegates to normal constructor.
			String(const String &obj);

			//! @brief		Destructor.
			//! @details	Deletes memory that was allocated for the string.
			~String();

			//! @brief		Call to find how many characters are in the string (excluding the null character).
			//! @returns	The number of characters in the string, excluding the terminating-null character.
			uint32_t GetLength();
						
			//! @brief		Searches for a particular character in the string.
			//! @returns	If character is found in string, returns the 0-based index of the first
			//!				occurrence. If character is not found in string, returns -1.
			int32_t Find(char charToFind, uint32_t startPos = 0);

			//! @brief		Looks for first occurrence of cStringToFind inside this string, starting at startPos.
			//! @param		cStringToFind	The string to search for.
			//!	@param		startPos		The 0-based index to start searching from.
			//! @returns	If cStringToFind is found in string, returns the 0-based index of the first
			//!				occurrence. If stringToFind is not found in string, returns -1.
			int32_t Find(const char * cStringToFind, uint32_t startPos = 0);

			//! @brief		Looks for stringToFind inside this string.
			//! @details	Calls int32_t Find(const char * cStringToFind, uint32_t startPos = 0),
			//!				passing in the C style string of stringToFind.
			//! @param		stringToFind	The string to search for.
			//!	@param		startPos		The 0-based index to start searching from.
			//! @returns	If stringToFind is found in string, returns the 0-based index of the first
			//!				occurrence. If stringToFind is not found in string, returns -1.
			int32_t Find(const String & stringToFind, uint32_t startPos = 0);

			//! @brief		Append a C-style string onto the end of the current string.
			//! @param		cStringToAppend		A null-terminated C-style string to append onto the
			//!									end of the current string.
			void Append(const char * cStringToAppend);

			//! @brief		Erases a specific number of characters from the string.
			//! @details	Similar to std::string::Erase(), except that it does not throw any exceptions.
			//! @param		startPos	The 0-indexed position to start erasing characters from. If startPos
			//!							> string length then no characters will be erased.
			//! @param		numOfChars	The number of characters to erase. If numOfChars > string length
			//!							then all characters will be erased.
			void Erase(uint32_t startPos, int32_t numOfChars = -1);

			//! @brief		Trims white-space (or specified chars) from either or both ends of the string.
			//! @details	Default characters are all those which are considered to be
			//!				 white space: ' ', '\r', '\n', '\t'.
			//!				Calls Erase().
			//! @param		charsToMatch	A string of all the characters that should be trimmed
			//!								from the string. Default is all characters considered to
			//!								be white space.
			void Trim(String charsToMatch = defCharsToMatch, EndsToTrim endsToTrim = EndsToTrim::BOTH);

			//! @brief		Simplified overload of Trim().
			//! @details	Calls the base Trim() with charsToMatch = defaultCharsToMatch.
			//! @sa			Trim().
			void Trim(EndsToTrim endsToTrim);

			//======================================================================================//
			//============================ PUBLIC OPERATOR OVERLOAD DECLARATIONS ===================//
			//======================================================================================//

			//! @brief		Assignment operator overload. Allows you to make one string equal another.
			//! @details	Copies the contents of the RHS string into the LHS, so that they both have
			//!				the same contents (but do not point to the same memory!).
			String & operator= (const String & other);

			//! @brief		Subscript operator overload. Allows individual char access.
			//! @returns	Reference to char located at position 'index'. Performs bounds checking, only
			//!				allows chars and terminating null to be indexed, any other number is out
			//!				of bounds. If index is out-of-bounds, the first character in the array will be
			//!				returned. We shouldn't be allowed to write to the terminating null, but
			//!				we have to provide access for read operations.
			char & operator[] (const uint32_t index);

			//! @brief		Compound assignment operator overload.
			//! @details	Appends the RHS C-style string onto the LHS string object.
			//!				Used by the "+" operator overload.
			String & operator+=(const char * rhs);

			//! @brief		Compound assignment operator overload.
			//! @details	Appends the RHS string onto the LHS string.
			//!				Used by the "+" operator overload.
			String & operator+=(const String &rhs);

			//! @brief		Equality operator overload. Allows you to compare one string object and
			//!				one C-style string for equality.
			//! @details	Used by the other equality operator overload and the inequality operator overload.
			friend bool operator==(String & lhs, const char * rhs);

			//! @brief		Equality operator overload. Allows you to compare two string objects for equality.
			//! @details	Calls the overload with one string object and one C-style string.
			//!				Also used by the inequality operator overload.
			friend bool operator==(String & lhs, String & rhs);

			//! @brief		Inequality operator overload. Allows you to compare one string and
			//!				one C-style string for inequality.
			//! @details	Internally calls the equality operator overload.
			friend bool operator!=(String & lhs, const char * rhs);

			//! @brief		Inequality operator overload. Allows you to compare two strings for inequality.
			//! @details	Internally calls the equality operator overload.
			friend bool operator!=(String & lhs, String & rhs);

			//! @brief		Allows you to concatenate two strings together.
			//! @details	Calls the Append() method.
			friend String operator+(String lhs, const char * rhs);

			//! @brief		Allows you to concatenate a string object and a C-style string together.
			//! @details	Calls the += operaotr which in turn calls the Append() method.
			//!				Pass LHS by value to allow to better optimisation.
			friend String operator+(String lhs, String & rhs);

			// TYPE CONVERSIONS

			operator const char *();

			//======================================================================================//
			//================================= PUBLIC VARIABLES ===================================//
			//======================================================================================//
				
			//! @brief		Pointer to internal memory where C-style string is stored. Guaranteed
			//!				to be null-terminated.
			//! @details	Access this to pass in string when a C-style function is called.
			char * cStr;
				
		private:
						
			//======================================================================================//
			//=================================== PRIVATE METHODS ==================================//
			//======================================================================================//
			
			// none
			
			//======================================================================================//
			//================================== PRIVATE VARIABLES =================================//
			//======================================================================================//

			//! @brief		Remembers the length of the string.
			uint32_t length;

		protected:

			//======================================================================================//
			//=================================== PROTECTED METHODS ================================//
			//======================================================================================//
			
			// none
			
			//======================================================================================//
			//================================== PROTECTED VARIABLES ===============================//
			//======================================================================================//

			// none
		
	}; // class String


} // namespace mNinja

#endif	// #ifndef STRING_CPP_STRING_H

// EOF
