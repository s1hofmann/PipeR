#pragma once


#include <QMainWindow>
#include <QDebug>

namespace Ui {
class PipelineConfigWindow;
}

class PipelineConfigWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PipelineConfigWindow(QWidget *parent = 0);
    ~PipelineConfigWindow();

private:
    Ui::PipelineConfigWindow *ui;
};
