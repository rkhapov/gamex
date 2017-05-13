#include <iostream>


#include "cfgmanager.h"


int main()
{
    gamex::CfgManager m1;

    m1.addKey("noski");
    m1.addValue("noski", "n1");
    m1.addValue("noski", "n2");

    m1.addValue("leel", "l1");

    m1.save("conf.txt");

    gamex::CfgManager m2("conf.txt");

    std::cout << m2.hasKey("leel") << std::endl;
    std::cout << m2.hasKey("noski") << std::endl;
    std::cout << m2.hasValue("leel", "l1") << std::endl;
    std::cout << m2.hasValue("leel", "l2") << std::endl;

    return 0;
}
