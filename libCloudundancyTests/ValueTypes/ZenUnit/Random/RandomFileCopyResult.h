#pragma once

namespace ZenUnit
{
   template<>
   FileCopyResult Random();
   FileCopyResult TestableRandomFileCopyResult(const RandomGenerator* randomGenerator);
}
