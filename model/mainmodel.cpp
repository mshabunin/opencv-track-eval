#include "mainmodel.h"

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/videoio.hpp>

struct MainModel::MainModelImpl
{
    cv::VideoCapture cap;
    cv::Mat frame;
};

MainModel::MainModel()
{
    impl = new MainModelImpl();
}

bool MainModel::load(const std::string &filename)
{
    impl->cap.open(filename);
    CV_LOG_WARNING(NULL, "Open stream: " << impl->cap.isOpened());
    if (!impl->cap.isOpened())
        return false;
    impl->cap.read(impl->frame);
    CV_LOG_WARNING(NULL, "Read frame: " << impl->frame.size());
    if (impl->frame.empty())
        return false;
    return true;
}

void MainModel::reset()
{
    impl->frame.release();
    impl->cap.release();
}

bool MainModel::seek(int shift)
{
    if (shift <= 0)
        return false;
    if (!impl->cap.isOpened())
        return false;
    if (!impl->cap.set(cv::CAP_PROP_POS_FRAMES, (int)impl->cap.get(cv::CAP_PROP_POS_FRAMES) + shift))
        return false;
    if (!impl->cap.retrieve(impl->frame))
        return false;
    if (impl->frame.empty())
        return false;
    return true;
}

int MainModel::frameNum() const
{
    return (int)impl->cap.get(cv::CAP_PROP_POS_FRAMES);
}

QImage MainModel::getFrame() const
{
    if (impl->frame.empty())
        return QImage();
    QImage img(impl->frame.data, impl->frame.size().width, impl->frame.size().height, impl->frame.step, QImage::Format_BGR888);
    return img.copy();
}