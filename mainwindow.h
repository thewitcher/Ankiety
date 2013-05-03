#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{

    Q_OBJECT
    
public:
    explicit MainWindow( QWidget * parent = 0 );
    ~MainWindow();
    
private:
    Ui::MainWindow * ui;

    void createConnections();

private slots:
    void showAddQuestionDialog();
    void showCreateSurveyDialog();
    void showCompleteSurveyDialog();
};

#endif // MAINWINDOW_H
