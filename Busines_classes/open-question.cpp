#include "open-question.h"

OpenQuestion::OpenQuestion():
    Question()
{
}

void OpenQuestion::addKeyWord( const QString & word, const double weight, const int row )
{
    if( row < 0 )
    {
        KeyWord kw;
        kw.setValues( word, weight );

        m_vWords.push_back( kw );
    }
    else
    {
        m_vWords[ row ].setValues( word, weight );
    }
}

int OpenQuestion::keyWordCount() const
{
    return m_vWords.size();
}

KeyWord OpenQuestion::getKeyWord( int index ) const
{
    return m_vWords.at( index );
}

void OpenQuestion::deleteKeyWord( const int row )
{
    m_vWords.remove( row );
}

QStringList OpenQuestion::data()
{
    QStringList d;

    for( QVector< KeyWord >::iterator it = m_vWords.begin() ; it != m_vWords.end() ; it++ )
    {
        d << ( * it ).keyWord();
    }

    return d;
}
