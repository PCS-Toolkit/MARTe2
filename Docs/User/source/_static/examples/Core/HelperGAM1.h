/**
 * @file FixedGAMExample1.h
 * @brief Header file for class FixedGAMExample1
 * @date 06/04/2018
 * @author Andre Neto
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

 * @details This header file contains the declaration of the class HelperGAM1
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef EXAMPLES_CORE_HELPERGAM1_H_
#define EXAMPLES_CORE_HELPERGAM1_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "GAM.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/
namespace MARTe2Tutorial {
/**
 * @brief An example of a GAM which has fixed inputs and outputs.
 *
 * @details This GAM multiplies the input signal by a Gain.
 * The configuration syntax is (names and types are only given as an example):
 *
 * +GAMExample1 = {
 *     Class = HelperGAM1
 *     Gain = 5 //Compulsory
 *     InputSignals = {
 *         Signal1 = {
 *             DataSource = "DDB1"
 *             Type = uint32
 *         }
 *     }
 *     OutputSignals = {
 *         DiffCounter = {   DataSource = DDB1  Type = uint32 }
 *         DACs = {          DataSource = DDB1  Type = int16 NumberOfElements = 64 }
 *         DOs = {           DataSource = DDB1  Type = uint8 NumberOfElements = 4 }
 *         PWMduty = {       DataSource = DDB1  Type = uint16 NumberOfelements = 8 }
 *
 *     }
 * }
 */
class HelperGAM1 : public MARTe::GAM {
public:
    CLASS_REGISTER_DECLARATION()
    /**
     * @brief Constructor. NOOP.
     */
    HelperGAM1();

    /**
     * @brief Destructor. NOOP.
     */
    virtual ~HelperGAM1();

    /**
     * @brief Reads the Gain from the configuration file.
     * @param[in] data see GAM::Initialise. The parameter Gain shall exist and will be read as an uint32.
     * @return true if the parameter Gain can be read.
     */
    virtual bool Initialise(MARTe::StructuredDataI & data);

    /**
     * @brief Verifies correctness of the GAM configuration.
     * @details Checks that the number of input signals is equal to the number of output signals is equal to one and that the same type is used.
     * @return true if the pre-conditions are met.
     * @pre
     *   SetConfiguredDatabase() &&
     *   GetNumberOfInputSignals() == GetNumberOfOutputSignals() == 1 &&
     *   GetSignalType(InputSignals, 0) == GetSignalType(OutputSignals, 0) == uint32 &&
     *   GetSignalNumberOfDimensions(InputSignals, 0) == GetSignalNumberOfDimensions(OutputSignals, 0) == 0 &&
     *   GetSignalNumberOfSamples(InputSignals, 0) == GetSignalNumberOfSamples(OutputSignals, 0) == 1 &&
     *   GetSignalNumberOfElements(InputSignals, 0) == GetSignalNumberOfElements(OutputSignals, 0) == 1
     */
    virtual bool Setup();

    /**
     * @brief Multiplies the input signal by the Gain.
     * @return true.
     */
    virtual bool Execute();

private:

    /**
     * The input signal
     */
    MARTe::uint32 *inputSignal;

    /**
     * The output signal
     */
    MARTe::uint32 *outputSignal;

    /**
     * The configured gain.
     */
    /*
    MARTe::uint32 gain;
    MARTe::uint32 prevval;
    MARTe::int16 *inputadcs;
    MARTe::int16 *outputdacs;
    MARTe::uint8 *outputdos;
    MARTe::uint16 *outputpwms;
    MARTe::uint32 cycle;
    */

    MARTe::float32 *outputrealtime;
    MARTe::int16 *outputadc;
    MARTe::uint8 *outputrfm_in;
    MARTe::float32 *outputwavegen;
    MARTe::uint8 *outputproc_in;

    MARTe::float32 f1, f2;

    MARTe::int32 *inputtime;
    MARTe::int32 *outputtimeformds;
    MARTe::uint8 *outputtriggerformds;

    MARTe::int32 mdstimeoffset;
    MARTe::int32 mdsstarttime;
    MARTe::int32 mdsstoptime;


};
}
/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* EXAMPLES_CORE_HELPERGAM1_H_ */

