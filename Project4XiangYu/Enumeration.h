#pragma once
#ifndef _ENUMERATION_H
#define _ENUMERATION_H

template<class DT>
class Enumeration {
public:
	virtual bool hasMoreElements() = NULL;
	virtual DT& nextElement() = NULL;
};

#endif // !_ENUMERATION_H
