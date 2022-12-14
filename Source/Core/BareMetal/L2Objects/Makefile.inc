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

PACKAGE=Core/BareMetal
ROOT_DIR=../../../..
MAKEDEFAULTDIR=$(ROOT_DIR)/MakeDefaults

OBJSX=  AnyType.x \
                ClassMethodCaller.x\
                ClassMethodInterfaceMapper.x\
		ClassProperties.x \
		ClassRegistryDatabase.x \
		ClassRegistryItem.x \
		Introspection.x\
		IntrospectionEntry.x \
		Object.x \
		ObjectRegistryDatabase.x \
		Reference.x \
		ReferenceContainer.x \
		ReferenceContainerNode.x \
		ReferenceContainerFilter.x \
		ReferenceContainerFilterReferences.x \
		ReferenceContainerFilterObjectName.x

include $(MAKEDEFAULTDIR)/MakeStdLibDefs.$(TARGET)

INCLUDES+=-I../L1Portability -I../L0Types

all: $(OBJS) $(SUBPROJ)   \
		$(BUILD_DIR)/L2ObjectsB$(LIBEXT) \
		$(BUILD_DIR)/L2ObjectsB.def
	echo  $(OBJS)

include depends.$(TARGET)

include $(MAKEDEFAULTDIR)/MakeStdLibRules.$(TARGET)

