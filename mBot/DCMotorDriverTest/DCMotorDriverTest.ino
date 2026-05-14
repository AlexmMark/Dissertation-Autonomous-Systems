/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    DCMotorDriverTest.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Description: this file is sample code for Me DC motor device.
 *
 * Function List:
 *    1. void MeDCMotor::run(int16_t speed)
 *    2. void MeDCMotor::stop(void)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Mark Yan     2015/09/09    1.0.0          rebuild the old lib
 * </pre>
 */
#include "MeMCore.h"

MeDCMotor motorPort1(PORT_1);

MeDCMotor motorPort2(PORT_2);

MeDCMotor motorL(M1);

MeDCMotor motorR(M2);

uint8_t motorSpeed = 100;

void setup()
{
}

void loop()
{
  motorPort1.run(motorSpeed); /* value: between -255 and 255. */
  motorPort2.run(motorSpeed); /* value: between -255 and 255. */
  motorL.run(motorSpeed);
  motorR.run(motorSpeed);
  delay(2000);
  motorPort1.stop();
  motorPort2.stop();
  motorL.stop();
  motorR.stop();
  delay(100);
}

