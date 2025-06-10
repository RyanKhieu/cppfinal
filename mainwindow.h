#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CandyBudgeting;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::CandyBudgeting *ui;

    double balance = 0.0;
    const QString balanceFile = "balance.txt";

    void loadBalance();
    void saveBalance();
    void updateBalance();

private slots:
    void addClicked();
    void subtractClicked();
    void tryClicked();
};
#endif // MAINWINDOW_H
