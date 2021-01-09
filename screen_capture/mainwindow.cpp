#include "mainwindow.h"
#include <QDebug>


//右键不能产生菜单  --->添加了一个单独的按钮来做复制图片
//窗口控件不能跟随变化  ---> 固定了窗口的大小

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600,600);
    setMinimumSize(600,600);
    setMaximumSize(600,600);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setMouseTracking(true);
}


MainWindow::~MainWindow()
{
  //  delete  pixmap;
}


void MainWindow::createUI(){
    label = new QLabel(this);
    label->resize(600,550);
    label->move(0,0);

    picButton = new QPushButton(this);
    saveButton = new QPushButton(this);
    selectButton = new QPushButton(this);

    picButton->setText("截屏");
    saveButton->setText("保存");
    selectButton->setText("选择截图");
    picButton->move(width()-200,height() - 40);
    saveButton->move(width()-100,height() - 40);
    selectButton->move(width()-400,height() - 40);
 }



void MainWindow::saveToFile(){
    connect(saveButton,&QPushButton::clicked,[=](){
        QString  path = QFileDialog::getSaveFileName(
                    this,
                    "save capturePicture",
                    "../screen_capture/pic",
                    "Image save: *.jpg;;"
                    "Image save: *.png;;"
                    "Image save: *.tif"
                    );

        pixmap.save(path);
    });
}
void MainWindow::copyToBoard(){
    copyButton = new QPushButton(this);
    copyButton->setText("复制");
    copyButton->move(300,560);
    connect(copyButton,&QPushButton::clicked,[=](){
         QApplication::clipboard()->setPixmap(pixmap);
    });
}

void MainWindow::allScreenCap(){
   //pixmap = new QPixmap;
    connect(picButton,&QPushButton::clicked,[=](){
        this->hide();
        time = new QTimer;
        connect(time,&QTimer::timeout,[=](){
        pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
        label->setPixmap(pixmap.scaled(label->size()));

        this->show();
        time->stop();

        });
        time->start(1000);  //1s
    });

    saveToFile();
    copyToBoard();
}


//鼠标事件
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        mouseIsPressed = true;
        m_beginPos = event->pos();
    }
    return QWidget::mousePressEvent(event);
}


void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(mouseIsPressed){
        m_endPos = event->pos();
        update();
    }

    return QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    m_endPos = event->pos();
    mouseIsPressed = false;
    return QWidget::mouseReleaseEvent(event);
}


void MainWindow::paintEvent(QPaintEvent * event){
    m_painter.begin(this);

    QColor shadowColor = QColor(0,0,0,100);
    m_painter.setPen(QPen(Qt::green,1,Qt::SolidLine,Qt::FlatCap)); //画笔
    m_painter.drawPixmap(0,0,pixmap);
    m_painter.fillRect(pixmap.rect(),shadowColor);

    if(mouseIsPressed){
        QRect selectRect = getRect(m_beginPos,m_endPos);
        selectPix = pixmap.copy(selectRect);

        m_painter.drawPixmap(selectRect.topLeft(),selectPix);
        m_painter.drawRect(selectRect);

    }
    m_painter.end();
}



QRect MainWindow::getRect(const QPoint &beginPoint, const QPoint &endPoint){
    int x, y, width, height;
       width = qAbs(beginPoint.x() - endPoint.x());
       height = qAbs(beginPoint.y() - endPoint.y());
       x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
       y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

       QRect selectedRect = QRect(x, y, width, height);
       // 避免宽或高为零时拷贝截图有误;
       // 可以看QQ截图，当选取截图宽或高为零时默认为2;
       if (selectedRect.width() == 0)
       {
           selectedRect.setWidth(1);
       }
       if (selectedRect.height() == 0)
       {
           selectedRect.setHeight(1);
       }

       return selectedRect;
}


void MainWindow::keyPressEvent(QKeyEvent *event){
    // Esc 键退出截图;
        if (event->key() == Qt::Key_Escape)
        {
            close();
        }
        // Eeter键完成截图;
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        {
      //      signalCompleteCature(selectPix);
            //this->show();
             label->setPixmap(selectPix.scaled(label->size()));

        }
}



void MainWindow::slectScreenCap(){
    connect(selectButton,&QPushButton::clicked,[=](){
        this->hide();
        pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
        this->show();
    });
}


void MainWindow::Run(){
    createUI();
    allScreenCap();
    slectScreenCap();
}







