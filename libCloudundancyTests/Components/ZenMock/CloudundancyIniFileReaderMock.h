#pragma once
#include "libCloudundancy/Components/CloudundancyIniFileReader.h"

class CloudundancyIniFileReaderMock : public Zen::Mock<CloudundancyIniFileReader>
{
public:
   ZENMOCK_NONVOID1_CONST(CloudundancyIni, ReadIniFile, const fs::path&)
};