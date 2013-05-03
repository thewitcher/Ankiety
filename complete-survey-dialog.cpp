#include "complete-survey-dialog.h"
#include "ui_complete-survey-dialog.h"
#include "Busines_classes/survey-database.h"
#include "Busines_classes/close-question.h"
#include "Busines_classes/open-question.h"

#include "open-question-widget.h"
#include "close-question-widget.h"

#include <QMessageBox>

CompleteSurveyDialog::CompleteSurveyDialog( QWidget * parent ):
    QDialog( parent ),
    ui( new Ui::CompleteSurveyDialog )
{
    ui->setupUi( this );

    connect(ui->m_pAnulujButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->m_pNextButton,SIGNAL(clicked()),this,SLOT(next()));
    connect(ui->m_pBackButton,SIGNAL(clicked()),this,SLOT(back()));

    SurveyDatabase::createFakeData();

    showSurveyPage();
}

CompleteSurveyDialog::~CompleteSurveyDialog()
{
    delete ui;
}

void CompleteSurveyDialog::showSurveyPage()
{
    ui->m_pBackButton->setVisible( false );
    ui->m_pNextButton->setText( "Dalej" );
    m_eCurrentPage = SURVEY;
    ui->stackedWidget->setCurrentIndex( m_eCurrentPage );

    QVector< Survey * > v = SurveyDatabase::surveys();
    for( int i = 0 ; i < v.size() ; i++ )
    {
        ui->comboBox->addItem( v.at( i )->surveyName() );
    }
}

void CompleteSurveyDialog::showFillPage()
{
    Survey * survey = SurveyDatabase::surveys().at( ui->comboBox->currentIndex() );

    for( int i = 0 ; i < survey->questionsCount() ; i++ )
    {
        CloseQuestion * cq = dynamic_cast< CloseQuestion * >( survey->question( i ) );
        if( cq == NULL ) // open
        {
            OpenQuestion * oq = dynamic_cast< OpenQuestion * >( survey->question( i ) );
            ui->questionsLayout->addWidget( new OpenQuestionWidget( oq ) );
        }
        else // close
        {
            ui->questionsLayout->addWidget( new CloseQuestionWidget( cq ) );
        }
    }

    ui->m_pBackButton->setVisible( true );
    ui->m_pNextButton->setText( "Zatwierdź" );
    m_eCurrentPage = FILL;
    ui->stackedWidget->setCurrentIndex( m_eCurrentPage );
}

void CompleteSurveyDialog::next()
{
    switch( m_eCurrentPage )
    {
    case SURVEY:
        showFillPage();
        break;
    case FILL:
        QMessageBox::information( this, "Sukces", "Ankieta została wypełniona poprawnie" );
        accept();
        break;
    }
}

void CompleteSurveyDialog::back()
{
    switch( m_eCurrentPage )
    {
    case SURVEY:
        break;
    case FILL:
        showSurveyPage();
        break;
    }
}
