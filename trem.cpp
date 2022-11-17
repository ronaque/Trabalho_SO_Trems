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

// Construtor
Trem::Trem(int ID, int x, int y, int velocidade)
{
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = velocidade;
}

void Trem::setVelocidade(int velocidade, int maxSlide)
{
    this->velocidade = maxSlide - velocidade;
}

// Função a ser executada após executar trem->START
void Trem::run()
{
    sem_init(&sem0, 0, 1);
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 1);
    sem_init(&sem3, 0, 1);
    sem_init(&sem4, 0, 1);
    sem_init(&sem5, 0, 1);
    sem_init(&sem6, 0, 1);
    while (true)
    {
        switch (ID)
        {
        case 1: // Trem 1
            if (this->velocidade != 500)
            {
                if (y == 30 && x < 330)
                {
                    if (x == 310)
                    {
                        sem_wait(&sem0);
                        sem_wait(&sem2);
                    }
                    x += 10;
                }
                else if (x == 330 && y < 150)
                {
                    if (y == 130)
                    {
                    }
                    y += 10; // Vertical direita (Crítico)
                }
                else if (x > 60 && y == 150)
                {
                    if (x == 310)
                    {
                        sem_post(&sem0);
                    }
                    else if (x == 170)
                        sem_post(&sem2);
                    x -= 10; // Horizontal baixo (Crítico)
                }
                else
                    y -= 10;
                emit updateGUI(ID, x, y); // Emite um sinal
            }
            break;
        case 2: // Trem 2
            if (this->velocidade != 500)
            {
                if (y == 30 && x < 600)
                {
                    if (x == 350)
                    {
                        sem_post(&sem0);
                    }
                    else if (x == 580)
                    {
                        sem_wait(&sem1);
                        sem_wait(&sem4);
                        sem_wait(&sem3);
                    }
                    x += 10;
                }
                else if (x == 600 && y < 150)
                {
                    if (y == 130)
                    {
                    }
                    y += 10; // (Crítico)
                }
                else if (x > 330 && y == 150)
                {
                    if (x == 580)
                    {
                        sem_post(&sem1);
                    }
                    else if (x == 480)
                    {
                    }
                    else if (x == 440)
                    {
                        sem_post(&sem4);
                    }
                    else if (x == 350)
                    {
                        sem_wait(&sem0);
                    }
                    x -= 10; // (Crítico)
                }
                else
                {
                    if (y == 130)
                    {
                        sem_post(&sem3);
                    }
                    y -= 10; // (Crítico)
                }
                emit updateGUI(ID, x, y); // Emite um sinal
            }
            break;
        case 3: // Trem 3
            if (this->velocidade != 500)
            {
                if (y == 30 && x < 870)
                {
                    if (x == 620)
                    {
                        sem_post(&sem1);
                    }
                    x += 10;
                }
                else if (x == 870 && y < 150)
                    y += 10;
                else if (x > 600 && y == 150)
                {
                    if (x == 750)
                    {
                        sem_wait(&sem5);
                        sem_wait(&sem1);
                    }
                    else if (x == 620)
                    {
                    }
                    x -= 10; // (Crítico)
                }
                else
                {
                    if (y == 130)
                    {
                        sem_post(&sem5);
                    }
                    y -= 10; // (Crítico)
                }
                emit updateGUI(ID, x, y); // Emite um sinal
            }
            break;
        case 4: // Trem 4
            if (this->velocidade != 500)
            {
                if (y == 150 && x < 730)
                {
                    if (x == 480)
                    {
                        sem_post(&sem6);
                    }
                    else if (x == 580)
                    {
                    }
                    else if (x == 620)
                    {
                        sem_post(&sem4);
                    }
                    x += 10; // (Crítico)
                }
                else if (x == 730 && y < 280)
                {
                    if (y == 170)
                    {
                        sem_post(&sem5);
                    }
                    y += 10;
                }
                else if (x > 460 && y == 280)
                {
                    if (x == 480)
                    {
                        sem_wait(&sem6);
                        sem_wait(&sem4);
                        sem_wait(&sem5);
                    }
                    x -= 10;
                }
                else
                {
                    if (y == 170)
                    {
                    }
                    y -= 10; // (Crítico)
                }
                emit updateGUI(ID, x, y); // Emite um sinal
            }
            break;
        case 5: // Trem 5
            if (this->velocidade != 500)
            {
                if (y == 150 && x < 460)
                {
                    if (x == 310)
                    {
                    }
                    else if (x == 350)
                    {
                        sem_post(&sem2);
                    }
                    else if (x == 440)
                    {
                    }
                    x += 10; // (Crítico)
                }
                else if (x == 460 && y < 280)
                {
                    if (y == 170)
                    {
                        sem_post(&sem3);
                    }
                    y += 10; // (Crítico)
                }
                else if (x > 190 && y == 280)
                {
                    if (x == 440)
                    {
                        sem_post(&sem6);
                    }
                    x -= 10;
                }
                else
                {
                    if (y == 170)
                    {
                        sem_wait(&sem2);
                        sem_wait(&sem3);
                        sem_wait(&sem6);
                    }
                    y -= 10;
                }
                emit updateGUI(ID, x, y); // Emite um sinal
            }
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}