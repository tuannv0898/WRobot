/*
 * System.h
 *
 *  Created on: Jul 16, 2018
 *      Author: 16138
 */

#ifndef SLIB_SYSTEM_SYSTEM_H_
#define SLIB_SYSTEM_SYSTEM_H_

#include <stdbool.h>
#include <stdint.h>

#include <slib/log/Log.h>
#include <slib/log/Logger.h>

#include "driverlib/sysctl.h"

class System
{
public:
    System();
    virtual ~System();
    static void init();
    static void delayMs(uint32_t time);
private:
    static Logger logger;
};

#endif /* SLIB_SYSTEM_SYSTEM_H_ */