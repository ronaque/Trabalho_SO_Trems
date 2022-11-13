#include "trem.h"
#include <QtCore>
#include <semaphore.h>

sem_t sem0;
sem_t sem1;
sem_t sem2;
sem_t sem3;
sem_t sem4;
sem_t sem5;
sem_t sem6;

//Construtor
Trem::Trem(int ID, int x, int y, int velocidade){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = velocidade;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    sem_init(&sem0, 0, 1);
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 1);
    sem_init(&sem3, 0, 1);
    sem_init(&sem4, 0, 1);
    sem_init(&sem5, 0, 1);
    sem_init(&sem6, 0, 1);
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <330)
                x+=10; 
            else if (x == 330 && y < 150){
                if (y == 30)
                    sem_wait(&sem0);
                y+=10;  // Vertical direita (Crítico)
            }
            else if (x > 60 && y == 150) {
                if (x == 330)
                    sem_post(&sem0);
                x-=10;  // Horizontal baixo (Crítico)
            }
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <600) {
                if (x == 330)
                    sem_post(&sem0);
                x+=10;
            }
            else if (x == 600 && y < 150)
                y+=10;  // (Crítico)
            else if (x > 330 && y == 150)
                x-=10;  // (Crítico)
            else {
                y-=10;  // (Crítico)
                if (y == 140)
                    sem_wait(&sem0);
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 30 && x < 870)
                x+=10;
            else if (x == 870 && y < 150)
                y+=10;
            else if (x > 600 && y == 150)
                x-=10;  // (Crítico)
            else
                y-=10;  // (Crítico)
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x < 730)
                x+=10;  // (Crítico)
            else if (x == 730 && y < 280)
                y+=10;
            else if (x > 460 && y == 280)
                x-=10;
            else
                y-=10;  // (Crítico)
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x < 460)
                x+=10;  // (Crítico)
            else if (x == 460 && y < 280)
                y+=10;  // (Crítico)
            else if (x > 190 && y == 280)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}




