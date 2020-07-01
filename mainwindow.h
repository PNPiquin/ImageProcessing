#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Standard includes
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <thread>

// Third parties libraries
#include <QMainWindow>
#include <QTimer>

#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

#include <boost/gil/gil_all.hpp>
#include <Eigen/Dense>

// Input output class
#include "IO/ImageIOManager.h"

// Image management
#include "ImageClasses/imagebundle.h"

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
    void ui_auto_update();
    void progress_update();
    void on_delete_push_button_clicked();
    void on_resize_pushButton_clicked();
    void on_display_frequency_spinBox_valueChanged(int new_frequency);
    void on_difference_pushButton_clicked();
    void on_v_grad_push_button_clicked();
    void on_h_grad_push_button_clicked();
    void on_morph_edge_detect_button_clicked();

private:
    Ui::MainWindow *ui;
    ImageBundle bundle;
    std::vector<std::string> displayed_imgs;

    void DisplayImg(std::string img_name);
    QPixmap CreatePixmap(std::string img_name);
    QPixmap CreatePixmapFromImg(std::shared_ptr<ImageHolder> img_holder);

    int timerID;

    // UI auto update timer --> allow to show multiple frames as a video
    QTimer *auto_update_timer;
    int displayed_img_index;

    // Progress timer --> update the progress bar value from a shared value with other threads
    QTimer* progress_update_timer;

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
