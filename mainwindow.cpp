#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "add-question-dialog.h"

MainWindow::MainWindow( QWidget * parent ):
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    createConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createConnections()
{
    connect(ui->m_addQuestionButton,SIGNAL(clicked()),this,SLOT(showAddQuestionDialog()));
    connect(ui->m_exitButton,SIGNAL(clicked()),this,SLOT(close()));
}

void MainWindow::showAddQuestionDialog()
{
    AddQuestionDialog aQD;

    aQD.exec();
}
