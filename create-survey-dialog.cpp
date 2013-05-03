#include <QMessageBox>
#include <QDebug>

#include "create-survey-dialog.h"
#include "ui_create-survey-dialog.h"
#include "add-question-dialog.h"

#include "Busines_classes/question-database.h"
#include "Busines_classes/question.h"
#include "Busines_classes/survey-database.h"

CreateSurveyDialog::CreateSurveyDialog( QWidget * parent ):
    QDialog( parent ),
    ui( new Ui::CreateSurveyDialog ),
    m_pSurvey( new Survey )
{
    ui->setupUi(this);

    QuestionDatabase::createFakeData();

    createConnections();

    setSurveyNamePage();
}

CreateSurveyDialog::~CreateSurveyDialog()
{
    delete ui;
    delete m_pSurvey;
}

void CreateSurveyDialog::createConnections()
{
    connect(ui->m_pAnulujButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->m_pNextButton,SIGNAL(clicked()),this,SLOT(next()));
    connect(ui->m_pBackButton,SIGNAL(clicked()),this,SLOT(back()));
    connect(ui->m_pFinishButton,SIGNAL(clicked()),this,SLOT(setResultPage()));
    connect(ui->m_pDeleteButton,SIGNAL(clicked()),this,SLOT(deleteQuestion()));

    connect(ui->m_pQuestionComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(fillQuestionLabel(int)));
}

void CreateSurveyDialog::setSurveyNamePage()
{
    ui->m_pBackButton->setVisible( false );
    m_eCurrentPage = SURVEY_NAME;
    ui->stackedWidget->setCurrentIndex( m_eCurrentPage );
}

void CreateSurveyDialog::setMainPage()
{
    ui->m_pBackButton->setVisible( true );
    m_eCurrentPage = MAIN;
    ui->stackedWidget->setCurrentIndex( m_eCurrentPage );
}

void CreateSurveyDialog::setCategoryPage()
{
    ui->m_pBackButton->setVisible( true );
    ui->m_pNextButton->setText( "Dalej" );
    m_eCurrentPage = CATEGORY;
    ui->stackedWidget->setCurrentIndex( m_eCurrentPage );

    QSet< QString > categories = QuestionDatabase::categoryList();

    ui->m_pCategoryComboBox->clear();
    for( QSet< QString >::iterator it = categories.begin() ; it != categories.end() ; it++ )
    {
        ui->m_pCategoryComboBox->addItem( * it );
    }
}

void CreateSurveyDialog::setQuestionListPage()
{
    ui->m_pBackButton->setVisible( true );
    ui->m_pNextButton->setText( "Dodaj pytanie do ankiety" );
    m_eCurrentPage = QUESTION_LIST;
    ui->stackedWidget->setCurrentIndex( m_eCurrentPage );

    ui->m_pCategoryLabel->setText( "Wybierz pytanie z kategorii: " + ui->m_pCategoryComboBox->currentText() );

    QVector< Question * > questions = QuestionDatabase::questionsFromCategory( ui->m_pCategoryComboBox->currentText() );

    ui->m_pQuestionComboBox->clear();

    for( QVector< Question * >::iterator it = questions.begin() ; it != questions.end() ; it++ )
    {
        ui->m_pQuestionComboBox->addItem( ( * it )->questionText(), ( * it )->id() );
    }
}

void CreateSurveyDialog::next()
{
    switch( m_eCurrentPage )
    {
    case SURVEY_NAME:
        if( ui->m_pSurveyNameLineEdit->text().isEmpty() == true )
        {
            QMessageBox::warning( this, "Ostrzeżenie", "Nie dodałeś nazwy ankiety" );
        }
        else
        {
            setMainPage();
            m_pSurvey->setSurveyName( ui->m_pSurveyNameLineEdit->text() );
        }
        break;
    case MAIN:
        if( ui->m_pExistingQuestionRadioButton->isChecked() == true )
        {
            setCategoryPage();
        }
        else
        {
            addNewQuestion();
        }
        break;
    case CATEGORY:
        setQuestionListPage();
        break;
    case QUESTION_LIST:
        addQuestionToSurvey();
        break;
    case RESULT:
        QMessageBox::information( this, "Sukces", "Udało się dodać ankietę" );
        SurveyDatabase::addSurvey( m_pSurvey );
        m_pSurvey = NULL;
        accept();
        break;
    }
}

void CreateSurveyDialog::back()
{
    switch( m_eCurrentPage )
    {
    case SURVEY_NAME:
        break;
    case MAIN:
        setSurveyNamePage();
        break;
    case CATEGORY:
        setMainPage();
        break;
    case QUESTION_LIST:
        setCategoryPage();
        break;
    case RESULT:
        setQuestionListPage();
        break;
    }
}

void CreateSurveyDialog::addNewQuestion()
{
    AddQuestionDialog aQD;

    aQD.exec();
}

void CreateSurveyDialog::addQuestionToSurvey()
{
    m_pSurvey->addQuestions( QuestionDatabase::questionWithId( ui->m_pQuestionComboBox->itemData( ui->m_pQuestionComboBox->currentIndex(), Qt::UserRole ).toInt() ) );

    QMessageBox::information( this, "Sukces", "Udało się dodać pytanie" );
}

void CreateSurveyDialog::fillQuestionLabel( int index )
{
    Question * question = QuestionDatabase::questionWithId( ui->m_pQuestionComboBox->itemData( index, Qt::UserRole ).toInt() );
    QStringList data = question->data();

    ui->m_pAnswersLabel->clear();

    QString textForLabel;
    for( int i = 0 ; i < data.size() ; i++ )
    {
        textForLabel.append( data.at( i ) + "<br>" );
    }

    ui->m_pAnswersLabel->setText( textForLabel );
}

void CreateSurveyDialog::setResultPage()
{
    ui->m_pBackButton->setVisible( true );
    ui->m_pNextButton->setText( "Zatwierdź" );
    m_eCurrentPage = RESULT;
    ui->stackedWidget->setCurrentIndex( m_eCurrentPage );

    ui->m_pAddedQuestionListWidget->clear();
    for( int i = 0 ; i < m_pSurvey->questionsCount() ; i++ )
    {
        ui->m_pAddedQuestionListWidget->addItem( m_pSurvey->question( i )->questionText() );
    }
}

void CreateSurveyDialog::deleteQuestion()
{
    if( ui->m_pAddedQuestionListWidget->selectedItems().size() < 1 )
    {
        QMessageBox::warning( this, "Ostrzeżenie", "Nie zanznaczono pozycji do edycji" );

        return;
    }

    m_pSurvey->deleteQuestion( ui->m_pAddedQuestionListWidget->currentRow() );
    ui->m_pAddedQuestionListWidget->takeItem( ui->m_pAddedQuestionListWidget->currentRow() );
}
