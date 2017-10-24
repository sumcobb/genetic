/*******************************************************************************
 * FILE NAME: strategyStore.h                                                  *
 * LAST DATE MOTIFIED: 23 October 2017                                         *
 *                                                                             *
 * REFERENCES:                                                                 *
 * [1] tolex3. “genetic”. GitHub, 14 March 2012,                               *
 *     https://github.com/tolex3/genetic. 23 October 2017.                     *
 ******************************************************************************/

#ifndef STRATEGYSTORE_H
#define STRATEGYSTORE_H

#include "constants.h"
#include "strategy.h"

class StrategyStore
{
    private:
        Strategy strategies[NR_AGENTS];
        void sortStrategies(Strategy strArray[] , int size);

    public:
        void addStrategy(Strategy& s);
        void getOne(Strategy& str, int rank);
        void resetRanks(void);
        int calculateGenerationAverage();
        int averageSimilarity();
        bool exists(Strategy& str);
        // DEBUG
        void printStore(void);
};
#endif
