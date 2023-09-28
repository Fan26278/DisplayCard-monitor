#ifndef FORM_H
#define FORM_H
#include <nvml.h>
#include <QWidget>
#include<QLabel>
#include<HardData.h>
#include<QSystemTrayIcon>
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
    QSystemTrayIcon *sysTrayIcon;
    bool isShow;

    void SetSysTrayIcon();
    void ExitApplication();
    void ShowForm(bool checked);
    void InitPage();
    void DragMode(bool checked);
private slots:
    void updateGPUInfo();
};
#endif // FORM_H
