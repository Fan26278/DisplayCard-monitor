#ifndef FORM_H
#define FORM_H
#include <nvml.h>
#include <QWidget>
#include<QLabel>
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
private:
    Ui::Form *ui;
    QTimer *timer;
    nvmlDevice_t device;
    nvmlUtilization_t nvmUtil;
    nvmlMemory_t memory;
    nvmlReturn_t result ;
    void SetSysTrayIcon();
    void ExitApplication();
    void ShowForm(bool checked);
private slots:
    void updateGPUInfo();
};
#endif // FORM_H
