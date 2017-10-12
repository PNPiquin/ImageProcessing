#include "mainwindow.h"
#include "ui_mainwindow.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    bundle = ImageBundle();
    ui->setupUi(this);

    ui->progress_bar->setMinimum(0);
    ui->progress_bar->setMaximum(100);
    ui->progress_bar->setValue(0);

    timerID = startTimer(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayImg(std::string img_name){
    ui->current_image->setCurrentText(QString::fromStdString(img_name));

    ui->image->setPixmap(CreatePixmap(img_name).scaled(ui->image->size(), Qt::KeepAspectRatio));
    ui->image->show();
}

QPixmap MainWindow::CreatePixmap(std::string img_name){
    try{
        std::shared_ptr<ImageHolder> img_holder = bundle.image_bundle.at(img_name);
        QImage img(img_holder->GetRows(), img_holder->GetCols(), QImage::Format_Grayscale8);
        for(int i = 0; i < img_holder->GetRows(); ++i){
            for(int j = 0; j < img_holder->GetCols(); ++j){
                int value = img_holder->mat_img(i, j);
                img.setPixel(QPoint(i, j), qRgb(value, value, value));
            }
        }
        return QPixmap::fromImage(img, Qt::NoFormatConversion);
    } catch(std::exception){
        printf("Image not found");
        return QPixmap();
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------
//                                                      Events
//------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::timerEvent(QTimerEvent *event){
    auto itr = bundle.image_bundle.begin();
    for(;itr != bundle.image_bundle.end(); ++itr){
        if(ui->current_image->findText(QString::fromStdString(itr->first)) == -1){
            ui->current_image->addItem(QString::fromStdString(itr->first));
            DisplayImg(itr->first);
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------
//                                                      On push button methods
//------------------------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonLoadImage_clicked()
{
    QString filename = ui->lineEditInputPath->text();
    bundle.LoadImg(filename.toStdString());
}

void MainWindow::on_pushButtonEdgeDetect_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->edge_tab_use_as_suffix->checkState() == Qt::Checked;
    bool use_vertical_sobel = ui->use_vertical_sobel->checkState() == Qt::Checked;
    bool use_horizontal_sobel = ui->use_horizontal_sobel->checkState() == Qt::Checked;
    bool use_gaussian_blur = ui->edge_tab_use_gaussian_blur->checkState() == Qt::Checked;
    int filter_size = ui->edge_tab_filter_size->currentText().toInt();
    int gaussian_filter_size = ui->gaussian_filter_size_spinbox->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->edge_tab_output_name->text().toStdString();
    } else{
        result_name = ui->edge_tab_output_name->text().toStdString();
    }
    if(use_vertical_sobel && use_horizontal_sobel){
        bundle.ProcessBothSobel(img_name, result_name, use_gaussian_blur, gaussian_filter_size, ui->progress_bar);
    }
    else if(use_vertical_sobel){
        bundle.ProcessVerticalSobel(img_name, result_name, use_gaussian_blur, gaussian_filter_size, ui->progress_bar);
    }
    else if(use_horizontal_sobel){
        bundle.ProcessHorizontalSobel(img_name, result_name, use_gaussian_blur, gaussian_filter_size, ui->progress_bar);
    }
    else{
        bundle.ProcessEdgeDetection(img_name, result_name, filter_size, use_gaussian_blur, gaussian_filter_size, ui->progress_bar);
    }
}


void MainWindow::on_histogram_tab_launch_normalization_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->histogram_tab_use_as_suffix->checkState() == Qt::Checked;
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->histogram_tab_output_name->text().toStdString();
    } else{
        result_name = ui->histogram_tab_output_name->text().toStdString();
    }
    bundle.ProcessHistogramNormalization(img_name, result_name, ui->progress_bar);
}

void MainWindow::on_intensity_tab_process_law_power_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->intensity_tab_use_as_suffix->checkState() == Qt::Checked;
    double gamma = ui->gamma_double_spinbox->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->intensity_tab_output_name->text().toStdString();
    } else{
        result_name = ui->intensity_tab_output_name->text().toStdString();
    }
    bundle.ProcessPowerLawTransformation(img_name, result_name, gamma, ui->progress_bar);
}

void MainWindow::on_intensity_tab_process_log_law_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->intensity_tab_use_as_suffix->checkState() == Qt::Checked;
    double c = ui->c_double_spinbox->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->intensity_tab_output_name->text().toStdString();
    } else{
        result_name = ui->intensity_tab_output_name->text().toStdString();
    }
    bundle.ProcessLogLawTransformation(img_name, result_name, c, ui->progress_bar);
}

void MainWindow::on_gaussian_blur_push_button_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->edge_tab_blur_use_as_suffix->checkState() == Qt::Checked;
    int gaussian_filter_size = ui->gaussian_filter_size_spinbox->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->edge_tab_blur_output_name->text().toStdString();
    } else{
        result_name = ui->edge_tab_blur_output_name->text().toStdString();
    }
    bundle.ProcessGaussianBlur(img_name, result_name, gaussian_filter_size, ui->progress_bar);
}

void MainWindow::on_intensity_tab_process_thresholding_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->intensity_tab_use_as_suffix->checkState() == Qt::Checked;
    int threshold = ui->intensity_tab_threshold_spinbox->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->intensity_tab_output_name->text().toStdString();
    } else{
        result_name = ui->intensity_tab_output_name->text().toStdString();
    }
    bundle.ProcessThresholding(img_name, result_name, threshold, ui->progress_bar);
}

void MainWindow::on_median_filter_push_button_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->median_use_as_suffix->checkState() == Qt::Checked;
    int filter_size = ui->median_filter_size->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->median_output_name->text().toStdString();
    } else{
        result_name = ui->median_output_name->text().toStdString();
    }
    bundle.ProcessMedianFilter(img_name, result_name, filter_size, ui->progress_bar);
}

void MainWindow::on_erosion_push_button_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->erosion_dilatation_use_as_suffix->checkState() == Qt::Checked;
    int filter_size = ui->erosion_dilatation_filter_size->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->erosion_dilatation_output_name->text().toStdString();
    } else{
        result_name = ui->erosion_dilatation_output_name->text().toStdString();
    }
    bundle.ProcessErosion(img_name, result_name, filter_size, ui->progress_bar);
}

void MainWindow::on_dilatation_push_button_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->erosion_dilatation_use_as_suffix->checkState() == Qt::Checked;
    int filter_size = ui->erosion_dilatation_filter_size->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->erosion_dilatation_output_name->text().toStdString();
    } else{
        result_name = ui->erosion_dilatation_output_name->text().toStdString();
    }
    bundle.ProcessDilatation(img_name, result_name, filter_size, ui->progress_bar);
}

void MainWindow::on_erosion_dilatation_push_button_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->erosion_dilatation_use_as_suffix->checkState() == Qt::Checked;
    int filter_size = ui->erosion_dilatation_filter_size->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->erosion_dilatation_output_name->text().toStdString();
    } else{
        result_name = ui->erosion_dilatation_output_name->text().toStdString();
    }
    bundle.ProcessErosionDilatation(img_name, result_name, filter_size, ui->progress_bar);
}

void MainWindow::on_sharp_process_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->sharp_use_as_suffix->checkState() == Qt::Checked;
    bool save_mask = ui->sharp_save_mask->checkState() == Qt::Checked;
    double alpha = ui->sharp_alpha_double_spinbox->value();
    int filter_size = ui->sharp_filter_size->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->sharp_output_name->text().toStdString();
    } else{
        result_name = ui->sharp_output_name->text().toStdString();
    }
    bundle.ProcessUnsharpMask(img_name, result_name, alpha, save_mask, filter_size, ui->progress_bar);
}

void MainWindow::on_change_working_dir_button_clicked()
{
    std::string work_dir = ui->working_dir_line->text().toStdString();
    bundle.SetWorkingDir(work_dir);
}

void MainWindow::on_save_push_button_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    std::string save_name = ui->save_name_line->text().toStdString();
    JpegManager::SaveGrayscaleMatrixImg(bundle.image_bundle.at(img_name)->mat_img, bundle.GetWorkingDir() + save_name);
    try {

    } catch (std::exception e){
        std::cout << "Error in method on_save_push_button_clicked --> " << e.what() << std::endl;
    }
}

void MainWindow::on_current_image_currentTextChanged(const QString &arg1)
{
    DisplayImg(arg1.toStdString());
}

void MainWindow::on_lmr_filter_push_button_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->lmr_use_as_suffix->checkState() == Qt::Checked;
    int filter_size = ui->lmr_filter_size->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->lmr_output_name->text().toStdString();
    } else{
        result_name = ui->lmr_output_name->text().toStdString();
    }
    bundle.ProcessLMR(img_name, result_name, filter_size, ui->progress_bar);
}

void MainWindow::on_canny_push_button_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->edge_tab_use_as_suffix->checkState() == Qt::Checked;
    bool save_tmp_imgs = ui->canny_tmp_imgs->checkState() == Qt::Checked;
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->edge_tab_output_name->text().toStdString();
    } else{
        result_name = ui->edge_tab_output_name->text().toStdString();
    }
    bundle.ProcessCanny(img_name, result_name, save_tmp_imgs, ui->progress_bar);
}

void MainWindow::on_otsu_push_button_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->segmentation_use_as_suffix->checkState() == Qt::Checked;
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->segmentation_output_name->text().toStdString();
    } else{
        result_name = ui->segmentation_output_name->text().toStdString();
    }
    bundle.ProcessOtsuSegmentation(img_name, result_name);
}

void MainWindow::on_k_means_push_button_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->segmentation_use_as_suffix->checkState() == Qt::Checked;
    int k = ui->k_means_spinbox->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->segmentation_output_name->text().toStdString();
    } else{
        result_name = ui->segmentation_output_name->text().toStdString();
    }
    bundle.ProcessKMeans(img_name, result_name, k);
}
