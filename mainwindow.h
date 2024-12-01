#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "model/mainmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MainModel & model_, QWidget *parent = nullptr);
    ~MainWindow();

private:
    void updateFrame();
    void timerEvent(QTimerEvent * evt) override;

private slots:
    void selectionChanged(const QRectF & rect);

    void on_button_choose_file_clicked();
    void on_edit_filename_textChanged(const QString &arg1);
    void on_button_load_clicked();
    void on_button_reset_clicked();
    void on_button_plus_one_clicked();
    void on_button_plus_five_clicked();
    void on_button_play_clicked();

private:
    Ui::MainWindow *ui;

private:
    int playing; // timer id
    MainModel & model;

};
#endif // MAINWINDOW_H
