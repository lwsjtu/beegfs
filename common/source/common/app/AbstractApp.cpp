#include <common/toolkit/StorageTk.h>
#include "AbstractApp.h"

bool AbstractApp::didRunTimeInit = false;

/**
 * Note: Will do nothing if pidFile string is empty.
 *
 * @pidFile will not be accepted if path is not absolute (=> throws exception).
 * @return LockFD for locked pid file or invalid if pidFile string was empty.
 */
LockFD AbstractApp::createAndLockPIDFile(const std::string& pidFile)
{
   if (pidFile.empty())
      return {};

   // PID file defined

   Path pidPath(pidFile);
   if(!pidPath.absolute() ) /* (check to avoid problems after chdir) */
      throw InvalidConfigException("Path to PID file must be absolute: " + pidFile);

   auto pidFileLockFD = StorageTk::createAndLockPIDFile(pidFile, true);
   if (!pidFileLockFD.valid())
      throw InvalidConfigException("Unable to create/lock PID file: " + pidFile);

   return pidFileLockFD;
}

/**
 * Updates a locked pid file, which is typically required after calling daemon().
 *
 * Note: Will do nothing if pidfileFD is invalid.
 */
void AbstractApp::updateLockedPIDFile(LockFD& pidFileFD)
{
   if (!pidFileFD.valid())
      return;

   if (auto err = pidFileFD.updateWithPID())
      throw InvalidConfigException("Unable to update PID file: " + err.message());
}


/**
 * @param component the thread that we're waiting for via join(); may be NULL (in which case this
 * method returns immediately)
 */
void AbstractApp::waitForComponentTermination(PThread* component)
{
   const char* logContext = "App (wait for component termination)";
   Logger* logger = Logger::getLogger();

   const int timeoutMS = 2000;

   if(!component)
      return;

   bool isTerminated = component->timedjoin(timeoutMS);
   if(!isTerminated)
   { // print message to show user which thread is blocking
      if(logger)
         logger->log(Log_WARNING, logContext,
            "Still waiting for this component to stop: " + component->getName() );

      component->join();

      if(logger)
         logger->log(Log_WARNING, logContext, "Component stopped: " + component->getName() );
   }
}

/**
 * Handle errors from new operator.
 *
 * This method is intended by the C++ standard to try to free up some memory after allocation
 * failed, but our options here are very limited, because we don't know which locks are being held
 * when this is called and how much memory the caller actually requested.
 *
 * @return this function should only return if it freed up memory (otherwise it might be called
 * infinitely); as we don't free up any memory here, we exit by throwing a std::bad_alloc
 * exeception.
 * @throw std::bad_alloc always.
 */
void AbstractApp::handleOutOfMemFromNew()
{
   int errCode = errno;

   std::cerr << "Failed to allocate memory via \"new\" operator. "
      "Will try to log a backtrace and then throw a bad_alloc exception..." << std::endl;
   std::cerr << "Last errno value: " << errno << std::endl;

   LogContext log(__func__);
   log.logErr("Failed to allocate memory via \"new\" operator. "
      "Will try to log a backtrace and then throw a bad_alloc exception...");

   log.logErr("Last errno value: " + System::getErrString(errCode) );

   log.logBacktrace();

   throw std::bad_alloc();
}

bool AbstractApp::performBasicInitialRunTimeChecks()
{
   bool timeTest = Time::testClock();
   if (!timeTest)
      return false;

   bool conditionTimeTest = Condition::testClockID();
   return conditionTimeTest;
}

bool AbstractApp::basicInitializations()
{
   bool condAttrRes = Condition::initStaticCondAttr();
   return condAttrRes;
}

bool AbstractApp::basicDestructions()
{
   bool condAttrRes = Condition::destroyStaticCondAttr();
   return condAttrRes;
}
