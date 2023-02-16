#include "helpfield.h"

HelpField::HelpField()
{
    setFixedSize(300,50);
    text="score : 0\n pause - space";
}

void HelpField::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    painter.drawRect(0,0,width()-1,height()-1);
    painter.setFont(QFont("Arial",10,700));
    painter.drawText(QRect(0,0,width(),height()),Qt::AlignHCenter,text);
}

void HelpField::ChangeTextSlot(QString text)
{
    HelpField::text=text;
    repaint();
}
