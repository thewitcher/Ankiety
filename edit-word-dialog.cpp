#include "edit-word-dialog.h"
#include "ui_editworddialog.h"

#include <QMessageBox>
#include <QDebug>

EditWordDialog::EditWordDialog( const QString & element, QWidget * parent ):
    QDialog( parent ),
    ui( new Ui::EditWordDialog )
{
    ui->setupUi( this );

    ui->m_newWordStringLineEdit->setText( element.left( element.indexOf( "<" ) - 1 ) );

    QString weight = element.right( 5 );
    weight.chop( 1 );

    qDebug() << "str: " << element;
    qDebug() << "-" << weight << "-";

    ui->m_newWordWeightSpinBox->setValue( weight.toDouble() );

    connect(ui->m_anulujButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->m_updateButton,SIGNAL(clicked()),this,SLOT(onUpdate()));
}

EditWordDialog::~EditWordDialog()
{
    delete ui;
}

void EditWordDialog::onUpdate()
{
    if( ui->m_newWordStringLineEdit->text().isEmpty() == true )
    {
        QMessageBox::warning( this, "Brak danych", "Nie można dodać pustego wyrazu" );
        return;
    }

    emit update( ui->m_newWordStringLineEdit->text() + " <" + ui->m_newWordWeightSpinBox->text() + ">" );

    accept();
}
