/**
 * @file RealTimeGenericDataDefTest.h
 * @brief Header file for class RealTimeGenericDataDefTest
 * @date 03/03/2016
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

 * @details This header file contains the declaration of the class RealTimeGenericDataDefTest
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef REALTIMEGENERICDATADEFTEST_H_
#define REALTIMEGENERICDATADEFTEST_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/
#include "RealTimeGenericDataDef.h"
/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

using namespace MARTe;

class RealTimeGenericDataDefTest {
public:

    bool TestConstructor();

    bool TestInitialise();

    bool TestMergeWithLocal();

    bool TestMergeWithLocalFalse_FinalGlobal();

    bool TestMergeWithLocalFalse_BothFinal();

    bool TestMergeWithLocal_AddType();

    bool TestMergeWithLocal_AddPath();

    bool TestMergeWithLocal_AddModifiers();

    bool TestMergeWithLocal_AddDefaultValues();

    bool TestMergeWithLocal_DifferentTypes();

    bool TestMergeWithLocal_DifferentPaths();

    bool TestMergeWithLocal_DifferentDefaultValues();

    bool TestMergeWithLocal_DifferentModifiers();

    bool TestGetDefaultValue();

    bool TestToStructuredData();

    bool TestVerify();

    bool TestVerifyFalse_UnregisteredType();

    bool TestVerifyFalse_UnintrospectableType();

    bool TestVerifyFalse_InvalidMemberName();

    bool TestVerifyFalse_InvalidMemberType();

    bool TestVerifyFalse_InvalidNumberOfMembers();

    bool TestVerifyFalse_EmptyType();

};

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* REALTIMEGENERICDATADEFTEST_H_ */

