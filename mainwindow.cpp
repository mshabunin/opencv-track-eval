#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QWheelEvent>

MainWindow::MainWindow(MainModel & model_, QWidget *parent)
    : model(model_), playing(0), QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFrame()
{
    ui->view_frame->updateFrame(QPixmap::fromImage(model.getFrame()));
    ui->edit_frame_num->setText(QString::number(model.frameNum()));
}

void MainWindow::timerEvent(QTimerEvent * evt)
{
    QObject::timerEvent(evt);
    if (model.seek(1))
    {
        updateFrame();
    }
    else
    {
        on_button_play_clicked();
    }
}

void MainWindow::on_button_choose_file_clicked()
{
    QFileDialog dlg(this, "Select video file");
    dlg.setOption(QFileDialog::HideNameFilterDetails, false);
    dlg.setNameFilters({"Video files (*.mp4 *.mkv *.mjpg *.avi)", "Any file (*.*)"});
    dlg.setAcceptMode(QFileDialog::AcceptOpen);
    dlg.setFileMode(QFileDialog::ExistingFile);
    dlg.selectFile(ui->edit_filename->text());
    if (dlg.exec())
        ui->edit_filename->setText(dlg.selectedFiles().at(0));
}

void MainWindow::on_edit_filename_textChanged(const QString &arg1)
{
    ui->button_load->setEnabled(QFile::exists(arg1));
}

void MainWindow::on_button_load_clicked()
{
    model.reset();
    updateFrame();
    if (model.load(ui->edit_filename->text().toStdString()))
    {
        updateFrame();
        if (playing != 0)
        {
            on_button_play_clicked();
        }
    }
}

void MainWindow::on_button_reset_clicked()
{
    model.reset();
    updateFrame();
    if (playing != 0)
    {
        on_button_play_clicked();
    }
}

void MainWindow::on_button_plus_one_clicked()
{
    model.seek(1);
    updateFrame();
}

void MainWindow::on_button_plus_five_clicked()
{
    model.seek(5);
    updateFrame();
}

void MainWindow::on_button_play_clicked()
{
    qDebug() << "Play button : " << ui->button_play->text();
    if (playing == 0)
    {
        playing = startTimer(10);
    }
    else
    {
        killTimer(playing);
        playing = 0;
    }
    ui->button_play->setText((playing != 0) ? "Pause" : "Play");
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
}

