#include "open-question-widget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>

OpenQuestionWidget::OpenQuestionWidget( OpenQuestion * question, QWidget * parent ):
    QWidget( parent ),
    m_pQuestion( question )
{
    QVBoxLayout * layout = new QVBoxLayout;

    QLabel * label = new QLabel( question->questionText() );
    QTextEdit * textEdit = new QTextEdit;

    layout->addWidget( label );
    layout->addWidget( textEdit );

    setLayout( layout );
}
