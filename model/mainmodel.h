#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QImage>
#include <string>
#include <opencv2/tracking.hpp>

class MainModel
{
public:
    MainModel();
    bool load(const std::string & filename);
    void reset();
    bool seek(int num);
    int frameNum() const;
    QPair<QImage, QRectF> getFrame() const;
    void initTrackingCSRT(const QRectF & rect, const cv::tracking::TrackerCSRT::Params & params);
private:
    struct MainModelImpl;
    MainModelImpl * impl;
};

#endif // MAINMODEL_H
