#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QWidget>
#include <QDialog>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QDateTime>
#include <QGroupBox>
#include <QCheckBox>
#include <QListWidget>
#include <QPushButton>
#include <QSpacerItem>
#include <QString>
#include<QMessageBox>
#include <QMouseEvent>
#include<QTextEdit>
#include<QVector>

class QWidget;
class QFileInfo;
class QTabWidget;
class QDialogButtonBox;

//期刊选项卡
class PeriodicalTab : public QWidget
{
        Q_OBJECT
public:
        PeriodicalTab(QWidget *parent = 0);
private slots:
     void check_add();
private:
QLineEdit *authorEdit;
QLineEdit *titleEdit;
QLineEdit *periodEdit;
QLineEdit *publishEdit;
QLineEdit *volumeEdit;
QLineEdit *pcountEdit;
QLineEdit *pageEdit;
};

//报纸
class NewspaperTab : public QWidget
{
        Q_OBJECT

public:
        NewspaperTab(QWidget *parent = 0);
private slots:
     void check_add();
private:
     QLineEdit *authorEdit;
     QLineEdit *titleEdit;
     QLineEdit *nameEdit;
     QLineEdit *publishEdit;
     QLineEdit *orderEdit;

};

//图书
class BookTab : public QWidget
{
        Q_OBJECT

public:
        BookTab( QWidget *parent = 0);
private:
        QLineEdit *authorEdit;
        QLineEdit *titleEdit;
        QLineEdit *orderEdit;
        QLineEdit *birthcomEdit;
        QLineEdit *birthlocEdit;
        QLineEdit *publishEdit;
        QLineEdit *pageEdit;
private slots:
     void check_add();
};
//会议集选项卡
class MeetingTab : public QWidget
{
        Q_OBJECT

public:
        MeetingTab(QWidget *parent = 0);
private slots:
     void check_add();
private:
      QLineEdit *authorEdit;
      QLineEdit *titleEdit;
      QLineEdit *MainEdit;
      QLineEdit *setnameEdit;
      QLineEdit *birthcomEdit;
      QLineEdit *birthlocEdit;
      QLineEdit *publishEdit;
      QLineEdit *pageEdit;
};

//学术论文
class AcademicTab : public QWidget
{
        Q_OBJECT

public:
        AcademicTab(QWidget *parent = 0);
private slots:
     void check_add();
private:
      QLineEdit *authorEdit;
      QLineEdit *titleEdit;
      QLineEdit *preservelocEdit;
      QLineEdit *preservecomEdit;
      QLineEdit *yearEdit;

};
//网络文献

class NetworkTab : public QWidget
{
        Q_OBJECT

public:
      NetworkTab( QWidget *parent = 0);
private slots:
     void check_add();
private:
      QLineEdit *authorEdit;
      QLineEdit *titleEdit;
      QLineEdit *publishEdit;
      QLineEdit *pathEdit;
      QLineEdit *yearEdit;

};
//报告
class ReportTab : public QWidget
{
        Q_OBJECT
public:
       ReportTab( QWidget *parent = 0);
private slots:
     void check_add();
private:
      QLineEdit *authorEdit;
      QLineEdit *titleEdit;
      QLineEdit *reportlocEdit;
      QLineEdit *reportcomEdit;
      QLineEdit *yearEdit;

};
class myLabel : public QLabel
{
    Q_OBJECT
public:
    myLabel(const QString &text, QWidget *parent=0);
signals:
    // 鼠标单击信号
    void clicked();//IMClickLabel* label);

protected:
    // 鼠标单击事件
    void mouseReleaseEvent(QMouseEvent *);
public slots:

};
//自定义Tab对话框
class Dialog:public QDialog
{
    Q_OBJECT
public:
  Dialog(QWidget *parent = 0);

private:
  QTabWidget *tabWidget;
  QDialogButtonBox *buttonBox;
  myLabel  *dropLabel;
  QLineEdit *deindex;
private slots:
   void dropresult();
   void deleteitem();
   void about();
};


void MessageBox(QString msg);
void updatestatus();
void updatetext();

#endif

