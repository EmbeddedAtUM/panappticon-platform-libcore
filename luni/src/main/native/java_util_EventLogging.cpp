/* This is to return the elapsed microseconds and current thread ID
 * author: Lide Zhang
*/

#include <unistd.h>
#include <sys/time.h>
#include "JniConstants.h"
#include <sys/syscall.h>


#if !defined(HAVE_ANDROID_OS)
#define __KERNEL__
# include <linux/unistd.h>
#ifdef _syscall0
_syscall0(pid_t,gettid)
#else
pid_t gettid() { return syscall(__NR_gettid);}
#endif
#undef __KERNEL__
#endif

static jlong EventLogging_getTime(JNIEnv*, jobject){
	struct timeval time;
	gettimeofday(&time, NULL);
	long long timestamp = (long long)time.tv_sec * 1000000 + (long long)time.tv_usec;
	return timestamp;
}

static jint EventLogging_getMyTid(JNIEnv*, jobject){
	pid_t myTid = gettid();
	return (jint)myTid;
}

static JNINativeMethod gMethods[] = {
	NATIVE_METHOD(EventLogging, getTime, "()J"),
	NATIVE_METHOD(EventLogging, getMyTid, "()I"),
};
void register_java_util_EventLogging(JNIEnv * env){
	jniRegisterNativeMethods(env, "java/util/EventLogging", gMethods, NELEM(gMethods));
}
