#pragma once
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileAppender.h"

class CloudundancyLogFileAppenderMock : public Metal::Mock<CloudundancyLogFileAppender>
{
public:
   METALMOCK_VOID1_CONST(AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders, const vector<fs::path>&)
   METALMOCK_VOID2_CONST(AppendTextToCloudundancyLogFileInDestinationFolder, const fs::path&, string_view)
};
