/**
 * @file HighResolutionTimer.cpp
 * @brief Header file for class HighResolutionTimer
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
 * @details This header file contains the declaration of the class HighResolutionTimer
 * (all of its public, protected and private members). It may also include
 * definitions for inline and friend methods which need to be visible to
 * the compiler.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "HighResolutionTimer.h"
#include INCLUDE_FILE_OPERATING_SYSTEM(OPERATING_SYSTEM,HighResolutionTimerCalibratorOS.h)

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/
static HighResolutionTimerCalibratorOS highResolutionTimerCalibratorOS;

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

/** the frequency of the HRT Clock. */
int64 HighResolutionTimerFrequency() {
    return highResolutionTimerCalibratorOS.HRTFrequency;
}

/** the HRT Clock period in seconds */
double HighResolutionTimerPeriod() {
    return highResolutionTimerCalibratorOS.HRTPeriod;
}

/** how many ticks in a msec for the HRT */
uint32 HighResolutionTimerMSecTics() {
    return highResolutionTimerCalibratorOS.HRTmSecTics;
}
