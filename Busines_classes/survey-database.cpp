#include "survey-database.h"
#include "open-question.h"
#include "close-question.h"

QVector< Survey * > SurveyDatabase::m_vSurveys;

SurveyDatabase::SurveyDatabase()
{
}

SurveyDatabase::~SurveyDatabase()
{
}

void SurveyDatabase::addSurvey( Survey * survey )
{
    m_vSurveys.push_back( survey );
}

void SurveyDatabase::createFakeData()
{
    Survey * survey = new Survey;
    survey->setSurveyName( "Ankieta 1" );

    OpenQuestion * oq = new OpenQuestion;
    oq->setCategory( "Kategoria 1" );
    oq->setQuestionText( "Pytanie otwarte" );
    oq->addKeyWord( "Dobry", 0.3 );
    oq->addKeyWord( "Ok", 0.5 );

    CloseQuestion * cq = new CloseQuestion;
    cq->setCategory( "Kategoria 2" );
    cq->setQuestionText( "Pytanie zamknięte" );
    cq->addAnswer( "1" );
    cq->addAnswer( "2" );
    cq->addAnswer( "3" );

    survey->addQuestions( oq );
    survey->addQuestions( cq );

    addSurvey( survey );
}

QVector< Survey * > SurveyDatabase::surveys()
{
    return m_vSurveys;
}
