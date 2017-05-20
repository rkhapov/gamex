#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <stdexcept>

#include "sgl.h"
#include "matrix.h"

namespace gamex
{
    class MapErrorException: public std::runtime_error
    {
    public:
        MapErrorException(const std::string &msg):
            runtime_error(msg)
        {}
    };

    class Map
    {
    public:
        Map(int n, int m);
        Map(const std::string &path);

        enum
        {
            EMPTY,
            SKY,
            WATER,
            GROUND
        };


        void loadFromFile(const std::string &path);
        void writeToFile(const std::string &path);


        int getWidth() const;
        int getHeight() const;
        void resize(int n, int m);

        int get(int i, int j) const;
        void set(int i, int j, int type);

        int getPointType(int x, int y) const;

    private:
        Matrix<int> _map;
    };
}

#endif // MAP_H
