#include <iostream>

#include "map.h"

int main()
{
    gamex::Map m1(5, 5);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            m1.get(i, j).setType(5);
        }
    }

    m1.writeToFile("map1.mp");

    gamex::Map m2("map1.mp");

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            std::cout << m2.get(i, j).getType() << " ";
        std::cout << std::endl;
    }


    return 0;
}
