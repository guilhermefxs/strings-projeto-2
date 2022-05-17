#include "util.hpp"
#include <cstring>

char* copyString( const char* string ){
    int stringSize = strlen(string);
    char* response = new char[stringSize+1];
	strcpy( response, string );
	return response;
}
