/**
 * @file Bootstrap.cpp
 * @brief Source file for class Bootstrap
 * @date 04/04/2018
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

 * @details This source file contains the definition of all the methods for
 * the class Bootstrap (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/
//This refers to the underlying Xilinx printf
#include "xil_printf.h"

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#include "AdvancedErrorManagement.h"
#include "Bootstrap.h"
#include "ConfigurationDatabase.h"
#include "StructuredDataI.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/
namespace MARTe {

//Note that some methods are implemented in FileSystem/L6App/Environment/Linux/Bootstrap.cpp

Bootstrap::Bootstrap() {

}

Bootstrap::~Bootstrap() {

}

ErrorManagement::ErrorType Bootstrap::ReadParameters(int32 argc, char8 **argv, StructuredDataI &loaderParameters) {
    //TODO finishe me
    ErrorManagement::ErrorType ret;
    ret.parametersError = !loaderParameters.Write("Loader", "RealTimeLoader");
    if (ret) {
        //ret.parametersError = !loaderParameters.Write("FirstState", "State1");
        ret.parametersError = !loaderParameters.Write("MessageDestination", "StateMachine");
        if (ret) {
            ret.parametersError = !loaderParameters.Write("MessageFunction", "START");
        }
    }
    if (ret) {
        ret.parametersError = !loaderParameters.Write("Parser", "cdb");
    }
    return ret;
}

extern "C" {
    void HardwarePrintf(const char8 * const msg);
}
void Bootstrap::Printf(const char8 * const msg) {
    xil_printf("%s\r\n", msg);
}

ErrorManagement::ErrorType Bootstrap::InitHAL(int32 argc, char8 **argv) {
    return ErrorManagement::NoError;
}

}
