/**
 * @file GAMITest.h
 * @brief Header file for class GAMITest
 * @date 06/04/2016
 * @author Giuseppe Ferrò
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

 * @details This header file contains the declaration of the class GAMITest
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef GAMITEST_H_
#define GAMITEST_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/
#include "BasicGAM.h"
#include "ConfigurationDatabase.h"
/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

using namespace MARTe;

class GAMITest {

public:

    /**
     * @brief Constructor
     */
    GAMITest();

    /**
     * @brief Destructor
     */
    ~GAMITest() ;

    /**
     * @brief Tests the constructor.
     */
    bool TestConstructor();

    /**
     * @brief Tests if the function initialises the gam from a StructuredDataI in input.
     */
    bool TestInitialise();

    /**
     * @brief Tests if the function sets correctly the application reference in the gam.
     */
    bool TestSetApplication();

    /**
     * @brief Tests if the function sets correctly the gam group reference in the gam.
     */
    bool TestSetGAMGroup();

    /**
     * @brief Tests if the function adds correctly a state to the gam.
     */
    bool TestAddState();

    /**
     * @brief Tests if the function returns false if the same gam is called by more than one
     * thread in the same state.
     */
    bool TestAddStateFalse_MoreThreadsPerGAM();

    /**
     * @brief Tests if the function returns correctly the number of the contextless gam supported states
     */
    bool TestGetNumberOfSupportedStates();

    /**
     * @brief Tests if the function returns correctly the number of the contextful gam supported states.
     */
    bool TestGetNumberOfSupportedStates_GAMGroup();

    /**
     * @brief Tests if the function returns correctly the contextless gam supported states
     */
    bool TestGetSupportedStates();

    /**
     * @brief Tests if the function returns correctly the number of the contextful gam supported threads.
     */
    bool TestGetSupportedThreads_GAMGroup();

    /**
     * @brief Tests if the function returns correctly the contextless gam supported threads
     */
    bool TestGetSupportedThreads();

    /**
     * @brief Tests if the function returns correctly the contextful gam supported states
     */
    bool TestGetSupportedStates_GAMGroup();

    /**
     * @brief Tests if the function creates correctly the RealTimeDataSourceDefs from the gam RealTimeDataDefI
     */
    bool TestConfigureDataSource();

    /**
     * @brief Tests if the function fails adding RealTimeDataSourceDefs if RealTimeDataSource is declared final.
     */
    bool TestConfigureDataSourceFalse_Final();

    /**
     * @brief Tests if the function fails if the application does not contain the "+Data" container.
     */
    bool TestConfigureDataSourceFalse_NoData();

    /**
     * @brief Tests if the function fails if the reference to the application in the gam is not set.
     */
    bool TestConfigureDataSourceFalse_NoApplicationSet();

    /**
     * @brief Tests if the function returns true also if the gam is not involved in any state. In this case a warning will be
     * generated.
     */
    bool TestConfigureDataSource_NoStates();

    /**
     * @brief Tests if the function returns false.
     */
    bool TestIsSync();
private:

    /**
     * A configuration database used for tests.
     */
    ConfigurationDatabase cdb;
};

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* GAMITEST_H_ */

