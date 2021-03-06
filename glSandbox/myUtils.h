#ifndef MYUTILS_H_
#define MYUTILS_H_

#include <string>

bool endsWith(const std::string &mainString, const std::string &suffix){
    if (mainString.size() < suffix.size()) return false;
    return mainString.compare(mainString.size() - suffix.size(), suffix.size(), suffix) == 0;
}




#endif /* MYUTILS_H_ */
