/**
 * @file RuntimeEvaluatorFunctionsGTest.cpp
 * @brief Source file for class RuntimeEvaluatorFunctionsGTest
 * @date 06/05/2020
 * @author Didac Magrinya
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
 * the class RuntimeEvaluatorFunctionsGTest (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "RuntimeEvaluatorFunctionsTest.h"
#include "gtest/gtest.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestDefaultConstructor) {
    RuntimeEvaluatorFunctionsTest test;
    ASSERT_TRUE(test.TestDefaultConstructor());
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestDupFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add1In2OutFunction("float64",  "float64",  "float64");
    test.Add1In2OutFunction("float32",  "float32",  "float32");
    test.Add1In2OutFunction("uint64",   "uint64",   "uint64");
    test.Add1In2OutFunction("int64",    "int64",    "int64");
    test.Add1In2OutFunction("uint32",   "uint32",   "uint32");
    test.Add1In2OutFunction("int32",    "int32",    "int32");
    test.Add1In2OutFunction("uint16",   "uint16",   "uint16");
    test.Add1In2OutFunction("int16",    "int16",    "int16");
    test.Add1In2OutFunction("uint8",    "uint8",    "uint8");
    test.Add1In2OutFunction("int8",     "int8",     "int8");

    ASSERT_TRUE(test.TestFunctionTypes("DUP", 1, 2));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestDupExecution) {
    RuntimeEvaluatorFunctionsTest test;

    StreamString rpnCode=
            "CONST int64 -152\n"
            "DUP\n"
            "WRITE RES1\n"
            "WRITE RES2\n";

    int64 expectedResults[] = {-152, -152};

    RuntimeEvaluator context(rpnCode);

    ASSERT_TRUE(test.PrepareContext(context, SignedInteger64Bit));
    ASSERT_TRUE(test.TestFunctionExecution<int64>(context, 2, expectedResults));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestReadFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add1OutFunction("float64");
    test.Add1OutFunction("float32");
    test.Add1OutFunction("uint64");
    test.Add1OutFunction("int64");
    test.Add1OutFunction("uint32");
    test.Add1OutFunction("int32");
    test.Add1OutFunction("uint16");
    test.Add1OutFunction("int16");
    test.Add1OutFunction("uint8");
    test.Add1OutFunction("int8");

    ASSERT_TRUE(test.TestFunctionTypes("READ", 0, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestWriteFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add1InFunction("float64");
    test.Add1InFunction("float32");
    test.Add1InFunction("uint16");
    test.Add1InFunction("int16");
    test.Add1InFunction("uint8");
    test.Add1InFunction("int8");
    for (uint8 i = 0; i < 4; ++i) {
        test.Add1InFunction("uint64");
    }
    for (uint8 i = 0; i < 8; ++i) {
        test.Add1InFunction("int64");
    }
    for (uint8 i = 0; i < 3; ++i) {
        test.Add1InFunction("uint32");
    }
    for (uint8 i = 0; i < 6; ++i) {
        test.Add1InFunction("int32");
    }

    ASSERT_TRUE(test.TestFunctionTypes("WRITE", 1, 0));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestCastFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;
    CCString typeNames[] = {"float64", "float32", "uint64", "int64", "uint32", "int32", "uint16", "int16", "uint8", "int8"};

    for (uint8 i = 0; i < 10; ++i) {
        for (uint8 j = 0; j < 10; ++j) {
            test.Add1In1OutFunction(typeNames[i], typeNames[j]);
        }
    }

    ASSERT_TRUE(test.TestFunctionTypes("CAST", 1, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestSinFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add1In1OutFunction("float32", "float32");
    test.Add1In1OutFunction("float64", "float64");

    ASSERT_TRUE(test.TestFunctionTypes("SIN", 1, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestCosFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add1In1OutFunction("float32", "float32");
    test.Add1In1OutFunction("float64", "float64");

    ASSERT_TRUE(test.TestFunctionTypes("COS", 1, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTanFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add1In1OutFunction("float32", "float32");
    test.Add1In1OutFunction("float64", "float64");

    ASSERT_TRUE(test.TestFunctionTypes("TAN", 1, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestExpFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add1In1OutFunction("float32", "float32");
    test.Add1In1OutFunction("float64", "float64");

    ASSERT_TRUE(test.TestFunctionTypes("EXP", 1, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestLogFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add1In1OutFunction("float32", "float32");
    test.Add1In1OutFunction("float64", "float64");

    ASSERT_TRUE(test.TestFunctionTypes("LOG", 1, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestLog10FunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add1In1OutFunction("float32", "float32");
    test.Add1In1OutFunction("float64", "float64");

    ASSERT_TRUE(test.TestFunctionTypes("LOG10", 1, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestPowFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("float32",  "float32",  "float32");
    test.Add2In1OutFunction("float64",  "float64",  "float64");

    ASSERT_TRUE(test.TestFunctionTypes("POW", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestEqFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("float64",  "float64",  "uint8");
    test.Add2In1OutFunction("float32",  "float32",  "uint8");
    test.Add2In1OutFunction("uint64",   "uint64",   "uint8");
    test.Add2In1OutFunction("int64",    "int64",    "uint8");
    test.Add2In1OutFunction("uint32",   "uint32",   "uint8");
    test.Add2In1OutFunction("int32",    "int32",    "uint8");
    test.Add2In1OutFunction("uint16",   "uint16",   "uint8");
    test.Add2In1OutFunction("int16",    "int16",    "uint8");
    test.Add2In1OutFunction("uint8",    "uint8",    "uint8");
    test.Add2In1OutFunction("int8",     "int8",     "uint8");

    test.AddInputCombinationFunctions("int8",   "int32",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int32",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int32",    "uint8");
    test.AddInputCombinationFunctions("int8",   "int64",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int64",    "uint8");
    test.AddInputCombinationFunctions("int32",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint64", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint32",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint32",   "uint8");
    test.AddInputCombinationFunctions("int8",   "uint64",   "uint8");
    test.AddInputCombinationFunctions("int16",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("int32",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint32", "uint64",   "uint8");

    ASSERT_TRUE(test.TestFunctionTypes("EQ", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestNeqFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("float64",  "float64",  "uint8");
    test.Add2In1OutFunction("float32",  "float32",  "uint8");
    test.Add2In1OutFunction("uint64",   "uint64",   "uint8");
    test.Add2In1OutFunction("int64",    "int64",    "uint8");
    test.Add2In1OutFunction("uint32",   "uint32",   "uint8");
    test.Add2In1OutFunction("int32",    "int32",    "uint8");
    test.Add2In1OutFunction("uint16",   "uint16",   "uint8");
    test.Add2In1OutFunction("int16",    "int16",    "uint8");
    test.Add2In1OutFunction("uint8",    "uint8",    "uint8");
    test.Add2In1OutFunction("int8",     "int8",     "uint8");

    test.AddInputCombinationFunctions("int8",   "int32",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int32",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int32",    "uint8");
    test.AddInputCombinationFunctions("int8",   "int64",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int64",    "uint8");
    test.AddInputCombinationFunctions("int32",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint64", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint32",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint32",   "uint8");
    test.AddInputCombinationFunctions("int8",   "uint64",   "uint8");
    test.AddInputCombinationFunctions("int16",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("int32",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint32", "uint64",   "uint8");

    ASSERT_TRUE(test.TestFunctionTypes("NEQ", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestGtFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("float64",  "float64",  "uint8");
    test.Add2In1OutFunction("float32",  "float32",  "uint8");
    test.Add2In1OutFunction("uint64",   "uint64",   "uint8");
    test.Add2In1OutFunction("int64",    "int64",    "uint8");
    test.Add2In1OutFunction("uint32",   "uint32",   "uint8");
    test.Add2In1OutFunction("int32",    "int32",    "uint8");
    test.Add2In1OutFunction("uint16",   "uint16",   "uint8");
    test.Add2In1OutFunction("int16",    "int16",    "uint8");
    test.Add2In1OutFunction("uint8",    "uint8",    "uint8");
    test.Add2In1OutFunction("int8",     "int8",     "uint8");

    test.AddInputCombinationFunctions("int8",   "int32",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int32",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int32",    "uint8");
    test.AddInputCombinationFunctions("int8",   "int64",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int64",    "uint8");
    test.AddInputCombinationFunctions("int32",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint64", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint32",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint32",   "uint8");
    test.AddInputCombinationFunctions("int8",   "uint64",   "uint8");
    test.AddInputCombinationFunctions("int16",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("int32",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint32", "uint64",   "uint8");

    ASSERT_TRUE(test.TestFunctionTypes("GT", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestLtFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("float64",  "float64",  "uint8");
    test.Add2In1OutFunction("float32",  "float32",  "uint8");
    test.Add2In1OutFunction("uint64",   "uint64",   "uint8");
    test.Add2In1OutFunction("int64",    "int64",    "uint8");
    test.Add2In1OutFunction("uint32",   "uint32",   "uint8");
    test.Add2In1OutFunction("int32",    "int32",    "uint8");
    test.Add2In1OutFunction("uint16",   "uint16",   "uint8");
    test.Add2In1OutFunction("int16",    "int16",    "uint8");
    test.Add2In1OutFunction("uint8",    "uint8",    "uint8");
    test.Add2In1OutFunction("int8",     "int8",     "uint8");

    test.AddInputCombinationFunctions("int8",   "int32",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int32",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int32",    "uint8");
    test.AddInputCombinationFunctions("int8",   "int64",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int64",    "uint8");
    test.AddInputCombinationFunctions("int32",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint64", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint32",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint32",   "uint8");
    test.AddInputCombinationFunctions("int8",   "uint64",   "uint8");
    test.AddInputCombinationFunctions("int16",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("int32",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint32", "uint64",   "uint8");

    ASSERT_TRUE(test.TestFunctionTypes("LT", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestGteFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("float64",  "float64",  "uint8");
    test.Add2In1OutFunction("float32",  "float32",  "uint8");
    test.Add2In1OutFunction("uint64",   "uint64",   "uint8");
    test.Add2In1OutFunction("int64",    "int64",    "uint8");
    test.Add2In1OutFunction("uint32",   "uint32",   "uint8");
    test.Add2In1OutFunction("int32",    "int32",    "uint8");
    test.Add2In1OutFunction("uint16",   "uint16",   "uint8");
    test.Add2In1OutFunction("int16",    "int16",    "uint8");
    test.Add2In1OutFunction("uint8",    "uint8",    "uint8");
    test.Add2In1OutFunction("int8",     "int8",     "uint8");

    test.AddInputCombinationFunctions("int8",   "int32",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int32",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int32",    "uint8");
    test.AddInputCombinationFunctions("int8",   "int64",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int64",    "uint8");
    test.AddInputCombinationFunctions("int32",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint64", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint32",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint32",   "uint8");
    test.AddInputCombinationFunctions("int8",   "uint64",   "uint8");
    test.AddInputCombinationFunctions("int16",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("int32",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint32", "uint64",   "uint8");

    ASSERT_TRUE(test.TestFunctionTypes("GTE", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestLteFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("float64",  "float64",  "uint8");
    test.Add2In1OutFunction("float32",  "float32",  "uint8");
    test.Add2In1OutFunction("uint64",   "uint64",   "uint8");
    test.Add2In1OutFunction("int64",    "int64",    "uint8");
    test.Add2In1OutFunction("uint32",   "uint32",   "uint8");
    test.Add2In1OutFunction("int32",    "int32",    "uint8");
    test.Add2In1OutFunction("uint16",   "uint16",   "uint8");
    test.Add2In1OutFunction("int16",    "int16",    "uint8");
    test.Add2In1OutFunction("uint8",    "uint8",    "uint8");
    test.Add2In1OutFunction("int8",     "int8",     "uint8");

    test.AddInputCombinationFunctions("int8",   "int32",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int32",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int32",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int32",    "uint8");
    test.AddInputCombinationFunctions("int8",   "int64",    "uint8");
    test.AddInputCombinationFunctions("int16",  "int64",    "uint8");
    test.AddInputCombinationFunctions("int32",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "int64",    "uint8");
    test.AddInputCombinationFunctions("uint16", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint32", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint64", "int64",    "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint32",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint32",   "uint8");
    test.AddInputCombinationFunctions("int8",   "uint64",   "uint8");
    test.AddInputCombinationFunctions("int16",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("int32",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint8",  "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint16", "uint64",   "uint8");
    test.AddInputCombinationFunctions("uint32", "uint64",   "uint8");

    ASSERT_TRUE(test.TestFunctionTypes("LTE", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestAndFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("uint8", "uint8", "uint8");

    ASSERT_TRUE(test.TestFunctionTypes("AND", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestOrFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("uint8", "uint8", "uint8");

    ASSERT_TRUE(test.TestFunctionTypes("OR", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestXorFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("uint8", "uint8", "uint8");

    ASSERT_TRUE(test.TestFunctionTypes("XOR", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestAddFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("float64", "float64", "float64");
    test.Add2In1OutFunction("float32", "float32", "float32");

    test.Add2In1OutFunction("int8",   "int8",     "int32");
    test.Add2In1OutFunction("int16",  "int16",    "int32");

    test.Add2In1OutFunction("int32",  "int32",    "int64");
    test.Add2In1OutFunction("int64",  "int64",    "int64");

    test.Add2In1OutFunction("uint8",  "uint8",    "uint32");
    test.Add2In1OutFunction("uint16", "uint16",   "uint32");
    test.Add2In1OutFunction("uint32", "uint32",   "uint32");

    test.Add2In1OutFunction("uint32", "uint32",   "uint64");
    test.Add2In1OutFunction("uint64", "uint64",   "uint64");

    test.AddInputCombinationFunctions("int8",   "int32",    "int32");
    test.AddInputCombinationFunctions("int16",  "int32",    "int32");
    test.AddInputCombinationFunctions("uint8",  "int32",    "int32");
    test.AddInputCombinationFunctions("uint16", "int32",    "int32");
    test.AddInputCombinationFunctions("uint32", "int32",    "int32");

    test.AddInputCombinationFunctions("int8",   "int64",    "int64");
    test.AddInputCombinationFunctions("int16",  "int64",    "int64");
    test.AddInputCombinationFunctions("int32",  "int64",    "int64");
    test.AddInputCombinationFunctions("uint8",  "int64",    "int64");
    test.AddInputCombinationFunctions("uint16", "int64",    "int64");
    test.AddInputCombinationFunctions("uint32", "int64",    "int64");
    test.AddInputCombinationFunctions("uint64", "int64",    "int64");

    test.AddInputCombinationFunctions("uint8",  "uint32",   "uint32");
    test.AddInputCombinationFunctions("uint16", "uint32",   "uint32");

    test.AddInputCombinationFunctions("uint8",  "uint64",   "uint64");
    test.AddInputCombinationFunctions("uint16", "uint64",   "uint64");
    test.AddInputCombinationFunctions("uint32", "uint64",   "uint64");

    ASSERT_TRUE(test.TestFunctionTypes("ADD", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestSubFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("float64",  "float64",  "float64");
    test.Add2In1OutFunction("float32",  "float32",  "float32");

    test.Add2In1OutFunction("int8",     "int8",     "int32");
    test.Add2In1OutFunction("int16",    "int16",    "int32");
    test.Add2In1OutFunction("int32",    "int32",    "int32");
    test.Add2In1OutFunction("uint8",    "uint8",    "int32");
    test.Add2In1OutFunction("uint16",   "uint16",   "int32");
    test.Add2In1OutFunction("uint32",   "uint32",   "int32");

    test.Add2In1OutFunction("uint64",   "uint64",   "int64");
    test.Add2In1OutFunction("int64",    "int64",    "int64");

    test.AddInputCombinationFunctions("int8",   "int32",    "int32");
    test.AddInputCombinationFunctions("int16",  "int32",    "int32");
    test.AddInputCombinationFunctions("uint8",  "int32",    "int32");
    test.AddInputCombinationFunctions("uint16", "int32",    "int32");
    test.AddInputCombinationFunctions("uint32", "int32",    "int32");
    test.AddInputCombinationFunctions("uint8",  "uint32",   "int32");
    test.AddInputCombinationFunctions("uint16", "uint32",   "int32");

    test.AddInputCombinationFunctions("int8",   "int64",    "int64");
    test.AddInputCombinationFunctions("int16",  "int64",    "int64");
    test.AddInputCombinationFunctions("int32",  "int64",    "int64");
    test.AddInputCombinationFunctions("uint8",  "int64",    "int64");
    test.AddInputCombinationFunctions("uint16", "int64",    "int64");
    test.AddInputCombinationFunctions("uint32", "int64",    "int64");
    test.AddInputCombinationFunctions("uint64", "int64",    "int64");
    test.AddInputCombinationFunctions("uint8",  "uint64",   "int64");
    test.AddInputCombinationFunctions("uint16", "uint64",   "int64");
    test.AddInputCombinationFunctions("uint32", "uint64",   "int64");

    ASSERT_TRUE(test.TestFunctionTypes("SUB", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestMulFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("float64", "float64", "float64");
    test.Add2In1OutFunction("float32", "float32", "float32");

    test.Add2In1OutFunction("int8",   "int8",     "int32");
    test.Add2In1OutFunction("int16",  "int16",    "int32");

    test.Add2In1OutFunction("int32",  "int32",    "int64");
    test.Add2In1OutFunction("int64",  "int64",    "int64");

    test.Add2In1OutFunction("uint8",  "uint8",    "uint32");
    test.Add2In1OutFunction("uint16", "uint16",   "uint32");
    test.Add2In1OutFunction("uint32", "uint32",   "uint32");

    test.Add2In1OutFunction("uint32", "uint32",   "uint64");
    test.Add2In1OutFunction("uint64", "uint64",   "uint64");

    test.AddInputCombinationFunctions("int8",   "int32",    "int32");
    test.AddInputCombinationFunctions("int16",  "int32",    "int32");
    test.AddInputCombinationFunctions("uint8",  "int32",    "int32");
    test.AddInputCombinationFunctions("uint16", "int32",    "int32");
    test.AddInputCombinationFunctions("uint32", "int32",    "int32");

    test.AddInputCombinationFunctions("int8",   "int64",    "int64");
    test.AddInputCombinationFunctions("int16",  "int64",    "int64");
    test.AddInputCombinationFunctions("int32",  "int64",    "int64");
    test.AddInputCombinationFunctions("uint8",  "int64",    "int64");
    test.AddInputCombinationFunctions("uint16", "int64",    "int64");
    test.AddInputCombinationFunctions("uint32", "int64",    "int64");
    test.AddInputCombinationFunctions("uint64", "int64",    "int64");

    test.AddInputCombinationFunctions("uint8",  "uint32",   "uint32");
    test.AddInputCombinationFunctions("uint16", "uint32",   "uint32");

    test.AddInputCombinationFunctions("uint8",  "uint64",   "uint64");
    test.AddInputCombinationFunctions("uint16", "uint64",   "uint64");
    test.AddInputCombinationFunctions("uint32", "uint64",   "uint64");

    ASSERT_TRUE(test.TestFunctionTypes("MUL", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestDivFunctionTypes) {
    RuntimeEvaluatorFunctionsTest test;

    test.Add2In1OutFunction("float64", "float64", "float64");
    test.Add2In1OutFunction("float32", "float32", "float32");

    test.Add2In1OutFunction("int8",   "int8",     "int8");
    test.Add2In1OutFunction("int16",  "int16",    "int16");
    test.Add2In1OutFunction("int32",  "int32",    "int32");
    test.Add2In1OutFunction("int64",  "int64",    "int64");

    test.Add2In1OutFunction("uint8",  "uint8",    "uint8");
    test.Add2In1OutFunction("uint16", "uint16",   "uint16");
    test.Add2In1OutFunction("uint32", "uint32",   "uint32");
    test.Add2In1OutFunction("uint64", "uint64",   "uint64");

    test.AddInputCombinationFunctions("int8",   "int32",    "int32");
    test.AddInputCombinationFunctions("int16",  "int32",    "int32");
    test.AddInputCombinationFunctions("uint8",  "int32",    "int32");
    test.AddInputCombinationFunctions("uint16", "int32",    "int32");
    test.AddInputCombinationFunctions("uint32", "int32",    "int32");

    test.AddInputCombinationFunctions("int8",   "int64",    "int64");
    test.AddInputCombinationFunctions("int16",  "int64",    "int64");
    test.AddInputCombinationFunctions("int32",  "int64",    "int64");
    test.AddInputCombinationFunctions("uint8",  "int64",    "int64");
    test.AddInputCombinationFunctions("uint16", "int64",    "int64");
    test.AddInputCombinationFunctions("uint32", "int64",    "int64");
    test.AddInputCombinationFunctions("uint64", "int64",    "int64");

    test.AddInputCombinationFunctions("uint8",  "uint32",   "uint32");
    test.AddInputCombinationFunctions("uint16", "uint32",   "uint32");

    test.AddInputCombinationFunctions("uint8",  "uint64",   "uint64");
    test.AddInputCombinationFunctions("uint16", "uint64",   "uint64");
    test.AddInputCombinationFunctions("uint32", "uint64",   "uint64");

    ASSERT_TRUE(test.TestFunctionTypes("DIV", 2, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeSuccessful) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float32Bit, Float64Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 1, 1, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    typeStack.Push(Float32Bit);

    ASSERT_TRUE(test.TestTryConsume(functionUT, "Test", typeStack, false, true, 1, 2));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeSuccessful_NoInputs) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float64Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 0, 1, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    ASSERT_TRUE(test.TestTryConsume(functionUT, "Test", typeStack, false, true, 0, 2));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeSuccessful_NoOutputs) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float32Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 1, 0, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    typeStack.Push(Float32Bit);

    ASSERT_TRUE(test.TestTryConsume(functionUT, "Test", typeStack, false, true, 1, 0));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeSuccessful_MultipleInputs) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float32Bit, UnsignedInteger64Bit, Float64Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 2, 1, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    typeStack.Push(UnsignedInteger64Bit);
    typeStack.Push(Float32Bit);

    ASSERT_TRUE(test.TestTryConsume(functionUT, "Test", typeStack, false, true, 3, 2));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeSuccessful_MultipleOutputs) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float32Bit, Float64Bit, UnsignedInteger32Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 1, 2, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    typeStack.Push(Float32Bit);

    ASSERT_TRUE(test.TestTryConsume(functionUT, "Test", typeStack, false, true, 1, 3));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeSuccessful_StackLeftover) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float32Bit, Float64Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 1, 1, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    typeStack.Push(UnsignedInteger8Bit);
    typeStack.Push(Float32Bit);

    ASSERT_TRUE(test.TestTryConsume(functionUT, "Test", typeStack, false, true, 2, 3));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeSuccessful_MatchOutput) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float32Bit, Float64Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 1, 1, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    typeStack.Push(Float32Bit);
    typeStack.Push(Float64Bit);

    ASSERT_TRUE(test.TestTryConsume(functionUT, "Test", typeStack, true, true, 1, 2));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeFailed_WrongName) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float32Bit, Float64Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 1, 1, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    typeStack.Push(Float32Bit);

    ASSERT_TRUE(test.TestTryConsume(functionUT, "WrongName", typeStack, false, false, 1, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeFailed_MissingInput) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float32Bit, Float64Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 1, 1, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    ASSERT_TRUE(test.TestTryConsume(functionUT, "Test", typeStack, false, false, 0, 0));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeFailed_WrongInputType) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float32Bit, Float64Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 1, 1, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    typeStack.Push(SignedInteger32Bit);

    ASSERT_TRUE(test.TestTryConsume(functionUT, "Test", typeStack, false, false, 1, 1));
}


TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeFailed_MatchOutputMissingOutput) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float32Bit, Float64Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 1, 1, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    typeStack.Push(Float32Bit);

    ASSERT_TRUE(test.TestTryConsume(functionUT, "Test", typeStack, true, false, 1, 1));
}

TEST(BareMetal_L4Configuration_RuntimeEvaluatorFunctionsGTest,TestTryConsumeFailed_MatchOutputWrongOutput) {
    RuntimeEvaluatorFunctionsTest test;

    TypeDescriptor functionTypes[] = {Float32Bit, Float64Bit};
    RuntimeEvaluatorFunctions functionUT("Test", 1, 1, &(functionTypes[0]), &MockFunction);
    StaticStack<TypeDescriptor,32> typeStack;

    typeStack.Push(Float32Bit);
    typeStack.Push(Float32Bit);

    ASSERT_TRUE(test.TestTryConsume(functionUT, "Test", typeStack, true, false, 2, 2));
}
