#include <algorithm>

#include "animation.h"

#include "my_string.h"


#define LINUX_BUILD

#ifndef LINUX_BUILD
#define WINDOWS_BUILD
#endif


#ifdef LINUX_BUILD

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>


bool isFileImage(const std::string &filename)
{
    struct stat st;

    if (stat(filename.c_str(), &st) == -1)
        return false;

    if (S_ISDIR(st.st_mode))
        return false;

    if (filename.size() > 4)
    {
        std::string ext = gamex::convertToLowerCase(filename.substr(filename.size() - 4, 4));

        if (ext == ".jpg" || ext == ".png")
        {
            return true;
        }
    }

    return false;
}

void sgl::Animation::_readDir(const std::string &path)
{
    _frames.clear();

    DIR *dir = opendir(path.c_str());

    if (errno == EACCES)
        throw AnimationErrorException("Error open \"" + path + "\": Permission denied");

    if (errno == ENOTDIR)
        throw AnimationErrorException("Error open \"" + path + "\": It isnt dir");

    if (errno == ENOENT)
        throw AnimationErrorException("Error open \"" + path + "\": Doesnt exist");

    if (errno == EMFILE ||
        errno == ENFILE ||
        errno == ENOMEM)
        throw AnimationErrorException("Error open \"" + path + "\": System error");


    struct dirent *entry = readdir(dir);

    std::vector<std::string> files;

    while (entry != nullptr)
    {
        if (isFileImage(entry->d_name))
        {
            files.push_back(entry->d_name);
        }

        entry = readdir(dir);
    }

    std::sort(files.begin(), files.end());

    for (int i = 0; i < static_cast<int>(files.size()); i++)
        _frames.push_back(Image(files[i]));

    closedir(dir);
}

#else

#error "Windows _readDir must be realized"

#endif


sgl::Animation::Animation(const std::string &path)
{
    _readDir(path);
    _currentFrameNo = 0;
    _reverseOrder   = false;
}

void sgl::Animation::reverseOrder()
{
    _reverseOrder = true;
}

void sgl::Animation::directOrder()
{
    _reverseOrder = false;
}

void sgl::Animation::goFirstFrame()
{
    _currentFrameNo = 0;
}

void sgl::Animation::goLastFrame()
{
    if (size() != 0)
        _currentFrameNo = size() - 1;
}


void sgl::Animation::goNextFrame()
{
    if (!_reverseOrder)
    {
        if (_currentFrameNo == size() - 1)
            _currentFrameNo = 0;
        else
            _currentFrameNo++;
    }
    else
    {
        if (_currentFrameNo == 0)
            _currentFrameNo = size() - 1;
        else
            _currentFrameNo--;
    }
}

int sgl::Animation::getCurrentFrameNo() const
{
    return _currentFrameNo;
}

int sgl::Animation::size() const
{
    return static_cast<int>(_frames.size());
}

sgl::Image& sgl::Animation::getCurrentFrame()
{
    return _frames[_currentFrameNo];
}

const sgl::Image& sgl::Animation::getCurrentFrame() const
{
    return _frames[_currentFrameNo];
}

bool sgl::Animation::isOrderReversed() const
{
    return _reverseOrder;
}

void sgl::Animation::goFrame(int frameNo)
{
    if (frameNo >= 0 && frameNo < size())
        _currentFrameNo = frameNo;
}

sgl::Image& sgl::Animation::operator [] (int index)
{
    if (index < 0 || index >= size())
    {
        std::string errorFormat = "Index %d out of range 0..%d";
        std::string errorMessage = gamex::constructMessage(errorFormat.c_str(), index, size() - 1);
        throw AnimationErrorException(errorMessage);
    }

    return _frames[index];
}

const sgl::Image& sgl::Animation::operator [] (int index) const
{
    if (index < 0 || index >= size())
    {
        std::string errorFormat = "Index %d out of range 0..%d";
        std::string errorMessage = gamex::constructMessage(errorFormat.c_str(), index, size() - 1);
        throw AnimationErrorException(errorMessage);
    }

    return _frames[index];
}
