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




void sgl::Menu::_printItems(int beginNo, int endNo, int currentItemNo,
                            const TextPrinter &textPrinter,
                            int starty, int flag) const
{
    for (int i = beginNo;
         i <= endNo && i < static_cast<int>(_items.size());
         i++)
    {
        std::string itemText = _items[i];
        if (i == currentItemNo)
        {
            if (flag != LEFT)
                itemText = ">" + itemText;
            else
                itemText += "<";
        }

        int ycord = starty + (i - beginNo) * (_indent + textPrinter.getFont().getLineHeight());
        int xcord;

        int printerFlag = 0;

        if (flag == LEFT)
        {
            xcord = 0;
        }
        else if (flag == CENTER)
        {
            xcord = textPrinter.getTargetWindow().getWidth() / 2;
            printerFlag = Font::ALIGN_CENTER;
        }
        else
        {
            xcord = textPrinter.getTargetWindow().getWidth() - 1;
            printerFlag = Font::ALIGN_RIGHT;
        }

        textPrinter.drawText(itemText, xcord, ycord, printerFlag);
    }
}


void sgl::Menu::_printTitle(const TextPrinter &textPrinter, int flag) const
{
    int drawFlag = 0;
    int xcord = 0;
    if (flag == CENTER)
    {
        drawFlag = Font::ALIGN_CENTER;
        xcord = textPrinter.getTargetWindow().getWidth() / 2;
    }
    else if (flag == RIGHT)
    {
        drawFlag = Font::ALIGN_RIGHT;
        xcord = textPrinter.getTargetWindow().getWidth();
    }
    textPrinter.drawText(_title, xcord, 0, drawFlag);
}

sgl::Menu::Menu()
{
    _unexpectedKeyPreffix   = "__";
    _windowBackgroundSaving = false;
    _clearingColor          = Color("black");
    _indent                 = 10;
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

void sgl::Menu::setTitle(const std::string &title)
{
    _title = title;
}

void sgl::Menu::clearWindowWithColor(const Color &color)
{
    _windowBackgroundSaving = false;
    _clearingColor          = color;
}

void sgl::Menu::saveWindowBackground()
{
    _windowBackgroundSaving = true;
}

void sgl::Menu::setIndent(int indent)
{
    if (indent >= 0)
        _indent = indent;
}


int sgl::Menu::getIndent() const
{
    return _indent;
}

std::string sgl::Menu::run(const TextPrinter &textPrinter, int flag) const
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

    int currentItemNo       = 0;
    int nitemsOnWindow      = (textPrinter.getTargetWindow().getHeight()
                              - 2 * (textPrinter.getFont().getLineHeight() + _indent)) /
                              (textPrinter.getFont().getLineHeight() + _indent);
    int pageSize            = nitemsOnWindow;
    int currentPage         = 0;
    bool isUserInChoosing   = true;

    Image background = textPrinter.getTargetWindow().getBackBufferImage();

    while (isUserInChoosing)
    {
        if (_windowBackgroundSaving)
            background.draw(textPrinter.getTargetWindow(), 0, 0);
        else
            textPrinter.getTargetWindow().clear(_clearingColor);
        _printTitle(textPrinter, flag);
        _printItems(currentPage * pageSize, (currentPage + 1) * pageSize,
                    currentItemNo, textPrinter,
                    textPrinter.getFont().getLineHeight() + _indent, flag);
        textPrinter.getTargetWindow().flip();

        eventManager.waitForNextEvent();
        if (windowCloseWatchmen.hadKeyPressed())
        {
            return "";
        }
        else if (keyboardKeySaver.getPressedKey() == UP_KEY_NAME)
        {
            if (currentItemNo != 0)
            {
                currentItemNo--;
                if (currentItemNo < currentPage * pageSize)
                    currentPage--;
            }
            else
            {
                currentItemNo   = static_cast<int>(_items.size() - 1);
                currentPage     = currentItemNo / pageSize;
            }
        }
        else if (keyboardKeySaver.getPressedKey() == DOWN_KEY_NAME)
        {
            if (currentItemNo != static_cast<int>(_items.size() - 1))
            {
                currentItemNo++;
                if (currentItemNo > (currentPage + 1) * pageSize)
                    currentPage++;
            }
            else
            {
                currentItemNo = 0;
                currentPage   = 0;
            }
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

    return _items[currentItemNo];
}
