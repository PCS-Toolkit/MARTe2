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

PACKAGE=Core/FileSystem
ROOT_DIR=../../../..
MAKEDEFAULTDIR=$(ROOT_DIR)/MakeDefaults

SPB=Environment/$(ENVIRONMENT).x

OBJSX=

include $(MAKEDEFAULTDIR)/MakeStdLibDefs.$(TARGET)

INCLUDES+=-I../../BareMetal/L0Types
INCLUDES+=-I../../BareMetal/L1Portability
INCLUDES+=-I../../BareMetal/L2Objects
INCLUDES+=-I../../BareMetal/L3Streams
INCLUDES+=-I../../BareMetal/L4Configuration
INCLUDES+=-I../../BareMetal/L4Logger
INCLUDES+=-I../../BareMetal/L4Messages
INCLUDES+=-I../../BareMetal/L5GAMs
INCLUDES+=-I../../BareMetal/L6App

LIBRARIES_STATIC+=$(BUILD_DIR)/$(ENVIRONMENT)/L6App$(LIBEXT)

all: $(OBJS) $(SUBPROJ)   \
		$(BUILD_DIR)/L6AppF$(LIBEXT) \
		$(BUILD_DIR)/L6AppF.def

	echo  $(OBJS)

include depends.$(TARGET)

include $(MAKEDEFAULTDIR)/MakeStdLibRules.$(TARGET)
