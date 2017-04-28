#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "sgl.h"

namespace gamex
{
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

        Cell& get(int i, int j);
        const Cell& get(int i, int j) const;


    private:
        Cell **_map;
        int _n;
        int _m;
    };
}

#endif // MAP_H
