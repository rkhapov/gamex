#include <iostream>

#include <algorithm>

#include "menu.h"
#include "event_manager.h"

const std::string UP_KEY_NAME    = "up";
const std::string DOWN_KEY_NAME  = "down";
const std::string ENTER_KEY_NAME = "return";


class KeyboardHandler
{
public:
    void operator () (std::string key)
    {
        _key = key;
    }

    const std::string& getPressedKey() const
    {
        return _key;
    }

private:
    std::string _key;
};

class WindowCloseHandler
{
public:
    WindowCloseHandler()
    {
        _hadKeyPressed = false;
    }

    void operator () ()
    {
        _hadKeyPressed = true;
    }

    bool hadKeyPressed() const
    {
        return _hadKeyPressed;
    }

    void reset()
    {
        _hadKeyPressed = false;
    }

private:
    bool _hadKeyPressed;
};




void sgl::Menu::_printItems(int beginNo, int endNo, int currentNo,
                            const TextPrinter &textPrinter,
                            int starty, int indent) const
{
    for (int i = beginNo; i <= endNo; i++)
    {
        auto ycord = starty + (i - beginNo) * (indent + textPrinter.getFont().getLineHeight());
        auto xcord = textPrinter.getTargetWindow().getWidth() / 2;

        if (i == currentNo)
            textPrinter.drawText("->" + _items[i], xcord, ycord, Font::ALIGN_CENTER);
        else
            textPrinter.drawText(_items[i], xcord, ycord, Font::ALIGN_CENTER);
    }
}


sgl::Menu::Menu()
{
    _unexpectedKeyPreffix = "__";
}



void sgl::Menu::addItem(const std::string &item)
{
    if (std::find(_items.begin(), _items.end(), item) == _items.end())
        _items.push_back(item);
}



void sgl::Menu::deleteItem(const std::string &item)
{
    auto it = std::find(_items.begin(), _items.end(), item);

    if (it != _items.end())
    {
        _items.erase(it);
    }
}



void sgl::Menu::setUnexpectedKeyPreffix(const std::string &preffix)
{
    _unexpectedKeyPreffix = preffix;
}



const std::string &sgl::Menu::getUnexpectedKeyPreffix() const
{
    return _unexpectedKeyPreffix;
}




std::string sgl::Menu::run(const TextPrinter &textPrinter) const
{
    EventManager<EmptyEventHandler, KeyboardHandler,
                 EmptyEventHandler, EmptyEventHandler,
                 EmptyEventHandler, EmptyEventHandler,
                 WindowCloseHandler> eventManager;
    KeyboardHandler    keyboardKeySaver;
    WindowCloseHandler windowCloseWatchmen;
    eventManager.setKeyDownHandler(keyboardKeySaver);
    eventManager.setWindowCloseHandler(textPrinter.getTargetWindow(),
                                       windowCloseWatchmen);
    windowCloseWatchmen.reset();

    int currentNo = 0;
    bool isUserInChoosing = true;

    while (isUserInChoosing)
    {
        textPrinter.getTargetWindow().clear(Color("black"));
        _printItems(0, static_cast<int>(_items.size() - 1),
                    currentNo, textPrinter, 0, 10);
        textPrinter.getTargetWindow().flip();

        eventManager.waitForNextEvent();
        if (windowCloseWatchmen.hadKeyPressed())
        {
            return "";
        }
        else if (keyboardKeySaver.getPressedKey() == UP_KEY_NAME)
        {
            if (currentNo != 0)
                currentNo--;
        }
        else if (keyboardKeySaver.getPressedKey() == DOWN_KEY_NAME)
        {
            if (currentNo != static_cast<int>(_items.size() - 1))
                currentNo++;
        }
        else if (keyboardKeySaver.getPressedKey() == ENTER_KEY_NAME)
        {
            isUserInChoosing = false;
        }
        else
        {
            return _unexpectedKeyPreffix + keyboardKeySaver.getPressedKey();
        }
    }

    return _items[currentNo];
}
