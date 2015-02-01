
#include "dialog.h"
#include "ui_dialog.h"

//定义全局变量
QLabel *countLabel;
QTextEdit *textEdt;
QVector<QString> textresult;
int count=0;

Dialog::Dialog(QWidget *parent):QDialog(parent)
{
  //top
    QGridLayout *topgrid=new QGridLayout;
    topgrid->setColumnStretch(0, 2);
    topgrid->setColumnStretch(1, 6);
    topgrid->setColumnStretch(2, 1);
    QLabel *warn=new QLabel("添加参考文献<font color=red>(*为必填项)</font>");
    myLabel *feedback=new myLabel("<font color=blue><u>问题反馈</u></font>");
    feedback->setCursor(Qt::PointingHandCursor);
    topgrid->addWidget(warn,0,0);
    topgrid->addWidget(feedback,0,2);
    //Tab
  tabWidget=new QTabWidget;
  tabWidget->addTab(new PeriodicalTab(),trUtf8("期刊"));
  tabWidget->addTab(new NewspaperTab(),trUtf8("报纸"));
  tabWidget->addTab(new BookTab(),trUtf8("图书"));
  tabWidget->addTab(new MeetingTab(),trUtf8("会议集/论文集"));
  tabWidget->addTab(new AcademicTab(),trUtf8("学位论文"));
  tabWidget->addTab(new ReportTab(),trUtf8("报告"));
  tabWidget->addTab(new NetworkTab(),trUtf8("网络文献"));
  tabWidget->setFixedSize(600,250);
  //中间
  QGridLayout *ingrid=new QGridLayout;
  countLabel=new QLabel("已添加<font color=green>0</font>个文献");
  dropLabel=new myLabel("<font color=blue><u>清空</u></font>");
  dropLabel->setCursor(Qt::PointingHandCursor);
  QPushButton *deletebutton=new QPushButton(trUtf8("删除"));
  deletebutton->setCursor(Qt::PointingHandCursor);
  deindex=new QLineEdit;
  deindex->setFixedWidth(30);

  ingrid->setColumnStretch(0, 1);
  ingrid->setColumnStretch(1, 1);
  ingrid->setColumnStretch(2, 5);
  ingrid->setColumnStretch(3, 2);
  ingrid->setColumnStretch(4, 1);
  ingrid->addWidget(countLabel,0,0);
  ingrid->addWidget(dropLabel,0,1);
  ingrid->addWidget(deindex,0,4);
  ingrid->addWidget(deletebutton,0,3);
  //下面
  textEdt= new QTextEdit;
  textEdt->setReadOnly(true);
  QVBoxLayout *mainLayout=new QVBoxLayout;
  mainLayout->addLayout(topgrid);
  mainLayout->addWidget(tabWidget);
  mainLayout->addLayout(ingrid);
  mainLayout->addWidget(textEdt);
  Dialog::setLayout(mainLayout);
  connect(dropLabel,SIGNAL(clicked()),this,SLOT(dropresult()));
  connect(feedback,SIGNAL(clicked()),this,SLOT(about()));
  connect(deletebutton,SIGNAL(clicked()),this,SLOT(deleteitem()));
  setWindowTitle(trUtf8("参考文献格式工具"));
  setWindowFlags(windowFlags()|Qt::WindowMinimizeButtonHint );
  setFixedSize(620,480);
}
void Dialog::about()
{
   QString str="  该工具根据原青岛大学同学使用C#写成的参考文献生成器改进得到,\r\n基本外观依照原软件,由C++/Qt全部重写。修改和加入了部分功能.\r\n     如有问题和意见,联系QQ:805356546";
   QMessageBox::about(NULL, "关于和问题反馈",str);
}

void Dialog::deleteitem()
{
 //int detext=(deindex->text().isEmpty())?count:(deindex->text().toInt());
   int detext=deindex->text().toInt();
  if(detext<=0||detext>count)
  {
   QMessageBox::critical(NULL, "输入错误", "输入数字不在范围内",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
  }else{
      QString str="确定要删除第"+QString::number(detext)+"篇文献?";
      QMessageBox message(QMessageBox::Question,"检查",str,QMessageBox::Ok|QMessageBox::Cancel,NULL);
      if(message.exec()==QMessageBox::Ok)
      {
        textresult.removeAt(detext-1);
       // textresult.resize(textresult.size()-1);
        count--;
        updatetext();
      }

  }
}
void updatetext()
{
  QString text="";
  for (int i = 0; i < textresult.size(); ++i)
  {
   text+="["+QString::number(i+1)+"] "+textresult[i];
  }
  textEdt->setText(text);
  updatestatus();
}

//清空
void Dialog::dropresult()
{
   QMessageBox message(QMessageBox::Question,"检查",tr("确定要清空?"),QMessageBox::Ok|QMessageBox::Cancel,NULL);
   switch(message.exec())
   {
      case QMessageBox::Ok:
      count=1;
      countLabel->setText("已添加<font color=green>0</font>个文献");
      textresult.clear();
      textEdt->setText("");
      break;
      case QMessageBox::Cancel:
      break;
   }
}
//期刊面板实现
PeriodicalTab::PeriodicalTab(QWidget *parent)
  :QWidget(parent)
{

    QLabel *authorLabel=new QLabel(trUtf8("*作者"));
    authorEdit =new QLineEdit();    // 作者
    QLabel *titleLabel=new QLabel(trUtf8("*题目"));
    titleEdit = new QLineEdit();          // 题目
    QLabel *periodLabel=new QLabel(trUtf8("*期刊名"));
    periodEdit = new QLineEdit();       // 期刊名
    QLabel *publishLabel=new QLabel(trUtf8("*出版年份"));
    publishEdit = new QLineEdit();   // 出版年份
    QLabel *volumeLabel=new QLabel(trUtf8(" 卷号"));
    volumeEdit = new QLineEdit();         // 卷号
    QLabel *pcountLabel=new QLabel(trUtf8("*期数"));
    pcountEdit = new QLineEdit();         // 期数
    QLabel *pageLabel=new QLabel(trUtf8(" 起止页码"));
    pageEdit = new QLineEdit();          // 起止页码
    QPushButton *button=new QPushButton(trUtf8("添加"));

    QGridLayout * gridLayout=new QGridLayout;
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 4);
    gridLayout->setColumnStretch(2, 1);
    gridLayout->setColumnStretch(3, 1);
    gridLayout->setColumnStretch(4, 2);
    gridLayout->setColumnStretch(5, 2);
    gridLayout->addWidget(authorLabel,0,0);
    gridLayout->addWidget(authorEdit,0,1);
    gridLayout->addWidget(titleLabel,0,3);
    gridLayout->addWidget(titleEdit,0,4,1,2);
    gridLayout->addWidget(periodLabel,1,0);
    gridLayout->addWidget(periodEdit,1,1);
    gridLayout->addWidget(publishLabel,1,3);
    gridLayout->addWidget(publishEdit,1,4,1,2);
    gridLayout->addWidget(volumeLabel,2,0);
    gridLayout->addWidget(volumeEdit,2,1);
    gridLayout->addWidget(pcountLabel,2,3);
    gridLayout->addWidget(pcountEdit,2,4,1,2);
    gridLayout->addWidget(pageLabel,3,0);
    gridLayout->addWidget(pageEdit,3,1);
    gridLayout->addWidget(button,4,5);
    setLayout(gridLayout);
    connect(button,SIGNAL(clicked()),this,SLOT(check_add()));
    //  PeriodicalTab::setMinimumHeight(180);
}
void PeriodicalTab::check_add()
{
   QString authortext=authorEdit->text();
   QString titletext=titleEdit->text();
   QString periodtext=periodEdit->text();
   QString publishtext=publishEdit->text();
   QString volumetext=volumeEdit->text();
   QString pcounttext=pcountEdit->text();
   QString pagetext=pageEdit->text();
   QString temp("");
   if(authortext.isEmpty()||titletext.isEmpty()||periodtext.isEmpty()||publishtext.isEmpty()||pcounttext.isEmpty()){
    //Qt的isEmpty函数，如果为空则为1,否则为0
       MessageBox("*为必填项");
   }else{
      volumetext=(!volumetext.isEmpty())?(", "+volumetext):volumetext;
      pagetext=(!pagetext.isEmpty())?(":"+pagetext):pagetext;
      temp+=authortext+"."+titletext+"[J]."+periodtext+", "+publishtext+volumetext+"("+pcounttext+")"+pagetext+".\r\n";
      //textEdt->setText(textEdt->toPlainText()+temp);
      textresult.push_back(temp);
      count++;
      updatetext();
   }
}
void updatestatus()
{
   QString str="已添加<font color=green>"+QString::number(count)+"</font>个文献";
   countLabel->setText(str);
}
void MessageBox(QString msg)
{
    QMessageBox message(QMessageBox::Warning,"检查",msg,QMessageBox::Yes,NULL);
    message.exec();
}


//报纸面板实现
NewspaperTab::NewspaperTab(QWidget *parent)
  :QWidget(parent)
{
    QLabel *authorLabel=new QLabel(trUtf8("*作者"));
    authorEdit =new QLineEdit();    // 作者
    QLabel *titleLabel=new QLabel(trUtf8("*题目"));
    titleEdit = new QLineEdit();          // 题目
    QLabel *nameLabel=new QLabel(trUtf8("*报纸名"));
    nameEdit = new QLineEdit();       // 报纸名
    QLabel *publishLabel=new QLabel(trUtf8("*出版日期"));
    publishEdit = new QLineEdit();   // 出版日期
    QLabel *orderLabel=new QLabel(trUtf8("*版次"));
    orderEdit = new QLineEdit();         // 版次
    QPushButton *button=new QPushButton(trUtf8("添加"));
    QGridLayout * gridLayout=new QGridLayout;
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 4);
    gridLayout->setColumnStretch(2, 1);
    gridLayout->setColumnStretch(3, 1);
    gridLayout->setColumnStretch(4, 2);
    gridLayout->setColumnStretch(5, 2);
    gridLayout->addWidget(authorLabel,0,0);
    gridLayout->addWidget(authorEdit,0,1);
    gridLayout->addWidget(titleLabel,0,3);
    gridLayout->addWidget(titleEdit,0,4,1,2);
    gridLayout->addWidget(nameLabel,1,0);
    gridLayout->addWidget(nameEdit,1,1);
    gridLayout->addWidget(publishLabel,1,3);
    gridLayout->addWidget(publishEdit,1,4,1,2);
    gridLayout->addWidget(orderLabel,2,0);
    gridLayout->addWidget(orderEdit,2,1);
    gridLayout->addWidget(button,4,5);
    setLayout(gridLayout);
    connect(button,SIGNAL(clicked()),this,SLOT(check_add()));

}
void NewspaperTab::check_add()
{
   QString authortext=authorEdit->text();
   QString titletext=titleEdit->text();
   QString nametext=nameEdit->text();
   QString publishtext=publishEdit->text();
   QString ordertext=orderEdit->text();
   QString temp("");
   if(authortext.isEmpty()||titletext.isEmpty()||nametext.isEmpty()||publishtext.isEmpty()||ordertext.isEmpty()){
    //Qt的isEmpty函数，如果为空则为1,否则为0
       MessageBox("*为必填项");
   }else{
      temp+=authortext+"."+titletext+"[N]."+nametext+", "+publishtext+"("+ordertext+").\r\n";
      //textEdt->setText(textEdt->toPlainText()+temp);
      textresult.push_back(temp);
      count++;
      updatetext();
   }
}
//图书面板实现
BookTab::BookTab(QWidget *parent)
  :QWidget(parent)
{
           QLabel *authorLabel=new QLabel(trUtf8("*作者"));
           authorEdit =new QLineEdit();    // 作者
           QLabel *titleLabel=new QLabel(trUtf8("*图书名称"));
           titleEdit = new QLineEdit();          // 图书名称
           QLabel *orderLabel=new QLabel(trUtf8("*版次"));
           orderEdit = new QLineEdit();       // 版次
           QLabel *birthcomLabel=new QLabel(trUtf8("*出版单位"));
           birthcomEdit = new QLineEdit();         // 出版单位
           QLabel *birthlocLabel=new QLabel(trUtf8(" 出版地"));
           birthlocEdit = new QLineEdit();      // 出版地
           QLabel *publishLabel=new QLabel(trUtf8("*出版年份"));
           publishEdit = new QLineEdit();   // 出版年份

           QLabel *pageLabel=new QLabel(trUtf8(" 起止页码"));
           pageEdit = new QLineEdit();          // 起止页码
           QPushButton *button=new QPushButton(trUtf8("添加"));

           QGridLayout * gridLayout=new QGridLayout;
           gridLayout->setColumnStretch(0, 1);
           gridLayout->setColumnStretch(1, 4);
           gridLayout->setColumnStretch(2, 1);
           gridLayout->setColumnStretch(3, 1);
           gridLayout->setColumnStretch(4, 2);
           gridLayout->setColumnStretch(5, 2);
           gridLayout->addWidget(authorLabel,0,0);
           gridLayout->addWidget(authorEdit,0,1);
           gridLayout->addWidget(titleLabel,0,3);
           gridLayout->addWidget(titleEdit,0,4,1,2);
           gridLayout->addWidget(orderLabel,1,0);
           gridLayout->addWidget(orderEdit,1,1);
           gridLayout->addWidget(birthcomLabel,2,0);
           gridLayout->addWidget(birthcomEdit,2,1);
           gridLayout->addWidget(birthlocLabel,1,3);
           gridLayout->addWidget(birthlocEdit,1,4,1,2);
           gridLayout->addWidget(publishLabel,2,3);
           gridLayout->addWidget(publishEdit,2,4,1,2);
           gridLayout->addWidget(pageLabel,3,0);
           gridLayout->addWidget(pageEdit,3,1);
           gridLayout->addWidget(button,4,5);
           setLayout(gridLayout);
           connect(button,SIGNAL(clicked()),this,SLOT(check_add()));

}
void BookTab::check_add()
{
   QString authortext=authorEdit->text();
   QString titletext=titleEdit->text();
   QString birthcomtext= birthcomEdit->text();
   QString publishtext=publishEdit->text();
   QString birthloctext= birthlocEdit->text();
   QString pagetext=pageEdit->text();
   QString ordertext=orderEdit->text();
   QString temp("");
   if(authortext.isEmpty()||titletext.isEmpty()||birthcomtext.isEmpty()||publishtext.isEmpty()||ordertext.isEmpty()){
    //Qt的isEmpty函数，如果为空则为1,否则为0
       MessageBox("*为必填项");
   }else{
      birthloctext=(!birthloctext.isEmpty())?(birthloctext+":"): birthloctext;
      pagetext=(!pagetext.isEmpty())?(" :"+pagetext):pagetext;
      temp+=authortext+"."+titletext+"[M]."+ordertext+"."+birthloctext+birthcomtext+", "+publishtext+pagetext+".\r\n";
      textresult.push_back(temp);
      count++;
      updatetext();
   }
}
//会议集/论文集
MeetingTab::MeetingTab(QWidget *parent)
  :QWidget(parent)
{
           QLabel *authorLabel=new QLabel(trUtf8("*作者"));
           authorEdit =new QLineEdit();    // 作者
           QLabel *titleLabel=new QLabel(trUtf8("*题目"));
           titleEdit = new QLineEdit();          // 题目
           QLabel *MainLabel=new QLabel(trUtf8(" 主编"));
           MainEdit = new QLineEdit();          // 主编
           QLabel *setnameLabel=new QLabel(trUtf8("*论文集名"));
           setnameEdit = new QLineEdit();       // 论文集名
           QLabel *birthcomLabel=new QLabel(trUtf8("*出版单位"));
           birthcomEdit = new QLineEdit();         // 出版单位
           QLabel *birthlocLabel=new QLabel(trUtf8(" 出版地"));
           birthlocEdit = new QLineEdit();      // 出版地
           QLabel *publishLabel=new QLabel(trUtf8("*出版年份"));
           publishEdit = new QLineEdit();   // 出版年份
           QLabel *pageLabel=new QLabel(trUtf8(" 起止页码"));
           pageEdit = new QLineEdit();          // 起止页码
           QPushButton *button=new QPushButton(trUtf8("添加"));

           QGridLayout * gridLayout=new QGridLayout;
           gridLayout->setColumnStretch(0, 1);
           gridLayout->setColumnStretch(1, 4);
           gridLayout->setColumnStretch(2, 1);
           gridLayout->setColumnStretch(3, 1);
           gridLayout->setColumnStretch(4, 2);
           gridLayout->setColumnStretch(5, 2);
           gridLayout->addWidget(authorLabel,0,0);
           gridLayout->addWidget(authorEdit,0,1);
           gridLayout->addWidget(titleLabel,0,3);
           gridLayout->addWidget(titleEdit,0,4,1,2);
           gridLayout->addWidget(MainLabel,1,0);
           gridLayout->addWidget(MainEdit,1,1);
           gridLayout->addWidget(setnameLabel,1,3);
           gridLayout->addWidget(setnameEdit,1,4,1,2);
           gridLayout->addWidget(birthlocLabel,2,0);
           gridLayout->addWidget(birthlocEdit,2,1);
           gridLayout->addWidget(birthcomLabel,2,3);
           gridLayout->addWidget(birthcomEdit,2,4,1,2);
           gridLayout->addWidget(publishLabel,3,0);
           gridLayout->addWidget(publishEdit,3,1);
           gridLayout->addWidget(pageLabel,3,3);
           gridLayout->addWidget(pageEdit,3,4,1,2);
           gridLayout->addWidget(button,4,5);
           setLayout(gridLayout);
           connect(button,SIGNAL(clicked()),this,SLOT(check_add()));

}
void MeetingTab::check_add()
{
   QString authortext=authorEdit->text();
   QString titletext=titleEdit->text();
   QString birthcomtext= birthcomEdit->text();
   QString publishtext=publishEdit->text();
   QString birthloctext= birthlocEdit->text();
   QString pagetext=pageEdit->text();
   QString Maintext=MainEdit->text();
   QString setnametext=setnameEdit->text();

   QString temp("");
   if(authortext.isEmpty()||titletext.isEmpty()||birthcomtext.isEmpty()||publishtext.isEmpty()||setnametext.isEmpty()){
    //Qt的isEmpty函数，如果为空则为1,否则为0
       MessageBox("*为必填项");
   }else{
      Maintext=(!Maintext.isEmpty())?(Maintext+"."): Maintext;
      birthloctext=(!birthloctext.isEmpty())?(birthloctext+": "): birthloctext;
      pagetext=(!pagetext.isEmpty())?(":"+pagetext):pagetext;
      temp+=authortext+"."+titletext+"[A]."+Maintext+setnametext+".[C]."+birthloctext+birthcomtext+", "+publishtext+pagetext+".\r\n";
      textresult.push_back(temp);
      count++;
      updatetext();
   }
}
//学术论文
AcademicTab::AcademicTab(QWidget *parent)
  :QWidget(parent)
{
    QLabel *authorLabel=new QLabel(trUtf8("*作者"));
    authorEdit =new QLineEdit();    // 作者
    QLabel *titleLabel=new QLabel(trUtf8("*题目"));
    titleEdit = new QLineEdit();          // 题目
    QLabel *preservelocLabel=new QLabel(trUtf8(" 保存地"));
    preservelocEdit = new QLineEdit();       // 保存地
    QLabel *preservecomLabel=new QLabel(trUtf8("*保存单位"));
    preservecomEdit = new QLineEdit();   // 保存单位
    QLabel *yearLabel=new QLabel(trUtf8("*年份"));
    yearEdit = new QLineEdit();         // 年份
    QPushButton *button=new QPushButton(trUtf8("添加"));
    QGridLayout * gridLayout=new QGridLayout;
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 4);
    gridLayout->setColumnStretch(2, 1);
    gridLayout->setColumnStretch(3, 1);
    gridLayout->setColumnStretch(4, 2);
    gridLayout->setColumnStretch(5, 2);
    gridLayout->addWidget(authorLabel,0,0);
    gridLayout->addWidget(authorEdit,0,1);
    gridLayout->addWidget(titleLabel,0,3);
    gridLayout->addWidget(titleEdit,0,4,1,2);
    gridLayout->addWidget(preservelocLabel,1,0);
    gridLayout->addWidget(preservelocEdit,1,1);
    gridLayout->addWidget(preservecomLabel,1,3);
    gridLayout->addWidget(preservecomEdit,1,4,1,2);
    gridLayout->addWidget(yearLabel,2,0);
    gridLayout->addWidget(yearEdit,2,1);
    gridLayout->addWidget(button,4,5);
    setLayout(gridLayout);
    connect(button,SIGNAL(clicked()),this,SLOT(check_add()));
}
void AcademicTab::check_add()
{
   QString authortext=authorEdit->text();
   QString titletext=titleEdit->text();
   QString preserveloctext=preservelocEdit->text();
   QString preservecomtext=preservecomEdit->text();
   QString yeartext=yearEdit->text();
   QString temp("");
   if(authortext.isEmpty()||titletext.isEmpty()||preservecomtext.isEmpty()||yeartext.isEmpty()){
    //Qt的isEmpty函数，如果为空则为1,否则为0
       MessageBox("*为必填项");
   }else{
      preserveloctext=(!preserveloctext.isEmpty())?(preserveloctext+":"): preserveloctext;
      temp+=authortext+"."+titletext+"[D]."+preserveloctext+preservecomtext+", "+yeartext+".\r\n";
      textresult.push_back(temp);
      count++;
      updatetext();
   }
}
//报告
ReportTab::ReportTab(QWidget *parent)
  :QWidget(parent)
{
    QLabel *authorLabel=new QLabel(trUtf8("*作者"));
    authorEdit =new QLineEdit();    // 作者
    QLabel *titleLabel=new QLabel(trUtf8("*题目"));
    titleEdit = new QLineEdit();          // 题目
    QLabel *reportlocLabel=new QLabel(trUtf8("*报告地"));
    reportlocEdit = new QLineEdit();       // 报告地
    QLabel *reportcomLabel=new QLabel(trUtf8("*主办单位"));
    reportcomEdit = new QLineEdit();   // 报告单位
    QLabel *yearLabel=new QLabel(trUtf8(" 报告年份"));
    yearEdit = new QLineEdit();         // 报告年份
    QPushButton *button=new QPushButton(trUtf8("添加"));
    QGridLayout * gridLayout=new QGridLayout;
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 4);
    gridLayout->setColumnStretch(2, 1);
    gridLayout->setColumnStretch(3, 1);
    gridLayout->setColumnStretch(4, 2);
    gridLayout->setColumnStretch(5, 2);
    gridLayout->addWidget(authorLabel,0,0);
    gridLayout->addWidget(authorEdit,0,1);
    gridLayout->addWidget(titleLabel,0,3);
    gridLayout->addWidget(titleEdit,0,4,1,2);
    gridLayout->addWidget(reportlocLabel,1,0);
    gridLayout->addWidget(reportlocEdit,1,1);
    gridLayout->addWidget(reportcomLabel,1,3);
    gridLayout->addWidget(reportcomEdit,1,4,1,2);
    gridLayout->addWidget(yearLabel,2,0);
    gridLayout->addWidget(yearEdit,2,1);
    gridLayout->addWidget(button,4,5);
    setLayout(gridLayout);
     connect(button,SIGNAL(clicked()),this,SLOT(check_add()));
}
void ReportTab::check_add()
{
   QString authortext=authorEdit->text();
   QString titletext=titleEdit->text();
   QString reportloctext=reportlocEdit->text();
   QString reportcomtext=reportcomEdit->text();
   QString yeartext=yearEdit->text();
   QString temp("");
   if(authortext.isEmpty()||titletext.isEmpty()||reportcomtext.isEmpty()||yeartext.isEmpty()||reportloctext.isEmpty()){
    //Qt的isEmpty函数，如果为空则为1,否则为0
       MessageBox("*为必填项");
   }else{
      temp+=authortext+"."+titletext+"[R]."+reportloctext+":"+reportcomtext+", "+yeartext+".\r\n";
      textresult.push_back(temp);
      count++;
      updatetext();
   }
}
//网络文献
NetworkTab::NetworkTab(QWidget *parent)
  :QWidget(parent)
{
    QLabel *authorLabel=new QLabel(trUtf8("*责任人"));
    authorEdit =new QLineEdit();    // 责任人
    QLabel *titleLabel=new QLabel(trUtf8("*题目"));
    titleEdit = new QLineEdit();          // 题目
    QLabel *publishLabel=new QLabel(trUtf8("*发表(更新)日期"));
    publishEdit = new QLineEdit();       // 发表或更新日期
    QLabel *yearLabel=new QLabel(trUtf8("*引用日期"));
    yearEdit = new QLineEdit();         // 引用日期
    QLabel *pathLabel=new QLabel(trUtf8("*访问路径"));
    pathEdit = new QLineEdit();   // 访问路径

    QPushButton *button=new QPushButton(trUtf8("添加"));
    QGridLayout * gridLayout=new QGridLayout;
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 4);
    gridLayout->setColumnStretch(2, 1);
    gridLayout->setColumnStretch(3, 1);
    gridLayout->setColumnStretch(4, 2);
    gridLayout->setColumnStretch(5, 2);
    gridLayout->addWidget(authorLabel,0,0);
    gridLayout->addWidget(authorEdit,0,1);
    gridLayout->addWidget(titleLabel,0,3);
    gridLayout->addWidget(titleEdit,0,4,1,2);
    gridLayout->addWidget(publishLabel,1,0);
    gridLayout->addWidget(publishEdit,1,1);
    gridLayout->addWidget(yearLabel,1,3);
    gridLayout->addWidget(yearEdit,1,4,1,2);
    gridLayout->addWidget(pathLabel,2,0);
    gridLayout->addWidget(pathEdit,2,1);
    gridLayout->addWidget(button,4,5);
    setLayout(gridLayout);
    connect(button,SIGNAL(clicked()),this,SLOT(check_add()));

}
void NetworkTab::check_add()
{
   QString authortext=authorEdit->text();
   QString titletext=titleEdit->text();
   QString publishtext=publishEdit->text();
   QString pathtext=pathEdit->text();
   QString yeartext=yearEdit->text();
   QString temp("");
   if(authortext.isEmpty()||titletext.isEmpty()||pathtext.isEmpty()||yeartext.isEmpty()||publishtext.isEmpty()){
    //Qt的isEmpty函数，如果为空则为1,否则为0
       MessageBox("*为必填项");
   }else{
      temp+=authortext+"."+titletext+"[EB/OL]."+pathtext+", "+publishtext+"/"+yeartext+".\r\n";
      textresult.push_back(temp);
      count++;
      updatetext();
   }
}
//重写QLabel,为其添加clicked()信号
myLabel::myLabel(const QString &text, QWidget *parent) :
    QLabel(parent)
{
    setText(text);
}

void myLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        emit clicked();//(this);
}

