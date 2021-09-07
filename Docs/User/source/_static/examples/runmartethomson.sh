#./MARTeApp.sh -l SPCRealTimeLoader -f ./Configurations/RTThomson-FAT.cfg -m ShotManager:Start
#DEMUX=0 EXT_UCLK=1 ./MARTeApp.sh -l SPCRealTimeLoader -f ./Configurations/RTThomson-2threads.cfg -m ShotManager:Start
DEMUX=0 EXT_UCLK=0 ./MARTeApp.sh -l SPCRealTimeLoader -f ./Configurations/RTThomson-2threads.cfg -m ShotManager:Start
#./MARTeApp.sh -l RealTimeLoader -f ./Configurations/SimulinkWrapperTester.cfg 
