/*
MIT License

Copyright (c) 2018 Brian T. Park

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// Significant portions of the design and implementation of this file came from
// https://github.com/mmurdoch/arduinounit/blob/master/src/ArduinoUnit.h

/**
 * @file MetaAssertion.h
 *
 * Various assertTestXxx() and checkTestXxx() macros are defined in this header.
 */

#ifndef AUNIT_META_ASSERTION_H
#define AUNIT_META_ASSERTION_H

#include <Arduino.h>  // definition of Print
#include "Printer.h"
#include "Assertion.h"

class __FlashStringHelper;

// Meta tests, same syntax as ArduinoUnit for compatibility.
// The checkTestXxx() macros return a boolean, and execution continues.

/** Return true if test 'name' is done. */
#define checkTestDone(name) (test_##name##_instance.isDone())

/** Return true if test 'name' is not done. */
#define checkTestNotDone(name) (test_##name##_instance.isNotDone())

/** Return true if test 'name' has passed. */
#define checkTestPass(name) (test_##name##_instance.isPassed())

/** Return true if test 'name' has not passed. */
#define checkTestNotPass(name) (test_##name##_instance.isNotPassed())

/** Return true if test 'name' has failed. */
#define checkTestFail(name) (test_##name##_instance.isFailed())

/** Return true if test 'name' has not failed. */
#define checkTestNotFail(name) (test_##name##_instance.isNotFailed())

/** Return true if test 'name' has been skipped. */
#define checkTestSkip(name) (test_##name##_instance.isSkipped())

/** Return true if test 'name' has not been skipped. */
#define checkTestNotSkip(name) (test_##name##_instance.isNotSkipped())

/** Return true if test 'name' has timed out. */
#define checkTestExpire(name) (test_##name##_instance.isExpired())

/** Return true if test 'name' has not timed out. */
#define checkTestNotExpire(name) (test_##name##_instance.isNotExpired())

// If the assertTestXxx() macros fail, they generate an optional output, calls
// fail(), and returns from the current test case.

/** Assert that test 'name' is done. */
#define assertTestDone(name) \
  assertTestStatus(name, isDone, kMessageIsDone)

/** Assert that test 'name' is not done. */
#define assertTestNotDone(name) \
    assertTestStatus(name, isNotDone, kMessageIsNotDone)

/** Assert that test 'name' has passed. */
#define assertTestPass(name) \
    assertTestStatus(name, isPassed, kMessageIsPassed)

/** Assert that test 'name' has not passed. */
#define assertTestNotPass(name) \
    assertTestStatus(name, isNotPassed, kMessageIsNotPassed)

/** Assert that test 'name' has failed. */
#define assertTestFail(name) \
    assertTestStatus(name, isFailed, kMessageIsFailed)

/** Assert that test 'name' has not failed. */
#define assertTestNotFail(name) \
    assertTestStatus(name, isNotFailed, kMessageIsNotFailed)

/** Assert that test 'name' has been skipped. */
#define assertTestSkip(name) \
    assertTestStatus(name, isSkipped, kMessageIsSkipped)

/** Assert that test 'name' has not been skipped. */
#define assertTestNotSkip(name) \
    assertTestStatus(name, isNotSkipped, kMessageIsNotSkipped)

/** Assert that test 'name' has timed out. */
#define assertTestExpire(name) \
    assertTestStatus(name, isExpired, kMessageIsExpired)

/** Assert that test 'name' has not timed out. */
#define assertTestNotExpire(name) \
    assertTestStatus(name, isNotExpired, kMessageIsNotExpired)

/** Internal helper macro, shouldn't be called directly by users. */
#define assertTestStatus(name,method,message) do {\
  if (!assertionTestStatus(\
      __FILE__,__LINE__,#name,FPSTR(message),test_##name##_instance.method()))\
    return;\
} while (false)

namespace aunit {

class MetaAssertion: public Assertion {
  protected:
    // Human-readable strings for various meta-asssertion failures.
    static const char kMessageIsDone[];
    static const char kMessageIsNotDone[];
    static const char kMessageIsPassed[];
    static const char kMessageIsNotPassed[];
    static const char kMessageIsFailed[];
    static const char kMessageIsNotFailed[];
    static const char kMessageIsSkipped[];
    static const char kMessageIsNotSkipped[];
    static const char kMessageIsExpired[];
    static const char kMessageIsNotExpired[];

    /** Empty constructor. */
    MetaAssertion() {}

    /** Empty virtual destructor. */
    virtual ~MetaAssertion() {}

    /**
     * Set the status of the current test based on 'ok, and  print assertion
     * message if requested.
     */
    bool assertionTestStatus(const char* file, uint16_t line,
        const char* testName, const __FlashStringHelper* statusMessage,
        bool ok);

    /** Print the meta assertion passed or failed message. */
    void printAssertionTestStatusMessage(
        bool ok, const char* file, uint16_t line,
        const char* testName, const __FlashStringHelper* statusMessage);

  private:
    // Disable copy-constructor and assignment operator
    MetaAssertion(const MetaAssertion&) = delete;
    MetaAssertion& operator=(const MetaAssertion&) = delete;
};

}

#endif
