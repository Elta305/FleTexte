#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTabWidget>
#include <QPlainTextEdit>
#include <QLabel>
#include <QTreeView>
#include <QSplitter>
#include <QFileSystemModel>

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

    QLabel* currentStatus();

    void textEditChanged();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void updateStatus();

    void on_actionOpen_Folder_triggered();

    void openTreeViewFile(QModelIndex index);

private:
    Ui::MainWindow *ui;

    QTabWidget *tabsWidget = new QTabWidget(this);

    QTreeView *treeView = new QTreeView;

    QSplitter *window = new QSplitter(this);

    QFileSystemModel *dirModel = new QFileSystemModel(this);

};
#endif // MAINWINDOW_H
