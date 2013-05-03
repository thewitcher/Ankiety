#ifndef CLOSEQUESTION_H
#define CLOSEQUESTION_H

#include <QVector>

#include "question.h"
#include "available-answer.h"

class CloseQuestion : public Question
{
public:
    explicit CloseQuestion();

    void addAnswer( const QString & answer, const int row = -1 );
    bool hasAtLestTwoAnswers() const;
    int answerCount() const;
    AvailableAnswer getAnswer( int index );
    void deleteAnswer( const int row );

    QStringList data();

private:
    QVector< AvailableAnswer > m_vAnswers;
};

#endif // CLOSEQUESTION_H
