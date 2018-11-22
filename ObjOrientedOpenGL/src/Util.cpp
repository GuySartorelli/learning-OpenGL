#include <fstream>

#include "Util.h"

bool Util::fileExists(std::string& path)
{
    std::ifstream file(path.c_str());
    return bool(file);
}


template<std::size_t N>
static int arrayLength(GLfloat (&A)[N]){
	return N; // or sizeof(A)/sizeof(A[0])
}

template<std::size_t N>
static int arrayLength(GLuint (&A)[N]){
    return N;
}
