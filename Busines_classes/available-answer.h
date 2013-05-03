#ifndef AVAILABLEANSWER_H
#define AVAILABLEANSWER_H

#include <QString>

class AvailableAnswer
{
public:
    AvailableAnswer();

    void setAnswerText( const QString & text );
    QString answerText() const;

private:
    QString m_sAnswerText;
};

#endif // AVAILABLEANSWER_H
