#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabsWidget->setMovable(true);
    tabsWidget->setTabsClosable(true);
    setCentralWidget(tabsWidget);

    connect(tabsWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    QFontDatabase::addApplicationFont(":/fonts/static/SourceCodePro-Regular.ttf");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNew_File_triggered()
{
    MainWindow::createTab();
}

void MainWindow::on_actionClose_File_triggered()
{
    tabsWidget->removeTab(tabsWidget->currentIndex());
}

void MainWindow::closeTab(int index)
{
    tabsWidget->removeTab(index);
}

void MainWindow::createTab()
{
    QFrame *tabFrame = new QFrame(this);
    QVBoxLayout *tabLayout = new QVBoxLayout(tabFrame);

    QPlainTextEdit *fileEdit = new QPlainTextEdit();
    fileEdit->setObjectName("textEdit");

    QFont font = fileEdit->document()->defaultFont();
    font.setFamily("Source Code Pro");
    fileEdit->setFont(font);

    fileEdit->setTabStopDistance(QFontMetrics(fileEdit->font()).horizontalAdvance(' ') * 4);

    tabLayout->addWidget(fileEdit);

    int tab = tabsWidget->addTab(tabFrame, "Untitled");
    tabsWidget->setCurrentIndex(tab);

    connect(MainWindow::currentTextEdit(), SIGNAL(textChanged()), this, SLOT(textEditChanged()));
}

void MainWindow::openTabFile(QString filePath)
{
    QFile file(filePath);
    QFileInfo fileName(filePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }

    tabsWidget->setTabToolTip(tabsWidget->currentIndex(), filePath);

    QTextStream in(&file);
    QString text = in.readAll();

    MainWindow::currentTextEdit()->setPlainText(text);

    file.close();

    tabsWidget->setTabText(tabsWidget->currentIndex(), fileName.fileName());
}

QPlainTextEdit* MainWindow::currentTextEdit()
{
    QList<QPlainTextEdit *> fileEditList = tabsWidget->findChildren<QPlainTextEdit *>("textEdit");
    for (int i = 0; i < fileEditList.count(); i++) {
        if (tabsWidget->indexOf(fileEditList[i]->parentWidget()) == tabsWidget->currentIndex()) {
            return fileEditList[i];
        }
    }

    return new QPlainTextEdit;
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open the file");

    MainWindow::createTab();
    MainWindow::openTabFile(filePath);
}

void MainWindow::textEditChanged ()
{
    QString tabName = tabsWidget->tabText(tabsWidget->currentIndex());

    if (tabName.at(0) != "*"){
        tabsWidget->setTabText(tabsWidget->currentIndex(), "*"+tabName);
    }
}
