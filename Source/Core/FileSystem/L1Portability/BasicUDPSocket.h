/**
 * @file BasicUDPSocket.h
 * @brief Header file for class BasicUDPSocket
 * @date 28/10/2015
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

 * @details This header file contains the declaration of the class BasicUDPSocket
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef BASICUDPSOCKET_H_
#define BASICUDPSOCKET_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "BasicSocket.h"
#include "Sleep.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {

/**
 * @brief Unbuffered UDP socket.
 */
class BasicUDPSocket: public BasicSocket {
public:

    /**
     * @brief Default constructor.
     */
    BasicUDPSocket();

    /**
     * @brief Copy constructor.
     */
    BasicUDPSocket(const SocketCore socketIn = 0);

    /**
     * @brief Destructor.
     */
    virtual ~BasicUDPSocket();

    /**
     * @brief Reads data from the socket.
     * @param[out] output pointer to an array where read data is stored.
     * @param[in,out] size number of bytes to read.
     * @return true if at least one byte is successfully read.
     * @post
     *   size is the number of bytes actually read.
     */
    virtual bool Read(char8* const output,
                      uint32 &size);

    /**
     * @brief Writes data to the socket.
     * @param[in] input pointer to an array with the data to send.
     * @param[in,out] size the number of bytes to write.
     * @return true if at least one byte is successfully written.
     * @post
     *   size is the number of bytes actually written.
     */
    virtual bool Write(const char8* const input,
                       uint32 &size);

    /**
     * @brief Opens an UDP socket.
     * @return true if the socket is successfully initialised.
     */
    bool Open();

    /**
     * @brief Sets the port where the socket will listen from.
     * @param[in] port the port number.
     * @return true if the socket is successfully bind into the \a port.
     */
    bool Listen(const uint16 port);

    /**
     * @brief Sets the writing destination address.
     * @param[in] address the destination IP address.
     * @param[in] port the destination port.
     * @return true if the address is successfully set.
     * @pre
     *   address must have the IPv4 format x.x.x.x
     * @post
     *   GetDestination() == InternetHost(port, address)
     */
    bool Connect(const char8 * const address,
                 const uint16 port);

    /**
     * @brief Sets the writing destination address.
     * @param[in] address the destination IP address.
     * @return true if the address is successfully set.
     * @post
     *   GetDestination() == address
     */
    bool Connect(const InternetHost &address);

    /**
     * @brief The UDP socket support writing.
     * @return true.
     */
    virtual bool CanWrite() const;

    /**
     * @brief The UDP socket support reading.
     * @return true.
     */
    virtual bool CanRead() const;

    /**
     * @brief The UDP socket does not support seeking.
     * @return false.
     */
    virtual bool CanSeek() const;

    /**
     * @brief Reads data from the socket.
     * @param[out] output pointer to an array where read data is stored.
     * @param[in,out] size number of bytes to read.
     * @param[in] msecTimeout is the desired timeout.
     * @return true if at least one byte is successfully read within the specified timeout.
     * @post
     *   size is the number of bytes actually read.
     */
    virtual bool Read(char8 * const output,
                      uint32 & size,
                      const TimeoutType &msecTimeout);

    /**
     * @brief Send data to socket within timeout.
     * @param[in] input contains the data to send.
     * @param[in,out] size is the number of bytes to write.
     * @param[in] msecTimeout is the desired timeout.
     * @return false if the timeout expires before writing.
     * @post size is the number of written bytes.
     */
    virtual bool Write(const char8 * const input,
                       uint32 & size,
                       const TimeoutType &msecTimeout);

    /**
     * @brief Unsupported feature.
     * @return 0xFFFFFFFFFFFFFFFF.
     */
    virtual uint64 Size();

    /**
     * @brief Unsupported feature.
     * @return false.
     */
    virtual bool Seek(uint64 pos);

    /**
     * @brief Unsupported feature.
     * @return false.
     */
    virtual bool RelativeSeek(const int32 deltaPos);

    /**
     * @brief Unsupported feature.
     * @return 0xFFFFFFFFFFFFFFFF.
     */
    virtual uint64 Position();

    /**
     * @brief Unsupported feature.
     * @return false.
     */
    virtual bool SetSize(uint64 size);

};

}

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* BASICUDPSOCKET_H_ */

