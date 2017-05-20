#include <iostream>
#include <fstream>

#include "map.h"

gamex::Map::Map(int n, int m):
    _map(n, m)
{
}

gamex::Map::Map(const std::string &path):
    _map(1, 1)
{
    loadFromFile(path);
}


int gamex::Map::getHeight() const
{
    return _map.getSize().first;
}

int gamex::Map::getWidth() const
{
    return _map.getSize().second;
}

void gamex::Map::resize(int n, int m)
{
    _map.resize(n, m);
}

int gamex::Map::get(int i, int j) const
{
    return _map.get(i, j);
}

void gamex::Map::set(int i, int j, int type)
{
    if (type != EMPTY &&
        type != GROUND &&
        type != SKY &&
        type != WATER)
    {
        throw MapErrorException(constructMessage("Unknown cell type: %d", type));
    }

    _map.set(i, j, type);
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
            int type = _map.get(i, j);
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


    Matrix<int> map(n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int type;
            file.read(reinterpret_cast<char*>(&type), sizeof(int));

            map.set(i, j, type);

            if (!file.good())
            {
                throw MapErrorException("Reading stream error with \"" + path + "\"");
            }
        }
    }

    file.close();
    _map = map;
}
