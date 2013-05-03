#ifndef SURVEY_H
#define SURVEY_H

#include <QString>
#include "question.h"

class Survey
{
public:
    Survey();

    void setSurveyName( const QString & name );
    QString surveyName();
    void addQuestions( Question * question );
    Question * question( int index );
    int questionsCount();
    void deleteQuestion( int index );

private:
    QString m_sSurveyName;
    QVector< Question * > m_questions;
};

#endif // SURVEY_H
