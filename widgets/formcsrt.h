#ifndef FORMCSRT_H
#define FORMCSRT_H

#include <QWidget>
#include <opencv2/tracking.hpp>

namespace Ui {
class FormCSRT;
}

class FormCSRT : public QWidget
{
    Q_OBJECT

public:
    explicit FormCSRT(QWidget *parent = nullptr);
    ~FormCSRT();
    cv::tracking::TrackerCSRT::Params getParams() const;
    void reset();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FormCSRT *ui;
};

#endif // FORMCSRT_H
