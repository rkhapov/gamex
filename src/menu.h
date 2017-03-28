#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

#include "text_printer.h"

namespace sgl
{
    class Menu
    {
    public:
        Menu();

        void addItem(const std::string &item);
        void deleteItem(const std::string &item);

        void setUnexpectedKeyPreffix(const std::string &preffix);
        const std::string &getUnexpectedKeyPreffix() const;

        //Returns item, which was selected by user
        //If user pressed unexpected key (for example 'a' key), method will return
        //Unexpected_key_preffix + keyname (default is "__")
        //In case user closed window, method will return ""
        std::string run(const TextPrinter &textPrinter) const;

    private:
        std::vector<std::string> _items;
        std::string _unexpectedKeyPreffix;

        void _printItems(int beginNo, int endNo, int currentNo,
                         const TextPrinter &TextPrinter,
                         int starty, int indent) const;
    };
}

#endif // MENU_H
