
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <RCF/RCF.hpp>

#include "Service.h"

class VideoServiceImp
{
public:
    // Reverses the order of strings in the vector.
    const char*  reverse(std::vector<std::string> &v)
    {
        std::cout << "Reversing a vector of strings...\n";
        std::vector<std::string> w;
        std::copy(v.rbegin(), v.rend(), std::back_inserter(w));
        v.swap(w);

        return "asdbcdtest";
    }
};


