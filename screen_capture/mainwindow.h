#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QPicture>
#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <QString>
#include <QFileDialog>
#include <QMenu>
#include <QAction>
#include <QClipboard>
#include <QCursor>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringLiteral>
#include <QTimer>
#include <QMouseEvent>
#include <QPointer>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createUI();
    void allScreenCap();
    void slectScreenCap();
    void saveToFile();
    void copyToBoard();
    void Run();

    //鼠标矩形截图
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent * event);
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);
    void keyPressEvent(QKeyEvent *event);


private:
    QPixmap   pixmap,selectPix;
    QPushButton * picButton;
    QPushButton * saveButton;
    QPushButton * copyButton;
    QPushButton * selectButton;
    QLabel  *label;
    QTimer *time;

    QHBoxLayout * hLayout;
    QGridLayout * mainLayout;
    bool mouseIsPressed;
    QPoint m_beginPos,m_endPos;
    QPainter m_painter;

    QMouseEvent *event;
    QPaintEvent *pEvent;
    QKeyEvent *kEvent;

};
#endif // MAINWINDOW_H
