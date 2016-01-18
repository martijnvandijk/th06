##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ServerSocketHandler
ConfigurationName      :=Debug
WorkspacePath          := "/home/pi/swirli/ServerSocketHandler"
ProjectPath            := "/home/pi/swirli/ServerSocketHandler/ServerSocketHandler"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=aydin
Date                   :=01/14/16
CodeLitePath           :="/home/aydin/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="ServerSocketHandler.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -pthread -lcrypto
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall -std=gnu++11 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/base64.cpp$(ObjectSuffix) $(IntermediateDirectory)/websocket.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/PracticalSocket.cpp$(ObjectSuffix) $(IntermediateDirectory)/broadcaster.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/base64.cpp$(ObjectSuffix): base64.cpp $(IntermediateDirectory)/base64.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/swirli/ServerSocketHandler/ServerSocketHandler/base64.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/base64.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/base64.cpp$(DependSuffix): base64.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/base64.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/base64.cpp$(DependSuffix) -MM "base64.cpp"

$(IntermediateDirectory)/base64.cpp$(PreprocessSuffix): base64.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/base64.cpp$(PreprocessSuffix) "base64.cpp"

$(IntermediateDirectory)/websocket.cpp$(ObjectSuffix): websocket.cpp $(IntermediateDirectory)/websocket.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/swirli/ServerSocketHandler/ServerSocketHandler/websocket.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/websocket.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/websocket.cpp$(DependSuffix): websocket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/websocket.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/websocket.cpp$(DependSuffix) -MM "websocket.cpp"

$(IntermediateDirectory)/websocket.cpp$(PreprocessSuffix): websocket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/websocket.cpp$(PreprocessSuffix) "websocket.cpp"

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/swirli/ServerSocketHandler/ServerSocketHandler/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/PracticalSocket.cpp$(ObjectSuffix): PracticalSocket.cpp $(IntermediateDirectory)/PracticalSocket.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/swirli/ServerSocketHandler/ServerSocketHandler/PracticalSocket.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PracticalSocket.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PracticalSocket.cpp$(DependSuffix): PracticalSocket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PracticalSocket.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PracticalSocket.cpp$(DependSuffix) -MM "PracticalSocket.cpp"

$(IntermediateDirectory)/PracticalSocket.cpp$(PreprocessSuffix): PracticalSocket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PracticalSocket.cpp$(PreprocessSuffix) "PracticalSocket.cpp"

$(IntermediateDirectory)/broadcaster.cpp$(ObjectSuffix): broadcaster.cpp $(IntermediateDirectory)/broadcaster.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/swirli/ServerSocketHandler/ServerSocketHandler/broadcaster.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/broadcaster.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/broadcaster.cpp$(DependSuffix): broadcaster.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/broadcaster.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/broadcaster.cpp$(DependSuffix) -MM "broadcaster.cpp"

$(IntermediateDirectory)/broadcaster.cpp$(PreprocessSuffix): broadcaster.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/broadcaster.cpp$(PreprocessSuffix) "broadcaster.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


