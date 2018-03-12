#pragma once

template<class... Args>
struct Requires
{

};

struct Filter
{

};

template<class Requires>
Filter MakeFilter()
{
	return Filter();
}
