#include "mainwindow.h"
#include "ui_mainwindow.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    bundle = ImageBundle();
    ui->setupUi(this);

    // LMR tree section setup

    ui->treeWidget->setColumnCount(2);

    QTreeWidgetItem *lmr_main_item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("LMR")));
    QList<QTreeWidgetItem *> items;
    QList<QWidget *> widgets;

    QTreeWidgetItem *output_name_edit = new QTreeWidgetItem(lmr_main_item, QStringList(QString("Output name")));
    items.append(output_name_edit);
    widgets.append(new QLineEdit("_lmr"));

    QTreeWidgetItem *use_as_suffix_checkbox = new QTreeWidgetItem(lmr_main_item, QStringList(QString("Use as suffix")));
    items.append(use_as_suffix_checkbox);
    widgets.append(new QCheckBox());

    QTreeWidgetItem *filter_size = new QTreeWidgetItem(lmr_main_item, QStringList(QString("Filter size")));
    items.append(filter_size);
    widgets.append(new QSpinBox());

    QTreeWidgetItem *process_button_item = new QTreeWidgetItem(lmr_main_item, QStringList(QString("Process")));
    items.append(process_button_item);
    QPushButton *process_button = new QPushButton("Process");
    QObject::connect(process_button, SIGNAL(clicked()), this, SLOT(on_lmr_process_clicked()));
    widgets.append(process_button);

    //ui->treeWidget->insertTopLevelItems(0, items);
    for(int i = 0; i < items.size(); ++i){
        ui->treeWidget->setItemWidget(items.value(i),1,widgets.value(i));
    }

    ui->treeWidget->insertTopLevelItem(0, lmr_main_item);


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
//                                                      On push button methods
//------------------------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonLoadImage_clicked()
{
    QString filename = ui->lineEditInputPath->text();
    bundle.LoadImg(filename.toStdString());
    //ui->current_image->addItem(filename);
    ui->current_image->addItem(filename + "_grayscale");
    DisplayImg(filename.toStdString() + "_grayscale");
}

void MainWindow::on_pushButtonEdgeDetect_clicked()
{
    std::string img_name = ui->current_image->currentText().toStdString();
    bool use_as_a_suffix = ui->edge_tab_use_as_suffix->checkState() == Qt::Checked;
    bool use_gaussian_blur = ui->edge_tab_use_gaussian_blur->checkState() == Qt::Checked;
    int filter_size = ui->edge_tab_filter_size->currentText().toInt();
    int gaussian_filter_size = ui->gaussian_filter_size_spinbox->value();
    std::string result_name;
    if(use_as_a_suffix){
        result_name = img_name + ui->edge_tab_output_name->text().toStdString();
    } else{
        result_name = ui->edge_tab_output_name->text().toStdString();
    }
    bundle.ProcessEdgeDetection(img_name, result_name, filter_size, use_gaussian_blur, gaussian_filter_size);
    ui->current_image->addItem(QString::fromStdString(result_name));

    DisplayImg(result_name);
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
    bundle.ProcessHistogramNormalization(img_name, result_name);
    ui->current_image->addItem(QString::fromStdString(result_name));

    DisplayImg(result_name);
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
    bundle.ProcessPowerLawTransformation(img_name, result_name, gamma);
    ui->current_image->addItem(QString::fromStdString(result_name));

    DisplayImg(result_name);
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
    bundle.ProcessLogLawTransformation(img_name, result_name, c);
    ui->current_image->addItem(QString::fromStdString(result_name));

    DisplayImg(result_name);
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
    bundle.ProcessGaussianBlur(img_name, result_name, gaussian_filter_size);
    ui->current_image->addItem(QString::fromStdString(result_name));

    DisplayImg(result_name);
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
    bundle.ProcessThresholding(img_name, result_name, threshold);
    ui->current_image->addItem(QString::fromStdString(result_name));

    DisplayImg(result_name);
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
    bundle.ProcessMedianFilter(img_name, result_name, filter_size);
    ui->current_image->addItem(QString::fromStdString(result_name));

    DisplayImg(result_name);
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
    bundle.ProcessErosion(img_name, result_name, filter_size);
    ui->current_image->addItem(QString::fromStdString(result_name));

    DisplayImg(result_name);
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
    bundle.ProcessDilatation(img_name, result_name, filter_size);
    ui->current_image->addItem(QString::fromStdString(result_name));

    DisplayImg(result_name);
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
    bundle.ProcessErosionDilatation(img_name, result_name, filter_size);
    ui->current_image->addItem(QString::fromStdString(result_name));

    DisplayImg(result_name);
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
    bundle.ProcessUnsharpMask(img_name, result_name, alpha, save_mask, filter_size);
    ui->current_image->addItem(QString::fromStdString(result_name));

    DisplayImg(result_name);
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

void MainWindow::on_lmr_process_clicked()
{
    std::cout << "coucou" << std::endl;
}
