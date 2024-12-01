#ifndef VIDEOVIEW_H
#define VIDEOVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>

class VideoView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit VideoView(QWidget *parent = nullptr);
    ~VideoView();

    void updateFrame(QPixmap img);
    QRectF getSelection() const;
    void updateSelection(const QRectF & sel);

private:
    QGraphicsScene * scene;
    QGraphicsPixmapItem * pixitem;
    QGraphicsRectItem * rectitem;

    int zoom = 100;
    QPointF initpt;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

signals:
    void selectionChanged(const QRectF & sel);
};

#endif // VIDEOVIEW_H
