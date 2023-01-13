#include <iostream>
#include "incl/some_file.h"

int main() {
    std::cout << "Result" << simple_function() << std::endl;
    #line 8 "incl/some_file.h"
    std::cout << "Function on line " << __LINE__ << " in file " << __FILE__ << std::endl;
    return 0;
}
