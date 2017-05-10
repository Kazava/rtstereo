#ifndef OPENPOSE__PRODUCER__IMAGE_DIRECTORY_READER_HPP
#define OPENPOSE__PRODUCER__IMAGE_DIRECTORY_READER_HPP

#include <string>
#include <vector>
#include "producer.hpp"

namespace op
{
    /**
     * ImageDirectoryReader is an abstract class to extract frames from a image directory. Its interface imitates the
     * cv::VideoCapture class, so it can be used quite similarly to the cv::VideoCapture class. Thus,
     * it is quite similar to VideoReader and WebcamReader.
     */
    class ImageDirectoryReader : public Producer
    {
    public:
        /**
         * Constructor of ImageDirectoryReader. It sets the image directory path from which the images will be loaded and
         * generates a std::vector<std::string> with the list of images on that directory.
         * @param imageDirectoryPath const std::string parameter with the folder path containing the images.
         */
        explicit ImageDirectoryReader(const std::string& imageDirectoryPath);

        std::string getFrameName();

        inline bool isOpened() const
        {
            return (mFrameNameCounter >= 0);
        }

        inline void release()
        {
            mFrameNameCounter = {-1ll};
        }

        double get(const int capProperty);

        void set(const int capProperty, const double value);

        inline double get(const ProducerProperty property)
        {
            return Producer::get(property);
        }

        inline void set(const ProducerProperty property, const double value)
        {
            Producer::set(property, value);
        }

    private:
        const std::string mImageDirectoryPath;
        const std::vector<std::string> mFilePaths;
        cv::Size mResolution;
        long long mFrameNameCounter;

        cv::Mat getRawFrame();

        DELETE_COPY(ImageDirectoryReader);
    };
}

#endif // OPENPOSE__PRODUCER__IMAGE_DIRECTORY_READER_HPP
