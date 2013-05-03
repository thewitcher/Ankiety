#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QDebug>

class Question
{
public:
    Question();
    virtual ~Question();

    void setQuestionText( const QString & text );
    void setCategory( const QString & category );
    QString questionText() const;
    QString category() const;
    int id() const;

    virtual QStringList data();

private:
    QString m_sQuestionText;
    QString m_sCategory;
    int m_iId;

    static int m_maxId;
};

#endif // QUESTION_H
