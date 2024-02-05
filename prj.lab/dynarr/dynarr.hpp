#pragma once
#ifndef DYNARR_DYNARR_HPP
#define DYNARR_DYNARR_HPP

#include <cstddef>
#include <iostream>

class DynArr
{
public:
	DynArr() = default;
	DynArr(const DynArr& dynArray);
	explicit DynArr(const std::ptrdiff_t size);

	std::ptrdiff_t Size() const noexcept;

	void Resize(const std::ptrdiff_t size);

	float& operator[](const std::ptrdiff_t index);

	const float& operator[](const std::ptrdiff_t index) const;

	std::ostream& WriteTo(std::ostream& ostrm) const;

	~DynArr();

private:
	std::ptrdiff_t size = 0;
	std::ptrdiff_t capacity = 0;
	float* dataPtr = nullptr;
};

inline std::ostream& operator<<(std::ostream& ostrm, const DynArr& rhs) {
	return rhs.WriteTo(ostrm);
}

#endif // !DYNARR_DYNARR_HPP