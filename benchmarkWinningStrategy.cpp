/*******************************************************************************
 * Summer Turner                                                               *
 *                                                                             *
 *                                                                             *
 ******************************************************************************/

// TODO: If Robby stands on a box with a can, and does not pick it up,
// then the can icon will still be replaced to a point. Should add
// check that if action != pick up, the can icon should not be overwritten.

#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <ncurses.h>
#include "constants.h"
#include "context.h"
#include "robby.h"
#include "strategy.h"

using namespace std;

int main(int argc, char **argv)
{
    Robby agent;
    Strategy fiftyKGen;
    Strategy random;
    Strategy hundredGen;
    Strategy thousandGen;
    Strategy tenKGen;
    Strategy hundredKGen;

    int cc;
    int nr_steps = 20;

    int hundredGenStrategy[243];
    int thousandGenStrategy[243];
    int tenKGenStrategy[243];
    int hundredKStrategy[243];
    int topStrategy[243];

    int ind = 0;
    int num;

    ifstream File;
    File.open("array.txt");
    while(!File.eof())
    {
        File >> num;
        hundredGenStrategy[ind] = num;
        thousandGenStrategy[ind] = num;
        tenKGenStrategy[ind] = num;
        hundredKStrategy[ind] = num;
        topStrategy[ind] = num;
        ind++;
    }
    File.close();

    while (1)
    {
        static struct option long_options[] =
        {
//          {"Number of agents",                    required_argument, 0, 'a'},
//          {"Number of cleaning sessions",         required_argument, 0, 'c'},
//          {"Number of survivors",                 required_argument, 0, 'n'},
            {"Number of steps in cleaning session", required_argument, 0, 's'},
            {0, 0, 0, 0}
        };

        // getopt_long stores the option index here.
        int option_index = 0;

        cc = getopt_long(argc, argv, "s:", long_options, &option_index);

        // Detect the end of the options.
        if (cc == -1)
            break;

        switch (cc)
        {
            case 0:
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");
                break;
            case 's':
                printf("option -%c with value `%s'\n", cc, optarg);
                nr_steps = (int)atol(optarg);
                break;
            default:
                abort();
        }
    }

    fiftyKGen.writeStrategy(topStrategy);
    hundredGen.writeStrategy(hundredGenStrategy);
    thousandGen.writeStrategy(thousandGenStrategy);
    tenKGen.writeStrategy(tenKGenStrategy);
    hundredKGen.writeStrategy(hundredKStrategy);

    srand(time(NULL));

    int score = 0;
    int matrix1[10][10];
    bool fiftyKActive, hundredActive, thousandActive, tenKActive, hundredKActive, randomActive;
    int c, n, e, s, w, x_pos, y_pos, x_old, y_old, action, old_c, old_action;
    char trackMarker = 'X';

    agent.setStrategy(fiftyKGen);
    agent.getStrategy().printStrategy();

    for (int nr_sessions = 0; nr_sessions < SESSIONS; nr_sessions++)
    {
        cout << endl << "Starting session: " << nr_sessions;

        hundredActive = false;
        thousandActive = false;
        tenKActive = false;
        fiftyKActive = false;
        randomActive = false;

        switch (nr_sessions)
        {
            case 0:
                random.setRandomStrategy();
                agent.setStrategy(random);
                randomActive= true;
                break;
            case 1:
                agent.setStrategy(hundredGen);
                hundredActive = true;
                break;
            case 2:
                agent.setStrategy(thousandGen);
                thousandActive = true;
                break;
            case 3:
                agent.setStrategy(tenKGen);
                tenKActive = true;
                break;
            case 4:
                agent.setStrategy(fiftyKGen);
                fiftyKActive = true;
                break;
            default:
                agent.setStrategy(hundredKGen);
                hundredKActive = true;
        }

        agent.setPos(0, 0);
        agent.initializeField(matrix1);

        initscr();
        clear();

        mvhline(10, 0, '-', 10);
        mvvline(0, 10, '|', 10);

        if (fiftyKActive)
            mvprintw(30, 0, "FIFTTYKGEN RUNNING");
        if (hundredActive)
            mvprintw(30, 0, "HUNDRED RUNNING");
        if (thousandActive)
            mvprintw(30, 0, "THOUSAND RUNNING");
        if (tenKActive)
	        mvprintw(30, 0, "TENTHOUSAND RUNNING");
        if (hundredKActive)
            mvprintw(30, 0, "HUNDRED-K RUNNING");
        if (randomActive)
            mvprintw(30, 0, "RANDOM RUNNING");

        for (int y = 0; y < 10; y++)
            for (int x = 0; x < 10; x++)
            {
	            if (matrix1[x][y] == 2)
	                mvprintw(y, x, "O");
            }

        agent.resetStatistics();

        for(int steps = 0; steps < nr_steps; steps++)
        {
            agent.updateContext();

            agent.getContext().getContext(c, n, e, s, w);
            action = agent.getStrategy().getAction(agent.getContext().getCoding());

            mvprintw(15, 30, "ROBBYS CURRENT CONTEXT");
            mvprintw(18, 40, "%d", c);
            mvprintw(17, 40, "%d", n);
            mvprintw(18, 41, "%d", e);
            mvprintw(19, 40, "%d", s);
            mvprintw(18, 39, "%d", w);
            mvprintw(23, 36, "ACTION: %d", action);

            agent.getPos(x_pos, y_pos);

            attron(A_BOLD);
            if (c == 2)
	           mvprintw(y_pos, x_pos, "*");
            else
	           mvprintw(y_pos, x_pos, "%c", trackMarker);

            attroff(A_BOLD);

            if (((old_c == 2) && (old_action != 4)))
                mvprintw(y_old, x_old, "o");
            else
            {
                if (old_c == 2)
                    mvprintw(y_old, x_old, "x");
                else
	                mvprintw(y_old, x_old, ".");
            }

            mvprintw(15, 0, "STEPS: %d", steps);
            mvprintw(21, 0, "CURRENT POINTS: %d", agent.getPoints());
            mvprintw(26, 0, "CURRENT PENALTIES: %d", agent.getPenalties());

            x_old = x_pos;
            y_old = y_pos;
            old_c = c;
            old_action = action;

            mvprintw(21, 36, "CODING:     "); // to clear up if previous code was longer than next
            mvprintw(21, 36, "CODING: %d", agent.getContext().getCoding());

            agent.makeMove(agent.getStrategy().getAction(agent.getContext().getCoding()), false);

            refresh();
            getch(); // tell console to wait until a key is hit
        }
        endwin(); // restores the terminal after curses activity

        score += agent.getPoints();
    }

    score = score / SESSIONS;
    cout << endl << "AGENTS'S testrun average score: " << score << endl;
}
