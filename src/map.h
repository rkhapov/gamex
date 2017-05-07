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

        class Cell
        {
        public:
            enum
            {
                EMPTY,
                SKY,
                WATER,
                GROUND
            };

            Cell();
            Cell(int type);

            int getType() const;
            void setType(int type);

            static const std::string imageDirPath;

            const sgl::Image &getImage() const;

        private:
            int _type;
            sgl::Image _image;
        };


        void loadFromFile(const std::string &path);
        void writeToFile(const std::string &path);


        std::pair<int, int> getSize() const;
        void resize(int n, int m);

        Cell& get(int i, int j);
        const Cell& get(int i, int j) const;

    private:
        Matrix<Cell> _map;
    };
}

#endif // MAP_H
