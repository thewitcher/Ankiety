#include "key-word.h"

KeyWord::KeyWord()
{
}

void KeyWord::setValues( const QString & keyWord, const double weight )
{
    m_sKeyWord = keyWord;
    m_dWeight = weight;
}

double KeyWord::weight() const
{
    return m_dWeight;
}

QString KeyWord::keyWord() const
{
    return m_sKeyWord;
}
