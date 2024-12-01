#include "videoview.h"
#include "ui_videoview.h"

VideoView::VideoView(QWidget *parent)
    : QWidget(parent), scene(new QGraphicsScene(this)), pixitem(nullptr)
    , ui(new Ui::VideoView)
{
    ui->setupUi(this);
    ui->view_frame->setScene(scene);
}

VideoView::~VideoView()
{
    delete ui;
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
            ui->view_frame->setScene(nullptr);
            scene->clear();
            delete scene;
            scene = new QGraphicsScene(this);
            pixitem = nullptr;
            ui->view_frame->setScene(scene);
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

