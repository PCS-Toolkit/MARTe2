/**
 * @file HttpMessageInterfaceTest.cpp
 * @brief Source file for class HttpMessageInterfaceTest
 * @date 18/03/2019
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

 * @details This source file contains the definition of all the methods for
 * the class HttpMessageInterfaceTest (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/
#include <stdio.h>

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#include "CLASSMETHODREGISTER.h"
#include "Directory.h"
#include "File.h"
#include "HttpClient.h"
#include "HttpMessageInterface.h"
#include "HttpMessageInterfaceTest.h"
#include "HttpObjectBrowser.h"
#include "HttpService.h"
#include "ObjectRegistryDatabase.h"
#include "StandardParser.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/
class HttpMessageInterfaceTestObject : public MARTe::Object, public MARTe::MessageI {
public:
    CLASS_REGISTER_DECLARATION()

HttpMessageInterfaceTestObject    () {
        MARTe::ReferenceT<MARTe::RegisteredMethodsMessageFilter> filter = MARTe::ReferenceT<MARTe::RegisteredMethodsMessageFilter>(MARTe::GlobalObjectsDatabase::Instance()->GetStandardHeap());
        filter->SetDestination(this);
        InstallMessageFilter(filter);
        flag = 0;
    }

    MARTe::ErrorManagement::ErrorType ReceiverMethod(MARTe::ReferenceContainer& ref) {
        flag++;
        return MARTe::ErrorManagement::NoError;
    }

    MARTe::int32 flag;

};
CLASS_REGISTER(HttpMessageInterfaceTestObject, "1.0")
CLASS_METHOD_REGISTER(HttpMessageInterfaceTestObject, ReceiverMethod)

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

bool HttpMessageInterfaceTest::TestInitialise() {
    using namespace MARTe;
    StreamString cfg = ""
            "+HttpService1 = {\n"
            "    Class = HttpService\n"
            "    Port = 9094\n"
            "    Timeout = 0\n"
            "    AcceptTimeout = 100"
            "    MinNumberOfThreads = 1\n"
            "    MaxNumberOfThreads = 8\n"
            "    ListenMaxConnections = 255\n"
            "    IsTextMode = 0\n"
            "    WebRoot = HttpObjectBrowser1\n"
            "}\n"
            "+HttpObjectBrowser1 = {\n"
            "    Class = HttpObjectBrowser\n"
            "    Root = \".\""
            "    +AChild = {\n"
            "        Class = ReferenceContainer\n"
            "    }\n"
            "    +DirectoryResource1 = {\n"
            "        Class = HttpDirectoryResource\n"
            "        BaseDir = \"HttpMessageInterfaceTestFolder\""
            "    }\n"
            "}\n";

    Directory d("HttpMessageInterfaceTestFolder");
    d.Create();
    File f;
    f.Open("HttpMessageInterfaceTestFolder/HttpMessageInterfaceTest.txt", BasicFile::FLAG_CREAT | BasicFile::ACCESS_MODE_W);
    f.Printf("Test %d", 1);
    f.Flush();
    f.Close();
    cfg.Seek(0LLU);
    StreamString err;
    ConfigurationDatabase cdb;
    StandardParser parser(cfg, cdb, &err);
    bool ok = parser.Parse();
    if (ok) {
        ok = cdb.MoveToRoot();
    }
    if (ok) {
        ok = ObjectRegistryDatabase::Instance()->Initialise(cdb);
    }
    ObjectRegistryDatabase::Instance()->Purge();

    return ok;
}

bool HttpMessageInterfaceTest::TestInitialise_False_No_BaseDir() {
    using namespace MARTe;
    ConfigurationDatabase cdb;
    ReferenceT<HttpDirectoryResource> httpDirectoryResource(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    bool ok = !httpDirectoryResource->Initialise(cdb);
    ObjectRegistryDatabase::Instance()->Purge();
    return ok;
}

bool HttpMessageInterfaceTest::TestGetAsStructuredData_Directory() {
    using namespace MARTe;
    StreamString cfg = ""
            "+HttpService1 = {\n"
            "    Class = HttpService\n"
            "    Port = 9094\n"
            "    Timeout = 0\n"
            "    AcceptTimeout = 100"
            "    MinNumberOfThreads = 1\n"
            "    MaxNumberOfThreads = 8\n"
            "    ListenMaxConnections = 255\n"
            "    IsTextMode = 0\n"
            "    WebRoot = HttpObjectBrowser1\n"
            "}\n"
            "+HttpObjectBrowser1 = {\n"
            "    Class = HttpObjectBrowser\n"
            "    Root = \".\""
            "    +AChild = {\n"
            "        Class = ReferenceContainer\n"
            "    }\n"
            "    +DirectoryResource1 = {\n"
            "        Class = HttpDirectoryResource\n"
            "        BaseDir = \"HttpMessageInterfaceTestFolder\""
            "    }\n"
            "}\n";

    Directory d("HttpMessageInterfaceTestFolder");
    d.Create();
    File f;
    f.Open("HttpMessageInterfaceTestFolder/HttpMessageInterfaceTest.txt", BasicFile::FLAG_CREAT | BasicFile::ACCESS_MODE_W);
    f.Printf("Test %d", 1);
    f.Flush();
    f.Close();
    cfg.Seek(0LLU);
    StreamString err;
    ConfigurationDatabase cdb;
    StandardParser parser(cfg, cdb, &err);
    bool ok = parser.Parse();
    if (ok) {
        ok = cdb.MoveToRoot();
    }
    if (ok) {
        ok = ObjectRegistryDatabase::Instance()->Initialise(cdb);
    }
    ReferenceT<HttpService> service = ObjectRegistryDatabase::Instance()->Find("HttpService1");
    ok = service.IsValid();

    if (ok) {
        ok = service->Start();
    }
    HttpClient test;
    test.SetServerAddress("127.0.0.1");
    test.SetServerPort(9094);
    test.SetServerUri("/DirectoryResource1?path=.");
    StreamString reply;
    if (ok) {
        ok = test.HttpExchange(reply, HttpDefinition::HSHCGet, NULL, 1000u);
    }
    const char8 * expectedReply = ""
            "1F\r\n{\n\r\"Name\": \"DirectoryResource1\"\r\n"
            "20\r\n,\n\r\"Class\": \"HttpDirectoryResour\r\n"
            "3\r\nce\"\r\nD\r\n\n\r,\"Files\": {\r\n8\r\n\n\r\"0\": {\r\n"
            "20\r\n\n\r\"Name\": \"HttpDirectoryResource\r\nF\r\nTestFolder/./.\"\r\n"
            "15\r\n,\n\r\"IsDirectory\": \"1\"\r\nF\r\n,\n\r\"Size\": \""
            "43\"\r\n3\r\n\n\r}\r\n9\r\n,\n\r\"1\": {\r\n"
            "20\r\n\n\r\"Name\": \"HttpDirectoryResource\r\n"
            "10\r\nTestFolder/./..\"\r\n"
            "15\r\n,\n\r\"IsDirectory\": \"1\"\r\n"
            "11\r\n,\n\r\"Size\": \"4096\"\r\n3\r\n\n\r}\r\n"
            "9\r\n,\n\r\"2\": {\r\n"
            "20\r\n\n\r\"Name\": \"HttpDirectoryResource\r\n"
            "20\r\nTestFolder/./HttpDirectoryResour\r\n"
            "B\r\nceTest.txt\"\r\n"
            "15\r\n,\n\r\"IsDirectory\": \"0\"\r\nE\r\n,\n\r\"Size\": \"6\"\r\n"
            "3\r\n\n\r}\r\n3\r\n\n\r}\r\n1\r\n}\r\n0\r\n\r\n";
    if (ok) {
        ok = (reply == expectedReply);
    }
    if (ok) {
        ok = service->Stop();
    }
    ObjectRegistryDatabase::Instance()->Purge();

    Directory df1("HttpMessageInterfaceTestFolder/HttpMessageInterfaceTest.txt");
    df1.Delete();
    d.Delete();
    return ok;
}

bool HttpMessageInterfaceTest::TestGetAsStructuredData_File() {
    using namespace MARTe;
    StreamString cfg = ""
            "+HttpService1 = {\n"
            "    Class = HttpService\n"
            "    Port = 9094\n"
            "    Timeout = 0\n"
            "    AcceptTimeout = 100"
            "    MinNumberOfThreads = 1\n"
            "    MaxNumberOfThreads = 8\n"
            "    ListenMaxConnections = 255\n"
            "    IsTextMode = 0\n"
            "    WebRoot = HttpObjectBrowser1\n"
            "}\n"
            "+HttpObjectBrowser1 = {\n"
            "    Class = HttpObjectBrowser\n"
            "    Root = \".\""
            "    +AChild = {\n"
            "        Class = ReferenceContainer\n"
            "    }\n"
            "    +DirectoryResource1 = {\n"
            "        Class = HttpDirectoryResource\n"
            "        BaseDir = \"HttpMessageInterfaceTestFolder\""
            "    }\n"
            "}\n";

    Directory d("HttpMessageInterfaceTestFolder");
    d.Create();
    File f;
    f.Open("HttpMessageInterfaceTestFolder/HttpMessageInterfaceTest.txt", BasicFile::FLAG_CREAT | BasicFile::ACCESS_MODE_W);
    f.Printf("Test %d", 1);
    f.Flush();
    f.Close();
    cfg.Seek(0LLU);
    StreamString err;
    ConfigurationDatabase cdb;
    StandardParser parser(cfg, cdb, &err);
    bool ok = parser.Parse();
    if (ok) {
        ok = cdb.MoveToRoot();
    }
    if (ok) {
        ok = ObjectRegistryDatabase::Instance()->Initialise(cdb);
    }
    ReferenceT<HttpService> service = ObjectRegistryDatabase::Instance()->Find("HttpService1");
    ok = service.IsValid();

    if (ok) {
        ok = service->Start();
    }
    HttpClient test;
    test.SetServerAddress("127.0.0.1");
    test.SetServerPort(9094);
    test.SetServerUri("/DirectoryResource1?path=HttpMessageInterfaceTest.txt");
    StreamString reply;
    if (ok) {
        ok = test.HttpExchange(reply, HttpDefinition::HSHCGet, NULL, 1000u);
    }
    const char8 * expectedReply = ""
            "1F\r\n{\n\r\"Name\": \"DirectoryResource1\"\r\n"
            "20\r\n,\n\r\"Class\": \"HttpDirectoryResour\r\n"
            "3\r\nce\"\r\nD\r\n\n\r,\"Files\": {\r\n"
            "8\r\n\n\r\"0\": {\r\n"
            "20\r\n\n\r\"Name\": \"HttpDirectoryResource\r\n"
            "20\r\nTestFolder/HttpDirectoryResource\r\n9\r\nTest.txt\"\r\n"
            "15\r\n,\n\r\"IsDirectory\": \"0\"\r\nE\r\n,\n\r\"Size\": \"6\"\r\n"
            "3\r\n\n\r}\r\n3\r\n\n\r}\r\n1\r\n}\r\n0\r\n\r\n";
    if (ok) {
        ok = (reply == expectedReply);
    }
    if (ok) {
        ok = service->Stop();
    }
    ObjectRegistryDatabase::Instance()->Purge();

    Directory df1("HttpMessageInterfaceTestFolder/HttpMessageInterfaceTest.txt");
    df1.Delete();
    d.Delete();
    return ok;
}

bool HttpMessageInterfaceTest::TestGetAsText() {
    using namespace MARTe;
    StreamString cfg = ""
            "+HttpService1 = {\n"
            "    Class = HttpService\n"
            "    Port = 9094\n"
            "    Timeout = 0\n"
            "    AcceptTimeout = 100"
            "    MinNumberOfThreads = 1\n"
            "    MaxNumberOfThreads = 8\n"
            "    ListenMaxConnections = 255\n"
            "    IsTextMode = 1\n"
            "    WebRoot = HttpObjectBrowser1\n"
            "}\n"
            "+HttpObjectBrowser1 = {\n"
            "    Class = HttpObjectBrowser\n"
            "    Root = \".\""
            "    +AChild = {\n"
            "        Class = ReferenceContainer\n"
            "    }\n"
            "    +DirectoryResource1 = {\n"
            "        Class = HttpDirectoryResource\n"
            "        BaseDir = \"HttpMessageInterfaceTestFolder\""
            "    }\n"
            "}\n";

    Directory d("HttpMessageInterfaceTestFolder");
    d.Create();
    File f;
    f.Open("HttpMessageInterfaceTestFolder/index.html", BasicFile::FLAG_CREAT | BasicFile::ACCESS_MODE_W);
    f.Printf("<html>Test %d</html>", 1);
    f.Flush();
    f.Close();
    cfg.Seek(0LLU);
    StreamString err;
    ConfigurationDatabase cdb;
    StandardParser parser(cfg, cdb, &err);
    bool ok = parser.Parse();
    if (ok) {
        ok = cdb.MoveToRoot();
    }
    if (ok) {
        ok = ObjectRegistryDatabase::Instance()->Initialise(cdb);
    }
    ReferenceT<HttpService> service = ObjectRegistryDatabase::Instance()->Find("HttpService1");
    ok = service.IsValid();

    if (ok) {
        ok = service->Start();
    }
    HttpClient test;
    test.SetServerAddress("127.0.0.1");
    test.SetServerPort(9094);
    test.SetServerUri(".");
    StreamString reply;
    if (ok) {
        ok = test.HttpExchange(reply, HttpDefinition::HSHCGet, NULL, 1000u);
    }
    const char8 * expectedReply = "<html>Test 1</html>";
    if (ok) {
        ok = (reply == expectedReply);
    }
    if (ok) {
        ok = service->Stop();
    }
    ObjectRegistryDatabase::Instance()->Purge();

    Directory df1("HttpMessageInterfaceTestFolder/index.html");
    df1.Delete();
    d.Delete();

    return ok;
}

bool HttpMessageInterfaceTest::TestGetAsText_MimeTypes() {
    using namespace MARTe;
    StreamString cfg = ""
            "+HttpService1 = {\n"
            "    Class = HttpService\n"
            "    Port = 9094\n"
            "    Timeout = 0\n"
            "    AcceptTimeout = 100"
            "    MinNumberOfThreads = 1\n"
            "    MaxNumberOfThreads = 8\n"
            "    ListenMaxConnections = 255\n"
            "    IsTextMode = 1\n"
            "    WebRoot = HttpObjectBrowser1\n"
            "}\n"
            "+HttpObjectBrowser1 = {\n"
            "    Class = HttpObjectBrowser\n"
            "    Root = \".\""
            "    +AChild = {\n"
            "        Class = ReferenceContainer\n"
            "    }\n"
            "    +DirectoryResource1 = {\n"
            "        Class = HttpDirectoryResource\n"
            "        BaseDir = \".\""
            "    }\n"
            "}\n";

    Directory d("HttpMessageInterfaceTestFolder");
    d.Create();

    const uint32 nOfFiles = 11u;
    const char8 * filenames[nOfFiles] = { "HttpMessageInterfaceTestFolder/f1.htm", "HttpMessageInterfaceTestFolder/f1.html", "HttpMessageInterfaceTestFolder/f1.txt",
            "HttpMessageInterfaceTestFolder/f1.csv", "HttpMessageInterfaceTestFolder/f1.css", "HttpMessageInterfaceTestFolder/f1.gif", "HttpMessageInterfaceTestFolder/f1.jpeg",
            "HttpMessageInterfaceTestFolder/f1.jpg", "HttpMessageInterfaceTestFolder/f1.jnlp", "HttpMessageInterfaceTestFolder/f1.js", "HttpMessageInterfaceTestFolder/f1.bin" };
    uint32 n;
    for (n = 0u; n < nOfFiles; n++) {
        File f;
        f.Open(filenames[n], BasicFile::FLAG_CREAT | BasicFile::ACCESS_MODE_W);
        f.Printf("<html>Test %d</html>", 1);
        f.Flush();
        f.Close();
    }
    cfg.Seek(0LLU);
    StreamString err;
    ConfigurationDatabase cdb;
    StandardParser parser(cfg, cdb, &err);
    bool ok = parser.Parse();
    if (ok) {
        ok = cdb.MoveToRoot();
    }
    if (ok) {
        ok = ObjectRegistryDatabase::Instance()->Initialise(cdb);
    }
    ReferenceT<HttpService> service = ObjectRegistryDatabase::Instance()->Find("HttpService1");
    ok = service.IsValid();

    if (ok) {
        ok = service->Start();
    }
    for (n = 0u; (n < nOfFiles) && (ok); n++) {
        HttpClient test;
        test.SetServerAddress("127.0.0.1");
        test.SetServerPort(9094);
        StreamString p;
        p.Printf("/?path=%s", filenames[n]);
        test.SetServerUri(p.Buffer());
        StreamString reply;
        if (ok) {
            ok = test.HttpExchange(reply, HttpDefinition::HSHCGet, NULL, 1000u);
        }
        const char8 * expectedReply = "<html>Test 1</html>";
        if (ok) {
            ok = (reply == expectedReply);
        }
    }
    if (ok) {
        ok = service->Stop();
    }
    ObjectRegistryDatabase::Instance()->Purge();

    for (n = 0u; n < nOfFiles; n++) {
        Directory df1(filenames[n]);
        df1.Delete();
    }
    d.Delete();

    return ok;
}

