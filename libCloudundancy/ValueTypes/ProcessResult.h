#pragma once

struct ProcessResult
{
   string processName;
	string arguments;
	int exitCode;
	string standardOutputAndError;
	unsigned durationInMilliseconds;

   ProcessResult();
   ProcessResult(
      string_view processName,
      string_view arguments,
      int exitCode,
      string_view standardOutputAndError,
      unsigned durationInMilliseconds);
};
