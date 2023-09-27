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

    nvmlDevice_t device;
    nvmlUtilization_t nvmUtil;
    nvmlMemory_t memory;
    nvmlReturn_t result ;
    void SetSysTrayIcon();
    void ExitApplication();
private slots:
    void updateGPUInfo();
};
#endif // FORM_H
