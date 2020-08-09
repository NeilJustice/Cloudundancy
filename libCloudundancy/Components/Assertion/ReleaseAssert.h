#pragma once

void ReleaseAssert(
   bool predicateExpressionResult,
   const char* predicateExpressionText,
   const char* filePath,
   size_t lineNumber,
   const char* functionName);

#ifndef release_assert
#define release_assert(predicateExpression) ReleaseAssert(predicateExpression, #predicateExpression, __FILE__, __LINE__, __func__)
#endif
