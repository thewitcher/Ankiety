#ifndef SURVEYDATABASE_H
#define SURVEYDATABASE_H

#include "survey.h"

class SurveyDatabase
{
public:
    static void addSurvey( Survey * survey );
    static void createFakeData();
    static QVector< Survey * > surveys();

private:
    static QVector< Survey * > m_vSurveys;

    SurveyDatabase();
    ~SurveyDatabase();
};

#endif // SURVEYDATABASE_H
