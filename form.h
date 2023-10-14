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

    // 标签字体
    QFont *labelFont;
private:
    Ui::Form *ui;
    // 获得数据计时器
    QTimer *timer;
    HardData *displayCard;
    // 系统托盘
    QSystemTrayIcon *sysTrayIcon;
    bool isShow;
    QAction *showAction;


    void SetSysTrayIcon();
    void ExitApplication();
    void ShowForm(bool checked);
    void InitPage();
    void DragMode(bool checked);
private slots:
    void updateGPUInfo();
};
#endif // FORM_H
