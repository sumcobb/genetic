/*******************************************************************************
 * FILE NAME: strategy.h                                                       *
 * LAST DATE MOTIFIED: 23 October 2017                                         *
 *                                                                             *
 * REFERENCES:                                                                 *
 * [1] tolex3. “genetic”. GitHub, 14 March 2012,                               *
 *     https://github.com/tolex3/genetic. 23 October 2017.                     *
 ******************************************************************************/

#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy
{
    private:
        int strategyImplementation[243];
        int score;
        int birthGeneration;
        int mutationCount;

    public:
        Strategy();
        int element(int index);
        void writeStrategy(int sArray[]);
        void printStrategy();
        void saveStrategy();
        void setRandomStrategy();
        int getAction(int index);
        friend Strategy* copulate(Strategy l, Strategy r);
        Strategy& operator = (const Strategy& rhs);
        void mutate(void);
        friend bool identical(Strategy l, Strategy r, int& diffPos);
        friend int similarityCount(Strategy l, Strategy r);
        void updateScore(int newScore);
        int getScore(void);
        void updateMutationCount(void);
        void setBirthGeneration(int generation);
        int getBirthGeneration(void);
        int getMutationCount(void);
};
#endif
