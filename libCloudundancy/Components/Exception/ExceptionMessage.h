#pragma once

class ExceptionMessage
{
public:
	ExceptionMessage() = delete;
	static const string InvalidConcurrentUnorderedMapKey;
	static const string InvalidUnorderedMapKey;
	static const string InvalidMapKey;
	static const string KeyAlreadyPresentInMap;
};
