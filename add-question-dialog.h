#ifndef ADDQUESTIONDIALOG_H
#define ADDQUESTIONDIALOG_H

#include <QDialog>
#include <QModelIndex>

class Question;

namespace Ui { class AddQuestionDialog; }

class AddQuestionDialog : public QDialog
{

    Q_OBJECT
    
public:
    enum PAGE { TYPE = 0, CATEGORY = 1, TEXT = 2, ANSWER = 3, KEY_WORD = 4, RESULT = 5 };
    enum QUESTION_TYPE { OPEN_QUESTION, CLOSE_QUESTION };

    explicit AddQuestionDialog( QWidget * parent = 0 );
    ~AddQuestionDialog();
    
private:
    Ui::AddQuestionDialog * ui;
    PAGE m_eCurrentPage;
    QUESTION_TYPE m_eQuestionType;

    Question * m_pQuestion;

    int m_iRowToEditInAnswerListWidget;

    void initialize();
    void createConnections();
    void getCategoryFromDB();

private slots:
    void next();
    void back();
    void exit();

    void setTypePage();
    void setCategoryPage();
    void setTextPage();
    void setAnswerPage();
    void setKeyWordPage();
    void setResultPage();

    void onTypeChange( bool closeQuestion );

    void addAnswer();
    void addKeyWord();

    void resultsForCloseQuestion();
    void resultsForOpenQuestion();
    void resultsForBoth();

    void deleteFromAnswerListWidget();
    void editAnswerFromListWidget();
};

#endif // ADDQUESTIONDIALOG_H
