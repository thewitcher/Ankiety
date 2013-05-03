#ifndef CREATESURVEYDIALOG_H
#define CREATESURVEYDIALOG_H

#include <QDialog>
#include "Busines_classes/survey.h"

namespace Ui { class CreateSurveyDialog; }

class CreateSurveyDialog : public QDialog
{

    Q_OBJECT
    
public:
    enum PAGE { SURVEY_NAME = 0, MAIN = 1, CATEGORY = 2, QUESTION_LIST = 3, RESULT = 4 };

    explicit CreateSurveyDialog( QWidget * parent = 0 );
    ~CreateSurveyDialog();
    
private:
    Ui::CreateSurveyDialog * ui;
    PAGE m_eCurrentPage;
    Survey * m_pSurvey;

    void createConnections();

private slots:
    void setSurveyNamePage();
    void setMainPage();
    void setCategoryPage();
    void setQuestionListPage();
    void setResultPage();

    void addNewQuestion();
    void addQuestionToSurvey();

    void next();
    void back();

    void fillQuestionLabel( int index );
    void deleteQuestion();
};

#endif // CREATESURVEYDIALOG_H
