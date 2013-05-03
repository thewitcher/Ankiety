#ifndef OPENQUESTION_H
#define OPENQUESTION_H

#include <QVector>

#include "Busines_classes/question.h"
#include "Busines_classes/key-word.h"


class OpenQuestion : public Question
{
public:
    explicit OpenQuestion();

    void addKeyWord( const QString & word, const double weight, const int row = -1 );
    int keyWordCount() const;
    KeyWord getKeyWord( int index ) const;
    void deleteKeyWord( const int row );

    QStringList data();

private:
    QVector< KeyWord > m_vWords;
};

#endif // OPENQUESTION_H
