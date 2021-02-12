#include "widget.h"
#include "asteroids.h"
#include "ship.h"
#include "shots.h"
#include "ui_widget.h"

#include <QKeyEvent>

//ближайшее TODO::
//
//вынести все константы
//в widget.cpp и widget.h посмотреть как разнести по разным классам (сейчас там хаос :)))
//добавить изображения отдельной папкой к проекту и прописать к ним относительный путь
//верхняя панель
//поменять начальную установку корабля (чтобы в самом начале игры был в середине)
//установить таймер
//вшить систему жизней
//когда будет вводиться система доп жизней, надо будет менять типы объектов
//отслеживание вылета астероидов за границу
//рандом астероидов --> фиксированные размеры + (пока не понятно как) отслеживать, чтобы два не вылетали рядом (издежать накладки графики)
//сменить графику на более крупную, все размыто
//+пофиксить изображение корабля, чтобы было симметричным
//возможно: смена управления бластерами на бесконечно стреляющие
//минимальное меню

//верхняя панель: прямоугольник унаследованный от сцены, покрасим в черный, лэйбл с таймером унаследованный от

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPixmap img("://Background.jpg");
    ui -> graphicsView -> setBackgroundBrush(img);

    scene = new QGraphicsScene(0, 0, 800, 600, this); //устанавливаем координаты отображения, указываем родителя
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect()); //добавляем прямоугольник по формату сцены
    scene->setStickyFocus(true); //теперь мы не можем потерять фокус с корабля

    scene->addItem(new Ship(scene->height()));

    animation = new QTimer(this);

    connect(animation, SIGNAL(timeout()), scene, SLOT(advance())); //от кого - какой сигнал - кому - что сделать, advance -смена кадра
                                                                   //метод - это метод классам Item, в нем в цикле вызывается каждый из элементов, которые содержит сцена - с параметром ноль, второй - единица
                                                                  //при первом проходе вычисляем новое состояние элемента (например столкновения или др взаиможействия), во второй фазе - отрисовываем или
                                                                  // меняем положение элемента

    animation->start(1000/60); //частота- 60 кадров в секунду, цисло в скобках - как часто запускается таймер

    generator = new QTimer(this);

    connect(generator, SIGNAL(timeout()), this, SLOT(OnGenerate())); //каждую секунду на сцену быдет добавляться новый астероид

    generator->start(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::OnGenerate(){
    scene->addItem(new Asteroids(scene->sceneRect().width())); //добавляем новый астероид на сцену
}

