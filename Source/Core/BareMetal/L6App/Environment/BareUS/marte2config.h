namespace MARTe {
    const char* configFile = 
    "$TestApp = {"
    "    Class = RealTimeApplication"
    "    +Functions = {"
    "        Class = ReferenceContainer"
    "        +GAMTimer = {"
    "            Class = IOGAM"
    "            InputSignals = {"
    "                Counter = {"
    "                    DataSource = Timer"
    "                    Type = uint32"
    "                }"
    "                Time = {"
    "                    Frequency = 1"
    "                    DataSource = Timer"
    "                    Type = uint32"
    "                }"
    "            }"
    "            OutputSignals = {"
    "                Counter = {"             	
    "                    DataSource = DDB1"
    "                    Type = uint32"
    "                }"
    "                Time = {"
    "                    DataSource = LoggerDS"
    "                    Type = uint32"
    "                }"
    "            }"
    "        }"
    "    }"
    "    +Data = {"
    "        Class = ReferenceContainer"
    "        DefaultDataSource = DDB1"
    "        +DDB1 = {"
    "            Class = GAMDataSource"
    "       	}"
    "        +LoggerDS = {"
    "            Class = LoggerDataSource"
    "        }" 
    "        +Timer = {"
    "            Class = LinuxTimer"
    "            SleepNature = \"Default\""
    "            ExecutionMode = \"RealTimeThread\""
    "            Signals = {"
    "                Counter = {"
    "                    Type = uint32"
    "                }"
    "                Time = {"
    "                    Type = uint32"
    "                }"
    "            }"
    "        }"
"            +Timings = {"
"               Class = TimingDataSource"
"            }"
    "    }"
    "    +States = {"
    "        Class = ReferenceContainer"
    "        +State1 = {"
    "            Class = RealTimeState"
    "            +Threads = {"
    "                Class = ReferenceContainer"
    "                +Thread1 = {"
    "                    Class = RealTimeThread"
    "                    CPUs = 0xFF"
    "                    Functions = { GAMTimer }"
    "                }"
    "            }"
    "        }"   
    "    }"
    "    +Scheduler = {"
    "        Class = GAMBareScheduler"
    "        TimingDataSource = Timings"
    "    }"
    "}";

}
