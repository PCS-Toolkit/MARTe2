/**
 * @file BasicUART.cpp
 * @brief Source file for class BasicUART.
 * @date 07/08/2018
 * @author Andre Neto
 * @author Pedro Lourenco
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
 * @details This source file contains the definition of all the methods for
 * the class BasicUART (public, protected, and private). Be aware that some 
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#include "BasicUART.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/
struct SpeedTable {
    MARTe::int32 code;
    MARTe::uint32 speed;
};

const SpeedTable speedTable[] = {
                                { B0, 0u }, { B50, 50u },
                                { B75, 75u }, { B110, 110u },
                                { B134, 134u }, { B150, 150u },
                                { B200, 200u }, { B300, 300u },
                                { B600, 600u }, { B1200, 1200u },
                                { B1800, 1800u }, { B2400, 2400u },
                                { B4800, 4800u }, { B9600, 9600u },
                                { B19200, 19200u }, { B38400, 38400u },
                                { B57600, 57600u }, { B115200, 115200u },
                                { B230400, 230400u }, { B460800, 460800u },
                                { B500000, 500000u }, { B576000, 576000u },
                                { B921600, 921600u }, { B1000000, 1000000u },
                                { B1152000, 1152000u }, { B1500000, 1500000u },
                                { B2000000, 2000000u }, { B2500000, 2500000u },
                                { B3000000, 3000000u }, { B3500000, 3500000u },
                                { B4000000, 4000000u }
                                };

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/
namespace MARTe {

BasicUART::BasicUART() {

    fileDescriptor = -1;
    speedCode = B19200;
    FD_ZERO(&readFDS);
    FD_ZERO(&readFDS_done);
    FD_ZERO(&writeFDS);
    FD_ZERO(&writeFDS_done);

}

BasicUART::~BasicUART() {
    Close();
}

bool BasicUART::SetSpeed(uint32 speed) {

    bool ok = (fileDescriptor == -1);
    if (ok) {
        int32 ix = 0;
        while ( (speedTable[ix].code != __MAX_BAUD) &&
                (speed > speedTable[ix].speed)) {
            ix++;
        }
        speedCode = speedTable[ix].code;
        ok = (speed == speedTable[ix].speed);
    }

    return ok;
}

bool BasicUART::Open(const char8* name) {

    // Info from termios.h:
    // c_iflag - input modes;
    // c_oflag - output modes;
    // c_cflag - control modes;
    // c_lflag - local modes;
    // c_cc[NCCS] - special characters.

    bool ok = (fileDescriptor == -1);
    if (ok) {
        ok = (name != NULL);
    }
    if (ok) {
        fileDescriptor = open(name, O_RDWR | O_NOCTTY | O_NONBLOCK);
        if (fileDescriptor == -1) {
            std::stringstream stream;
            stream << "BasicUART::Open - cannot open serial device " << name
                   << ".";
            std::string msg = stream.str();
            const char8* message = msg.c_str();
            REPORT_ERROR_STATIC_0(ErrorManagement::OSError, message);
            ok = false;
        }
        FD_SET(fileDescriptor, &readFDS);
        FD_SET(fileDescriptor, &writeFDS);
    }
    if (ok) {
        struct termios newtio;
        // Clean all settings
        cfmakeraw(&newtio); 
        // Eight Data bits
        // CSIZE - Character size mask. Values are CS5, CS6, CS7, or CS8.
        newtio.c_cflag = (newtio.c_cflag & ~CSIZE) | CS8 | speedCode;
        // CLOCAL - Ignore modem control lines.
        // CREAD - Enable receiver.
        newtio.c_cflag |= (CLOCAL | CREAD);
        // No parity:
        // PARENB - Enable parity generation on output and parity checking for
        // input.
        // PARODD - If set, then parity for input and output is odd; otherwise
        // even parity is used.
        newtio.c_cflag &= ~(PARENB | PARODD);
        // No hardware handshake:
        // CRTSCTS - Enable RTS/CTS (hardware) flow control.
        newtio.c_cflag &= ~CRTSCTS;
        // One stopbit:
        // CSTOPB - Set two stop bits, rather than one.
        newtio.c_cflag &= ~CSTOPB; 
        // IGNBRK - Ignore BREAK condition on input.
        //newtio.c_iflag = IGNBRK;
        // Software handshake:
        // IXON - Enable XON/XOFF flow control on output.
        // IXANY - Typing any character will restart stopped output.
        // IXOFF - Enable XON/XOFF flow control on input.
        //newtio.c_iflag |= (IXON | IXOFF | IXANY);
        newtio.c_iflag &= ~(IXON | IXOFF | IXANY);
        // Non cannonical mode
        // ICANON - Enable canonical mode.
        // ECHO - Echo input characters.
        // ECHOE - If ICANON is also set, the ERASE character erases the
        // preceding input character, and WERASE erases the preceding word.
        // ISIG - When any of the characters INTR, QUIT, SUSP, or DSUSP are
        // received, generate the corresponding signal.
        newtio.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        newtio.c_lflag = 0;
        newtio.c_oflag = 0;
        // VMIN - Minimum number of characters for noncanonical read (MIN).
        newtio.c_cc[VMIN] = 1;
        // VTIME - Timeout in deciseconds for noncanonical read (TIME).
        newtio.c_cc[VTIME] = 5;
        ok = (cfsetspeed(&newtio, speedCode) == 0);
        if (!ok) {
            std::stringstream stream;
            stream << "BasicUART::Open - cannot set serial device " << name
                   << " speed to " << speedCode << ".";
            std::string msg = stream.str();
            const char8* message = msg.c_str();
            REPORT_ERROR_STATIC_0(ErrorManagement::OSError, message);
        }
        if (ok) {
            if (tcsetattr(fileDescriptor, TCSANOW, &newtio) == -1) {
                REPORT_ERROR_STATIC_0(ErrorManagement::OSError, "BasicUART::Op"
                                    "en - unable to set terminal parameters.");
                ok = false;
            }
        }
    }

    return ok;
}

void BasicUART::Close() {

    if (fileDescriptor != -1) {
        int32 err = close(fileDescriptor);
        if (err != 0) {
            REPORT_ERROR_STATIC_0(ErrorManagement::OSError, "BasicUART::Close "
                                "- failed to close serial interface.");
        }
        fileDescriptor = -1;
    }

}

bool BasicUART::Read(char8* buffer, uint32 &size) {

    int32 readBytes = read(fileDescriptor, buffer, size);
    size = readBytes;
    bool ok = (readBytes == static_cast<int32>(size));

    return ok;
}

bool BasicUART::Read(char8* buffer, uint32 &size, uint32 timeoutUsec) {
    
    bool ok = true;
    uint32 leftToRead = size;
    void *rbuffer = &buffer[0u];
    while ((leftToRead > 0u) && (ok)) {
        ok = WaitRead(timeoutUsec);
        if (ok) {
            int32 readBytes = read(fileDescriptor, rbuffer, leftToRead);
            if (readBytes > 0) {
                leftToRead -= readBytes;
                rbuffer = &buffer[size - leftToRead];
                // std::stringstream stream;
                // stream << "BasicUART::Read - read " << readBytes << " bytes "
                //        "from serial device.";
                // std::string msg = stream.str();
                // const char8* message = msg.c_str();
                // REPORT_ERROR_STATIC_0(ErrorManagement::Debug, message);
            }
            else {
                std::stringstream stream;
                stream << "BasicUART::Read - Failed to read from serial "
                        "device with error " << strerror(errno) << ".";
                std::string msg = stream.str();
                const char8* message = msg.c_str();
                REPORT_ERROR_STATIC_0(ErrorManagement::OSError, message);
                ok = false;
            }
        }
    }
    size = (size - leftToRead);

    return ok;
}

bool BasicUART::Write(char8 *buffer, uint32 size) {

    int32 writtenBytes = write(fileDescriptor, buffer, size);
    // std::stringstream stream;
    // stream << "BasicUART::Write - wrote " << writtenBytes << " bytes "
    //        "to serial device.";
    // std::string msg = stream.str();
    // const char8* message = msg.c_str();
    // REPORT_ERROR_STATIC_0(ErrorManagement::Debug, message);
    bool ok = (writtenBytes == static_cast<int32>(size));

    return ok;
}

bool BasicUART::WaitRead(uint32 timeoutUsec) {

    struct timeval timeWait;
    timeWait.tv_sec = timeoutUsec / 1000000u;
    timeWait.tv_usec = timeoutUsec % 1000000u;
    readFDS_done = readFDS;
    int32 readyCount = select(fileDescriptor + 1, &readFDS_done,
                                NULL_PTR(fd_set *), NULL_PTR(fd_set *),
                                &timeWait);

    return (readyCount > 0);
}

bool BasicUART::WaitWrite(MARTe::uint32 timeoutUsec) {

    struct timeval timeWait;
    timeWait.tv_sec = timeoutUsec / 1000000u;
    timeWait.tv_usec = timeoutUsec % 1000000u;
    writeFDS_done = writeFDS;
    int32 readyCount = select(fileDescriptor + 1, NULL_PTR(fd_set *),
                            &writeFDS_done, NULL_PTR(fd_set *),
                            &timeWait);

    return (readyCount > 0);
}

}
