#include "fontstylefrm.h"
#include "ui_fontstylefrm.h"
#include<form.h>
FontStyleFrm::FontStyleFrm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontStyleFrm)
{
    ui->setupUi(this);

}

// 析构函数
FontStyleFrm::~FontStyleFrm()
{
    delete ui;
}
