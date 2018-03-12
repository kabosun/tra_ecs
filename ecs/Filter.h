#pragma once

template<typename... Args>
struct Requires
{

};

struct Filter
{

};

template<typename Requires>
Filter MakeFilter()
{
	return Filter();
}
