/**
 * @file GAM.cpp
 * @brief Source file for class GAM
 * @date 07/04/2016
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

 * @details This source file contains the definition of all the methods for
 * the class GAM (public, protected, and private). Be aware that some 
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

#define DLL_API

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "GAM.h"
#include "GAMSignalsContainer.h"
#include "DataSourceContainer.h"
#include "AdvancedErrorManagement.h"
#include <BrokerI.h>
#include <DataSourceI.h>

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/
namespace MARTe {

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

GAM::GAM() :
        ExecutableI() {
    numberOfInputSignals = 0u;
    numberOfOutputSignals = 0u;
    inputSignalsMemory = NULL_PTR(void **);
    outputSignalsMemory = NULL_PTR(void **);

    heap = GlobalObjectsDatabase::Instance()->GetStandardHeap();
#if 0
    localData = NULL_PTR(StructuredDataI*);
    numberOfSupportedStates = 0u;
    supportedStates = NULL_PTR(StreamString *);
    supportedThreads = NULL_PTR(StreamString *);
    group = NULL_PTR(GAMGroup*);
    application = NULL_PTR(RealTimeApplication *);
    inputReaders = ReferenceT<BrokerContainer>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    outputWriters = ReferenceT<BrokerContainer>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
#endif
}

/*lint -e{1551} no exception should be thrown*/
GAM::~GAM() {
    if (inputSignalsMemory != NULL_PTR(void **)) {
        heap->Free(inputSignalsMemory);
    }
    if (outputSignalsMemory != NULL_PTR(void **)) {
        heap->Free(outputSignalsMemory);
    }

#if 0
    if (supportedStates != NULL) {
        delete[] supportedStates;
    }

    if (supportedThreads != NULL) {
        delete[] supportedThreads;
    }

    application = NULL_PTR(RealTimeApplication *);
    group = NULL_PTR(GAMGroup*);
#endif
}

#include <stdio.h>
bool GAM::Initialise(StructuredDataI & data) {

    bool ret = ReferenceContainer::Initialise(data);
    if (data.MoveRelative("InputSignals")) {
        ret = signalsDatabase.Write("InputSignals", data);
        if (ret) {
            ret = data.MoveToAncestor(1u);
        }
    }
    if (ret) {
        ret = signalsDatabase.MoveToRoot();
    }
    if (ret) {
        if (data.MoveRelative("OutputSignals")) {
            ret = signalsDatabase.Write("OutputSignals", data);
            if (ret) {
                ret = data.MoveToAncestor(1u);
            }
        }
    }
    if (ret) {
        ret = signalsDatabase.MoveToRoot();
    }
#if 0
    ret = inputReaders.IsValid();
    if (ret) {
        StreamString irName = GetName();
        irName += "_InputReader";
        inputReaders->SetName(irName.Buffer());
        inputReaders->SetInput(true);
    }

    if (ret) {
        ret = outputWriters.IsValid();
        if (ret) {
            StreamString owName = GetName();
            owName += "_OutputWriter";
            outputWriters->SetName(owName.Buffer());
            outputWriters->SetInput(false);
        }
        else {
            REPORT_ERROR_PARAMETERS(ErrorManagement::FatalError, "The GAM %s does not have a valid input BrokerContainer", GetName())
        }
    }
    else {
        REPORT_ERROR_PARAMETERS(ErrorManagement::FatalError, "The GAM %s does not have a valid output BrokerContainer", GetName())
    }

    if (ret) {
        // implemented in the derived classes
        // get the local cdb
        SetUp();
        // merge definitions
        ret = ConfigureFunction();
    }
#endif
    return ret;
}

bool GAM::AddSignals(StructuredDataI &data) {
    return data.Write("Signals", signalsDatabase);
}

bool GAM::Finalise() {
    return true;
}

void * GAM::AllocateInputSignalsMemory(uint32 numberOfBytes) {
    if (inputSignalsMemory != NULL) {
        inputSignalsMemory = heap->Malloc(numberOfBytes);
    }

    return inputSignalsMemory;
}

bool GAM::AllocateInputSignalsMemory2() {
    const char8* dirStr = "Signals.InputSignals";
    configuredDatabase.MoveToRoot();
    bool ret = configuredDatabase.MoveRelative(dirStr);
    uint32 totalByteSize = 0u;
    if (ret) {
        ret = configuredDatabase.Read("ByteSize", totalByteSize);
    }
    if (ret) {
        inputSignalsMemory = heap->Malloc(totalByteSize);
    }
    return ret;
}

void * GAM::AllocateOutputSignalsMemory(uint32 numberOfBytes) {
    outputSignalsMemory = heap->Malloc(numberOfBytes);
    return outputSignalsMemory;
}

bool GAM::AllocateOutputSignalsMemory2() {
    const char8* dirStr = "Signals.OutputSignals";
    configuredDatabase.MoveToRoot();
    bool ret = configuredDatabase.MoveRelative(dirStr);
    uint32 totalByteSize = 0u;
    if (ret) {
        ret = configuredDatabase.Read("ByteSize", totalByteSize);
    }
    if (ret) {
        inputSignalsMemory = heap->Malloc(totalByteSize);
    }
    return ret;
}

void *GAM::GetInputMemoryPointer() {
    return inputSignalsMemory;
}

void *GAM::GetOutputMemoryPointer() {
    return outputSignalsMemory;
}

bool GAM::SetConfiguredDatabase(StructuredDataI &data) {
    bool ret = data.Copy(configuredDatabase);
    if (ret) {
        ret = configuredDatabase.MoveToRoot();
    }
    if (configuredDatabase.MoveAbsolute("Signals.InputSignals")) {
        numberOfInputSignals = configuredDatabase.GetNumberOfChildren();
    }
    if (configuredDatabase.MoveAbsolute("Signals.OutputSignals")) {
        numberOfOutputSignals = configuredDatabase.GetNumberOfChildren();
    }

    return ret;
}

uint32 GAM::GetNumberOfInputSignals() {
    return numberOfInputSignals;
}

uint32 GAM::GetNumberOfOutputSignals() {
    return numberOfOutputSignals;
}

bool GAM::GetSignalName(SignalDirection direction,
                        uint32 signalIdx,
                        StreamString &signalName) {
    bool ret = MoveToSignalIndex(direction, signalIdx);
    if (ret) {
        ret = configuredDatabase.Read("QualifiedName", signalName);
    }
    return ret;
}

bool GAM::GetSignalIndex(SignalDirection direction,
                         uint32 &signalIdx,
                         const char8* const signalName) {
    uint32 numberOfSignals = 0u;
    if (direction == InputSignals) {
        numberOfSignals = GetNumberOfInputSignals();
    }
    else {
        numberOfSignals = GetNumberOfOutputSignals();
    }
    bool ret = true;
    bool found = false;
    uint32 i;
    for (i = 0u; (i < numberOfSignals) && (ret) && (!found); i++) {
        StreamString searchName;
        ret = GetSignalName(direction, i, searchName);
        if (ret) {
            found = (StringHelper::Compare(signalName, searchName.Buffer()) == 0u);
            signalIdx = i;
        }
    }
    if (ret) {
        ret = found;
    }
    return ret;
}

bool GAM::GetSignalDataSourceName(SignalDirection direction,
                                  uint32 signalIdx,
                                  StreamString &dataSourceName) {

    bool ret = MoveToSignalIndex(direction, signalIdx);
    if (ret) {
        ret = configuredDatabase.Read("DataSource", dataSourceName);
    }
    return ret;
}

TypeDescriptor GAM::GetSignalType(SignalDirection direction,
                                  uint32 signalIdx) {
    TypeDescriptor signalTypeDescriptor = InvalidType;
    bool ret = MoveToSignalIndex(direction, signalIdx);
    StreamString signalType;
    if (ret) {
        ret = configuredDatabase.Read("Type", signalType);
    }
    if (ret) {
        signalTypeDescriptor = TypeDescriptor::GetTypeDescriptorFromTypeName(signalType.Buffer());
    }
    return signalTypeDescriptor;
}

bool GAM::GetSignalNumberOfDimensions(SignalDirection direction,
                                      uint32 signalIdx,
                                      uint32 &numberOfDimensions) {
    bool ret = MoveToSignalIndex(direction, signalIdx);
    if (ret) {
        ret = configuredDatabase.Read("NumberOfDimensions", numberOfDimensions);
    }
    return ret;
}

bool GAM::GetSignalNumberElements(SignalDirection direction,
                                  uint32 signalIdx,
                                  uint32 &numberOfElements) {
    bool ret = MoveToSignalIndex(direction, signalIdx);
    if (ret) {
        ret = configuredDatabase.Read("NumberOfElements", numberOfElements);
    }
    return ret;
}

bool GAM::GetSignalByteSize(SignalDirection direction,
                            uint32 signalIdx,
                            uint32 &byteSize) {

    bool ret = MoveToSignalIndex(direction, signalIdx);
    if (ret) {
        ret = configuredDatabase.Read("ByteSize", byteSize);
    }
    return ret;
}

bool GAM::GetSignalNumberOfByteOffsets(SignalDirection direction,
                                       uint32 signalIdx,
                                       uint32 &numberOfByteOffsets) {
    bool ret = MoveToSignalIndex(direction, signalIdx);
    AnyType byteOffset;
    if (ret) {
        byteOffset = configuredDatabase.GetType("ByteOffset");
        ret = (byteOffset.GetDataPointer() != NULL_PTR(void *));
    }
    numberOfByteOffsets = 0u;
    if (ret) {
        numberOfByteOffsets = byteOffset.GetNumberOfElements(1u);
    }
    return ret;
}

bool GAM::GetSignalByteOffsetInfo(SignalDirection direction,
                                  uint32 signalIdx,
                                  uint32 byteOffsetIndex,
                                  uint32 &byteOffsetStart,
                                  uint32 &byteOffsetSize) {

    uint32 numberOfByteOffsets = 0u;
    bool ret = GetSignalNumberOfByteOffsets(direction, signalIdx, numberOfByteOffsets);
    if (ret) {
        ret = (numberOfByteOffsets > 0u);
    }
    if (ret) {
        ret = (numberOfByteOffsets > byteOffsetIndex);
    }
    if (ret) {
        ret = MoveToSignalIndex(direction, signalIdx);
    }

    Matrix<uint32> byteOffsetMat(numberOfByteOffsets, 2u);
    if (ret) {
        ret = configuredDatabase.Read("ByteOffset", byteOffsetMat);
    }
    if (ret) {
        byteOffsetStart = byteOffsetMat[byteOffsetIndex][0u];
        byteOffsetSize = byteOffsetMat[byteOffsetIndex][1u];
    }

    return ret;
}

bool GAM::GetSignalNumberOfRanges(SignalDirection direction,
                                  uint32 signalIdx,
                                  uint32 &numberOfRanges) {
    bool ret = MoveToSignalIndex(direction, signalIdx);
    AnyType ranges;
    if (ret) {
        ranges = configuredDatabase.GetType("Ranges");
        ret = (ranges.GetDataPointer() != NULL_PTR(void *));
    }
    numberOfRanges = 0u;
    if (ret) {
        numberOfRanges = ranges.GetNumberOfElements(1u);
    }
    return ret;
}

bool GAM::GetSignalRangesInfo(SignalDirection direction,
                              uint32 signalIdx,
                              uint32 rangeIndex,
                              uint32 &rangeStart,
                              uint32 &rangeEnd) {
    uint32 numberOfRanges = 0u;
    bool ret = GetSignalNumberOfRanges(direction, signalIdx, numberOfRanges);
    if (ret) {
        ret = (numberOfRanges > 0u);
    }
    if (ret) {
        ret = (numberOfRanges > rangeIndex);
    }
    if (ret) {
        ret = MoveToSignalIndex(direction, signalIdx);
    }

    Matrix<uint32> rangesMat(numberOfRanges, 2u);
    if (ret) {
        ret = configuredDatabase.Read("Ranges", rangesMat);
    }
    if (ret) {
        rangeStart = rangesMat[rangeIndex][0u];
        rangeEnd = rangesMat[rangeIndex][1u];
    }

    return ret;
}

bool GAM::GetSignalTimeCyclesInfo(SignalDirection direction,
                                  uint32 signalIdx,
                                  uint32 &timeCycles,
                                  uint32 &timeSamples) {

    Vector<uint32> timeCyclesSamplesVec(2u);
    bool ret = MoveToSignalIndex(direction, signalIdx);
    if (configuredDatabase.Read("TimeCyclesSamples", timeCyclesSamplesVec)) {
        timeCycles = timeCyclesSamplesVec[0u];
        timeSamples = timeCyclesSamplesVec[1u];
    }
    else {
        timeCycles = 1u;
        timeSamples = 1u;
    }
    return ret;
}

bool GAM::MoveToSignalIndex(SignalDirection direction,
                            uint32 signalIdx) {
    bool ret = configuredDatabase.MoveToRoot();
    const char8 * signalDirection = "Signals.InputSignals";
    if (direction == OutputSignals) {
        signalDirection = "Signals.OutputSignals";
    }
    if (ret) {
        ret = configuredDatabase.MoveRelative(signalDirection);
    }
    StreamString signalIdxStr;
    signalIdxStr.Printf("%d", signalIdx);
    if (ret) {
        ret = configuredDatabase.MoveRelative(signalIdxStr.Buffer());
    }
    return ret;
}

void GAM::AddInputBrokers(ReferenceContainer brokers) {
    uint32 n;
    for (n = 0u; n < brokers.Size(); n++) {
        inputBrokers.Insert(brokers.Get(n));
    }
}

void GAM::AddOutputBrokers(ReferenceContainer brokers) {
    uint32 n;
    for (n = 0u; n < brokers.Size(); n++) {
        outputBrokers.Insert(brokers.Get(n));
    }
}

ReferenceContainer GAM::GetInputBrokers() {
    return inputBrokers;
}

ReferenceContainer GAM::GetOutputBrokers() {
    return outputBrokers;
}

const void * GAM::GetInputSignalsBuffer() {
    return inputSignalsMemory;
}

void * GAM::GetOutputSignalsBuffer() {
    return outputSignalsMemory;
}

#if 0
/*void GAM::SetUp() {
 // initialises the local status
 }*/

/*
 virtual void Execute(){
 // execution routine
 */

bool GAM::ConfigureFunction() {
// use for each of them before RealTimeDataContainer::MergeWithLocal(localData)
// and merge the result with the existing one
    bool ret = true;
    if (localData != NULL) {
        uint32 numberOfElements = Size();
        for (uint32 i = 0u; (i < numberOfElements) && (ret); i++) {

            ReferenceT<GAMSignalsContainer> def = Get(i);

// must be all GAMSignalsContainer ??

            if (def.IsValid()) {
                StreamString defName = "+";
                defName += def->GetName();
                if (localData->MoveRelative(defName.Buffer())) {
                    // the partial definitions after this must become complete
                    ret = def->MergeWithLocal(*localData);
                    if (ret) {
                        ret = localData->MoveToAncestor(1u);
                    }
                }
                if (ret) {
                    // check if the definitions are meaningful
                    ret = def->Verify();
                }
            }
        }
    }
    return ret;
}

bool GAM::ConfigureDataSource() {

    bool ret = true;
    if (GetNumberOfSupportedStates() > 0u) {
        ret = (application != NULL);
        if (ret) {
            ReferenceT<DataSourceContainer> dataContainer = application->GetDataSourceContainer();
            ret = dataContainer.IsValid();
            if (ret) {
                ret = dataContainer->AddDataDefinition(ReferenceT<GAM>(this));
            }
            else {
                REPORT_ERROR(ErrorManagement::FatalError, "+Data container not found or invalid in the application");
            }
        }
        else {
            REPORT_ERROR(ErrorManagement::FatalError, "Application not set");
        }
    }
    else {
        REPORT_ERROR(ErrorManagement::Warning, "GAM never called in states or threads");
    }
    return ret;
}

void GAM::SetApplication(RealTimeApplication &rtApp) {
    if (application == NULL) {
        application = &rtApp;
    }
    inputReaders->SetApplication(rtApp);
    outputWriters->SetApplication(rtApp);
}

void GAM::SetGAMGroup(ReferenceT<GAMGroup> gamGroup) {
    if (group == NULL) {
        group = gamGroup.operator->();
    }
}

bool GAM::AddState(const char8 * const stateName,
        const char8 * const threadName) {

    bool ret = true;
    bool found = false;
    for (uint32 i = 0u; (i < numberOfSupportedStates) && (!found); i++) {
        /*lint -e{613} never enter here if supportedStates is NULL (because numberOfSupportedStates == 0) */
        found = (supportedStates[i] == stateName);

        if (found) {
            ret = (supportedThreads[i] == threadName);
            if (!ret) {
                REPORT_ERROR_PARAMETERS(ErrorManagement::FatalError, "The GAM %s cannot be in both %s and %s threads into the state %s", GetName(),
                        supportedThreads[i].Buffer(), threadName, stateName)
                //TODO same gam in two different threads!
            }
        }

    }
    if (!found) {
        if ((numberOfSupportedStates % stateNamesGranularity) == 0u) {
            uint32 newSize = numberOfSupportedStates + stateNamesGranularity;
            StreamString *tempStates = new StreamString[newSize];
            StreamString *tempThreads = new StreamString[newSize];
            if (supportedStates != NULL) {
                for (uint32 i = 0u; i < numberOfSupportedStates; i++) {
                    tempStates[i] = supportedStates[i];
                    tempThreads[i] = supportedThreads[i];
                }
                delete[] supportedStates;
                delete[] supportedThreads;
            }
            supportedStates = tempStates;
            supportedThreads = tempThreads;

        }
        /*lint -e{613} the memory of supportedStates is already allocated (numberOfSupportedStates == 0) */
        supportedStates[numberOfSupportedStates] = stateName;
        supportedThreads[numberOfSupportedStates] = threadName;
        numberOfSupportedStates++;
    }
    return ret;
}

StreamString * GAM::GetSupportedStates() {
    return supportedStates;
}

StreamString * GAM::GetSupportedThreads() {
    return supportedThreads;
}

uint32 GAM::GetNumberOfSupportedStates() const {
    return numberOfSupportedStates;

}

/*void GAM::SetUp() {
 // initialises the local status
 }*/

/*
 virtual void Execute(){
 // execution routine
 */

bool GAM::ConfigureDataSourceLinks() {
    bool ret = true;
    uint32 numberOfElements = Size();

    for (uint32 i = 0u; (i < numberOfElements) && (ret); i++) {
        ReferenceT<GAMSignalsContainer> defContainer = Get(i);
        if (defContainer.IsValid()) {
            uint32 numberOfDefs = defContainer->Size();
            for (uint32 j = 0u; (j < numberOfDefs) && (ret); j++) {
                ReferenceT<GAMSignalI> def = defContainer->Get(j);
                ret = def.IsValid();
                if (ret) {

                    if (defContainer->IsInput()) {
                        ret = (inputReaders->AddSignal(def));
                        if (!ret) {
                            // TODO definition not compatible with
                            // its data source !!!

                        }
                    }
                    if (defContainer->IsOutput()) {
                        ret = (outputWriters->AddSignal(def));
                        if (!ret) {
                            // TODO definition not compatible with
                            // its data source !!!

                        }
                    }
                }
                else {
                    REPORT_ERROR(ErrorManagement::FatalError, "The GAMSignalsContainer must contain GAMSignalI objects");
                }
            }
        }
    }

    if (ret) {
        ret = inputReaders->Finalise();
        if (!ret) {
//TODO Failed readers finalisation
        }
    }
    if (ret) {
        ret = outputWriters->Finalise();
        if (!ret) {
//TODO Failed readers finalisation
        }
    }

    if (ret) {
// not both sync!
        ret = !((inputReaders->IsSync()) && (outputWriters->IsSync()));
    }

    return ret;
}

bool GAM::IsSync() {
    return (inputReaders->IsSync() || outputWriters->IsSync());
}

Reference GAM::GetInputReader() {
    return inputReaders;
}

Reference GAM::GetOutputWriter() {
    return outputWriters;
}

RealTimeApplication *GAM::GetApplication() {
    return application;
}
#endif
}
