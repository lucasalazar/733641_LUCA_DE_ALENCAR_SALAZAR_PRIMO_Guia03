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
    world->set(6, 2, HWALL);
    world->set(7, 2, HWALL);
    world->set(8, 2, HWALL);
    world->set(2, 7, HWALL);
    world->set(3, 7, HWALL);
    world->set(4, 7, HWALL);
    world->set(6, 7, HWALL);
    world->set(7, 7, HWALL);
    world->set(8, 7, HWALL);
    //
    world->set(1, 3, VWALL);
    world->set(1, 4, VWALL);
    world->set(1, 5, VWALL);
    world->set(1, 6, VWALL);
    world->set(1, 7, VWALL);
    world->set(4, 3, VWALL);
    world->set(4, 4, VWALL);
    world->set(4, 5, VWALL);
    world->set(4, 6, VWALL);
    world->set(4, 7, VWALL);
    world->set(5, 3, VWALL);
    world->set(5, 4, VWALL);
    world->set(5, 5, VWALL);
    world->set(5, 6, VWALL);
    world->set(5, 7, VWALL);
    world->set(8, 3, VWALL);
    world->set(8, 4, VWALL);
    world->set(8, 5, VWALL);
    world->set(8, 6, VWALL);
    world->set(8, 7, VWALL);
    //
    world->set(3, 2, BEEPER);
    world->set(1, 5, BEEPER);
    world->set(3, 8, BEEPER);
    //
    world->save(fileName);
} // decorateWorld ( )
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
    int readCommands(int commands[], const char *fileName)
    {
        // definir dados
        int x = 0;
        int action = 0;
        int lenght = 0;
        std::ifstream archive(fileName);
        lenght = countCommands(fileName);
        if (lenght < MAX_COMMANDS)
        {
            for (x = 0; x < lenght; x++)
            {
                archive >> action;
                commands[x] = action;
            }
            archive.close();
        }
        return (lenght);
    }
    /**
 execute - Metodo para executar um comando.
 @param action - comando a ser executado
*/
    void execute(int option)
    {
        // executar a opcao de comando
        switch (option)
        {
        case 0: // terminar
            // nao fazer nada
            break;
        case 1: // virar para a esquerda
            if (leftIsClear())
            {
                turnLeft();
            } // end if
            break;
        case 2: // virar para o sul
            while (!facingSouth())
            {
                turnLeft();
            } // end while
            break;
        case 3: // virar para a direita
            if (rightIsClear())
            {
                turnRight();
            } // end if
            break;
        case 4: // virar para o oeste
            while (!facingWest())
            {
                turnLeft();
            } // end while
            break;
        case 5: // mover
            if (frontIsClear())
            {
                move();
            } // end if
            break;
        case 6: // virar para o leste
            while (!facingEast())
            {
                turnLeft();
            } // end while
            break;
        case 7: // pegar marcador
            if (nextToABeeper())
            {
                pickBeeper();
            } // end if
            break;
        case 8: // virar para o norte
            while (!facingNorth())
            {
                turnLeft();
            } // end while
            break;
        case 9: // colocar marcador
            if (beepersInBag())
            {
                putBeeper();
            } // end if
            break;
        default: // nenhuma das alternativas anteriores
            // comando invalido
            show_Error("ERROR: Invalid command.");
        } // end switch
    }     // end execute( )
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
    /**
 * doCommands - Metodo para executar comandos de arquivo.
 * @param length - quantidade de comandos
 * @param commands - grupo de comandos para executar
 */
    void doCommands(int length, int commands[])
    {
        // definir dados
        int action = 0;
        int x = 0;
        // repetir para a quantidade de comandos
        for (x = 0; x < length; x = x + 1)
        {
            // executar esse comando
            execute(commands[x]);
        } // end for
    }     // end doCommands( )
    /**
 countCommands - Metodo para contar comandos de arquivo.
 @param fileName - nome do arquivo
 */
    int countCommands(const char *fileName)
    {
        // definir dados
        int x = 0;
        int length = 0;
        // abrir arquivo para leitura
        std::ifstream archive(fileName);
        // repetir enquanto houver dados
        archive >> x;
        while (!archive.eof())
        {
            // contar mais um comando
            length = length + 1;
            // tentar ler a proxima linha
            archive >> x;
        } // end while
        // fechar o arquivo
        archive.close();
        // retornar o resultado
        return (length);
    } // end countCommands( )

}; // end class MyRobot
// --------------------------- acao principal
/**
 Acao principal: executar a tarefa descrita acima.
*/
int main()
{
    // definir o contexto
    world->create("");
    decorateWorld("Guia0311.txt");
    world->show();
    // preparar ambiente para uso
    world->reset();
    world->read("Guia0311.txt");
    world->show();
    set_Speed(1);
    // criar robo
    MyRobot *robot = new MyRobot();
    robot->create(1, 1, EAST, 0, "Karel");
    robot->countCommands("Tarefa0311.txt");
    // definir armazenador para comandos
    int comandos[MAX_COMMANDS];
    char msg[80];
    int quantidade = robot->readCommands(comandos, "Tarefa0311.txt");
    msg[0] = '\0';
    sprintf(msg, "Commands = %d", quantidade);
    show_Text(msg);
    // executar movimentos
    robot->doCommands(quantidade, comandos);
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