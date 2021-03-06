#pragma once
#include "libCloudundancy/Components/IniFile/CloudundancyIniFileReader.h"

class CloudundancyIniFileReaderMock : public Metal::Mock<CloudundancyIniFileReader>
{
public:
   METALMOCK_NONVOID1_CONST(CloudundancyIni, ReadIniFile, const fs::path&)
};