/**
  ******************************************************************************
  * @file    /inc/variables.h
  * @author  Miroslav Mitrovic
  * @brief   This file contains shared variables.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 Yakamooda electronics GmbH.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Yakamooda electronics GmbH under GPL
  *
  *
 ******************************************************************************
*/

#ifndef INC_VARIABLES_H_
#define INC_VARIABLES_H_
#endif /*INC_VARIABLES_H_*/
/* Includes ------------------------------------------------------------------*/
#include "Reflow_functions.h"
#include  <stdint.h>


/*
Note: #define VAR_DECLS 1 before including this file to DECLARE and INITIALIZE
global variables.  Include this file without defining VAR_DECLS to extern
these variables.
----------------------------------------------------------------------------*/

#ifndef VAR_DEFS          // Make sure this file is included only once
#define VAR_DEFS 1
/*----------------------------------------------
Setup variable declaration macros.
----------------------------------------------*/
#ifndef VAR_DECLS
# define _DECL extern
# define _INIT(x)
#else
# define _DECL
# define _INIT(x)  = x
#endif
#define ULONG_MAX 					0xFFFFFFFFUL

/*----------------------------------------------
Declare variables as follows:

_DECL [standard variable declaration] _INIT(x);

where x is the value with which to initialize
the variable.  If there is no initial value for
the varialbe, it may be declared as follows:

_DECL [standard variable declaration];
----------------------------------------------*/


uint8_t PIDFlag;
_DECL volatile float temperature _INIT(0);
_DECL volatile float PIDerror _INIT(0);
_DECL uint8_t State _INIT(0);
_DECL arm_pid_instance_f32 PID;
_DECL volatile float *p_temperature _INIT(&temperature);
_DECL uint16_t ReflowCurve_main[15000] _INIT(0);
_DECL uint16_t PhaseIndex_main[6];
_DECL volatile uint8_t ui8_encButtonPressed _INIT(0);
_DECL uint32_t ms_counter;
_DECL ReflowTemplate *p_ReflowParameters;
_DECL uint16_t *p_ReflowCurve;
_DECL uint16_t *p_PhaseIndex;







#endif
//
