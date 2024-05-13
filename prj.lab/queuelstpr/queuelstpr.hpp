#pragma once
#ifndef QUEUELSTPR_QUEUELSTPR_HPP
#define QUEUELSTPR_QUEUELSTPR_HPP

#include <cstddef>

class QueueLstPr {
public:
    QueueLstPr() = default;

    QueueLstPr(const QueueLstPr&) = default;
    QueueLstPr(QueueLstPr&& rhs) noexcept;

    ~QueueLstPr() = default;

    [[nodiscard]] QueueLstPr& operator=(QueueLstPr&& rhs);

    [[nodiscard]] bool IsEmpty() const noexcept;

    void Pop() noexcept;

    void Push(const float& val);

    [[nodiscard]] float& Top();

    [[nodiscard]] const float& Top() const;

    void Clear() noexcept;

private:
    struct Node {
        float val;
        Node* next = nullptr;
    };

    Node* head_ = nullptr;
};

#endif // !QUEUELSTPR_QUEUELSTPR_HPP