#include "question-database.h"
#include "question.h"
#include "open-question.h"
#include "close-question.h"

#include <QSet>
#include <QVector>

QMultiMap< QString, Question * > QuestionDatabase::m_database;

QuestionDatabase::QuestionDatabase()
{
}

QuestionDatabase::~QuestionDatabase()
{
    for( QMultiMap< QString, Question * >::iterator it = m_database.begin() ; it != m_database.end() ; it++ )
    {
        delete it.value();
    }
}

void QuestionDatabase::addQuestion( Question * question )
{
    m_database.insertMulti( question->category(), question );
}

QSet< QString > QuestionDatabase::categoryList()
{
    return m_database.keys().toSet();
}

QVector< Question * > QuestionDatabase::questionsFromCategory( const QString & category )
{
    QPair< QMultiMap< QString, Question * >::iterator, QMultiMap< QString, Question * >::iterator > range = m_database.equal_range( category );

    QVector< Question * > vec;

    for( QMultiMap< QString, Question * >::iterator it = range.first ; it != range.second ; it++ )
    {
        vec.push_back( it.value() );
    }

    return vec;
}

void QuestionDatabase::createFakeData()
{
    OpenQuestion * oq = new OpenQuestion;
    oq->setCategory( "Kategoria 1" );
    oq->setQuestionText( "Pytanie otwarte" );
    oq->addKeyWord( "Dobry", 0.3 );
    oq->addKeyWord( "Ok", 0.5 );

    m_database.insertMulti( oq->category(), oq );

    CloseQuestion * cq = new CloseQuestion;
    cq->setCategory( "Kategoria 2" );
    cq->setQuestionText( "Pytanie zamknięte" );
    cq->addAnswer( "1" );
    cq->addAnswer( "2" );
    cq->addAnswer( "3" );

    m_database.insertMulti( cq->category(), cq );
}

Question * QuestionDatabase::questionWithId( const int id )
{
    QList< Question * > list = m_database.values();

    for( QList< Question * >::iterator it = list.begin() ; it != list.end() ; it++ )
    {
        if( ( * it )->id() == id )
        {
            return * it;
        }
    }

    return NULL;
}
