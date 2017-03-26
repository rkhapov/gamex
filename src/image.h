
#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <stdexcept>

class ALLEGRO_BITMAP;

namespace sgl
{
    class Window;

    /*
     * Image - class to control 2D image which can be load from file
     * Wrapper of ALLEGRO_BITMAP + al_load_bitmap
    */

    class Image
    {
    public:

        class ImageErrorException: public std::runtime_error
        {
        public:
            ImageErrorException(const std::string &msg):
                runtime_error(msg)
            {}
        };


        Image();
        Image(const std::string &path);
        Image(ALLEGRO_BITMAP *bitmap);
        Image(const Image &image);
        ~Image();

        static const int FLIP_HORIZONTAL;
        static const int FLIP_VERTICAL;

        /*
         * Draw Image to the window into (destx, desty) with flags
         * flags can be FLIP_HORIZONTAL or(and) FLIP_VERTICAL
        */
        void draw(Window &window, float destx, float desty, int flags = 0) const;

        /*
         * Draw part of image to the (destx, desty) whith start
         * of (srcx, srcy) and with width and height in pixel
        */
        void draw(Window &window, float destx, float desty, float srcx,
                  float srcy, float width, float height, int flags = 0) const;

        /*
         * Draw rotated image to the (destx, desty) which rotated
         * to the angle (in radians). (centerx, centery) - center of rotating
        */

        void drawRotated(Window &window, float destx, float desty, float centerx,
                  float centery, float angle, int flags = 0) const;


        /*
         * Draw scaled to window
         * (scrx, scry) and (scrw, srch) specify part of source image
         * (dstt, dsty) and (dstw, dsth) specify output coordinates and size
        */

        void drawScaled(Window &window, float srcx, float scry, float scrw,
                        float srch, float destx, float desty, float destw,
                        float desth, int flags = 0) const;

        int getHeight() const;
        int getWidth() const;

        Image getSubImage(int startx, int starty, int width, int height) const;

        /*
         * You can use Image with allegro functions
        */
        operator ALLEGRO_BITMAP*();
        operator const ALLEGRO_BITMAP*() const;

        Image &operator =(const Image &image);

    private:
        ALLEGRO_BITMAP *_bitmap;

        void _copyFrom(const Image &image);
    };
}

#endif // IMAGE_H

