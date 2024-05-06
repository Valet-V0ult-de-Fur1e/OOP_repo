#pragma once
#ifndef DYNARR_DYNARR_HPP
#define DYNARR_DYNARR_HPP

#include <cstddef>
#include <iostream>
#include <memory>

class DynArr
{
public:
	DynArr() = default;
	DynArr(const DynArr& dynArray);
	DynArr(DynArr&& dynarr) noexcept;
	explicit DynArr(const std::ptrdiff_t size);

	[[nodiscard]] DynArr& operator=(const DynArr& dynArray);
	DynArr& operator=(DynArr&& dynarr) noexcept;
	std::ptrdiff_t Size() const noexcept;

	void Resize(const std::ptrdiff_t size);

	[[nodiscard]] float& operator[](const std::ptrdiff_t index);
	[[nodiscard]] const float& operator[](const std::ptrdiff_t index) const;

	std::ostream& WriteTo(std::ostream& ostrm) const;

	~DynArr() = default;

private:
	std::ptrdiff_t size_ = 0;
	std::unique_ptr<float[]> dataPtr_ = std::make_unique<float[]>(0);;
};

inline std::ostream& operator<<(std::ostream& ostrm, const DynArr& rhs) {
	return rhs.WriteTo(ostrm);
}

#endif // !DYNARR_DYNARR_HPP