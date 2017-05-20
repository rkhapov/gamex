#ifndef CFGMANAGER_H
#define CFGMANAGER_H

/*
 * Simple manager of configure file
 *
 * Lets Cfg file containes only information in format
 * 'key: values[]'
 * where
 * key - key :)
 * values - array of string values to key
 *
 * (yes, its just std::map<std::string, std::set<std::string> > wrapper)
*/

#include <map>
#include <set>
#include <string>
#include <stdexcept>

namespace gamex
{
    class CfgManager
    {
    public:
        CfgManager();
        CfgManager(const std::string &path);

        //read/write cfg file
        void load(const std::string &path);
        void save(const std::string &path) const;


        void addKey(const std::string &key);
        void deleteKey(const std::string &key);
        bool hasKey(const std::string &key) const;
        std::set<std::string> getKeys() const;

        void addValue(const std::string &key, const std::string &value);
        void deleteValue(const std::string &key, const std::string &value);
        bool hasValue(const std::string &key, const std::string &value) const;
        std::set<std::string> getValues(const std::string &key) const;

    private:
        std::map<std::string, std::set<std::string> > _parameters;
    };

    class CfgManagerErrorException: public std::runtime_error
    {
    public:
        enum { IO_ERROR, FORMAT_ERROR };

        CfgManagerErrorException(int type, const std::string &msg):
            runtime_error(msg),
            _type(type)
        {}

        int type() const { return _type; }

    private:
        int _type;
    };
}

#endif // CFGMANAGER_H
