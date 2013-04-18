#include "add-question-dialog.h"
#include "ui_add-question-dialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QAction>
#include <QStringListModel>
#include <QMenu>

#include "edit-word-dialog.h"

AddQuestionDialog::AddQuestionDialog( QWidget * parent ):
    QDialog( parent ),
    ui( new Ui::AddQuestionDialog )
{
    ui->setupUi( this );

    initialize();
    initializeCategoryComboBox();
    initializeWordComboBox();

    createConnections();
}

AddQuestionDialog::~AddQuestionDialog()
{
    delete ui;
}

void AddQuestionDialog::initialize()
{
    ui->m_closedQuestionRadioButton->setChecked( false );
    ui->m_openedQuestionRadioButton->setChecked( true );

    ui->m_addedWordListView->setModel( new QStringListModel( this ) );
    ui->m_answersListView->setModel( new QStringListModel( this ) );

    ui->m_questionTypeStackedWidget->setCurrentIndex( 0 );
}

void AddQuestionDialog::createConnections()
{
    connect(ui->m_closedQuestionRadioButton,SIGNAL(toggled(bool)),this,SLOT(onQuestionTypeChange(bool)));
    connect(ui->m_anulujButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->m_addCustomWordButton,SIGNAL(clicked()),this,SLOT(addCustomWord()));
    connect(ui->m_deleteMarkedButton,SIGNAL(clicked()),this,SLOT(deleteWordFromList()));
    connect(ui->m_addedWordListView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(showEditWordDialog(QModelIndex)));
    connect(ui->m_addStoredWordButton,SIGNAL(clicked()),this,SLOT(addPredefinedWord()));
    connect(ui->m_addQuestionButton,SIGNAL(clicked()),this,SLOT(addQuestion()));
    connect(ui->m_answersListView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showMenu(QPoint)));
}

void AddQuestionDialog::deleteWordFromList()
{
    ui->m_addedWordListView->model()->removeRow( ui->m_addedWordListView->currentIndex().row() );
}

void AddQuestionDialog::onQuestionTypeChange( bool b )
{
    if( b == true )
    {
        ui->m_questionTypeStackedWidget->setCurrentIndex( CLOSED );
    }
    else
    {
        ui->m_questionTypeStackedWidget->setCurrentIndex( OPENED );
    }
}

void AddQuestionDialog::initializeCategoryComboBox()
{
    ui->m_categoryComboBox->addItem( "Inne" );
    ui->m_categoryComboBox->addItem( "Jakościowe" );
    ui->m_categoryComboBox->addItem( "Podchwytliwe" );
    ui->m_categoryComboBox->addItem( "Zaskakujące" );
    ui->m_categoryComboBox->addItem( "Interesujące" );
}

void AddQuestionDialog::initializeWordComboBox()
{
    ui->m_wordComboBox->addItem( "dobry <0.3>" );
    ui->m_wordComboBox->addItem( "ciekawy <0.6>" );
    ui->m_wordComboBox->addItem( "interesujący <0.9>" );
    ui->m_wordComboBox->addItem( "wspaniały <0.4>" );
    ui->m_wordComboBox->addItem( "nudny <-0.3>" );
}

void AddQuestionDialog::addCustomWord()
{
    if( ui->m_newWordStringLineEdit->text().isEmpty() == true )
    {
        QMessageBox::warning( this, "Brak danych", "Nie można dodać pustego wyrazu" );

        return;
    }

    QStringListModel * model = qobject_cast<QStringListModel*>(ui->m_addedWordListView->model());

    QString string = ui->m_newWordStringLineEdit->text() + " <" + ui->m_newWordWeightSpinBox->text() + ">";

    if( wasAdded( string ) == true )
    {
        QMessageBox::warning( this, "Duplikat", "Taki wyraz istnieje już w liście" );

        return;
    }

    model->setStringList( model->stringList() << string );
}

void AddQuestionDialog::showEditWordDialog( QModelIndex index )
{
    EditWordDialog eWD( ui->m_addedWordListView->model()->data( index ).toString() );
    connect(&eWD,SIGNAL(update(QString)),this,SLOT(onListViewUpdate(QString)));

    eWD.exec();
}

void AddQuestionDialog::onListViewUpdate( const QString & string )
{
    if( wasAdded( string ) == true )
    {
        QMessageBox::warning( this, "Duplikat", "Taki wyraz istnieje już w liście" );

        return;
    }

    ui->m_addedWordListView->model()->setData( ui->m_addedWordListView->currentIndex(), string );
}

bool AddQuestionDialog::wasAdded( const QString & element )
{
    QStringListModel * model = qobject_cast<QStringListModel*>( ui->m_addedWordListView->model() );

    for( int i = 0 ; i < model->stringList().size() ; i++ )
    {
        if( element.left( element.indexOf( "<" ) - 1 ) == model->stringList().at( i ).left( model->stringList().at( i ).indexOf( "<" ) - 1 ) )
        {
            return true;
        }
    }

    return false;
}

void AddQuestionDialog::addPredefinedWord()
{
    QString string = ui->m_wordComboBox->currentText();

    if( wasAdded( string ) == true )
    {
        QMessageBox::warning( this, "Duplikat", "Taki wyraz istnieje już w liście" );

        return;
    }

    QStringListModel * model = qobject_cast<QStringListModel*>(ui->m_addedWordListView->model());

    model->setStringList( model->stringList() << string );
}

void AddQuestionDialog::addQuestion()
{
    if( ui->m_questionTextTextEdit->toPlainText().isEmpty() == true )
    {
        QMessageBox::warning( this, "Dodawanie pytania", "Nie można dodać pytania bez treści" );

        return;
    }

    if( ui->m_closedQuestionRadioButton->isChecked() == true )
    {
        QStringListModel * model = qobject_cast<QStringListModel*>( ui->m_answersListView->model() );

        if( model->stringList().size() < 2 )
        {
            QMessageBox::warning( this, "Dodawanie pytania", "Musisz dodać co najmniej dwie odpowiedzi zamknięte" );

            return;
        }
    }

    QMessageBox::warning( this, "Dodawanie pytania", "Pytanie zostało dodane pomyślnie" );

    accept();
}

void AddQuestionDialog::showMenu( QPoint )
{
    QMenu menu;

    QAction * addAction = new QAction( "Dodaj odpowiedź", & menu );
    QAction * deleteAction = new QAction( "Usuń odpowiedź", & menu );

    connect(addAction,SIGNAL(triggered()),this,SLOT(addAnswer()));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(deleteAnswer()));

    menu.addAction( addAction );
    menu.addAction( deleteAction );
    menu.exec( QCursor::pos() );
}

void AddQuestionDialog::addAnswer()
{
    QStringListModel * model = qobject_cast<QStringListModel*>(ui->m_answersListView->model());

    model->setStringList( model->stringList() << "Nowa odpowiedź" );
}

void AddQuestionDialog::deleteAnswer()
{
    ui->m_answersListView->model()->removeRow( ui->m_answersListView->currentIndex().row() );
}
