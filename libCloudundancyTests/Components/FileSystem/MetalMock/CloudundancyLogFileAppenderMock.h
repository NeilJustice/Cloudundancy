#pragma once
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileAppender.h"

class CloudundancyLogFileAppenderMock : public Metal::Mock<CloudundancyLogFileAppender>
{
public:
   METALMOCK_VOID2_CONST(AppendTextToCloudundancyLogFileInFolder, const fs::path&, string_view)
};
