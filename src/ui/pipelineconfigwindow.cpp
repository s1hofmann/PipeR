#include "pipelineconfigwindow.h"
#include "ui_pipelineconfigwindow.h"

PipelineConfigWindow::PipelineConfigWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PipelineConfigWindow)
{
    ui->setupUi(this);
}

PipelineConfigWindow::~PipelineConfigWindow()
{
    delete ui;
}
