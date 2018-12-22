/**
* @copyright st
* @author moki
* @date 2018/12/21 09:58:50
* @version
*
* @file Event.h
* @brief event，the same as windows Event
* helpful url:https://en.wikipedia.org/wiki/C%2B%2B11
* http://www.cplusplus.com/reference/mutex/lock_guard/
*/
#ifndef EVENT_HPP
#define EVENT_HPP

namespace kit
{
/**
* @class event_object
*
* @brief 事件
*
*/
class event_object : boost::noncopyable
{
public:
    /**
    * @brief 等待事件有信
    * @return void
    */
    void wait();

    /**
    * @brief 等待事件有信
    * @param int64 milliseconds 最长等待的时间(毫秒)
    * @return bool
    */
    bool wait_for(int64 milliseconds);
    /**
    * @brief 设置事件有信
    * @return void
    */
    void set_event();

    /**
    * @brief 重置事件无信
    * @return void
    */
    inline void reset_event()
    {
        //boost::mutex::scoped_lock autolock(mutex_);
        std::lock_guard<std::mutex> lck (mutex_);
        state_ = false;
    }

public:
    /**
    * @brief Constructor for event_object
    * @param bool in_manual_reset 是否手动重置事件
    * @param bool in_initial_state 是否初始化为有信状态
    *
    */
    event_object(bool manual_reset, bool initial_state)
        : manual_reset_(manual_reset)
        , state_(initial_state) {}

    /**
    * @brief Destructor for event_object
    *
    */
    ~event_object() {}

private:
    bool state_;                         /**< 状态： true - 有信 false - 无信 */
    bool manual_reset_;                  /**< 复位方式： true - 手动 false - 自动 */
    std::mutex mutex_;                 /**< 操作互斥 */
    std::condition_variable_any cond_; /**< 条件变量 */
};
}

#endif // EVENT_HPP
