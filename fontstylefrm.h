#ifndef FONTSTYLEFRM_H
#define FONTSTYLEFRM_H

#include <QDialog>

namespace Ui {
class FontStyleFrm;
}

class FontStyleFrm : public QDialog
{
    Q_OBJECT

public:
    explicit FontStyleFrm(QWidget *parent = nullptr);
    ~FontStyleFrm();

private:

    Ui::FontStyleFrm *ui;
    QFont *font;
};

#endif // FONTSTYLEFRM_H
