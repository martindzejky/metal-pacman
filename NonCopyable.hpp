#ifndef _NONCOPYABLE_HPP_
#define _NONCOPYABLE_HPP_


/**
 * Represents a non-copyable resource. Inherit if you want to forbig copying.
 */


class NonCopyable {

public:

    NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    void operator=(const NonCopyable&) = delete;

};


#endif
