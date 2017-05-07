#include <iostream>
#include <fstream>

#include "map.h"

const std::string gamex::Map::Cell::imageDirPath = "./img/map/cells/";


gamex::Map::Cell::Cell():
    _image(imageDirPath + "empty.jpg")
{
    setType(EMPTY);
}

gamex::Map::Cell::Cell(int type):
    _image(imageDirPath + "empty.jpg")
{
    setType(type);
}

int gamex::Map::Cell::getType() const
{
    return _type;
}

void gamex::Map::Cell::setType(int type)
{
    switch (type)
    {
    case WATER:
        _image = sgl::Image(imageDirPath + "water.jpg");
        break;

    case SKY:
        _image = sgl::Image(imageDirPath + "sky.jpg");
        break;

     case GROUND:
        _image = sgl::Image(imageDirPath + "ground.jpg");
        break;

    case EMPTY:
    default:
        type = EMPTY;
        _image = sgl::Image(imageDirPath + "empty.jpg");
        break;
    }

    _type = type;
}

const sgl::Image& gamex::Map::Cell::getImage() const
{
    return _image;
}


gamex::Map::Map(int n, int m):
    _map(n, m)
{
}

gamex::Map::Map(const std::string &path):
    _map(1, 1)
{
    loadFromFile(path);
}


std::pair<int, int> gamex::Map::getSize() const
{
    return _map.getSize();
}

void gamex::Map::resize(int n, int m)
{
    _map.resize(n, m);
}

gamex::Map::Cell& gamex::Map::get(int i, int j)
{
    return _map.get(i, j);
}

const gamex::Map::Cell& gamex::Map::get(int i, int j) const
{
    return _map.get(i, j);
}


void gamex::Map::writeToFile(const std::string &path)
{
    std::ofstream file(path.c_str(),
                       std::ios_base::out |
                       std::ios_base::binary |
                       std::ios_base::trunc);

    if (!file.is_open())
    {
        throw MapErrorException("Cant open file \"" + path + "\" to write");
    }

    std::pair<int, int> size = _map.getSize();

    file.write(reinterpret_cast<char*>(&(size.first)), sizeof(int));
    file.write(reinterpret_cast<char*>(&(size.second)), sizeof(int));

    if (!file.good())
    {
        throw MapErrorException("Writing stream error for \"" + path + "\"");
    }

    for (int i = 0; i < size.first; i++)
    {
        for (int j = 0; j < size.second; j++)
        {
            int type = _map.get(i, j).getType();
            file.write(reinterpret_cast<char*>(&type), sizeof(int));

            if (!file.good())
            {
                throw MapErrorException("Writing stream error for \"" + path + "\"");
            }
        }
    }

    file.close();
}

void gamex::Map::loadFromFile(const std::string &path)
{
    std::ifstream file(path.c_str(),
                       std::ios_base::in |
                       std::ios_base::binary);

    if (!file.is_open())
    {
        throw MapErrorException("Cant open file \"" + path + "\" to load");
    }

    int n, m;
    file.read(reinterpret_cast<char*>(&n), sizeof(int));
    file.read(reinterpret_cast<char*>(&m), sizeof(int));

    if (!file.good())
    {
        throw MapErrorException("Reading stream error with \"" + path + "\"");
    }


    Matrix<Cell> map(n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int type;
            file.read(reinterpret_cast<char*>(&type), sizeof(int));

            map.get(i, j).setType(type);

            if (!file.good())
            {
                throw MapErrorException("Reading stream error with \"" + path + "\"");
            }
        }
    }

    file.close();
    _map = map;
}
