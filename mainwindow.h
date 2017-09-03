#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <map>
#include <boost/gil/gil_all.hpp>
#include <Eigen/Dense>

#include "imagebundle.h"

#include "SpatialFilter.h"
#include "JpegManager.h"
#include "CommonSpatialFilters.h"
#include "HistogramProcessor.h"
#include "IntensityTransformation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonLoadImage_clicked();

    void on_pushButtonEdgeDetect_clicked();

    void on_histogram_tab_launch_normalization_clicked();

    void on_intensity_tab_process_law_power_clicked();

    void on_intensity_tab_process_log_law_clicked();

    void on_gaussian_blur_push_button_clicked();

    void on_intensity_tab_process_thresholding_clicked();

    void on_median_filter_push_button_clicked();

    void on_erosion_push_button_clicked();

    void on_dilatation_push_button_clicked();

    void on_erosion_dilatation_push_button_clicked();

    void on_sharp_process_clicked();

    void on_change_working_dir_button_clicked();

    void on_save_push_button_clicked();

    void on_current_image_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    ImageBundle bundle;

    void DisplayImg(std::string img_name);
    QPixmap CreatePixmap(std::string img_name);
};

#endif // MAINWINDOW_H