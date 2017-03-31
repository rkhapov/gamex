#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <string>

#include "window.h"
#include "image.h"

namespace sgl
{
    class AnimationErrorException: public std::runtime_error
    {
    public:
        AnimationErrorException(const std::string &msg):
            runtime_error(msg)
        {
        }
    };


    class Animation
    {
    public:
        Animation(const std::string &path);

        void goNextFrame();
        void goFirstFrame();
        void goLastFrame();
        void reverseOrder();
        void directOrder();

        bool isOrderReversed() const;

        int getCurrentFrameNo() const;
        int size() const;

        void goFrame(int frameNo);

        const Image& getCurrentFrame() const;
        Image& getCurrentFrame();

        Image &operator [](int index);
        const Image& operator [] (int index) const;

    private:
        std::vector<Image> _frames;
        int _currentFrameNo;
        bool _reverseOrder;

        void _readDir(const std::string &path);
    };
}

#endif // ANIMATION_H
