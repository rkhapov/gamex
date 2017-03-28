#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

/*
 * Event Manager - class to control general programs events as
 * key down, key up, timer out, mouse move, window closed
 * Class is an wrapper of ALLEGRO_EVENT_QUEUE
*/

#include <vector>
#include <utility>
#include <algorithm>

#include <allegro5/allegro5.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>

#include "timer.h"
#include "my_string.h"
#include "window.h"


namespace sgl
{
    //Empty handler special for you
    class EmptyEventHandler
    {
    public:
        void operator () (...)
        {
            ; //nothing to be done
        }
    };

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    class EventManager
    {
    public:
        EventManager();
        ~EventManager();

        /*
         * When next time tick, execute timer.callHandler()
        */

        void addTimer(Timer<timer_handler_T> &timer);

        /*
         * keyboard handler must have this cinematics:
         * f(std::string keystr) {}
         * where keystr - name of pressed key ("enter", "space" and e.t.c)
        */

        void setKeyDownHandler(keyboard_down_handler_T& handler);

        const keyboard_down_handler_T& getKeyDownHandler() const;

        void setKeyUpHandler(keyboard_up_handler_T& handler);
        const keyboard_up_handler_T& getKeyUpHandler() const;

        /*
         * mouse click handler must have this cinematics:
         * f(int x, int y, int b) {}
         * where x, y - Cordss of mouse cursor
         * b - number of pressed mouse key (numbered from 1)
         *
         * mouse move handler:
         * f(int x, int y) {}
        */


        void setMouseMoveHandler(mouse_move_handler_T& handler);
        const mouse_move_handler_T& getMouseMoveHandler() const;

        void setMouseClickDownHandler(mouse_click_down_handler_T& handler);
        const mouse_click_down_handler_T& getMouseClickDownHandler() const;

        void setMouseClickUpHandler(mouse_click_up_handler_T& handler);
        const mouse_click_up_handler_T& getMouseClickUpHandler() const;


        /*
         * Window close handler: function which called when user press
         * exit button of window
        */

        void setWindowCloseHandler(Window &window, window_close_handler_T& handler);
        const window_close_handler_T& getWindowCloseHandler() const;

        void waitForNextEvent();

        bool waitForNextEventTimed(double timeLimit);

        //You can use this class with allegro functions
        operator ALLEGRO_EVENT_QUEUE*();
        operator const ALLEGRO_EVENT_QUEUE*() const;

    private:
        ALLEGRO_EVENT_QUEUE *_eventQueue;

        keyboard_down_handler_T *_keyDownHandler;
        keyboard_up_handler_T *_keyUpHandler;

        mouse_move_handler_T *_mouseMoveHandler;
        mouse_click_down_handler_T *_mouseClickDownHandler;
        mouse_click_up_handler_T *_mouseClickUpHandler;

        std::vector<Timer<timer_handler_T>*> _timers;

        window_close_handler_T *_windowCloseHandler;
        Window *_window;

        bool _callEventHandler(const ALLEGRO_EVENT &event);

        EventManager(const EventManager &eventManager);
        EventManager &operator =(const EventManager &EventManager);
    };

    class EventManagerErrorException: public std::runtime_error
    {
    public:
        EventManagerErrorException(const std::string &msg):
            runtime_error(msg)
        {
        }
    };






    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    EventManager()
    {
        _eventQueue = al_create_event_queue();

        _window                = nullptr;
        _windowCloseHandler    = nullptr;
        _keyDownHandler        = nullptr;
        _keyUpHandler          = nullptr;
        _mouseClickDownHandler = nullptr;
        _mouseClickUpHandler   = nullptr;
        _mouseMoveHandler      = nullptr;

        if (!al_is_keyboard_installed())
        {
            if (!al_install_keyboard())
                throw EventManagerErrorException("al_install_keyboard() returned false");
        }

        if (!al_is_mouse_installed())
        {
            if (!al_install_mouse())
                throw EventManagerErrorException("al_install_mouse() returned false");
        }

        if (_eventQueue == nullptr)
            throw EventManagerErrorException("al_create_event_queue returned NULL");

        al_register_event_source(_eventQueue, al_get_keyboard_event_source());
        al_register_event_source(_eventQueue, al_get_mouse_event_source());
    }

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    ~EventManager()
    {
        al_destroy_event_queue(_eventQueue);
    }

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    void EventManager<timer_handler_T, keyboard_down_handler_T,
                      keyboard_up_handler_T, mouse_move_handler_T,
                      mouse_click_down_handler_T, mouse_click_up_handler_T,
                      window_close_handler_T>::
    addTimer(Timer<timer_handler_T> &timer)
    {
        auto timerPos = std::find(_timers.begin(), _timers.end(), &timer);

        if (timerPos == _timers.end())
        {
            _timers.insert(timerPos, &timer);
            al_register_event_source(_eventQueue, al_get_timer_event_source(timer));
        }
    }


    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    void EventManager<timer_handler_T, keyboard_down_handler_T,
                      keyboard_up_handler_T, mouse_move_handler_T,
                      mouse_click_down_handler_T, mouse_click_up_handler_T,
                      window_close_handler_T>::
    setKeyDownHandler(keyboard_down_handler_T& handler)
    {
        _keyDownHandler = &handler;
    }

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    void
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    setKeyUpHandler(keyboard_up_handler_T& handler)
    {
        _keyUpHandler = &handler;
    }

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    void
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    setMouseClickDownHandler(mouse_click_down_handler_T& handler)
    {
        _mouseClickDownHandler = &handler;
    }

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    void
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    setMouseClickUpHandler(mouse_click_up_handler_T& handler)
    {
        _mouseClickUpHandler = &handler;
    }

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    void
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    setMouseMoveHandler(mouse_move_handler_T& handler)
    {
        _mouseMoveHandler = &handler;
    }


    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    void
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    setWindowCloseHandler(Window &window, window_close_handler_T &handler)
    {
        if (_windowCloseHandler != nullptr)
        {
            al_unregister_event_source(_eventQueue, al_get_display_event_source(*_window));
        }

        _window = &window;
        al_register_event_source(_eventQueue, al_get_display_event_source(*_window));
        _windowCloseHandler = &handler;
    }


    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    const keyboard_down_handler_T&
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    getKeyDownHandler() const
    {
        if (_keyDownHandler == nullptr)
        {
            throw EventManagerErrorException("getKeyDownHandler with empty key down handler");
        }

        return *_keyDownHandler;
    }

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    const keyboard_up_handler_T&
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    getKeyUpHandler() const
    {
        if (_keyUpHandler == nullptr)
        {
            throw EventManagerErrorException("getKeyUpHandler with empty key up handler");
        }

        return *_keyUpHandler;
    }

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    const mouse_click_down_handler_T&
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    getMouseClickDownHandler() const
    {
        if (_mouseClickDownHandler == nullptr)
        {
            throw EventManagerErrorException("getMouseClickDownHandler with empty mouse click down handler");
        }

        return *_mouseClickDownHandler;
    }


    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    const mouse_click_up_handler_T&
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    getMouseClickUpHandler() const
    {
        if (_mouseClickUpHandler == nullptr)
        {
            throw EventManagerErrorException("getMouseClickUpHandler with empty mouse click up handler");
        }

        return *_mouseClickUpHandler;
    }


    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    const mouse_move_handler_T&
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    getMouseMoveHandler() const
    {
        if (_mouseMoveHandler == nullptr)
        {
            throw EventManagerErrorException("getMouseMoveHandler with empty mouse move handler");
        }

        return *_mouseClickDownHandler;
    }


    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    const window_close_handler_T&
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    getWindowCloseHandler() const
    {
        if (_windowCloseHandler == nullptr)
        {
            throw EventManagerErrorException("getWindowCloseHandler with empty window close handler handler");
        }

        return *_windowCloseHandler;
    }



    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    void
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    waitForNextEvent()
    {
        while (true)
        {
            ALLEGRO_EVENT event;

            al_wait_for_event(_eventQueue, &event);

            if (_callEventHandler(event))
                break;
        }
    }

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    bool
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    waitForNextEventTimed(double timeLimit)
    {
        ALLEGRO_EVENT event;

        bool wasEvent = al_wait_for_event_timed(_eventQueue, &event, timeLimit);

        if (wasEvent)
            _callEventHandler(event);

        return wasEvent;
    }

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    bool
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    _callEventHandler(const ALLEGRO_EVENT &event)
    {

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            std::size_t timerPos = 0;

            for (; timerPos < _timers.size(); timerPos++)
            {
                if (*_timers[timerPos] == event.timer.source)
                {
                    break;
                }
            }

            if (timerPos == _timers.size())
                throw EventManagerErrorException("Strange error: no registered Timer for timer event");

            _timers[timerPos]->callHandler();
            return true;
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            if (_windowCloseHandler != nullptr)
            {
                (*_windowCloseHandler)();
                return true;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (_keyDownHandler != nullptr)
            {
                (*_keyDownHandler)(gamex::convertToLowerCase(
                                    al_keycode_to_name(event.keyboard.keycode)));
                return true;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (_keyUpHandler != nullptr)
            {
                (*_keyUpHandler)(gamex::convertToLowerCase(
                                    al_keycode_to_name(event.keyboard.keycode)));
                return true;
            }
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (_mouseClickDownHandler != nullptr)
            {
                (*_mouseClickDownHandler)(event.mouse.x, event.mouse.y, event.mouse.button);
                return true;
            }
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if (_mouseClickUpHandler != nullptr)
            {
                (*_mouseClickUpHandler)(event.mouse.x, event.mouse.y, event.mouse.button);
                return true;
            }
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            if (_mouseMoveHandler != nullptr)
            {
                (*_mouseMoveHandler)(event.mouse.x, event.mouse.y);
                return true;
            }
        }
        return false;
    }


    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    operator ALLEGRO_EVENT_QUEUE* ()
    {
        return _eventQueue;
    }

    template <typename timer_handler_T, typename keyboard_down_handler_T,
              typename keyboard_up_handler_T, typename mouse_move_handler_T,
              typename mouse_click_down_handler_T, typename mouse_click_up_handler_T,
              typename window_close_handler_T>
    EventManager<timer_handler_T, keyboard_down_handler_T,
                 keyboard_up_handler_T, mouse_move_handler_T,
                 mouse_click_down_handler_T, mouse_click_up_handler_T,
                 window_close_handler_T>::
    operator const ALLEGRO_EVENT_QUEUE* () const
    {
        return _eventQueue;
    }

} //namespace sgl

#endif // EVENT_MANAGER_H

