#pragma once
#ifndef BITSET_BITSET_HPP
#define BITSET_BITSET_HPP

#include <vector>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <cstdint>
#include <cstddef>
#include <istream>
#include <ostream>


class BitSet {
public:
    BitSet() = default;
    BitSet(const int32_t n_size);
    BitSet(const BitSet& copy);
    BitSet(BitSet&& copy) noexcept;
    BitSet(const std::initializer_list<bool>& copy_list);

    BitSet& operator=(const BitSet& copy);
    BitSet& operator=(BitSet&& copy) noexcept;

    ~BitSet() = default;

    [[nodiscard]] bool operator==(const BitSet& other) const noexcept;
    [[nodiscard]] bool operator!=(const BitSet& other) const noexcept;

    [[nodiscard]] bool IsEmpty() const noexcept;
    [[nodiscard]] int32_t Size() const noexcept;
    void Clear() noexcept;
    void Resize(const int32_t n_size);

    [[nodiscard]] bool Get(const int32_t index) const;
    void Set(const int32_t index, const bool value);

    [[nodiscard]] BitSet operator~() const;

    BitSet& operator&=(const BitSet& other);
    BitSet& operator|=(const BitSet& other);
    BitSet& operator^=(const BitSet& other);

    void Fill(const bool value);

    friend std::ostream& operator<<(std::ostream& stream, const BitSet& bs);
    friend std::istream& operator>>(std::istream& stream, BitSet& bs);


private:
    std::vector<uint32_t> data_;
    size_t last_offset;
    static const int32_t C_BLOCKSIZE = 32;

    class iterator {
    public:
        iterator(uint32_t& n_elem, int32_t n_offset);
        bool operator=(const bool value);
        operator bool();
    private:
        uint32_t& elem;
        int32_t offset;
    };

    static void negate_block(uint32_t& block) {
        block = ~block;
    }

    void check_sizes_are_equal(const BitSet& other) const;

public:
    [[nodiscard]] iterator operator[](const int index);
};

BitSet operator&(const BitSet& left, const BitSet& right);
BitSet operator|(const BitSet& left, const BitSet& right);
BitSet operator^(const BitSet& left, const BitSet& right);


#endif // !BITSET_BITSET_HPP