/**
 * @file HighResolutionTimerCalibratorOS.h
 * @brief Header file for class HighResolutionTimerCalibratorOS
 * @date 11/06/2015
 * @author Giuseppe Ferr�
 *
 * @copyright Copyright 2015 F4E | European Joint Undertaking for ITER and
 * the Development of Fusion Energy ('Fusion for Energy').
 * Licensed under the EUPL, Version 1.1 or - as soon they will be approved
 * by the European Commission - subsequent versions of the EUPL (the "Licence")
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at: http://ec.europa.eu/idabc/eupl
 *
 * @warning Unless required by applicable law or agreed to in writing, 
 * software distributed under the Licence is distributed on an "AS IS"
 * basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the Licence permissions and limitations under the Licence.
 *
 * @details This header file contains the declaration of the class HighResolutionTimerCalibratorOS
 * (all of its public, protected and private members). It may also include
 * definitions for inline and friend methods which need to be visible to
 * the compiler.
 */

#ifndef HIGHRESOLUTIONTIMERCALIBRATOROS_H_
#define 		HIGHRESOLUTIONTIMERCALIBRATOROS_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/
#include <windows.h>

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/
#include "../../HighResolutionTimer.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

/** @brief A class to get the period and the frequency of the clock. */
class HighResolutionTimerCalibratorOS {

public:
    /** Number of cpu ticks in a milliseconsd. */
    uint32 HRTmSecTics;

    /** Number of cpu ticks in a second. */
    uint64 HRTFrequency;

    /** Time between a tick and the other in seconds. */
    double HRTPeriod;

    /** @brief Get the frequency and the period of the cpu clock. */
    HighResolutionTimerCalibratorOS() {
        uint64 tt0, tt1, tt2, tt3, tt4, tt5, dTa, dTb;
        dTa = 0;
        dTb = 0;
        for (int i = 0; i < 50; i++) {
            tt2 = HighResolutionTimer::Counter();
            QueryPerformanceCounter((LARGE_INTEGER *) &tt0);
            tt3 = tt4 = HighResolutionTimer::Counter();
            while ((tt4 - tt3) < 100000)
                tt4 = HighResolutionTimer::Counter(); // .5 ms at 200 Mhz
            QueryPerformanceCounter((LARGE_INTEGER *) &tt1);
            tt5 = HighResolutionTimer::Counter();
            dTa += (tt1 - tt0);
            dTb += ((tt5 + tt4) - (tt3 + tt2)) / 2;
        }
        QueryPerformanceFrequency((LARGE_INTEGER *) &HRTFrequency);
        HRTFrequency *= dTb;
        HRTFrequency /= dTa;

        HRTFrequency += 999999;
        HRTFrequency /= 2000000;
        HRTFrequency *= 2000000;

        HRTPeriod = 1.0 / (int64) HRTFrequency;
        HRTmSecTics = HRTFrequency / 1000;
    }
};
/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Friend method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* HIGHRESOLUTIONTIMERCALIBRATOROS_H_ */

