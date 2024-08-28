#include <JSON>
#include <string>
#include <map>
#ifndef __global__
	#define __global__ extern
#endif
__global__ JSON Layout;
__global__ std::string Description;
__global__ std::string Return;
__global__ std::map<std::string,std::string> Parameters;
