#include "bitset.hpp"
#include <iostream>
#include <string>

BitSet::BitSet(const int32_t n_size) {
    Resize(n_size);
}

BitSet::BitSet(const BitSet& copy) {
    data_ = copy.data_;
    last_offset = copy.last_offset;
}

BitSet::BitSet(BitSet&& copy) noexcept {
    data_ = std::move(copy.data_);
    last_offset = copy.last_offset;
}

BitSet::BitSet(const std::initializer_list<bool>& copy_list) {
    Resize(copy_list.size());
    for (size_t i = 0; i < copy_list.size(); ++i) {
        Set(i, *(copy_list.begin() + i));
    }
}

BitSet& BitSet::operator=(const BitSet& copy) {
    data_.assign(copy.data_.begin(), copy.data_.end());
    last_offset = copy.last_offset;
    return *this;
}

BitSet& BitSet::operator=(BitSet&& copy) noexcept {
    data_ = std::move(copy.data_);
    last_offset = copy.last_offset;
    return *this;
}

[[nodiscard]] bool BitSet::operator==(const BitSet& other) const noexcept {
    if (data_.size() != other.data_.size()
        || last_offset != other.last_offset) {
        return false;
    }

    if (data_.empty()) {
        return true;
    }

    for (int i = 0; i < static_cast<int>(data_.size()) - static_cast<int>(last_offset != 0); ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }

    uint32_t offset = 1;
    for (size_t i = 0; i < last_offset; ++i) {
        if ((data_.back() & offset) != (other.data_.back() & offset)) {
            return false;
        }
        offset <<= 1;
    }
    return true;
}

[[nodiscard]] bool BitSet::operator!=(const BitSet& other) const noexcept {
    return !(*this == other);
}

[[nodiscard]] bool BitSet::IsEmpty() const noexcept {
    return data_.empty();
}

[[nodiscard]] int32_t BitSet::Size() const noexcept {
    if (IsEmpty()) {
        return 0;
    }

    if (last_offset == 0) {
        return data_.size() * C_BLOCKSIZE;
    }
    else {
        return (data_.size() - 1) * C_BLOCKSIZE + last_offset;
    }

}

void BitSet::Clear() noexcept {
    data_.clear();
    last_offset = 0;
}


void BitSet::Resize(const int32_t n_size) {
    if (n_size < 0) {
        throw std::runtime_error("Size can\'t be negative");
    }

    int32_t old_size = data_.size();
    int32_t old_last_offset = last_offset;
    data_.resize(n_size / C_BLOCKSIZE + static_cast<int>(n_size % C_BLOCKSIZE != 0));
    last_offset = n_size % C_BLOCKSIZE;

    if (old_size > 0 && n_size > (old_size - 1) * C_BLOCKSIZE + old_last_offset) {
        for (int32_t index = old_last_offset; index < C_BLOCKSIZE; ++index) {
            data_[old_size - 1] &= ~(1 << index);
        }
        for (size_t block = old_size; block < data_.size(); ++block) {
            data_[block] = 0;
        }
    }
}

[[nodiscard]] bool BitSet::Get(const int32_t index) const {
    if (index >= Size()) {
        throw std::runtime_error("Index is too large ");
    }

    return data_[index / C_BLOCKSIZE] & (1 << (index % C_BLOCKSIZE));
}

void BitSet::Set(const int32_t index, const bool value) {
    if (index >= Size()) {
        throw std::runtime_error("Index is too large");
    }

    if (value) {
        data_[index / C_BLOCKSIZE] |= (1 << (index % C_BLOCKSIZE));
    }
    else {
        data_[index / C_BLOCKSIZE] &= ~(1 << (index % C_BLOCKSIZE));
    }
}

[[nodiscard]] BitSet BitSet::operator~() const {
    BitSet other(*this);
    std::for_each(other.data_.begin(), other.data_.end(), negate_block);
    return other;
}

BitSet& BitSet::operator&=(const BitSet& other) {
    check_sizes_are_equal(other);
    for (size_t block = 0; block < data_.size(); ++block) {
        data_[block] &= other.data_[block];
    }
    return *this;
}

BitSet& BitSet::operator|=(const BitSet& other) {
    check_sizes_are_equal(other);
    for (size_t block = 0; block < data_.size(); ++block) {
        data_[block] |= other.data_[block];
    }
    return *this;
}

BitSet& BitSet::operator^=(const BitSet& other) {
    check_sizes_are_equal(other);
    for (size_t block = 0; block < data_.size(); ++block) {
        data_[block] ^= other.data_[block];
    }
    return *this;
}

void BitSet::Fill(const bool value) {
    for (size_t block = 0; block < data_.size(); ++block) {
        data_[block] = ((value) ? (~0) : (0));
    }
}


BitSet::iterator::iterator(uint32_t& n_elem, int32_t n_offset)
    : elem{ n_elem }, offset{ n_offset } {}

bool BitSet::iterator::operator=(const bool value) {
    if (value) {
        elem |= (1 << (offset % C_BLOCKSIZE));
    }
    else {
        elem &= ~(1 << (offset % C_BLOCKSIZE));
    }
    return value;
}

BitSet::iterator::operator bool() {
    return elem & (1 << (offset % C_BLOCKSIZE));
}


void BitSet::check_sizes_are_equal(const BitSet& other) const {
    if (data_.size() != other.data_.size()
        || last_offset != other.last_offset) {
        throw std::runtime_error("Sizes should be equal");
    }
}

[[nodiscard]] BitSet::iterator BitSet::operator[](const int index) {
    return iterator(data_[index / C_BLOCKSIZE], index % C_BLOCKSIZE);
}

BitSet operator&(const BitSet& left, const BitSet& right) {
    BitSet result(left);
    result &= right;
    return result;
}

BitSet operator|(const BitSet& left, const BitSet& right) {
    BitSet result(left);
    result |= right;
    return result;
}

BitSet operator^(const BitSet& left, const BitSet& right) {
    BitSet result(left);
    result ^= right;
    return result;
}

std::ostream& operator<<(std::ostream& stream, const BitSet& bs) {
    const int C_OUTPUT_BLOCK_SIZE = 32;
    stream << bs.Size() << '\n';

    if (bs.Size() == 0) {
        return stream;
    }

    int elems_written = 0;
    int blocks_count = 0;
    for (size_t block = 0; block < bs.data_.size() - 1; ++block) {
        uint32_t offset = 1;
        for (int elem = 0; elem < bs.C_BLOCKSIZE; ++elem) {
            stream << ((bs.data_[block] & offset) ? '1' : '0');
            offset <<= 1;

            ++elems_written;
            if (elems_written == C_OUTPUT_BLOCK_SIZE) {
                stream << ' ' << blocks_count << '\n';
                ++blocks_count;
                elems_written = 0;
            }
        }
    }

    int offset = 1;
    size_t cur_block_offset = (bs.last_offset) ? bs.last_offset : BitSet::C_BLOCKSIZE;

    for (size_t elem = 0; elem < cur_block_offset; ++elem) {
        stream << ((bs.data_.back() & offset) ? '1' : '0');
        offset <<= 1;
        ++elems_written;
        if (elems_written == C_OUTPUT_BLOCK_SIZE) {
            stream << ' ' << blocks_count << '\n';
            ++blocks_count;
            elems_written = 0;
        }
    }

    if (elems_written != 0) {
        stream << ' ' << blocks_count << '\n';
        ++blocks_count;
        elems_written = 0;
    }

    return stream;
}

std::istream& operator>>(std::istream& stream, BitSet& bs) {
    std::string size_string;
    size_t ss_pos = 0;
    std::getline(stream, size_string);

    // skip leading spaces
    while (ss_pos < size_string.size()
        && (size_string[ss_pos] == ' ' || size_string[ss_pos] == '\t')) {
        ++ss_pos;
    }
    if (ss_pos == size_string.size()) {
        throw std::runtime_error("remove it later -3");
    }

    // read size value
    int elems_count = 0;
    while (ss_pos < size_string.size()
        && !(size_string[ss_pos] == ' ' || size_string[ss_pos] == '\t' || size_string[ss_pos] == '\n')) {
        if (!(size_string[ss_pos] >= '0' && size_string[ss_pos] <= '9')) {
            throw std::runtime_error("remove it later -4");
        }

        elems_count *= 10;
        elems_count += size_string[ss_pos] - '0';
        ++ss_pos;
    }
    bs.Resize(elems_count);
    if (elems_count == 0) {
        return stream;
    }

    // skip trailing spaces
    while (ss_pos < size_string.size()
        && (size_string[ss_pos] == ' ' || size_string[ss_pos] == '\t' || size_string[ss_pos] == '\n')) {
        ++ss_pos;
    }

    // check bounds
    if (ss_pos != size_string.size()) {
        throw std::runtime_error("remove it later -4.5");
    }
    int elems_read = 0;
    int cur_block = 0;
    int cur_elem = 0;
    int line_number_prev = -1;
    int offset = 1;

    std::string input_string;

    bool bs_reading = true;
    while (bs_reading) {
        getline(stream, input_string);
        size_t pos = 0;

        // skip leading spaces
        while (pos < input_string.size()
            && (input_string[pos] == ' ' || input_string[pos] == '\t')) {
            ++pos;
        }
        // check bounds
        if (pos == input_string.size() || elems_read == elems_count) {
            bs_reading = false;
            break;
        }

        // read current data sequence
        while (pos < input_string.size()
            && !(input_string[pos] == ' ' || input_string[pos] == '\t')) {
            if (!bs_reading) {
                throw std::runtime_error("remove it later 6");
            }

            if (input_string[pos] == '0') {
                bs.data_[cur_block] &= ~offset;
            }
            else if (input_string[pos] == '1') {
                bs.data_[cur_block] |= offset;
            }
            else {
                throw std::runtime_error("remove it later 6.5");
            }

            ++pos;
            offset <<= 1;

            ++cur_elem;
            if (cur_elem == BitSet::C_BLOCKSIZE) {
                cur_elem = 0;
                ++cur_block;
                offset = 1;
            }

            ++elems_read;
            if (elems_read == elems_count) {
                bs_reading = false;
            }
            if (elems_read > elems_count) {
                throw std::runtime_error("remove it later 6");
            }
        }

        // check bounds
        if (pos == input_string.size()) {
            throw std::runtime_error("remove it later 7");
            break;
        }

        // skip separation spaces
        while (pos < input_string.size()
            && (input_string[pos] == ' ' || input_string[pos] == '\t')) {
            ++pos;
        }
        // check bounds
        if (pos == input_string.size()) {
            throw std::runtime_error("remove it later 7");
            break;
        }

        // read line number
        int line_number = 0;
        while (pos < input_string.size()
            && !(input_string[pos] == ' ' || input_string[pos] == '\t' || input_string[pos] == '\n')) {
            if (!(input_string[pos] >= '0' && input_string[pos] <= '9')) {
                throw std::runtime_error("remove it later 4");
            }
            line_number *= 10;
            line_number += input_string[pos] - '0';
            ++pos;
        }

        if (line_number - line_number_prev != 1) {
            throw std::runtime_error("remove it later 5");
        }

        line_number_prev = line_number;

        // skip trailing spaces
        while (pos < input_string.size()
            && (input_string[pos] == ' ' || input_string[pos] == '\t' || input_string[pos] == '\n')) {
            ++pos;
        }

        // check bounds
        if (pos != input_string.size()) {
            throw std::runtime_error("remove it later 6");
        }
    }

    if (elems_read != elems_count) {
        throw std::runtime_error("remove it later 7");
    }

    return stream;
}
