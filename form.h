#ifndef FORM_H
#define FORM_H
#include <nvml.h>
#include <QWidget>
#include<QLabel>
#include<HardData.h>
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
    HardData *displayCard;
    void SetSysTrayIcon();
    void ExitApplication();
    void ShowForm(bool checked);
    void InitPage();
private slots:
    void updateGPUInfo();
};
#endif // FORM_H
