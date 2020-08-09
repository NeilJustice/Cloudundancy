#pragma once

class Repeatedly
{
public:
   static void Call(size_t iterations, const function<void()>& func);
};
