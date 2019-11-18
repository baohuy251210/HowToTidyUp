#ifndef ENDSCENE02_H
#define ENDSCENE02_H

#include <QWidget>

namespace Ui {
class EndScene02;
}

class EndScene02 : public QWidget
{
    Q_OBJECT

public:
    explicit EndScene02(QWidget *parent = nullptr);
    ~EndScene02();

private:
    Ui::EndScene02 *ui;
};

#endif // ENDSCENE02_H
