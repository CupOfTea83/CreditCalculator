#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool eventFilter(QObject* , QEvent* );
    ~MainWindow();

private slots:
    void digit_numbers();

    void on_numButtonDot_clicked();

    void on_calculateButton_clicked();

    void on_resetButton_clicked();

    void on_cancelButton_clicked();

    void on_rubLineEdit_editingFinished();

    void on_percentLineEdit_editingFinished();

    void on_monLineEdit_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QDoubleValidator m_dobVal;
    QIntValidator m_intVal;

    QString oldRub = "";
    QString oldMon = "";
    QString oldPerc = "";
};
#endif // MAINWINDOW_H
