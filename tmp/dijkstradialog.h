#ifndef DIJKSTRADIALOG_H
#define DIJKSTRADIALOG_H

#include <QWidget>

namespace Ui {
class dijkstraDialog;
}

class dijkstraDialog : public QWidget
{
    Q_OBJECT
    
signals:
    void runDijkstraFromTo(int from, int to);

public slots:
    void okButton_Pressed();

public:
    explicit dijkstraDialog(QWidget *parent = 0);
    ~dijkstraDialog();
    void setSize(int size);
    
private:
    Ui::dijkstraDialog *ui;
};

#endif // DIJKSTRADIALOG_H
