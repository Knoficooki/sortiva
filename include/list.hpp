#pragma once
#include <algorithm>
#include <cstddef>
#include <memory>
#include <mutex>
#include <utility>

/**
 * @brief A thread-safe dynamic array container class
 * 
 * List provides a fixed-size array container with thread-safe access through mutex protection.
 * It supports construction with a size or initializer list, as well as copy/move operations.
 * All operations that access or modify the internal data are protected by a mutex.
 *
 * @tparam T The type of elements stored in the list
 */
template <typename T>
class List {
public:
    /** 
     * @brief Type alias for the element type stored in the list
     * 
     * This type represents the template parameter T that defines
     * the type of elements contained in the List container.
     */
    using value_type = T;
	
    /**
     * @brief Constructs a List with specified size
     * @param size The number of elements to allocate
     */
    explicit List(std::size_t size)
        : data_(std::make_unique<T[]>(size))
        , size_(size) {
    }

    /**
     * @brief Constructs a List from an initializer list
     * @param init The initializer list containing initial values
     */
    List(std::initializer_list<T> init)
        : data_(std::make_unique<T[]>(init.size()))
        , size_(init.size()) {
        std::lock_guard lock(mutex_);
        std::copy(init.begin(), init.end(), data_.get());
    }

    /**
     * @brief Copy constructor
     * @param other The List to copy from
     * @thread_safety Both this and other List's mutexes are locked during copy
     */
    List(const List& other) {
        std::lock_guard lock(mutex_);
        std::lock_guard<std::mutex> other_lock(other.mutex_);
        data_ = std::make_unique<T[]>(other.size_);
        std::copy(other.data_.get(), other.data_.get() + other.size_, data_.get());
        size_ = other.size_;
    }

    /**
     * @brief Move constructor
     * @param other The List to move from
     * @thread_safety Both this and other List's mutexes are locked during move
     */
    List(List&& other) noexcept {
        std::lock_guard lock(mutex_);
        std::lock_guard<std::mutex> other_lock(other.mutex_);
        data_ = std::move(other.data_);
        size_ = other.size_;
        other.size_ = 0;
    }

    /**
     * @brief Copy assignment operator
     * @param other The List to copy from
     * @return Reference to this List
     * @thread_safety Both this and other List's mutexes are locked during assignment
     */
    List& operator=(const List& other) {
        if (this != &other) {
            std::lock_guard lock(mutex_);
            std::lock_guard<std::mutex> other_lock(other.mutex_);
            data_ = std::make_unique<T[]>(other.size_);
            std::copy(other.data_.get(), other.data_.get() + other.size_, data_.get());
            size_ = other.size_;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator
     * @param other The List to move from
     * @return Reference to this List
     * @thread_safety Both this and other List's mutexes are locked during move
     */
    List& operator=(List&& other) noexcept {
        if (this != &other) {
            std::lock_guard lock(mutex_);
            std::lock_guard<std::mutex> other_lock(other.mutex_);
            data_ = std::move(other.data_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }
    
    /**
     * @brief Access element at specified index with bounds wrapping
     * @param index The index of the element to access
     * @return Reference to the element at the wrapped index
     * @thread_safety Protected by mutex
     */
    T& operator[](std::size_t index) {
        std::lock_guard lock(mutex_);
        return data_[index % size_];
    }
    
    /**
     * @brief Access const element at specified index with bounds wrapping
     * @param index The index of the element to access
     * @return Const reference to the element at the wrapped index
     * @thread_safety Protected by mutex
     */
    const T& operator[](std::size_t index) const {
        std::lock_guard lock(mutex_);
        return data_[index % size_];
    }

    /**
     * @brief Get const element at specified index with bounds wrapping
     * @param index The index of the element to access
     * @return Const reference to the element at the wrapped index
     * @thread_safety Protected by mutex
     */
    const T& get(std::size_t index) const
    {
        std::lock_guard lock(mutex_);
        return data_[index % size_];
    }

    /**
     * @brief Set element at specified index with bounds wrapping
     * @param index The index of the element to set
     * @param value The value to set at the specified index
     * @thread_safety Protected by mutex
     */
    void set(std::size_t index, const T& value) {
        std::lock_guard lock(mutex_);
        data_[index % size_] = value;
    }

    /**
     * @brief Get the size of the List
     * @return The number of elements in the List
     * @thread_safety Protected by mutex
     */
    std::size_t size() const {
        std::lock_guard lock(mutex_);
        return size_;
    }

private:
    std::unique_ptr<T[]> data_;    ///< Underlying array storage
    std::size_t size_;             ///< Number of elements in the array
    mutable std::mutex mutex_;      ///< Mutex for thread-safe access
};