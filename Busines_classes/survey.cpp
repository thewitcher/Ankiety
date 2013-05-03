#include "survey.h"

Survey::Survey()
{
}

void Survey::setSurveyName( const QString & name )
{
    m_sSurveyName = name;
}

void Survey::addQuestions( Question * question )
{
    m_questions.push_back( question );
}

Question * Survey::question( int index )
{
    return m_questions.at( index );
}

int Survey::questionsCount()
{
    return m_questions.size();
}

void Survey::deleteQuestion( int index )
{
    m_questions.remove( index );
}

QString Survey::surveyName()
{
    return m_sSurveyName;
}
