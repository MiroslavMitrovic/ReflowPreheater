/*
 * NextionLib.h
 *
 *  Created on: 7 Apr 2021
 *      Author: mmitr
 */
#define ARM_MATH_CM4
#include "arm_math.h"

#ifndef INC_NEXTIONLIB_H_
#define INC_NEXTIONLIB_H_

extern arm_pid_instance_f32 PID;
extern void arm_pid_init_f32(arm_pid_instance_f32 * S,
		  int32_t resetStateFlag);

void SaveParameters(void);
void LoadParameters(void);
void NEXTION_SendString (char *ID, char *string);
void NEXTION_SendFloat (char *ID, float32_t number);
void NEXTION_SenduInt (char *ID, uint32_t number);
void NEXTION_CMD (const char *string);
void UpdatePage(void);
void NextionDrawDot(uint32_t x, uint32_t y);
void NextionDrawTemp(uint32_t x, uint32_t y);
float32_t HandleKeyPad(void);
void Update_Page_0(void);

void Update_Page_2(void);
void Update_Page_3(void);
void HandleGui(void);
void startReflow(void);
void stopReflow(void);
void Draw_Reflow_Curve(void);
void setReflowParameters(void);
void calculateReflowCurve(void);
void initFlags(void);
void sendToNum(char *obj,uint16_t value);
extern uint8_t ReflowEnable;
extern uint16_t PhaseIndex[6];
extern char ConsoleMSG[20];

#endif /* INC_NEXTIONLIB_H_ */
