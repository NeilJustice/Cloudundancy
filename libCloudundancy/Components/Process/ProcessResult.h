#pragma once

struct ProcessResult
{
   string processName;
	string arguments;
	int exitCode;
	string standardOutputAndError;
	unsigned milliseconds;

   ProcessResult();
   ProcessResult(
      string_view processName,
      string_view arguments,
      int exitCode,
      string_view standardOutputAndError,
      unsigned milliseconds);
};
