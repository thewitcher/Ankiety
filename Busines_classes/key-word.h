#ifndef KEYWORD_H
#define KEYWORD_H

#include <QString>

class KeyWord
{
public:
    KeyWord();

    void setValues( const QString & keyWord, const double weight );
    double weight() const;
    QString keyWord() const;

private:
    QString m_sKeyWord;
    double m_dWeight;
};

#endif // KEYWORD_H
