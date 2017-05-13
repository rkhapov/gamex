#include <iostream>
#include <fstream>
#include <cerrno>

#include "cfgmanager.h"
#include "my_string.h"


gamex::CfgManager::CfgManager()
{
}

gamex::CfgManager::CfgManager(const std::string &path)
{
    load(path);
}

void gamex::CfgManager::save(const std::string &path) const
{
    std::ofstream file(path.c_str(), std::ios_base::out | std::ios_base::trunc);

    if (!file.is_open())
    {
        int errorType = CfgManagerErrorException::IO_ERROR;
        std::string msgFormat = "Cant open \"" + path + "\": %s";
        std::string msg = constructMessage(msgFormat.c_str(), std::strerror(errno));
        throw CfgManagerErrorException(errorType, msg);
    }

    file << _parameters.size() << "\n";

    for (auto it = _parameters.begin(); it != _parameters.end(); it++)
    {
        file << it->first << " " << (it->second).size() << "\n";

        for (auto it2 = (it->second).begin(); it2 != (it->second).end(); it2++)
            file << *it2 << "\n";
    }

    file.close();
}

void gamex::CfgManager::load(const std::string &path)
{
    std::ifstream file(path.c_str(), std::ios_base::in);

    if (!file.is_open())
    {
        int errorType = CfgManagerErrorException::IO_ERROR;
        std::string msgFormat = "Cant open \"" + path + "\": %s";
        std::string msg = constructMessage(msgFormat.c_str(), std::strerror(errno));
        throw CfgManagerErrorException(errorType, msg);
    }

    _parameters.clear();

    int n;
    file >> n;

    if (!file.good())
    {
        int errorType = CfgManagerErrorException::FORMAT_ERROR;
        std::string msgFormat = "Wrong format of cfg file \"" + path + "\"";
        std::string msg = constructMessage(msgFormat.c_str());
        throw CfgManagerErrorException(errorType, msg);
    }

    for (int i = 0; i < n; i++)
    {
        std::string key;
        int nValues;
        file >> key >> nValues;

        std::set<std::string> values;

        for (int j = 0; j < nValues; j++)
        {
            std::string value;
            file >> value;
            values.insert(value);
        }

        if (!file.good())
        {
            int errorType = CfgManagerErrorException::FORMAT_ERROR;
            std::string msgFormat = "Wrong format of cfg file \"" + path + "\"";
            std::string msg = constructMessage(msgFormat.c_str());
            throw CfgManagerErrorException(errorType, msg);
        }

        _parameters[key] = values;
    }

    file.close();
}


void gamex::CfgManager::addKey(const std::string &key)
{
    if (_parameters.find(key) == _parameters.end())
    {
        _parameters[key] = std::set<std::string>();
    }
}

void gamex::CfgManager::deleteKey(const std::string &key)
{
    _parameters.erase(key);
}

bool gamex::CfgManager::hasKey(const std::string &key) const
{
    return _parameters.find(key) != _parameters.end();
}

std::set<std::string> gamex::CfgManager::getKeys() const
{
    std::set<std::string> keys;

    for (auto it = _parameters.begin(); it != _parameters.end(); it++)
        keys.insert(it->first);

    return keys;
}


void gamex::CfgManager::addValue(const std::string &key, const std::string &value)
{
    _parameters[key].insert(value);
}

void gamex::CfgManager::deleteValue(const std::string &key, const std::string &value)
{
    if (_parameters.find(key) != _parameters.end())
    {
        _parameters[key].erase(value);
    }
}

bool gamex::CfgManager::hasValue(const std::string &key, const std::string &value) const
{
    if (_parameters.find(key) == _parameters.end())
        return false;

    return _parameters.at(key).find(value) != _parameters.at(key).end();
}

std::set<std::string> gamex::CfgManager::getValues(const std::string &key) const
{
    if (_parameters.find(key) == _parameters.end())
        return std::set<std::string>();

    std::set<std::string> values = _parameters.at(key);

    return values;
}
