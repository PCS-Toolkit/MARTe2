/**
 * @file MemoryMapInputReader.h
 * @brief Header file for class MemoryMapInputReader
 * @date 11/04/2016
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

 * @details This header file contains the declaration of the class MemoryMapInputReader
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef MEMORYMAPINPUTREADER_H_
#define MEMORYMAPINPUTREADER_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "MemoryMapBroker.h"
/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {

/**
 * @brief Reads data from a collection of DataSourceSignalI and copies it to a collection of GAMSignalI signals.
 */
class DLL_API MemoryMapInputReader: public MemoryMapBroker {
public:
    CLASS_REGISTER_DECLARATION()

    /**
     * @brief Constructor
     */
    MemoryMapInputReader();

    /**
     * @see DataSourceBrokerI::Read(*)
     */
    virtual bool Read(const uint8 activeDataSourceBuffer,
                      const TimeoutType &timeout=TTInfiniteWait);


    /**
     * @brief NOOP
     * @return false.
     */
    virtual bool Write(const uint8 activeDataSourceBuffer,
                       const TimeoutType &timeout=TTInfiniteWait);

};

}
/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* MEMORYMAPINPUTREADER_H_ */

