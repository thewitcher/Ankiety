#include "close-question-widget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>

CloseQuestionWidget::CloseQuestionWidget( CloseQuestion * question, QWidget * parent ):
    QWidget( parent ),
    m_pQuestion( question )
{
    QVBoxLayout * layout = new QVBoxLayout;

    QLabel * label = new QLabel( question->questionText() );

    layout->addWidget( label );

    for( int i = 0 ; i < question->answerCount() ; i++ )
    {
        QCheckBox * checkBox = new QCheckBox;
        checkBox->setText( question->getAnswer( i ).answerText() );

        layout->addWidget( checkBox );
    }

    setLayout( layout );
}
