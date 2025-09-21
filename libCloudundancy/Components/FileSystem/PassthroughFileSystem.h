#pragma once

class PassthroughFileSystem
{
public:
   virtual ~PassthroughFileSystem();
   virtual unsigned long long remove_all(const fs::path& p) const;
   virtual unsigned long long file_size(const fs::path& p) const;
};
