#ifndef COMPLETESURVEYDIALOG_H
#define COMPLETESURVEYDIALOG_H

#include <QDialog>

namespace Ui { class CompleteSurveyDialog; }

class CompleteSurveyDialog : public QDialog
{

    Q_OBJECT
    
public:
    enum PAGE { SURVEY = 0, FILL = 1 };

    explicit CompleteSurveyDialog( QWidget * parent = 0 );
    ~CompleteSurveyDialog();
    
private:
    Ui::CompleteSurveyDialog * ui;
    PAGE m_eCurrentPage;

private slots:
    void showSurveyPage();
    void showFillPage();

    void next();
    void back();
};

#endif // COMPLETESURVEYDIALOG_H
