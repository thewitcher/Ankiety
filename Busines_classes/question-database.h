#ifndef QUESTIONDATABASE_H
#define QUESTIONDATABASE_H

#include <QMultiMap>

class Question;

class QuestionDatabase
{
public:
    static void addQuestion( Question * question );
    static QSet< QString > categoryList();
    static QVector< Question * > questionsFromCategory( const QString & category );
    static void createFakeData();
    static Question * questionWithId( const  int id );

private:
    QuestionDatabase();
    ~QuestionDatabase();

    // category - questions from category
    static QMultiMap< QString, Question * > m_database;
};

#endif // QUESTIONDATABASE_H
