/**
 * @file ClassMethodCallerT.h
 * @brief Header file for class ClassMethodCallerT
 * @date 13/giu/2016
 * @author pc
 *
 * @copyright Copyright 2015 F4E | European Joint Undertaking for ITER and
 * the Development of Fusion Energy ('Fusion for Energy').
 * Licensed under the EUPL, Version 1.1 or - as soon they will be approved
 * by the European Commission - subsequent versions of the EUPL (the "Licence")
 * argTypeou may not use this work except in compliance with the Licence.
 * argTypeou may obtain a copy of the Licence at: http://ec.europa.eu/idabc/eupl
 *
 * @warning Unless required by applicable law or agreed to in writing, 
 * software distributed under the Licence is distributed on an "AS IS"
 * basis, WITHOUT WARRANTIES OR CONDITIONS OF ANargType KIND, either express
 * or implied. See the Licence permissions and limitations under the Licence.

 * @details This header file contains the declaration of the class ClassMethodCallerT
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef CLASSMETHODCALLERT_H_
#define CLASSMETHODCALLERT_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "ClassMethodCaller.h"
/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {



template<typename className, typename argType>
class ClassMethodCallerT: public ClassMethodCaller {
public:

    ClassMethodCallerT(bool (className::*f)(argType ref));
    virtual ~ClassMethodCallerT();


    virtual ErrorManagement::ErrorType Call(Object * context,
                                            argType ref);

private:
    bool (className::*pFun)(argType ref);

};


// specialization to call methods without parameters
template<typename className>
class ClassMethodCallerT<className, void>: public ClassMethodCaller {
public:

    ClassMethodCallerT(bool (className::*f)(void));

    virtual ~ClassMethodCallerT();


    virtual ErrorManagement::ErrorType Call(Object * context);

private:
    bool (className::*pFun)(void);

};






/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

template<class className, class argType>
ClassMethodCallerT<className, argType>::ClassMethodCallerT(bool (className::*f)(argType ref)) {
    pFun = f;
}

template<class className, class argType>
ClassMethodCallerT<className, argType>::~ClassMethodCallerT() {

}

template<class className, class argType>
ErrorManagement::ErrorType ClassMethodCallerT<className, argType>::Call(Object * context,
                                                          argType ref) {
    ErrorManagement::ErrorType err = ErrorManagement::NoError;

    className *actualContext = dynamic_cast<className *>(context);
    if (actualContext == NULL_PTR(className *)) {
        err = ErrorManagement::UnsupportedFeature;
    }
    else {
        (actualContext->*pFun)(ref) ? (err = ErrorManagement::NoError) : (err = ErrorManagement::FatalError);
    }
    return err;
}


template<class className>
ClassMethodCallerT<className, void>::ClassMethodCallerT(bool (className::*f)(void)) {
    pFun = f;
}

template<class className>
ClassMethodCallerT<className, void>::~ClassMethodCallerT() {

}


template<class className>
ErrorManagement::ErrorType ClassMethodCallerT<className, void>::Call(Object * context) {
    ErrorManagement::ErrorType err = ErrorManagement::NoError;

    className *actualContext = dynamic_cast<className *>(context);
    if (actualContext == NULL_PTR(className *)) {
        err = ErrorManagement::UnsupportedFeature;
    }
    else {
        (actualContext->*pFun)() ? (err = ErrorManagement::NoError) : (err = ErrorManagement::FatalError);
    }
    return err;
}

}

#endif /* CLASSMETHODCALLERT_H_ */

