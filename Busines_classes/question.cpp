#include "question.h"

int Question::m_maxId = 0;

Question::Question()
{
    m_iId = m_maxId;

    m_maxId++;
}

Question::~Question()
{
}

void Question::setQuestionText( const QString & text )
{
    m_sQuestionText = text;
}

void Question::setCategory( const QString & category )
{
    m_sCategory = category;
}

QString Question::questionText() const
{
    return m_sQuestionText;
}

QString Question::category() const
{
    return m_sCategory;
}

QStringList Question::data()
{
    return QStringList();
}

int Question::id() const
{
    return m_iId;
}
