#include "available-answer.h"

AvailableAnswer::AvailableAnswer()
{
}

void AvailableAnswer::setAnswerText( const QString & text )
{
    m_sAnswerText = text;
}

QString AvailableAnswer::answerText() const
{
    return m_sAnswerText;
}
