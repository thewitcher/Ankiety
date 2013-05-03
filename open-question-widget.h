#ifndef OPENQUESTIONWIDGET_H
#define OPENQUESTIONWIDGET_H

#include <QWidget>

#include "Busines_classes/open-question.h"

class OpenQuestionWidget : public QWidget
{

    Q_OBJECT

public:
    explicit OpenQuestionWidget( OpenQuestion * question, QWidget * parent = 0 );

private:
    OpenQuestion * m_pQuestion;
};

#endif // OPENQUESTIONWIDGET_H
