#include "game.h"

GameField::GameField()
{
    speed=150;
    moveSnakeTimer=new QTimer();
    connect(moveSnakeTimer,&QTimer::timeout,this,&GameField::MoveSnakeSlot);
    setFocusPolicy(Qt::StrongFocus);
    snakeItemSize=10;
    StartNewGame();
}

GameField::~GameField()
{
    //delete moveSnakeTimer;
}

void GameField::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QBrush gameFieldBrush(QColor(139,144,163),Qt::SolidPattern);
    QBrush snakeBrush(QColor(69,164,72),Qt::SolidPattern);
    QBrush foodBrush(QColor(249,183,123),Qt::SolidPattern);
    QPainter painter;
    painter.begin(this);
    if(isGameOver)
    {
        painter.setFont(QFont("Arial",10,700));
        painter.drawText(QRect(0,0,width(),height()),Qt::AlignHCenter,"GAME OVER\nscore : "+
                         QString::number(score));
        return ;
    }
    painter.setBrush(gameFieldBrush);
    painter.drawRect(0,0,width()-1,height()-1);

    painter.setBrush(snakeBrush);
    for(int i=0;i<snakeBody.size();i++)
    {
        painter.drawEllipse(snakeBody[i]->x*snakeItemSize,snakeBody[i]->y*snakeItemSize,
                            snakeItemSize,snakeItemSize);
    }

    painter.setBrush(foodBrush);
    painter.setPen(QColor(0,0,0));
    painter.drawEllipse(eat.x*snakeItemSize,eat.y*snakeItemSize,snakeItemSize,snakeItemSize);

    painter.end();
}

void GameField::keyPressEvent(QKeyEvent *event)
{
    QString text;
    switch (event->key())
    {
    case Qt::Key_Left:
        if(snakeDirection != SnakeDirection::right)
            snakeDirection=SnakeDirection::left;
        break;
    case Qt::Key_Right:
        if(snakeDirection != SnakeDirection::left)
            snakeDirection=SnakeDirection::right;
        break;
    case Qt::Key_Down:
        if(snakeDirection != SnakeDirection::up)
            snakeDirection=SnakeDirection::down;
        break;
    case Qt::Key_Up:
        if(snakeDirection != SnakeDirection::down)
            snakeDirection=SnakeDirection::up;
        break;
    case Qt::Key_Space:
        isPause = !isPause;
        isPause ? moveSnakeTimer->stop() : moveSnakeTimer->start();
        isPause ? text="score : "+QString::number(score)+"\n continue - space" : text="score : "+QString::number(score)+"\n pause - space";
        emit ChangeTextSignal(text);
        if(isGameOver)
        {
            StartNewGame();
            return;
        }
        break;
    }
}

void GameField::GameOver()
{
    isGameOver=true;
    QString text = "start new game - space";
    emit ChangeTextSignal(text);
    moveSnakeTimer->stop();

    qDeleteAll(snakeBody.begin(),snakeBody.end());
    snakeBody.clear();

    snakeBody.append(new points{0,0});
}

void GameField::StartNewGame()
{
    moveSnakeTimer->start(speed);
    isPause=false;
    snakeSize=3;
    snakeDirection=SnakeDirection::right;
    score=0;
    isGameOver=false;
    for(int i=0;i<snakeSize;i++)
    {
        snakeBody.insert(0,new points{i,0});
    }
    eat.x=10;
    eat.y=10;
}

void GameField::MoveSnakeSlot()
{
    if(snakeDirection == SnakeDirection::right)
    {
        snakeBody.insert(0,new points{snakeBody[0]->x+1,snakeBody[0]->y});
    }
    if(snakeDirection==SnakeDirection::left)
    {
        snakeBody.insert(0,new points{snakeBody[0]->x-1,snakeBody[0]->y});
    }
    if(snakeDirection==SnakeDirection::up)
    {
        snakeBody.insert(0,new points{snakeBody[0]->x,snakeBody[0]->y-1});
    }
    if(snakeDirection==SnakeDirection::down)
    {
        snakeBody.insert(0,new points{snakeBody[0]->x,snakeBody[0]->y+1});
    }
    snakeBody.removeLast();

    if((snakeBody[0]->x) > (width()/snakeItemSize))
    {
        snakeBody[0]->x=0;
    }
    if((snakeBody[0]->y) > (height()/snakeItemSize))
    {
        snakeBody[0]->y=0;
    }
    if((snakeBody[0]->y) < 0)
    {
        snakeBody[0]->y=(height()/snakeItemSize);
    }
    if((snakeBody[0]->x) < 0)
    {
        snakeBody[0]->x=(width()/snakeItemSize);
    }

    for(int i=1;i<snakeBody.size();i++)
    {
        if(snakeBody[0]->x==snakeBody[i]->x && snakeBody[0]->y==snakeBody[i]->y)
        {
            GameOver();
        }
    }
    if(snakeBody[0]->x==eat.x && snakeBody[0]->y==eat.y)
    {
        snakeBody.insert(0,new points{eat.x,eat.y});
        score++;
        QString text="score : "+QString::number(score)+"\n continue - space";
        emit ChangeTextSignal(text);
        eat.x=QRandomGenerator::global()->bounded(0,width()/10-1);
        eat.y=QRandomGenerator::global()->bounded(0,height()/10-1);
        moveSnakeTimer->stop();
        moveSnakeTimer->start(speed--);
    }
    repaint();
    //update();
}
