/**
 * @file LoaderTest.h
 * @brief Header file for class LoaderTest
 * @date 05/04/2018
 * @author Andre Neto
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

 * @details This header file contains the declaration of the class LoaderTest
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef L6APP_LOADERTEST_H_
#define L6APP_LOADERTEST_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/
/**
 * @brief Tests the Loader public methods.
 */
class LoaderTest {

public:

    /**
     * @brief Tests the constructor.
     */
    bool TestConstructor();

    /**
     * @brief Tests the Configure method
     */
    bool TestConfigure();

    /**
     * @brief Tests the Configure method with non default cpus
     */
    bool TestConfigure_CPUs();

    /**
     * @brief Tests the Configure method with the json parser.
     */
    bool TestConfigure_Json();

    /**
     * @brief Tests the Configure method with the xml parsers.
     */
    bool TestConfigure_Xml();

    /**
     * @brief Tests the Configure method without specifying a parser.
     */
    bool TestConfigure_False_NoParser();

    /**
     * @brief Tests the Configure method specifying an inexistent parser.
     */
    bool TestConfigure_False_BadParser();

    /**
     * @brief Tests the Configure method with a Parser that fails to Parse.
     */
    bool TestConfigure_False_FailedParser();

    /**
     * @brief Tests the Configure method with a bad configuration (parsed ok but not initialised).
     */
    bool TestConfigure_False_FailedConfiguration();

    /**
     * @brief Tests the Configure method specifying a MessageDestination but not specifying a MessageFunction.
     */
    bool TestConfigure_False_FailedMessageFunction();

    /**
     * @brief Tests the Start method.
     */
    bool TestStart();

    /**
     * @brief Tests the Start method with no message.
     */
    bool TestStart_NoMessage();

    /**
     * @brief Tests the Start method with an unreachable message.
     */
    bool TestStart_WrongMessage();

    /**
     * @brief Tests the Stop method.
     */
    bool TestStop();
};

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* L6APP_LOADERTEST_H_ */
