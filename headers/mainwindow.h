#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTabWidget>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionNew_File_triggered();

    void on_actionClose_File_triggered();

    void closeTab(int index);

    void createTab();

    void on_actionOpen_File_triggered();

    void openTabFile(QString filePath);

    QPlainTextEdit* currentTextEdit();

    void textEditChanged();

private:
    Ui::MainWindow *ui;

    QTabWidget *tabsWidget = new QTabWidget(this);
};
#endif // MAINWINDOW_H
