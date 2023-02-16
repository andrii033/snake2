#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QRandomGenerator>

class GameField : public QWidget
{
    Q_OBJECT
public:
    GameField();
    ~GameField();
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    struct points
    {
        int x,y;
    }eat;
    int snakeItemSize;
    QTimer *moveSnakeTimer;
    QList<points*> snakeBody;
    int snakeSize;
    enum SnakeDirection{
        right,left,up,down
    };
    SnakeDirection snakeDirection;
    bool isPause;
    int score;
    bool isGameOver;
    unsigned int speed;
    void GameOver();
    void StartNewGame();

private slots:
    void MoveSnakeSlot();
signals:
    void ChangeTextSignal(QString text);
};

#endif // GAME_H
