/**
 * @file IntrospectionT.h
 * @brief Header file for class IntrospectionT
 * @date 17/06/2016
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

 * @details This header file contains the declaration of the class IntrospectionT
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef INTROSPECTIONT_H_
#define INTROSPECTIONT_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/
#include "Introspection.h"
#include "ClassRegistryItem.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {
/**
 * TODO
 */
template<class T>
class IntrospectionT: public Introspection {
public:

    /**
     * TODO
     */
    IntrospectionT(const IntrospectionEntry ** const introspectionListIn,
                   const uint32 classSizeIn) :
            Introspection(introspectionListIn, classSizeIn) {

        ClassRegistryItem *cri;
        cri = T::GetClassRegistryItem_Static();
        if (cri != NULL)
            cri->SetIntrospection(this);

    }
};

}
/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

/**
 * This macro retrieves the member address with respect to the class begin.
 */
#define INTROSPECTION_MEMBER_INDEX(className, memberName) \
    (intptr)(&(((className *)0)->memberName))

/**
 * This macro retrieves the member size.
 */
#define INTROSPECTION_MEMBER_SIZE(className, memberName) \
    sizeof(((className *)0)->memberName)

/**
 * This macro creates a static instance of IntrospectionEntry with the provided inputs.
 */
#define DECLARE_CLASS_MEMBER(className, memberName, type, modifierString, attributeString ) \
    static const MARTe::IntrospectionEntry className ## _ ## memberName ## _introspectionEntry =   \
    MARTe::IntrospectionEntry(                                                                     \
        #memberName,                                                                        \
        #type,                                                                              \
        modifierString,                                                                     \
        attributeString,                                                                    \
        INTROSPECTION_MEMBER_SIZE(className, memberName),                                   \
        INTROSPECTION_MEMBER_INDEX(className, memberName)                                   \
    )

/**
 * This macro creates a static instance of Introspection with the provided inputs.
 */
#define DECLARE_CLASS_INTROSPECTION(className, introEntryArray) \
    static MARTe::IntrospectionT<className> className ## _ ## introspection(introEntryArray, sizeof(className));

#define DECLARE_STRUCT_INTROSPECTION(structName, introEntryArray)                                                              \
class structName ## _Registrable: public Object {                                                                          \
public:                                                                                                                        \
    static MARTe::ClassProperties classProperties;                                                                             \
    static MARTe::ClassRegistryItem * GetClassRegistryItem_Static() {                                                          \
        return ClassRegistryItemT<structName ## _Registrable>::Instance();                                                    \
    }                                                                                                                          \
};                                                                                                                             \
MARTe::ClassProperties structName ## _Registrable::classProperties                                                             \
                                  ( #structName, typeid(structName).name(), "", static_cast<uint32>(sizeof(structName)));      \
static MARTe::IntrospectionT<structName ## _Registrable> structName ## _ ## introspection(introEntryArray, sizeof(structName));

#endif /* INTROSPECTIONT_H_ */

