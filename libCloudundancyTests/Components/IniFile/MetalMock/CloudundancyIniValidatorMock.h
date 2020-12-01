#pragma once
#include "libCloudundancy/Components/IniFile/CloudundancyIniValidator.h"

class CloudundancyIniValidatorMock : public Metal::Mock<CloudundancyIniValidator>
{
public:
   METALMOCK_VOID2_CONST(ThrowIfZeroDestinationFolderPaths, const CloudundancyIni&, const fs::path&)
};
