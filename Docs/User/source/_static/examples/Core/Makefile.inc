#############################################################
#
# Copyright 2015 F4E | European Joint Undertaking for ITER 
#  and the Development of Fusion Energy ('Fusion for Energy')
# 
# Licensed under the EUPL, Version 1.1 or - as soon they 
# will be approved by the European Commission - subsequent  
# versions of the EUPL (the "Licence"); 
# You may not use this work except in compliance with the 
# Licence. 
# You may obtain a copy of the Licence at: 
#  
# http://ec.europa.eu/idabc/eupl
#
# Unless required by applicable law or agreed to in 
# writing, software distributed under the Licence is 
# distributed on an "AS IS" basis, 
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either 
# express or implied. 
# See the Licence for the specific language governing 
# permissions and limitations under the Licence. 
#
#############################################################

OBJSX=ErrorLoggerExample.x

PACKAGE=Examples
ROOT_DIR=../../../../../..
MAKEDEFAULTDIR=$(MARTe2_DIR)/MakeDefaults

include $(MAKEDEFAULTDIR)/MakeStdLibDefs.$(TARGET)
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L0Types
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L1Portability
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L2Objects
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L3Streams
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L4Configuration
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L4Messages
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L5GAMs
INCLUDES += -I$(MARTe2_DIR)/Source/Core/FileSystem/L1Portability
INCLUDES += -I$(MARTe2_DIR)/Source/Core/FileSystem/L3Streams
INCLUDES += -I$(MARTe2_DIR)/Source/Core/Scheduler/L1Portability
INCLUDES += -I$(MARTe2_DIR)/Source/Core/Scheduler/L3Services
INCLUDES += -I$(MARTe2_DIR)/Source/Core/Scheduler/L4Messages
INCLUDES += -I$(MARTe2_DIR)/Source/Core/Scheduler/L4StateMachine

all: $(OBJS) $(SUBPROJ)   \
        $(BUILD_DIR)/ObjectsExample1$(EXEEXT) \
        $(BUILD_DIR)/ObjectsExample2$(EXEEXT) \
        $(BUILD_DIR)/ReferencesExample1$(EXEEXT) \
        $(BUILD_DIR)/ReferencesExample2$(EXEEXT) \
        $(BUILD_DIR)/ReferencesExample3$(EXEEXT) \
        $(BUILD_DIR)/ReferencesExample4$(EXEEXT) \
        $(BUILD_DIR)/ReferencesExample5$(EXEEXT) \
	$(BUILD_DIR)/ReferencesExample6$(EXEEXT) \
        $(BUILD_DIR)/ConfigurationExample1$(EXEEXT) \
        $(BUILD_DIR)/ConfigurationExample2$(EXEEXT) \
        $(BUILD_DIR)/ConfigurationExample3$(EXEEXT) \
        $(BUILD_DIR)/ConfigurationExample4$(EXEEXT) \
        $(BUILD_DIR)/ConfigurationExample5$(EXEEXT) \
        $(BUILD_DIR)/LoggerServiceExample1$(EXEEXT) \
        $(BUILD_DIR)/TypesExample1$(EXEEXT)
	echo  $(OBJS)


include depends.$(TARGET)

include $(MAKEDEFAULTDIR)/MakeStdLibRules.$(TARGET)
