#ifndef GRAPHDRAWINGDIALOG_H
#define GRAPHDRAWINGDIALOG_H

#include <QWidget>

namespace Ui {
class graphDrawingDialog;
}

class graphDrawingDialog : public QWidget
{
    Q_OBJECT
    
public:
    explicit graphDrawingDialog(QWidget *parent = 0);
    ~graphDrawingDialog();

public slots:
    void okButtonPressed();
signals:
    void drawThis(int vertices, int edges);
    
private:
    Ui::graphDrawingDialog *ui;
};

#endif // GRAPHDRAWINGDIALOG_H
