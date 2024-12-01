#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QImage>
#include <string>

class MainModel
{
public:
    MainModel();
    bool load(const std::string & filename);
    void reset();
    bool seek(int num);
    int frameNum() const;
    QPair<QImage, QRectF> getFrame() const;
    void initTracking(const QRectF & rect);
private:
    struct MainModelImpl;
    MainModelImpl * impl;
};

#endif // MAINMODEL_H
