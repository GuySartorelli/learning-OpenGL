#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <glad/glad.h>


class Util
{
    public:
        static bool fileExists(std::string& path);

        template<std::size_t N>
        static int arrayLength(GLfloat (&A)[N]);

        template<std::size_t N>
		static int arrayLength(GLuint (&A)[N]);
    protected:
    private:
};

#endif // UTIL_H
