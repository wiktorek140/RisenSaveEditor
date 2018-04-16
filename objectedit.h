#ifndef OBJECTEDIT_H
#define OBJECTEDIT_H

#include <QWidget>

namespace Ui {
class ObjectEdit;
}

class ObjectEdit : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectEdit(QWidget *parent = 0);
    ~ObjectEdit();

private:
    Ui::ObjectEdit *ui;
};

#endif // OBJECTEDIT_H
