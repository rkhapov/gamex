#ifndef TIMER_H
#define TIMER_H

#include <stdexcept>
#include <cstdint>

#include <allegro5/allegro.h>

#include "my_string.h"

/*
 * Timer - wrapper of allegro timer
 * May use only with EventManager
*/

namespace sgl
{
    template <typename handler_T>
    class Timer
    {
    public:

        //speed - seconds per tick
        Timer(double speed = 1.00000000);
        Timer(const Timer<handler_T> &timer);
        virtual ~Timer();

        void start();
        void stop();

        bool isStarted() const;

        int64_t getCount() const;
        void setCount(int64_t val);

        double getSpeed() const;
        void setSpeed(double speed);

        /*
         * Handler is and function which called when next tick
         * function should have sinematic void f(Timer &timer) {...}
        */

        void setHandler(const handler_T &handler);
        const handler_T &getHandler() const;

        //Function for EventManager
        void callHandler();

        //You can use this class with allegro functions
        operator ALLEGRO_TIMER*();
        operator const ALLEGRO_TIMER *() const;

        Timer<handler_T> &operator = (const Timer<handler_T> &timer);

    private:
        ALLEGRO_TIMER *_timer;
        handler_T *_handler;

        void _copyFrom(const Timer &timer);
    };

    class TimerErrorException: public std::runtime_error
    {
    public:
        TimerErrorException(const std::string &msg):
            runtime_error(msg)
        {}
    };







    template <typename handler_T>
    void Timer<handler_T>::_copyFrom(const Timer &timer)
    {
        delete _handler;
        al_destroy_timer(_timer);

        _timer = al_create_timer(timer.getSpeed());
        _handler = nullptr;

        if (_timer == nullptr)
            throw TimerErrorException("al_create_timer() returned NULL");

        setCount(timer.getCount());
        setHandler(timer.getHandler());

        if (timer.isStarted())
            start();
    }

    template <typename handler_T>
    Timer<handler_T>::Timer(double speed)
    {
        if (speed <= 0)
        {
            std::string msg = gamex::constructMessage("Timer speed parameter must be positive but not [%f]", speed);

            throw TimerErrorException(msg);
        }

        _timer = al_create_timer(speed);
        _handler = nullptr;

        if (_timer == nullptr)
            throw TimerErrorException("al_create_timer() returned NULL");
    }

    template <typename handler_T>
    Timer<handler_T>::Timer(const Timer<handler_T> &timer)
    {
        _timer = nullptr;
        _handler = nullptr;
        _copyFrom(timer);
    }

    template <typename handler_T>
    Timer<handler_T>::~Timer()
    {
        al_destroy_timer(_timer);
        delete _handler;
    }

    template <typename handler_T>
    void Timer<handler_T>::start()
    {
        al_start_timer(_timer);
    }

    template <typename handler_T>
    void Timer<handler_T>::stop()
    {
        al_stop_timer(_timer);
    }

    template <typename handler_T>
    bool Timer<handler_T>::isStarted() const
    {
        return al_get_timer_started(_timer);
    }

    template <typename handler_T>
    int64_t Timer<handler_T>::getCount() const
    {
        return al_get_timer_count(_timer);
    }

    template <typename handler_T>
    void Timer<handler_T>::setCount(int64_t val)
    {
        al_set_timer_count(_timer, val);
    }

    template <typename handler_T>
    void Timer<handler_T>::setSpeed(double speed)
    {
        al_set_timer_speed(_timer, speed);
    }

    template <typename handler_T>
    double Timer<handler_T>::getSpeed() const
    {
        return al_get_timer_speed(_timer);
    }

    template <typename handler_T>
    void Timer<handler_T>::setHandler(const handler_T &handler)
    {
        delete _handler;
        _handler = new handler_T(handler);
    }

    template <typename handler_T>
    const handler_T& Timer<handler_T>::getHandler() const
    {
        if (_handler == nullptr)
            throw TimerErrorException("getHandler for timer with no handler");

        return *_handler;
    }

    template <typename handler_T>
    void Timer<handler_T>::callHandler()
    {
        if (_handler != nullptr)
        {
            (*_handler)(*this);
        }
    }

    template <typename handler_T>
    Timer<handler_T>::operator ALLEGRO_TIMER* ()
    {
        return _timer;
    }

    template <typename handler_T>
    Timer<handler_T>::operator const ALLEGRO_TIMER* () const
    {
        return _timer;
    }

    template <typename handler_T>
    Timer<handler_T>& Timer<handler_T>::operator = (const Timer &timer)
    {
        if (this == &timer)
            return *this;

        _copyFrom(timer);
        return *this;
    }
}

#endif // TIMER_H

