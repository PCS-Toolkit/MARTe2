/**
 * @file GrammarInfo.h
 * @brief Source file for class GrammarInfo
 * @date 18/12/2015
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
 * the class GrammarInfo (public, protected, and private). Be aware that some 
 * methods, such as those inline could be defined on the header file, instead.
 */
#ifndef GRAMMARINFO_H_
#define GRAMMARINFO_H_

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/


#include "GeneralDefinitions.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {

/**
 * @brief Structure which contains the lexical elements for a language, like
 * terminals, separators, operators, and delimiters.
 *
 * @invariant All the characters must be !='\0' and the \a openTypeCast
 * character must be different from the other open terminals.
 */
struct GrammarInfo {

    /**
     * List of separator characters.
     */
    const char8 *separators;

    /**
     * One line comment begin pattern.
     */
    const char8 *beginOneLineComment;

    /**
     * Multiple line comment begin pattern.
     */
    const char8 *beginMultipleLinesComment;

    /**
     * Multiple line comment end pattern.
     */
    const char8 *endMultipleLinesComment;

    /**
     * Assignment operator
     */
    char8 assignment;

    /**
     * Specifies that a block begins
     */
    char8 openBlock;

    /**
     * Specifies that a block ends
     */
    char8 closeBlock;

    /**
     * Specifies that a vector begins
     */
    char8 openVector;

    /**
     * Specifies that a vector ends
     */
    char8 closeVector;

    /**
     * Specifies that a matrix begins
     */
    char8 openMatrix;

    /**
     * Specifies that a matrix ends
     */
    char8 closeMatrix;

    /**
     * Specifies that a type cast expression begins
     */
    char8 openTypeCast;

    /**
     * Specifies that a type cast expression ends
     */
    char8 closeTypeCast;

    /**
     * Allows to get the terminals as a C-string.
     */
    char8 terminal;

};


}

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* GRAMMARINFO_H_ */
