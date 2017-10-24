/*******************************************************************************
 * FILE NAME: context.h                                                        *
 * LAST DATE MOTIFIED: 23 October 2017                                         *
 *                                                                             *
 * REFERENCES:                                                                 *
 * [1] tolex3. “genetic”. GitHub, 14 March 2012,                               *
 *     https://github.com/tolex3/genetic. 23 October 2017.                     *
 ******************************************************************************/

#ifndef CONTEXT_H
#define CONTEXT_H

class Context
{
    private:
        int current;
        int north;
        int east;
        int south;
        int west;
        int coding;
        void encode(void);

    public:
        Context();
        void setContext(int c, int n, int e, int s, int w);
        int getCoding(void);
        void getContext(int& c, int& n, int& e, int& s, int& w);

        // DEBUG
        void printContext(void);
};
#endif
