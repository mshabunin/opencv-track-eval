#include "formcsrt.h"
#include "ui_formcsrt.h"

FormCSRT::FormCSRT(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormCSRT)
{
    ui->setupUi(this);
    reset();
}

FormCSRT::~FormCSRT()
{
    delete ui;
}

cv::TrackerCSRT::Params FormCSRT::getParams() const
{
    cv::tracking::TrackerCSRT::Params params;

    params.use_hog = ui->cb_use_hog->isChecked();
    params.use_color_names = ui->cb_use_color_names->isChecked();
    params.use_gray = ui->cb_use_gray->isChecked();
    params.use_rgb = ui->cb_use_rgb->isChecked();
    params.use_channel_weights = ui->cb_use_channel_weights->isChecked();
    params.use_segmentation = ui->cb_use_segmentation->isChecked();

    params.window_function = ui->cb_window_function->currentText().toStdString();

    params.num_hog_channels_used = ui->sb_hog_channels->value();
    params.admm_iterations = ui->sb_admm_iterations->value();
    params.histogram_bins = ui->sb_histogram_bins->value();
    params.background_ratio = ui->sb_background_ratio->value();
    params.number_of_scales = ui->sb_number_of_scales->value();

    params.kaiser_alpha = ui->sb_kaiser_alpha->value();
    params.cheb_attenuation = ui->sb_cheb_attenuation->value();
    params.template_size = ui->sb_template_size->value();
    params.gsl_sigma = ui->sb_gsl_sigma->value();
    params.hog_orientations = ui->sb_hog_orientations->value();
    params.hog_clip = ui->sb_hog_clip->value();
    params.padding = ui->sb_padding->value();
    params.filter_lr = ui->sb_filter_lr->value();
    params.weights_lr = ui->sb_weights_lr->value();
    params.histogram_lr = ui->sb_histogram_lr->value();
    params.scale_sigma_factor = ui->sb_scale_sigma_factor->value();
    params.scale_model_max_area = ui->sb_scale_model_max_area->value();
    params.scale_lr = ui->sb_scale_lr->value();
    params.scale_step = ui->sb_scale_step->value();
    params.psr_threshold = ui->sb_psr_threshold->value();

    return params;
}

void FormCSRT::reset()
{
    cv::tracking::TrackerCSRT::Params params;

    ui->cb_use_hog->setChecked(params.use_hog);
    ui->cb_use_color_names->setChecked(params.use_color_names);
    ui->cb_use_gray->setChecked(params.use_gray);
    ui->cb_use_rgb->setChecked(params.use_rgb);
    ui->cb_use_channel_weights->setChecked(params.use_channel_weights);
    ui->cb_use_segmentation->setChecked(params.use_segmentation);

    ui->cb_window_function->setCurrentText(QString::fromStdString(params.window_function));

    ui->sb_hog_channels->setValue(params.num_hog_channels_used);
    ui->sb_admm_iterations->setValue(params.admm_iterations);
    ui->sb_histogram_bins->setValue(params.histogram_bins);
    ui->sb_background_ratio->setValue(params.background_ratio);
    ui->sb_number_of_scales->setValue(params.number_of_scales);

    ui->sb_kaiser_alpha->setValue(params.kaiser_alpha);
    ui->sb_cheb_attenuation->setValue(params.cheb_attenuation);
    ui->sb_template_size->setValue(params.template_size);
    ui->sb_gsl_sigma->setValue(params.gsl_sigma);
    ui->sb_hog_orientations->setValue(params.hog_orientations);
    ui->sb_hog_clip->setValue(params.hog_clip);
    ui->sb_padding->setValue(params.padding);
    ui->sb_filter_lr->setValue(params.filter_lr);
    ui->sb_weights_lr->setValue(params.weights_lr);
    ui->sb_histogram_lr->setValue(params.histogram_lr);
    ui->sb_scale_sigma_factor->setValue(params.scale_sigma_factor);
    ui->sb_scale_model_max_area->setValue(params.scale_model_max_area);
    ui->sb_scale_lr->setValue(params.scale_lr);
    ui->sb_scale_step->setValue(params.scale_step);
    ui->sb_psr_threshold->setValue(params.psr_threshold);
}

void FormCSRT::on_pushButton_clicked()
{
    reset();
}

