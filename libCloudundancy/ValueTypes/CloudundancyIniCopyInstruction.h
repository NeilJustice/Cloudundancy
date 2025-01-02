#pragma once

struct CloudundancyIniCopyInstruction
{
   fs::path absoluteSourceFileOrFolderPath;
   fs::path relativeDestinationFolderPath;
};

#ifdef _WIN32
#ifdef _DEBUG
static_assert(sizeof(CloudundancyIniCopyInstruction) == 80);
#else
static_assert(sizeof(CloudundancyIniCopyInstruction) == 64);
#endif
#elifdef __linux__
static_assert(sizeof(CloudundancyIniCopyInstruction) == 80);
#endif
