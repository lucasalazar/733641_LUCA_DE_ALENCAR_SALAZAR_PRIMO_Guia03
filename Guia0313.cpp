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
    world->set(2, 2, HWALL);
    world->set(3, 2, HWALL);
    world->set(4, 2, HWALL);
    world->set(5, 2, HWALL);
    world->set(6, 2, HWALL);
    world->set(7, 2, HWALL);
    world->set(5, 4, HWALL);
    world->set(6, 4, HWALL);
    world->set(3, 7, HWALL);
    world->set(4, 7, HWALL);
    world->set(5, 7, HWALL);
    world->set(6, 7, HWALL);
    world->set(7, 7, HWALL);
    world->set(4, 6, HWALL);
    world->set(2, 8, HWALL);
    world->set(3, 8, HWALL);
    world->set(4, 8, HWALL);
    world->set(5, 8, HWALL);
    world->set(6, 8, HWALL);
    world->set(7, 8, HWALL);
    world->set(6, 6, HWALL);
    //
    world->set(1, 3, VWALL);
    world->set(1, 4, VWALL);
    world->set(1, 5, VWALL);
    world->set(1, 6, VWALL);
    world->set(1, 7, VWALL);
    world->set(1, 8, VWALL);
    world->set(2, 4, VWALL);
    world->set(2, 5, VWALL);
    world->set(2, 6, VWALL);
    world->set(2, 7, VWALL);
    world->set(3, 5, VWALL);
    world->set(3, 6, VWALL);
    world->set(4, 7, VWALL);
    world->set(5, 7, VWALL);
    world->set(7, 3, VWALL);
    world->set(7, 4, VWALL);
    world->set(7, 5, VWALL);
    world->set(7, 6, VWALL);
    world->set(7, 7, VWALL);
    world->set(6, 5, VWALL);
    world->set(6, 6, VWALL);
    //
    world->set(4, 7, BEEPER);
    world->set(5, 7, BEEPER);
    world->set(5, 7, BEEPER);
    world->set(6, 7, BEEPER);
    world->set(6, 7, BEEPER);
    world->set(6, 7, BEEPER);
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
    void pickBeepers(const char *fileName)
    {
        int x, y = 0;
        //definir arquivo para receber acrescimos ao final
        std::fstream archive(fileName, std::ios::app);
        if (nextToABeeper())
        {
            x = xAvenue(); //obter posicao atual(avenue)
            y = yStreet(); //obter posicao atual(street)
            archive << x << "\n";
            archive << y << "\n";
            int quantidade = 0;
            //repetir (com teste no inicio)
            //enquanto houver marcador proximo
            while (nextToABeeper())
            {
                //coletar um marcador
                pickBeeper();
                quantidade = quantidade + 1;
            } //end while
            //guardar o comando em arquivo e salta uma linha depois
            archive << quantidade << "\n";
        } //end if
          //fechar o arquivo INDISPENSAVEL para a gravacao
        archive.close();
    }

    void doTask()
    {
        moveN(7);
        turnLeft();
        moveN(7);
        turnLeft();
        moveN(6);
        turnLeft();
        moveN(5);
        turnLeft();
        move();
        turnLeft();
        moveN(4);
        turnRight();
        move();
        pickBeepers("Tarefa0313.txt");
        turnLeft();
        turnLeft();
        move();
        turnLeft();
        moveN(3);
        turnLeft();
        move();
        turnLeft();
        moveN(2);
        turnRight();
        move();
        turnLeft();
        move();
        pickBeepers("Tarefa0313.txt");
        turnLeft();
        turnLeft();
        moveN(2);
        turnRight();
        move();
        turnLeft();
        move();
        turnLeft();
        moveN(3);
        turnLeft();
        moveN(3);
        turnLeft();
        move();
        pickBeepers("Tarefa0313.txt");
        turnLeft();
        turnLeft();
        move();
        turnRight();
        moveN(4);
        turnRight();
        moveN(5);
        turnRight();
        moveN(5);
        turnRight();
        moveN(6);
        turnRight();
        moveN(7);
        turnRight();
        moveN(7);
        turnLeft();
        turnLeft();
        turnOff();
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
    decorateWorld("Guia0313.txt");
    world->show();
    // preparar ambiente para uso
    world->reset();
    world->read("Guia0313.txt");
    world->show();
    set_Speed(1);
    // criar robo
    MyRobot *robot = new MyRobot();
    robot->create(1, 1, EAST, 0, "Karel");
    // executar movimentos
    robot->doTask();
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