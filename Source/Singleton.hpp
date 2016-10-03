#include <memory>


/**
 * Singleton. Popular pattern. Inherit from this in singleton classes and define
 * using SINGLETON_DEFINE macro.
 */


template<typename Type>
class Singleton {

public:

    typedef std::shared_ptr<Type> Ptr;


    static Ptr &GetSingleton() {
        if (!msSingleton) {
            msSingleton.reset(new Type());
        }

        return msSingleton;
    }

    Singleton(const Singleton<Type> &other) = delete;
    void operator=(const Singleton<Type> &other) = delete;


protected:

    Singleton() = default;

    static std::shared_ptr<Type> msSingleton;

};


/**
 * Singleton definition help macro.
 */
#define SINGLETON_DEFINE(Type) Singleton<Type>::Ptr Singleton<Type>::msSingleton
