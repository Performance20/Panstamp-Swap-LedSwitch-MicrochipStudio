/*
 * CPPFile1.cpp
 *
 * Created: 16.02.2021 09:30:42
 *  Author: Helge
 */ 

/**
 * regtable
 *
 * Copyright (c) 2014 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 01/26/2012
 */

#include "product.h"
#include "regtable.h"

/**
 * Declaration of custom functions
 */
const void setBinOutput(byte rId, byte *state);
const void setPwmOutput(byte rId, byte *level);
const void getHelloWorld(byte rId, byte *level);

/**
 * Definition of common registers
 */
DEFINE_COMMON_REGISTERS()

/*
 * Definition of custom registers
 */
// Repater config. Not being used by the application. Only kept for backward compatibility
byte dtRepeaterCfg[1];       // Repeater config
REGISTER regRepeaterCfg(dtRepeaterCfg, sizeof(dtRepeaterCfg), NULL, NULL);
// Binary output registers
byte dtBinOutput0[1] = { 1 };       // Binary output state 0
REGISTER regBinOutput0(dtBinOutput0, sizeof(dtBinOutput0), NULL, &setBinOutput);
byte dtBinOutput1[1];       // Binary output state 1
REGISTER regBinOutput1(dtBinOutput1, sizeof(dtBinOutput1), NULL, &setBinOutput);
// PWM output registers
byte dtPwmOutput0[1];       // PWM output 0
REGISTER regPwmOutput0(dtPwmOutput0, sizeof(dtPwmOutput0), NULL, &setPwmOutput);
byte dtPwmOutput1[1];       // PWM output 1
REGISTER regPwmOutput1(dtPwmOutput1, sizeof(dtPwmOutput1), NULL, &setPwmOutput);
byte dtPwmOutput2[1];       // PWM output 2
REGISTER regPwmOutput2(dtPwmOutput2, sizeof(dtPwmOutput2), NULL, &setPwmOutput);

/**
 * Initialize table of registers
 */
DECLARE_REGISTERS_START()
  &regRepeaterCfg, // Not used
  &regBinOutput0,
  &regBinOutput1,
  &regPwmOutput0,
  &regPwmOutput1,
  &regPwmOutput2
DECLARE_REGISTERS_END()

/**
 * Definition of common getter/setter callback functions
 */
DEFINE_COMMON_CALLBACKS()

/**
 * Definition of custom getter/setter callback functions
 */

/**
 * setBinOutput
 *
 * Set binary output
 *
 * 'rId'     Register ID
 * 'state'   New output level
 */
const void setBinOutput(byte rId, byte *state)
{
  byte output = rId - REGI_BINOUTPUT0;

  // Update register
  regTable[rId]->value[0] = state[0];

  // Control pin
  digitalWrite(binaryPin[output], state[0]);
  Serial.print(state[0]);
}

/**
 * setPwmOutput
 *
 * Set PWM level
 *
 * 'rId'     Register ID
 * 'level'   New PWM level
 */
const void setPwmOutput(byte rId, byte *level)
{
  byte output = rId - REGI_PWMOUTPUT0;
  
  // Update register
  regTable[rId]->value[0] = level[0];

  // Control PWM output
  analogWrite(pwmPin[output], level[0]);
}
