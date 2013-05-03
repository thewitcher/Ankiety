#include "add-question-dialog.h"
#include "ui_add-question-dialog.h"

#include <QDebug>
#include <QMessageBox>

#include "Busines_classes/open-question.h"
#include "Busines_classes/close-question.h"
#include "Busines_classes/question-database.h"

AddQuestionDialog::AddQuestionDialog( QWidget * parent ):
    QDialog( parent ),
    ui( new Ui::AddQuestionDialog ),
    m_pQuestion( NULL ),
    m_iRowToEditInAnswerListWidget( -1 )
{
    ui->setupUi( this );

    initialize();
    createConnections();
}

AddQuestionDialog::~AddQuestionDialog()
{
    delete ui;
    delete m_pQuestion;
}

void AddQuestionDialog::initialize()
{
    m_eQuestionType = OPEN_QUESTION;
    ui->m_pOpenQuestionRadioButton->setChecked( true );
    m_pQuestion = new OpenQuestion;

    setTypePage();
}

void AddQuestionDialog::createConnections()
{
    connect(ui->m_pAnulujButton,SIGNAL(clicked()),this,SLOT(exit()));
    connect(ui->m_pNextButton,SIGNAL(clicked()),this,SLOT(next()));
    connect(ui->m_pBackButton,SIGNAL(clicked()),this,SLOT(back()));
    connect(ui->m_pCloseQuestionRadioButton,SIGNAL(toggled(bool)),this,SLOT(onTypeChange(bool)));
    connect(ui->m_pSummarizeButton,SIGNAL(clicked()),this,SLOT(setResultPage()));
    connect(ui->m_pRemoveButton,SIGNAL(clicked()),this,SLOT(deleteFromAnswerListWidget()));
    connect(ui->m_pEditButton,SIGNAL(clicked()),this,SLOT(editAnswerFromListWidget()));
}

void AddQuestionDialog::onTypeChange( bool closeQuestion )
{
    if( closeQuestion == true )
    {
        m_eQuestionType = CLOSE_QUESTION;

        if( m_pQuestion != NULL )
        {
            delete m_pQuestion;
        }
        m_pQuestion = new CloseQuestion;
    }
    else
    {
        m_eQuestionType = OPEN_QUESTION;

        if( m_pQuestion != NULL )
        {
            delete m_pQuestion;
        }
        m_pQuestion = new OpenQuestion;
    }
}

void AddQuestionDialog::exit()
{
    reject();
}

void AddQuestionDialog::next()
{
    switch( m_eCurrentPage )
    {
    case TYPE:
        setCategoryPage();
        break;
    case CATEGORY:
        setTextPage();
        m_pQuestion->setCategory( ui->m_pCategoryComboBox->currentText() );
        break;
    case TEXT:
        if( ui->m_pQuestionTextEdit->toPlainText().isEmpty() == false )
        {
            m_pQuestion->setQuestionText( ui->m_pQuestionTextEdit->toPlainText() );

            if( m_eQuestionType == OPEN_QUESTION )
            {
                setKeyWordPage();
            }
            else if( m_eQuestionType == CLOSE_QUESTION )
            {
                setAnswerPage();
            }
        }
        else
        {
            QMessageBox::warning( this, "Ostrzeżenie", "Aby przejść dalej należy dodać treść pytania" );
        }
        break;
    case ANSWER:
        if( ui->m_pAnswerTextEdit->toPlainText().isEmpty() == false )
        {
            addAnswer();
        }
        else
        {
            QMessageBox::warning( this, "Ostrzeżenie", "Aby przejść dalej należy dodać treść odpowiedzi" );
        }
        break;
    case KEY_WORD:
        if( ui->m_pKeyWordLineEdit->text().isEmpty() == false )
        {
            addKeyWord();
        }
        else
        {
            QMessageBox::warning( this, "Ostrzeżenie", "Aby przejść dalej należy dodać treść odpowiedzi" );
        }
        break;
    case RESULT:
        if( m_eQuestionType == OPEN_QUESTION )
        {
            QuestionDatabase::addQuestion( m_pQuestion );
            m_pQuestion = NULL;
            QMessageBox::information( this, "Sukcses", "Pytanie zostało dodane pomyślnie" );
            accept();
        }
        else if( m_eQuestionType == CLOSE_QUESTION )
        {
            CloseQuestion * closeQuestion = dynamic_cast< CloseQuestion * >( m_pQuestion );

            if( closeQuestion != NULL )
            {
                if( closeQuestion->hasAtLestTwoAnswers() == false )
                {
                    QMessageBox::warning( this, "Ostrzeżenie", "Aby przejść do podsumowania należy dodać co najmniej dwie odpowiedzi zamknięte" );
                    return;
                }
                else
                {
                    QuestionDatabase::addQuestion( m_pQuestion );
                    m_pQuestion = NULL;
                    QMessageBox::information( this, "Sukcses", "Pytanie zostało dodane pomyślnie" );
                    accept();
                }
            }
        }
        break;
    }
}

void AddQuestionDialog::back()
{
    switch( m_eCurrentPage )
    {
    case TYPE:
        break;
    case CATEGORY:
        setTypePage();
        break;
    case TEXT:
        setCategoryPage();
        break;
    case ANSWER:
    case KEY_WORD:
        setTextPage();
        break;
    case RESULT:
        setTextPage();
        break;
    }
}

void AddQuestionDialog::setTypePage()
{
    ui->m_pBackButton->setVisible( false );
    ui->m_pNextButton->setVisible( true );
    ui->m_pNextButton->setText( "Przejdź do wyboru kategorii" );
    ui->m_pQuestionTypeStackedWidget->setCurrentIndex( TYPE );
    m_eCurrentPage = TYPE;
}

void AddQuestionDialog::setCategoryPage()
{
    getCategoryFromDB();

    ui->m_pBackButton->setVisible( true );
    ui->m_pBackButton->setText( "Wróć do wyboru typu pytania" );
    ui->m_pNextButton->setVisible( true );
    ui->m_pNextButton->setText( "Przejdź do dodawania treści pytania" );
    ui->m_pQuestionTypeStackedWidget->setCurrentIndex( CATEGORY );
    m_eCurrentPage = CATEGORY;
}

void AddQuestionDialog::setTextPage()
{
    ui->m_pBackButton->setVisible( true );
    ui->m_pBackButton->setText( "Wróć do wyboru kategorii" );
    ui->m_pNextButton->setVisible( true );

    if( m_eQuestionType == OPEN_QUESTION )
    {
        ui->m_pNextButton->setText( "Dodaj słowa kluczowe" );
    }
    else if( m_eQuestionType == CLOSE_QUESTION )
    {
        ui->m_pNextButton->setText( "Dodaj odpowiedzi" );
    }

    ui->m_pQuestionTypeStackedWidget->setCurrentIndex( TEXT );
    m_eCurrentPage = TEXT;
}

void AddQuestionDialog::setAnswerPage()
{
    ui->m_pBackButton->setVisible( true );
    ui->m_pBackButton->setText( "Wróć do dodawania treści pytania" );
    ui->m_pNextButton->setVisible( true );
    ui->m_pNextButton->setText( "Dodaj" );
    ui->m_pQuestionTypeStackedWidget->setCurrentIndex( ANSWER );
    m_eCurrentPage = ANSWER;
}

void AddQuestionDialog::setKeyWordPage()
{
    ui->m_pBackButton->setVisible( true );
    ui->m_pBackButton->setText( "Wróć do dodawania treści pytania" );
    ui->m_pNextButton->setVisible( true );
    ui->m_pNextButton->setText( "Dodaj kolejne słowo kluczowe" );
    ui->m_pQuestionTypeStackedWidget->setCurrentIndex( KEY_WORD );
    m_eCurrentPage = KEY_WORD;
}

void AddQuestionDialog::setResultPage()
{
    if( ui->m_pQuestionTextEdit->toPlainText().isEmpty() == true )
    {
        QMessageBox::warning( this, "Ostrzeżenie", "Aby przejść dalej należy dodać treść pytania" );

        return;
    }

    ui->m_pBackButton->setVisible( true );
    ui->m_pBackButton->setText( "Wróć do dodawania treści pytania" );
    ui->m_pNextButton->setVisible( true );
    ui->m_pQuestionTypeStackedWidget->setCurrentIndex( RESULT );
    m_eCurrentPage = RESULT;

    if( m_eQuestionType == OPEN_QUESTION )
    {
        resultsForOpenQuestion();
    }
    else if( m_eQuestionType == CLOSE_QUESTION )
    {
        resultsForCloseQuestion();
    }
}

void AddQuestionDialog::getCategoryFromDB()
{
    ui->m_pCategoryComboBox->addItem( "Inne" );
    ui->m_pCategoryComboBox->addItem( "Naukowe" );
    ui->m_pCategoryComboBox->addItem( "Zabawne" );
}

void AddQuestionDialog::addAnswer()
{
    CloseQuestion * closeQuestion = dynamic_cast< CloseQuestion * >( m_pQuestion );

    closeQuestion->addAnswer( ui->m_pAnswerTextEdit->toPlainText(), m_iRowToEditInAnswerListWidget );

    ui->m_pAnswerTextEdit->clear();
}

void AddQuestionDialog::addKeyWord()
{
    OpenQuestion * openQuestion = dynamic_cast< OpenQuestion * >( m_pQuestion );

    openQuestion->addKeyWord( ui->m_pKeyWordLineEdit->text(), ui->m_pKeyWordWeightSpinBox->value(), m_iRowToEditInAnswerListWidget );

    ui->m_pKeyWordLineEdit->clear();
    ui->m_pKeyWordWeightSpinBox->setValue( 0.0 );
}

void AddQuestionDialog::resultsForCloseQuestion()
{
    resultsForBoth();

    CloseQuestion * closeQuestion = dynamic_cast< CloseQuestion * >( m_pQuestion );

    for( int answer = 0 ; answer < closeQuestion->answerCount() ; answer++ )
    {
        ui->m_pAnswersListWidget->addItem( closeQuestion->getAnswer( answer ).answerText() );
    }
}

void AddQuestionDialog::resultsForOpenQuestion()
{
    resultsForBoth();

    OpenQuestion * openQuestion = dynamic_cast< OpenQuestion * >( m_pQuestion );

    for( int key = 0 ; key < openQuestion->keyWordCount() ; key++ )
    {
        ui->m_pAnswersListWidget->addItem( openQuestion->getKeyWord( key ).keyWord() + " <" + QString::number( openQuestion->getKeyWord( key ).weight() ) + ">" );
    }
}

void AddQuestionDialog::resultsForBoth()
{
    ui->m_pAnswersListWidget->clear();
    m_pQuestion->setQuestionText( ui->m_pQuestionTextEdit->toPlainText() );
    m_pQuestion->setCategory( ui->m_pCategoryComboBox->currentText() );

    ui->m_pQuestionTextLabel->setText( "Treść pytania: " + m_pQuestion->questionText() );
    ui->m_pCategoryLabel->setText( "Kategoria pytania: " + m_pQuestion->category() );

    ui->m_pNextButton->setText( "Dodaj pytanie" );
}

void AddQuestionDialog::deleteFromAnswerListWidget()
{
    if( ui->m_pAnswersListWidget->selectedItems().size() < 1 )
    {
        QMessageBox::warning( this, "Ostrzeżenie", "Nie zanznaczono pozycji do edycji" );

        return;
    }

    if( m_eQuestionType == OPEN_QUESTION )
    {
        OpenQuestion * openQuestion = dynamic_cast< OpenQuestion * >( m_pQuestion );
        openQuestion->deleteKeyWord( ui->m_pAnswersListWidget->currentRow() );

    }
    else if( m_eQuestionType == CLOSE_QUESTION )
    {
        CloseQuestion * closeQuestion = dynamic_cast< CloseQuestion * >( m_pQuestion );
        closeQuestion->deleteAnswer( ui->m_pAnswersListWidget->currentRow() );
    }

    ui->m_pAnswersListWidget->takeItem( ui->m_pAnswersListWidget->currentRow() );
}

void AddQuestionDialog::editAnswerFromListWidget()
{
    if( ui->m_pAnswersListWidget->selectedItems().size() < 1 )
    {
        QMessageBox::warning( this, "Ostrzeżenie", "Nie zanznaczono pozycji do edycji" );

        return;
    }

    m_iRowToEditInAnswerListWidget = ui->m_pAnswersListWidget->currentRow();

    if( m_eQuestionType == OPEN_QUESTION )
    {
        OpenQuestion * openQuestion = dynamic_cast< OpenQuestion * >( m_pQuestion );

        ui->m_pKeyWordLineEdit->setText( openQuestion->getKeyWord( ui->m_pAnswersListWidget->currentRow() ).keyWord() );
        ui->m_pKeyWordWeightSpinBox->setValue( openQuestion->getKeyWord( ui->m_pAnswersListWidget->currentRow() ).weight() );
        setKeyWordPage();
    }
    else if( m_eQuestionType == CLOSE_QUESTION )
    {
        ui->m_pAnswerTextEdit->setText( ui->m_pAnswersListWidget->currentItem()->text() );
        setAnswerPage();
    }
}
