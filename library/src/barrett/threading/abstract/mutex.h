/*
 * mutex.h
 *
 *  Created on: Dec 15, 2009
 *      Author: dc
 */

#ifndef MUTEX_H_
#define MUTEX_H_


#include <boost/thread.hpp>
#include "../../detail/ca_macro.h"


#define SCOPED_LOCK(mutex)  \
	boost::lock_guard<threading::Mutex> _barrett_lock_scope_lg(mutex)


namespace barrett {
namespace threading {


// An abstract, recursive mutex object. Is a model of the boost::thread::Lockable concept.
class Mutex {
public:
	Mutex() {}
	virtual ~Mutex() {}

	virtual void lock() = 0;
	virtual bool try_lock() = 0;
	virtual void unlock() = 0;

private:
	DISALLOW_COPY_AND_ASSIGN(Mutex);
};


}
}

#endif /* MUTEX_H_ */
