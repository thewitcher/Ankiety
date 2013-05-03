#ifndef CLOSEQUESTIONWIDGET_H
#define CLOSEQUESTIONWIDGET_H

#include <QWidget>

#include "Busines_classes/close-question.h"

class CloseQuestionWidget : public QWidget
{

    Q_OBJECT

public:
    explicit CloseQuestionWidget( CloseQuestion * question, QWidget * parent = 0 );

private:
    CloseQuestion * m_pQuestion;
};


#endif // CLOSEQUESTIONWIDGET_H
