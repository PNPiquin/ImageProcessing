#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Segmentation/kmeans.h"

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

    ui->K_means_combobox->addItem("SVD");
    ui->K_means_combobox->addItem("Euclidian distance");
    ui->K_means_combobox->addItem("ED + SVD");

    timerID = startTimer(500);

    // Building UI update timer
    displayed_img_index = 0;
    auto_update_timer = new QTimer(this);
    connect(auto_update_timer, SIGNAL(timeout()), this, SLOT(ui_auto_update()));
    auto_update_timer->start(40);

    // Building progress update timer
    progress_update_timer = new QTimer(this);
    connect(progress_update_timer, SIGNAL(timeout()), this, SLOT(progress_update()));
    progress_update_timer->start(100);
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
        std::shared_ptr<ImageHolder> img_holder = bundle.FindImage(img_name);
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

QPixmap MainWindow::CreatePixmapFromImg(std::shared_ptr<ImageHolder> img_holder){
    try{
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
        if(std::find(displayed_imgs.begin(), displayed_imgs.end(), itr->first) == displayed_imgs.end()){
            ui->current_image->addItem(QString::fromStdString(itr->first));
            DisplayImg(itr->first);
            displayed_imgs.push_back(itr->first);
        }
    }
}

void MainWindow::ui_auto_update(){
    try{
        std::string img_group = ui->current_image->currentText().toStdString();
        if(img_group.size() == 0){
            return;
        }

        std::vector<std::shared_ptr<ImageHolder>> image_vect = bundle.FindImageVector(img_group);
        if(image_vect.size() == 0){
            return;
        }

        const int current_index = displayed_img_index;
        if(displayed_img_index >= (int)(image_vect.size() - 1)){
            displayed_img_index = 0;
        } else {
            displayed_img_index++;
        }

        // To avoid useless processing
        if(current_index == displayed_img_index){
            return;
        }

        std::shared_ptr<ImageHolder> img_holder = image_vect[displayed_img_index];
        ui->image->setPixmap(CreatePixmapFromImg(img_holder).scaled(ui->image->size(), Qt::KeepAspectRatio));
        ui->image->show();
    } catch(...) {
        std::cout << "An error ocurred while updating the displayed image" << std::endl;
    }
}

void MainWindow::progress_update(){
    try{
        ui->progress_bar->setValue(bundle.GetProgress());
    } catch(...){
        std::cout << "An error ocurred while updating the progress bar" << std::endl;
    }
}

void MainWindow::on_display_frequency_spinBox_valueChanged(int new_frequency)
{
    int new_interval = 1000 / new_frequency;
    auto_update_timer->setInterval(new_interval);
}

//------------------------------------------------------------------------------------------------------------------------------------------
//                                                On push button utils methods
//------------------------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonLoadImage_clicked()
{
    QString filename = ui->lineEditInputPath->text();
    bundle.LoadImg(filename.toStdString());
}

void MainWindow::on_load_folder_img_button_clicked()
{
    QString folder_path = ui->lineEditInputFolderPath->text();
    bundle.LoadImgFolder(folder_path.toStdString());
}

void MainWindow::on_save_folder_push_button_clicked()
{
    std::string save_folder = ui->save_folder_name_line->text().toStdString();
    std::string img_name = ui->current_image->currentText().toStdString();
    bundle.SaveImgGroup(img_name, save_folder);
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
    JpegManager::SaveGrayscaleMatrixImg(bundle.FindImage(img_name)->mat_img, bundle.GetWorkingDir() + save_name);
    try {

    } catch (std::exception e){
        std::cout << "Error in method on_save_push_button_clicked --> " << e.what() << std::endl;
    }
}

void MainWindow::on_current_image_currentTextChanged(const QString &arg1)
{
    DisplayImg(arg1.toStdString());
}

void MainWindow::on_delete_push_button_clicked()
{
    std::string name = ui->current_image->currentText().toStdString();
    bundle.DeleteImageGroup(name);

    // Remove old name
    ui->current_image->removeItem(ui->current_image->currentIndex());
    DisplayImg(ui->current_image->itemText(0).toStdString());
}

//------------------------------------------------------------------------------------------------------------------------------------------
//                                           On push button processing methods
//------------------------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonEdgeDetect_clicked()
{
    // Get image name
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    bool use_vertical_sobel = ui->use_vertical_sobel->checkState() == Qt::Checked;
    bool use_horizontal_sobel = ui->use_horizontal_sobel->checkState() == Qt::Checked;
    bool use_gaussian_blur = ui->edge_tab_use_gaussian_blur->checkState() == Qt::Checked;
    int filter_size = ui->edge_tab_filter_size->currentText().toInt();
    int gaussian_filter_size = ui->gaussian_filter_size_spinbox->value();

    // Get output name
    std::string result_name = img_name + ui->edge_tab_output_name->text().toStdString();

    // Edge detection method selection
    if(use_vertical_sobel && use_horizontal_sobel){
        std::thread t(&ImageBundle::ProcessBothSobel,
                      &bundle,
                      img_name,
                      result_name,
                      use_gaussian_blur,
                      gaussian_filter_size);
        t.detach();
    }
    else if(use_vertical_sobel){
        std::thread t(&ImageBundle::ProcessVerticalSobel,
                      &bundle,
                      img_name,
                      result_name,
                      use_gaussian_blur,
                      gaussian_filter_size);
        t.detach();
    }
    else if(use_horizontal_sobel){
        std::thread t(&ImageBundle::ProcessHorizontalSobel,
                      &bundle,
                      img_name,
                      result_name,
                      use_gaussian_blur,
                      gaussian_filter_size);
        t.detach();
    }
    else{
        std::thread t(&ImageBundle::ProcessEdgeDetection,
                      &bundle,
                      img_name,
                      result_name,
                      filter_size,
                      use_gaussian_blur,
                      gaussian_filter_size);
        t.detach();
    }
}


void MainWindow::on_histogram_tab_launch_normalization_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get output name
    std::string result_name = img_name + ui->histogram_tab_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessHistogramNormalization, &bundle, img_name, result_name);
    t.detach();
}

void MainWindow::on_intensity_tab_process_law_power_clicked()
{
    // Get Image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    double gamma = ui->gamma_double_spinbox->value();

    // Get output name
    std::string result_name = img_name + ui->intensity_tab_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessPowerLawTransformation,
                  &bundle,
                  img_name,
                  result_name,
                  gamma);
    t.detach();
}

void MainWindow::on_intensity_tab_process_log_law_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    double c = ui->c_double_spinbox->value();

    // Get output name
    std::string result_name = img_name + ui->intensity_tab_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessLogLawTransformation,
                  &bundle,
                  img_name,
                  result_name,
                  c);
    t.detach();
}

void MainWindow::on_gaussian_blur_push_button_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    int gaussian_filter_size = ui->gaussian_filter_size_spinbox->value();

    // Get output name
    std::string result_name = img_name + ui->edge_tab_blur_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessGaussianBlur,
                  &bundle,
                  img_name,
                  result_name,
                  gaussian_filter_size);
    t.detach();
}

void MainWindow::on_intensity_tab_process_thresholding_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    int threshold = ui->intensity_tab_threshold_spinbox->value();

    // Get output name
    std::string result_name = img_name + ui->intensity_tab_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessThresholding,
                  &bundle,
                  img_name,
                  result_name,
                  threshold);
    t.detach();
}

void MainWindow::on_median_filter_push_button_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

     // Get params
    int filter_size = ui->median_filter_size->value();

    // Get output name
    std::string result_name = img_name + ui->median_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessMedianFilter,
                  &bundle,
                  img_name,
                  result_name,
                  filter_size);
    t.detach();
}

void MainWindow::on_erosion_push_button_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    int filter_size = ui->erosion_dilatation_filter_size->value();

    // Get output name
    std::string result_name = img_name + ui->erosion_dilatation_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessErosion,
                  &bundle,
                  img_name,
                  result_name,
                  filter_size);
    t.detach();
}

void MainWindow::on_dilatation_push_button_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    int filter_size = ui->erosion_dilatation_filter_size->value();

    // Get output name
    std::string result_name = img_name + ui->erosion_dilatation_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessDilatation,
                  &bundle,
                  img_name,
                  result_name,
                  filter_size);
    t.detach();
}

void MainWindow::on_erosion_dilatation_push_button_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    int filter_size = ui->erosion_dilatation_filter_size->value();

    // Get output name
    std::string result_name = img_name + ui->erosion_dilatation_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessErosionDilatation,
                  &bundle,
                  img_name,
                  result_name,
                  filter_size);
    t.detach();
}

void MainWindow::on_sharp_process_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    bool save_mask = ui->sharp_save_mask->checkState() == Qt::Checked;
    double alpha = ui->sharp_alpha_double_spinbox->value();
    int filter_size = ui->sharp_filter_size->value();

    // Get output name
    std::string result_name = img_name + ui->sharp_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessUnsharpMask,
                  &bundle,
                  img_name,
                  result_name,
                  alpha,
                  save_mask,
                  filter_size);
    t.detach();
}

void MainWindow::on_lmr_filter_push_button_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    int filter_size = ui->lmr_filter_size->value();

    // Get output name
    std::string result_name = img_name + ui->lmr_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessLMR,
                  &bundle,
                  img_name,
                  result_name,
                  filter_size);
    t.detach();
}

void MainWindow::on_canny_push_button_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    bool save_tmp_imgs = ui->canny_tmp_imgs->checkState() == Qt::Checked;

    // Get output name
    std::string result_name = img_name + ui->edge_tab_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessCanny,
                  &bundle,
                  img_name,
                  result_name,
                  save_tmp_imgs);
    t.detach();
}

void MainWindow::on_otsu_push_button_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get output name
    std::string result_name = img_name + ui->segmentation_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessOtsuSegmentation,
                  &bundle,
                  img_name,
                  result_name);
    t.detach();
}

void MainWindow::on_k_means_push_button_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    int k = ui->k_means_spinbox->value();
    KMeans::K_MEANS_DISTANCE distance_method = KMeans::K_MEANS_DISTANCE::SVD;
    std::string distance_method_string = ui->K_means_combobox->currentText().toStdString();
    if(distance_method_string == "Euclidian distance"){
        distance_method = KMeans::K_MEANS_DISTANCE::EUCLIDIAN_DISTANCE;
    } else if(distance_method_string == "ED + SVD"){
        distance_method = KMeans::K_MEANS_DISTANCE::ED_SVD;
    } else if(distance_method_string == "SVD"){
        distance_method = KMeans::K_MEANS_DISTANCE::SVD;
    }

    // Get output name
    std::string result_name = img_name + ui->segmentation_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessKMeans,
                  &bundle,
                  img_name,
                  result_name,
                  k,
                  distance_method);
    t.detach();
}

void MainWindow::on_negative_push_button_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get output name
    std::string result_name = img_name + ui->intensity_tab_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessNegative,
                  &bundle,
                  img_name,
                  result_name);
    t.detach();
}

void MainWindow::on_resize_pushButton_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Get params
    int x0 = ui->x0_spinBox->value();
    int y0 = ui->y0_spinBox->value();
    int x1 = ui->x1_spinBox->value();
    int y1 = ui->y1_spinBox->value();

    // Get output name
    std::string result_name = ui->resize_tab_output_name->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessImageResize,
                  &bundle,
                  img_name,
                  result_name,
                  x0, y0, x1, y1);
    t.detach();
}

void MainWindow::on_difference_pushButton_clicked()
{
    // Get image to process
    std::string img_name = ui->current_image->currentText().toStdString();

    // Params
    const int step = ui->difference_spinBox->value();

    // Get output name
    std::string result_name = ui->difference_output_suffix->text().toStdString();

    // Process
    std::thread t(&ImageBundle::ProcessDifference,
                  &bundle,
                  img_name,
                  result_name,
                  step);
    t.detach();
}
