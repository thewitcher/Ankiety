#ifndef ADDQUESTIONDIALOG_H
#define ADDQUESTIONDIALOG_H

#include <QDialog>
#include <QModelIndex>

namespace Ui { class AddQuestionDialog; }

class AddQuestionDialog : public QDialog
{

    Q_OBJECT
    
public:
    enum TYPE { OPENED, CLOSED };

    explicit AddQuestionDialog( QWidget * parent = 0 );
    ~AddQuestionDialog();
    
private:
    Ui::AddQuestionDialog * ui;

    void initialize();
    void initializeCategoryComboBox();
    void initializeWordComboBox();
    void createConnections();
    bool wasAdded( const QString & element );

private slots:
    void onQuestionTypeChange( bool b );
    void addCustomWord();
    void addPredefinedWord();
    void deleteWordFromList();
    void showEditWordDialog( QModelIndex index );
    void onListViewUpdate( const QString & string );
    void addQuestion();
    void showMenu( QPoint );
    void addAnswer();
    void deleteAnswer();
};

#endif // ADDQUESTIONDIALOG_H
