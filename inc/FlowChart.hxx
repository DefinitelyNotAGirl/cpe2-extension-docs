//stdc++ includes
#include <string>
#include <map>
//compiler includes
#include <compiler/inc/function.h>
//COCK
#ifndef COCK
	#define COCK extern
#endif
//global variables
COCK std::string content;
class FunctionData {
public:
	std::string content;
	double xpos = 0;
	double ypos = 0;
};
COCK std::map<function*,FunctionData> Functions;
COCK FunctionData* CurrentFunction;
