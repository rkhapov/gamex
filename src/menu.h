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

        void setTitle(const std::string &title);
        const std::string& getTitle() const;

        void setIndent(int indent);
        int getIndent() const;

        void saveWindowBackground();
        void clearWindowWithColor(const Color &color);

        //Returns item, which was selected by user
        //If user pressed unexpected key (for example 'a' key), method will return
        //Unexpected_key_preffix + keyname (default is "__")
        //In case user closed window, method will return ""
        enum { LEFT, RIGHT, CENTER, CENTRE = CENTER };
        std::string run(const TextPrinter &textPrinter, int flag = LEFT) const;

    private:
        std::vector<std::string> _items;
        std::string _unexpectedKeyPreffix;
        std::string _title;
        Color _clearingColor;
        bool _windowBackgroundSaving;
        int _indent;

        void _printItems(int beginNo, int endNo, int currentNo,
                         const TextPrinter &textPrinter,
                         int starty, int flag) const;
        void _printTitle(const TextPrinter &textPrinter, int flag) const;
    };
}

#endif // MENU_H
