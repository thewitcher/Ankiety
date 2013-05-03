#include "close-question.h"

CloseQuestion::CloseQuestion() :
    Question()
{
}

void CloseQuestion::addAnswer( const QString & answer, const int row )
{
    if( row < 0 )
    {
        AvailableAnswer aa;
        aa.setAnswerText( answer );

        m_vAnswers.push_back( aa );
    }
    else
    {
        m_vAnswers[ row ].setAnswerText( answer );
    }
}

bool CloseQuestion::hasAtLestTwoAnswers() const
{
    if( m_vAnswers.size() < 2 )
    {
        return false;
    }

    return true;
}

int CloseQuestion::answerCount() const
{
    return m_vAnswers.size();
}

AvailableAnswer CloseQuestion::getAnswer( int index )
{
    return m_vAnswers.at( index );
}

void CloseQuestion::deleteAnswer( const int row )
{
    m_vAnswers.remove( row );
}

QStringList CloseQuestion::data()
{
    QStringList d;

    for( QVector< AvailableAnswer >::iterator it = m_vAnswers.begin() ; it != m_vAnswers.end() ; it++ )
    {
        d << ( * it ).answerText();
    }

    return d;
}
