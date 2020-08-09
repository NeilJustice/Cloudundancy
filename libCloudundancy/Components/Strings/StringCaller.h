#pragma once

class StringCaller
{
public:
	virtual std::vector<std::string> Split(const std::string& str, char separator) const;
   virtual ~StringCaller();
};
