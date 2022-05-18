
#ifndef SUFIXARRAY_H
#define SUFIXARRAY_H
#include <string>
#include <vector>

void createSufix (std::string fileToCreateSufix);

void findPattern (std::string sufixFile, std::vector<char*> pattern, bool showOnlyCountOfPatterns);

#endif 
