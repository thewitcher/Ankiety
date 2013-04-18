#ifndef EDITWORDDIALOG_H
#define EDITWORDDIALOG_H

#include <QDialog>

namespace Ui { class EditWordDialog; }

class EditWordDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditWordDialog( const QString & element, QWidget * parent = 0 );
    ~EditWordDialog();
    
private:
    Ui::EditWordDialog * ui;

private slots:
    void onUpdate();

signals:
    void update(QString);
};

#endif // EDITWORDDIALOG_H
