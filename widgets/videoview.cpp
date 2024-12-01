#include "videoview.h"

VideoView::VideoView(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), pixitem(nullptr), rectitem(nullptr)
{
    this->setScene(scene);
}

VideoView::~VideoView()
{
}

void VideoView::updateFrame(QPixmap img)
{
    if (!pixitem)
    {
        if (img.isNull())
        {
            // nothing
        }
        else
        {
            qDebug() << "view: init image";
            pixitem = scene->addPixmap(img);
        }
    }
    else
    {
        if (img.isNull())
        {
            qDebug() << "view: reset";
            this->setScene(nullptr);
            scene->clear();
            delete scene;
            scene = new QGraphicsScene(this);
            pixitem = nullptr;
            this->setScene(scene);
        }
        else
        {
            qDebug() << "view: update image";
            pixitem->setPixmap(img);
            pixitem->update();
            scene->update();
        }
    }
}

QRectF VideoView::getSelection() const
{
    if (rectitem)
    {
        return rectitem->rect();
    }
    else
    {
        return QRectF();
    }
}

void VideoView::updateSelection(const QRectF &sel)
{
    if (!rectitem)
    {
        rectitem = scene->addRect(sel);
    }
    else
    {
        rectitem->setRect(sel);
    }
}

void VideoView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton && pixitem)
    {
        if (rectitem)
        {
            scene->removeItem(rectitem);
        }
        initpt = mapToScene(event->pos());
        QRectF rect = QRectF(initpt, QSizeF(1, 1));
        rectitem = scene->addRect(rect, QPen(Qt::PenStyle::SolidLine), QBrush(Qt::BrushStyle::Dense7Pattern));
    }
    QGraphicsView::mousePressEvent(event);
}

void VideoView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        if (rectitem)
        {
            rectitem->setRect(QRect::span(initpt.toPoint(), mapToScene(event->pos()).toPoint()));
            emit selectionChanged(rectitem->rect());
        }
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void VideoView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::RightButton))
    {
        if (rectitem)
        {
            rectitem->setRect(QRect::span(initpt.toPoint(), mapToScene(event->pos()).toPoint()));
        }
    }
    QGraphicsView::mouseMoveEvent(event);
}

void VideoView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
    {
        const int degrees = event->angleDelta().y();
        qDebug() << "view: wheel event : " << degrees << " | " << event->isEndEvent();
        zoom += degrees > 0 ? 10 : -10;
        zoom = std::clamp(zoom, 10, 300);
        setTransform(QTransform::fromScale(zoom / 100., zoom / 100.));
    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}

