#ifndef VIDEOVIEW_H
#define VIDEOVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

namespace Ui {
class VideoView;
}

class VideoView : public QWidget
{
    Q_OBJECT

public:
    explicit VideoView(QWidget *parent = nullptr);
    ~VideoView();

    void updateFrame(QPixmap img);

private:
    QGraphicsScene * scene;
    QGraphicsPixmapItem * pixitem;

private:
    Ui::VideoView *ui;
};

#endif // VIDEOVIEW_H
