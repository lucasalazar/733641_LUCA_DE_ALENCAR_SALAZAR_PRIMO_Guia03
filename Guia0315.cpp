/*
 Matricula: 733641
 Author: LUCA DE ALENCAR SALAZAR PRIMO
*/
// lista de dependencias
#include "karel.hpp"
#include "io.hpp"
// --------------------------- definicoes de metodos
/**
 decorateWorld - Metodo para preparar o cenario.
 @param fileName - nome do arquivo para guardar a descricao.
*/
void decorateWorld(const char *fileName)
{
    //
    world->set(2, 4, HWALL);
    world->set(3, 4, HWALL);
    world->set(4, 4, HWALL);
    world->set(5, 4, HWALL);
    world->set(6, 4, HWALL);
    world->set(7, 4, HWALL);
    world->set(8, 4, HWALL);
    world->set(2, 5, HWALL);
    world->set(3, 5, HWALL);
    world->set(4, 5, HWALL);
    world->set(6, 5, HWALL);
    world->set(7, 5, HWALL);
    world->set(8, 5, HWALL);
    world->set(2, 6, HWALL);
    world->set(3, 6, HWALL);
    world->set(4, 6, HWALL);
    world->set(5, 6, HWALL);
    world->set(6, 6, HWALL);
    world->set(7, 6, HWALL);
    world->set(8, 6, HWALL);
    //
    world->set(1, 5, VWALL);
    world->set(1, 6, VWALL);
    world->set(8, 5, VWALL);
    world->set(8, 6, VWALL);
    //
    world->set(2, 6, BEEPER);
    //
    world->save(fileName);
}
/**
 Classe para definir robo particular (MyRobot),
 a partir do modelo generico (Robot)
 Nota: Todas as definicoes irao valer para qualquer outro robo
 criado a partir dessa nova descricao de modelo.
*/
class MyRobot : public Robot
{
public:
    /**
 turnRight - Procedimento para virar 'a direita.
 */
    void turnRight()
    {
        // definir dado local
        int step = 0;
        // testar se o robo esta' ativo
        if (checkStatus())
        {
            // o agente que executar esse metodo
            // devera' virar tres vezes 'a esquerda
            for (step = 1; step <= 3; step = step + 1)
            {
                turnLeft();
            } // end for
        }     // end if
    }         // end turnRight ( )
    /**
 moveN - Metodo para mover certa quantidade de passos.
 @param steps - passos a serem dados.
 */
    void moveN(int steps)
    {
        // definir dado local
        int step = 0;
        // testar se a quantidade de passos e' maior que zero
        for (step = steps; step > 0; step = step - 1)
        {
            // dar um passo
            move();
        } // end if
    }     // end moveN( )
    void pickBeepers()
    {
        while (nextToABeeper())
        {
            //coletar um marcador
            pickBeeper();
        } //end while
    }     //end if
    void faceNorth()
    {
        while (!facingNorth())
        {
            turnLeft();
        }
    }
    void faceEast()
    {
        while (!facingEast())
        {
            turnLeft();
        }
    }
    void faceWest()
    {
        while (!facingWest())
        {
            turnLeft();
        }
    }
    void faceSouth()
    {
        while (!facingSouth())
        {
            turnLeft();
        }
    }
    void wayArobotK()
    {
        if (checkStatus())
        {
            faceWest();
            moveN(3);
            faceNorth();
            move();
        }
    }
    void wayArobotJ()
    {
        if (checkStatus())
        {
            faceEast();
            moveN(3);
            faceNorth();
            move();
            faceWest();
            moveN(3);
            pickBeeper();
            faceEast();
            moveN(3);
            if (nextToARobot())
            {
                putBeeper();
            }
            else
            {
                faceSouth();
                move();
                faceWest();
                moveN(3);
                turnOff();
            }
        }
    }
    void wayBrobotK()
    {
        if (checkStatus())
        {
            if (nextToARobot())
            {
                pickBeeper();
                faceSouth();
                move();
                faceEast();
                moveN(3);
                putBeeper();
                faceWest();
                moveN(3);
                faceNorth();
                move();
                faceWest();
                moveN(3);
                faceEast();
            }
            else
            {
                faceSouth();
                move();
                faceEast();
                moveN(3);
                turnOff();
            }
        }
    }
    void wayBrobotJ()
    {
        if (checkStatus())
        {
            faceEast();
            moveN(3);
            turnOff();
        }
    }
}; // end class MyRobot
// --------------------------- acao principal
/**
 Acao principal: executar a tarefa descrita acima.
*/
int main()
{
    // definir o contexto
    world->create("");
    decorateWorld("Guia0315.txt");
    world->show();
    // preparar ambiente para uso
    world->reset();
    world->read("Guia0315.txt");
    world->show();
    set_Speed(1);
    // criar robo
    MyRobot *robot1 = new MyRobot();
    MyRobot *robot2 = new MyRobot();
    robot1->create(2, 5, EAST, 0, "Jarel");
    robot2->create(8, 5, EAST, 0, "Karel");
    // definir armazenador para comandos
    int comandos[MAX_COMMANDS];
    // executar movimentos
    robot2->wayArobotK();
    robot1->wayArobotJ();
    robot2->wayBrobotK();
    robot1->wayBrobotJ();
    // encerrar operacoes no ambiente
    world->close();
    // encerrar programar
    getchar();
    return (0);
}
// ------------------------------------------- testes
/*
---------------------------------------------- documentacao complementar
---------------------------------------------- notas / observacoes / comentarios
---------------------------------------------- previsao de testes
---------------------------------------------- historico
Versao Data Modificacao
 0.1 __/__ esboco
---------------------------------------------- testes
Versao Teste
 0.1 01. ( OK ) identificacao de programa
*/