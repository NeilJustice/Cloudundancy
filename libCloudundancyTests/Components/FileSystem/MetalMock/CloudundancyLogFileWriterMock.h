#pragma once
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileWriter.h"

class CloudundancyLogFileWriterMock : public Metal::Mock<CloudundancyLogFileWriter>
{
public:
   METALMOCK_VOID2_CONST(AppendTextToCloudundancyLogFileInFolder, const fs::path&, string_view)
};
