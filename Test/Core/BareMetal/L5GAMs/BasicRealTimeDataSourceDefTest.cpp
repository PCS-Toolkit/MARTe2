/**
 * @file BasicRealTimeDataSourceDefTest.cpp
 * @brief Source file for class BasicRealTimeDataSourceDefTest
 * @date 22/mar/2016
 * @author pc
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
 * the class BasicRealTimeDataSourceDefTest (public, protected, and private). Be aware that some 
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "BasicRealTimeDataSourceDefTest.h"
#include "GAMTestHelper.h"
#include "RealTimeDataSourceDefRecord.h"
#include "stdio.h"
/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

bool BasicRealTimeDataSourceDefTest::TestConstructor() {
    BasicRealTimeDataSourceDef x;
    return (x.Size() == 0);
}

bool BasicRealTimeDataSourceDefTest::TestInitialise() {
    ConfigurationDatabase cdb;
    cdb.Write("Modifiers", "[3][2]");
    cdb.Write("Type", "int32");
    cdb.Write("Default", "1");
    BasicRealTimeDataSourceDef def;
    if (!def.Initialise(cdb)) {
        return false;
    }
    if (def.GetNumberOfDimensions() != 2) {
        return false;
    }
    if (def.GetNumberOfElements(0) != 2) {
        return false;
    }
    if (def.GetNumberOfElements(1) != 3) {
        return false;
    }

    return StringHelper::Compare(def.GetDefaultValue(), "1")==0;
}

bool BasicRealTimeDataSourceDefTest::TestAddConsumer() {

    BasicRealTimeDataSourceDef def;
    const uint32 size = 32;

    for (uint32 i = 0u; i < size; i++) {
        ReferenceT<PIDGAM> gam = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
        def.AddConsumer("state1", gam);
    }

    for (uint32 i = 0u; i < size; i++) {
        ReferenceT<PIDGAM> gam = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
        def.AddConsumer("state2", gam);
    }

    if (def.Size() != 2) {
        return false;
    }

    if (def.GetNumberOfConsumers("state1") != size) {
        return false;
    }

    if (def.GetNumberOfConsumers("state2") != size) {
        return false;
    }
    return true;
}

bool BasicRealTimeDataSourceDefTest::TestAddProducer() {
    BasicRealTimeDataSourceDef def;
    const uint32 size = 32;

    for (uint32 i = 0u; i < size; i++) {
        ReferenceT<PIDGAM> gamS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
        ReferenceT<PIDGAM> gamS2 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
        def.AddProducer("state1", gamS1);
        def.AddProducer("state2", gamS2);
    }

    if (def.Size() != 2) {
        return false;
    }

    printf("\n%s\n", def.Get(0)->GetName());
    printf("\n%s\n", def.Get(1)->GetName());

    if (def.GetNumberOfProducers("state1") != size) {
        return false;
    }

    if (def.GetNumberOfProducers("state2") != size) {
        return false;
    }
    return true;
}

bool BasicRealTimeDataSourceDefTest::TestGetNumberOfConsumers() {
    return TestAddConsumer();
}

bool BasicRealTimeDataSourceDefTest::TestGetNumberOfProducers() {
    return TestAddProducer();
}

bool BasicRealTimeDataSourceDefTest::TestVerifyTrue() {
    BasicRealTimeDataSourceDef def;
    const uint32 size = 32;

    for (uint32 i = 0u; i < size; i++) {
        ReferenceT<PIDGAM> gamS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
        ReferenceT<PIDGAM> gamS2 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
        def.AddConsumer("state1", gamS1);
        def.AddConsumer("state2", gamS2);
    }
    ReferenceT<PIDGAM> prodS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddProducer("state1", prodS1);

    ReferenceT<PIDGAM> prodS2 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddProducer("state2", prodS2);

    return def.Verify();
}

bool BasicRealTimeDataSourceDefTest::TestVerifyFalse_MoreThanOneProducer() {
    BasicRealTimeDataSourceDef def;
    const uint32 size = 32;

    for (uint32 i = 0u; i < size; i++) {
        ReferenceT<PIDGAM> gamS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
        ReferenceT<PIDGAM> gamS2 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
        def.AddConsumer("state1", gamS1);
        def.AddConsumer("state2", gamS2);
    }
    ReferenceT<PIDGAM> prodS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddProducer("state1", prodS1);

    ReferenceT<PIDGAM> prodS2 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    ReferenceT<PIDGAM> prodX = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());

    def.AddProducer("state2", prodS2);
    def.AddProducer("state2", prodX);

    return !def.Verify();

}

bool BasicRealTimeDataSourceDefTest::TestVerifyNoConsumers() {
    BasicRealTimeDataSourceDef def;
    const uint32 size = 32;

    for (uint32 i = 0u; i < size; i++) {
        ReferenceT<PIDGAM> gamS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
        def.AddConsumer("state1", gamS1);
    }
    ReferenceT<PIDGAM> prodS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddProducer("state1", prodS1);

    ReferenceT<PIDGAM> prodS2 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());

    def.AddProducer("state2", prodS2);

    return def.Verify();

}

bool BasicRealTimeDataSourceDefTest::TestGetType() {
    BasicRealTimeDataSourceDef def;
    if (!def.SetType("A_Type")) {
        return false;
    }
    return StringHelper::Compare(def.GetType(), "A_Type") == 0;
}

bool BasicRealTimeDataSourceDefTest::TestSetType() {
    return TestGetType();
}

bool BasicRealTimeDataSourceDefTest::TestAllocate_Basic() {

    BasicRealTimeDataSourceDef def;
    def.SetType("uint32");

    if (def.GetDataSourcePointer(0) != NULL) {
        return false;
    }

    if (def.GetDataSourcePointer(1) != NULL) {
        return false;
    }

    MemoryArea mem;

    if (!def.Allocate(mem)) {
        return false;
    }
    // double buffer
    if (mem.GetMemorySize() != (2 * sizeof(uint32))) {
        return false;
    }
    return true;

}

bool BasicRealTimeDataSourceDefTest::TestSetType_WarningAlreadySet() {
    BasicRealTimeDataSourceDef def;
    if (!def.SetType("type1")) {
        return false;
    }
    if (StringHelper::Compare(def.GetType(), "type1") != 0) {
        return false;
    }
    if (def.SetType("type2")) {
        return false;
    }
    return (StringHelper::Compare(def.GetType(), "type1") == 0);

}

bool BasicRealTimeDataSourceDefTest::TestAllocate_Structured() {
    BasicRealTimeDataSourceDef def;
    def.SetType("TrackError");

    if (def.GetDataSourcePointer(0) != NULL) {
        return false;
    }

    if (def.GetDataSourcePointer(1) != NULL) {
        return false;
    }

    MemoryArea mem;

    if (!def.Allocate(mem)) {
        return false;
    }
    // double buffer
    if (mem.GetMemorySize() != (2 * sizeof(TrackError))) {
        return false;
    }
    return true;

}

bool BasicRealTimeDataSourceDefTest::TestAllocate_Unintrospectable() {
    BasicRealTimeDataSourceDef def;
    def.SetType("Object");

    if (def.GetDataSourcePointer(0) != NULL) {
        return false;
    }

    if (def.GetDataSourcePointer(1) != NULL) {
        return false;
    }

    MemoryArea mem;

    if (!def.Allocate(mem)) {
        return false;
    }
    // double buffer
    if (mem.GetMemorySize() != (2 * sizeof(Object))) {
        return false;
    }
    return true;

}

bool BasicRealTimeDataSourceDefTest::TestAllocateFalse_Invalid() {
    BasicRealTimeDataSourceDef def;
    def.SetType("Invalid");

    if (def.GetDataSourcePointer(0) != NULL) {
        return false;
    }

    if (def.GetDataSourcePointer(1) != NULL) {
        return false;
    }

    MemoryArea mem;

    return (!def.Allocate(mem));

}

bool BasicRealTimeDataSourceDefTest::TestAllocateMultiDim_Vector() {
    BasicRealTimeDataSourceDef def;
    def.SetType("uint32");

    const uint32 numberOfElements = 32;

    def.SetNumberOfDimensions(1);
    def.SetNumberOfElements(0, numberOfElements);

    if (def.GetDataSourcePointer(0) != NULL) {
        return false;
    }

    if (def.GetDataSourcePointer(1) != NULL) {
        return false;
    }

    MemoryArea mem;

    if (!def.Allocate(mem)) {
        return false;
    }

    return mem.GetMemorySize() == 2 * sizeof(uint32) * numberOfElements;
}

bool BasicRealTimeDataSourceDefTest::TestAllocateMultiDim_Matrix() {
    BasicRealTimeDataSourceDef def;
    def.SetType("uint32");

    const uint32 numberOfRows = 32;
    const uint32 numberOfColumns = 12;

    def.SetNumberOfDimensions(2);
    def.SetNumberOfElements(1, numberOfRows);
    def.SetNumberOfElements(0, numberOfColumns);

    if (def.GetDataSourcePointer(0) != NULL) {
        return false;
    }

    if (def.GetDataSourcePointer(1) != NULL) {
        return false;
    }

    MemoryArea mem;

    if (!def.Allocate(mem)) {
        return false;
    }

    return mem.GetMemorySize() == 2 * sizeof(uint32) * numberOfRows * numberOfColumns;

}

bool BasicRealTimeDataSourceDefTest::TestAllocateFalse_MultiDimStructured() {
    BasicRealTimeDataSourceDef def;
    def.SetType("TrackError");

    const uint32 numberOfRows = 32;
    const uint32 numberOfColumns = 12;

    def.SetNumberOfDimensions(2);
    def.SetNumberOfElements(1, numberOfRows);
    def.SetNumberOfElements(0, numberOfColumns);

    MemoryArea mem;

    return (!def.Allocate(mem));
}

bool BasicRealTimeDataSourceDefTest::TestGetDataSourcePointer() {
    BasicRealTimeDataSourceDef def;
    def.SetType("uint32");

    if (def.GetDataSourcePointer(0) != NULL) {
        return false;
    }

    if (def.GetDataSourcePointer(1) != NULL) {
        return false;
    }

    MemoryArea mem;

    if (!def.Allocate(mem)) {
        return false;
    }

    // double buffer
    if (mem.GetMemorySize() != (2 * sizeof(uint32))) {
        return false;
    }

    uint32 *first = (uint32 *) mem.GetPointer(0);
    uint32 *second = (uint32 *) mem.GetPointer(sizeof(uint32));

    *first = 1;
    *second = 2;

    uint32 **buff1 = (uint32**) def.GetDataSourcePointer(0);
    uint32 **buff2 = (uint32**) def.GetDataSourcePointer(1);

    if (*first != **buff1) {
        return false;
    }

    if (*second != **buff2) {
        return false;
    }

    return (**((uint32**) def.GetDataSourcePointer(2)) == *first) && (**((uint32**) def.GetDataSourcePointer(3)) == *second);
}

bool BasicRealTimeDataSourceDefTest::TestPrepareNextState_Basic_ContinueVar() {
    BasicRealTimeDataSourceDef def;

    def.SetType("uint32");

    MemoryArea mem;

    if (!def.Allocate(mem)) {
        return false;
    }

    uint32 **buff1 = (uint32**) def.GetDataSourcePointer(0);
    uint32 **buff2 = (uint32**) def.GetDataSourcePointer(1);

    ReferenceT<PIDGAM> gamS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddConsumer("state1", gamS1);

    def.SetDefaultValue("1");
    ReferenceT<PIDGAM> gamS2 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddConsumer("state2", gamS2);

    // begin
    RealTimeStateInfo info;
    info.activeBuffer = 1;
    info.currentState = "";
    info.nextState = "state1";
    if (!def.PrepareNextState(info)) {
        return false;
    }

    if (**((uint32**) buff1) != 1) {
        return false;
    }

    uint32 *var = (uint32 *) mem.GetPointer(0);
    *var = 2;

    // switch state
    info.activeBuffer = 0;
    info.currentState = "state1";
    info.nextState = "state2";

    if (!def.PrepareNextState(info)) {
        return false;
    }

    return **((uint32**) buff2) == 2;
}

bool BasicRealTimeDataSourceDefTest::TestPrepareNextState_Basic_DeadVar() {
    BasicRealTimeDataSourceDef def;

    def.SetType("uint32");

    MemoryArea mem;

    if (!def.Allocate(mem)) {
        return false;
    }

    uint32 **buff1 = (uint32**) def.GetDataSourcePointer(0);
    uint32 **buff2 = (uint32**) def.GetDataSourcePointer(1);

    ReferenceT<PIDGAM> gamS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddConsumer("state1", gamS1);

    def.SetDefaultValue("1");
    ReferenceT<PIDGAM> gamS3 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddConsumer("state3", gamS3);

    RealTimeStateInfo info;
    // begin
    info.activeBuffer = 1;
    info.currentState = "";
    info.nextState = "state1";
    if (!def.PrepareNextState(info)) {
        return false;
    }

    if (**((uint32**) buff1) != 1) {
        return false;
    }

    uint32 *var = (uint32 *) mem.GetPointer(0);
    *var = 2;

    // switch state
    info.activeBuffer = 0;
    info.currentState = "state2";
    info.nextState = "state3";

    if (!def.PrepareNextState(info)) {
        return false;
    }

    return **((uint32**) buff2) == 1;

}

bool BasicRealTimeDataSourceDefTest::TestPrepareNextState_Structured_ContinueVar() {
    BasicRealTimeDataSourceDef def;

    def.SetType("TrackError");

    MemoryArea mem;

    if (!def.Allocate(mem)) {
        return false;
    }

    TrackError **buff1 = (TrackError**) def.GetDataSourcePointer(0);
    TrackError **buff2 = (TrackError**) def.GetDataSourcePointer(1);

    ReferenceT<PIDGAM> gamS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddConsumer("state1", gamS1);

    def.SetDefaultValue("Class=TrackError \n Par1=1\n Par2=2");

    ReferenceT<PIDGAM> gamS2 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddConsumer("state2", gamS2);

    // begin
    RealTimeStateInfo info;
    info.activeBuffer = 1;
    info.currentState = "";
    info.nextState = "state1";
    if (!def.PrepareNextState(info)) {
        return false;
    }

    if ((*buff1)->Par1 != 1) {
        return false;
    }

    if ((*buff1)->Par2 != 2) {
        return false;
    }

    TrackError *var = (TrackError *) mem.GetPointer(0);
    var->Par1 = 3;
    var->Par2 = 4;

    // switch state
    info.activeBuffer = 0;
    info.currentState = "state1";
    info.nextState = "state2";

    if (!def.PrepareNextState(info)) {
        return false;
    }

    if ((*buff2)->Par1 != 3) {
        return false;
    }

    if ((*buff2)->Par2 != 4) {
        return false;
    }

    return true;

}

bool BasicRealTimeDataSourceDefTest::TestPrepareNextState_Structured_DeadVar() {
    BasicRealTimeDataSourceDef def;

    def.SetType("TrackError");

    MemoryArea mem;

    if (!def.Allocate(mem)) {
        return false;
    }

    TrackError **buff1 = (TrackError**) def.GetDataSourcePointer(0);
    TrackError **buff2 = (TrackError**) def.GetDataSourcePointer(1);

    ReferenceT<PIDGAM> gamS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddConsumer("state1", gamS1);

    def.SetDefaultValue("Class=TrackError \n Par1=1\n Par2=2");

    ReferenceT<PIDGAM> gamS3 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddConsumer("state3", gamS3);

    // begin
    RealTimeStateInfo info;
    info.activeBuffer = 1;
    info.currentState = "";
    info.nextState = "state1";
    if (!def.PrepareNextState(info)) {
        return false;
    }

    if ((*buff1)->Par1 != 1) {
        return false;
    }

    if ((*buff1)->Par2 != 2) {
        return false;
    }

    TrackError *var = (TrackError *) mem.GetPointer(0);
    var->Par1 = 3;
    var->Par2 = 4;

    // switch state
    info.activeBuffer = 0;
    info.currentState = "state2";
    info.nextState = "state3";

    if (!def.PrepareNextState(info)) {
        return false;
    }

    if ((*buff2)->Par1 != 1) {
        return false;
    }

    if ((*buff2)->Par2 != 2) {
        return false;
    }

    return true;

}

bool BasicRealTimeDataSourceDefTest::TestPrepareNextStateMultiDimensional() {
    BasicRealTimeDataSourceDef def;

    def.SetType("uint32");
    def.SetNumberOfDimensions(1);

    const uint32 numberOfElements = 4;
    const char8 *defaultVal = "{0,1,2,3}";
    def.SetNumberOfElements(0, numberOfElements);

    MemoryArea mem;

    if (!def.Allocate(mem)) {
        return false;
    }

    uint32 **buff1 = (uint32**) def.GetDataSourcePointer(0);
    uint32 **buff2 = (uint32**) def.GetDataSourcePointer(1);

    ReferenceT<PIDGAM> gamS1 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddConsumer("state1", gamS1);

    def.SetDefaultValue(defaultVal);

    ReferenceT<PIDGAM> gamS3 = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def.AddConsumer("state3", gamS3);

    // begin
    RealTimeStateInfo info;
    info.activeBuffer = 1;
    info.currentState = "";
    info.nextState = "state1";
    if (!def.PrepareNextState(info)) {
        return false;
    }

    for (uint32 i = 0; i < numberOfElements; i++) {
        if ((*buff1)[i] != i) {
            return false;
        }
    }

    uint32 *var = (uint32 *) mem.GetPointer(0);

    for (uint32 i = 0; i < (2 * numberOfElements); i++) {
        var[i] = 0;
    }

    // switch state
    info.activeBuffer = 0;
    info.currentState = "state2";
    info.nextState = "state3";

    if (!def.PrepareNextState(info)) {
        return false;
    }

    for (uint32 i = 0; i < numberOfElements; i++) {
        if ((*buff2)[i] != i) {
            return false;
        }
    }

    return true;

}

bool BasicRealTimeDataSourceDefTest::TestSetDefaultValue() {
    BasicRealTimeDataSourceDef def;

    const char8 * defVal1 = "123123";
    def.SetDefaultValue(defVal1);

    if (StringHelper::Compare(defVal1, def.GetDefaultValue()) != 0) {
        return false;
    }

    return true;
}

bool BasicRealTimeDataSourceDefTest::TestGetDefaultValue() {
    return TestSetDefaultValue();
}

bool BasicRealTimeDataSourceDefTest::TestSetNumberOfElements() {
    BasicRealTimeDataSourceDef def;
    def.SetNumberOfElements(0, 32);
    if (def.GetNumberOfElements(0) != 32) {
        return false;
    }

    def.SetNumberOfElements(1, 32);
    if (def.GetNumberOfElements(1) != 32) {
        return false;
    }
    def.SetNumberOfElements(2, 32);
    if (def.GetNumberOfElements(2) != 32) {
        return false;
    }

    def.SetNumberOfElements(3, 12);
    if (def.GetNumberOfElements(2) != 12) {
        return false;
    }
    return true;
}

bool BasicRealTimeDataSourceDefTest::TestSetNumberOfDimensions() {
    BasicRealTimeDataSourceDef def;
    def.SetNumberOfDimensions(0);
    if (def.GetNumberOfDimensions() != 0) {
        return false;
    }
    def.SetNumberOfDimensions(1);
    if (def.GetNumberOfDimensions() != 1) {
        return false;
    }
    def.SetNumberOfDimensions(2);
    if (def.GetNumberOfDimensions() != 2) {
        return false;
    }
    def.SetNumberOfDimensions(3);
    if (def.GetNumberOfDimensions() != 2) {
        return false;
    }
    return true;

}

bool BasicRealTimeDataSourceDefTest::TestGetNumberOfElements() {
    BasicRealTimeDataSourceDef def;
    def.SetNumberOfElements(0, 32);
    if (def.GetNumberOfElements(0) != 32) {
        return false;
    }

    def.SetNumberOfElements(1, 32);
    if (def.GetNumberOfElements(1) != 32) {
        return false;
    }
    def.SetNumberOfElements(2, 32);
    if (def.GetNumberOfElements(2) != 32) {
        return false;
    }

    def.SetNumberOfElements(2, 12);
    if (def.GetNumberOfElements(3) != 12) {
        return false;
    }
    return true;
}

bool BasicRealTimeDataSourceDefTest::TestGetNumberOfDimensions() {
    return TestSetNumberOfDimensions();
}


bool BasicRealTimeDataSourceDefTest::TestGetSpinLockSemaphore(){
    BasicRealTimeDataSourceDef def;
    return def.GetSpinLockSemaphore()==NULL;
}


bool BasicRealTimeDataSourceDefTest::TestToStructuredData() {
    ReferenceT<BasicRealTimeDataSourceDef> def = ReferenceT<BasicRealTimeDataSourceDef>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    def->SetName("DefinitonToPrint");

    ReferenceT<PIDGAM> gamS1_Prod = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    gamS1_Prod->SetName("GAMS1_Prod");
    def->AddProducer("state1", gamS1_Prod);

    ReferenceT<PIDGAM> gamS1_Cons = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    gamS1_Cons->SetName("GAMS1_Cons");
    def->AddConsumer("state1", gamS1_Cons);

    ReferenceT<PIDGAM> gamS2_Prod = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    gamS2_Prod->SetName("GAMS2_Prod");
    def->AddProducer("state2", gamS2_Prod);

    ReferenceT<PIDGAM> gamS2_Cons = ReferenceT<PIDGAM>(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    gamS2_Cons->SetName("GAMS2_Cons");
    def->AddConsumer("state2", gamS2_Cons);

    def->SetType("uint32");
    def->SetDefaultValue("{{1,2},{3,4}}");
    def->SetNumberOfDimensions(2);

    def->SetNumberOfElements(0, 2);
    def->SetNumberOfElements(1, 2);

    StreamString display;
    ConfigurationDatabase output;
    def->ToStructuredData(output);
    display.Printf("%!", output);

    StreamString test = "DefinitonToPrint = {\n"
            "Class = BasicRealTimeDataSourceDef\n"
            "Type = uint32\n"
            "Default = {{1,2},{3,4}}\n"
            "NumberOfDimensions = 2\n"
            "NumberOfElements = { 2 2 1 } \n"
            "state1 = {\n"
            "Class = RealTimeDataSourceDefRecord\n"
            "Producers = {\n"
            "Class = ReferenceContainer\n"
            "GAMS1_Prod = {\n"
            "Class = PIDGAM\n"
            "}\n"
            "}\n"
            "Consumers = {\n"
            "Class = ReferenceContainer\n"
            "GAMS1_Cons = {\n"
            "Class = PIDGAM\n"
            "}\n"
            "}\n"
            "}\n"
            "state2 = {\n"
            "Class = RealTimeDataSourceDefRecord\n"
            "Producers = {\n"
            "Class = ReferenceContainer\n"
            "GAMS2_Prod = {\n"
            "Class = PIDGAM\n"
            "}\n"
            "}\n"
            "Consumers = {\n"
            "Class = ReferenceContainer\n"
            "GAMS2_Cons = {\n"
            "Class = PIDGAM\n"
            "}\n"
            "}\n"
            "}\n"
            "}\n";

    printf("\n%s\n", display.Buffer());
    return test == display;

}
