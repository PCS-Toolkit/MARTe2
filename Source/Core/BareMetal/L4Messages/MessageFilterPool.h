/**
 * @file MessageFilterPool.h
 * @brief Header file for class MessageFilterPool
 * @date 22/08/2016
 * @author Filippo Sartori
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

 * @details This header file contains the declaration of the class MessageFilterPool
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef MESSAGEFILTERPOOL_H_
#define MESSAGEFILTERPOOL_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "ReferenceContainer.h"
#include "MessageFilter.h"


/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {

/**
 * @brief Default message handling mechanism.
 * @details A pool of MessageFilter objects which are tested when a new message is received. As soon as one of the filters
 *  declares that the message was consumed (see MessageFilter::IsMessageConsumed) the message will not be tested on any
 *  subsequent filters.
 *  If the message is consumed
 */
class MessageFilterPool: public ReferenceContainer {

public:

    /**
     * @brief Default constructor.
     */
    MessageFilterPool();

    /**
     * @brief Default message handling mechanism.
     * @details Handles the reception of a message and by default simply calls SortMessage(). Can be overridden to implement message Queues etc...
     * @param[in,out] message is the message to be received.
     * @return
     *   ErrorManagement::NoError if the function specified in \a message is called correctly and returns true.
     *   ErrorManagement::UnsupportedFeature if something goes wrong trying to call the registered function.
     */
    ErrorManagement::ErrorType ReceiveMessage(ReferenceT<Message> &message);

    /**
     * @brief Installs a message filter in a given position.
     * @
     * TODO
     */
    ErrorManagement::ErrorType InstallMessageFilter(ReferenceT<MessageFilter> messageFilter, int32 position=0);

    /**
     * TODO
     */
    ErrorManagement::ErrorType RemoveMessageFilter(ReferenceT<MessageFilter> messageFilter);

    /**
     * TODO
     */
    ErrorManagement::ErrorType RemoveMessageFilter(CCString name);

    /**
     * TODO
     */
    ErrorManagement::ErrorType FindMessageFilter(CCString name,ReferenceT<MessageFilter> messageFilter);

};

}

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* MESSAGEFILTERPOOL_H_ */
	
