#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <map>
#include <boost/gil/gil_all.hpp>
#include <Eigen/Dense>

#include "IO/JpegManager.h"

#include "ImageClasses/imagebundle.h"

#include "SpatialFiltering/SpatialFilter.h"
#include "SpatialFiltering/CommonSpatialFilters.h"
#include "SpatialFiltering/HistogramProcessor.h"
#include "SpatialFiltering/IntensityTransformation.h"

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

    void on_lmr_filter_push_button_clicked();

    void on_canny_push_button_clicked();

    void on_otsu_push_button_clicked();

    void on_k_means_push_button_clicked();

    void on_negative_push_button_clicked();

    void on_load_folder_img_button_clicked();

    void on_save_folder_push_button_clicked();

private:
    Ui::MainWindow *ui;
    ImageBundle bundle;

    void DisplayImg(std::string img_name);
    QPixmap CreatePixmap(std::string img_name);

    int timerID;

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
