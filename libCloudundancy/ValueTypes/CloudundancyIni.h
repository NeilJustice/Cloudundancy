#pragma once

struct CloudundancyIni
{
   vector<string> iniFileLines;
   vector<fs::path> destinationFolderPaths;
   vector<CloudundancyIniCopyInstruction> cloudundancyIniCopyInstructions;
   vector<string> fileSubpathsToIgnore;
};

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(CloudundancyIni) == 128);
   #else
      static_assert(sizeof(CloudundancyIni) == 96);
   #endif
#else
   static_assert(sizeof(CloudundancyIni) == 96);
#endif
