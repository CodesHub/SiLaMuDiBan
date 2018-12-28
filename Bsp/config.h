#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "stm32f10x.h"
#include "millisecondtimer.h"

#define PI      3.1415926
#define DEBUG   1

#define IMU_PUBLISH_RATE 50 //hz
#define BAT_PUBLISH_RATE 0.2 //hz
#define COMMAND_RATE 50 //hz
#define DEBUG_RATE 1

#define K_P    0.1 // P constant
#define K_I    0.2 // I constant
#define K_D    0.2 // D constant


/** motor param **/
#define PWM_BITS        8
#define MAX_RPM         366 //motor's maximum RPM
#define COUNTS_PER_REV  1560 //wheel encoder's no of ticks per rev(gear_ratio * pulse_per_rev)
#define WHEEL_DIAMETER  0.068 //wheel's diameter in meters

#define LR_WHEELS_DISTANCE 0.18
#define FR_WHEELS_DISTANCE 0.16

#define 	USE_SERIAL1
#define 	USE_SERIAL2
#define 	USE_SERIAL3
#define  	USE_MOTOR1
#define  	USE_MOTOR2
#define 	USE_ENCODER1
#define 	USE_ENCODER2
#define 	USE_I2C
#define 	USE_SERVO1
#define 	USE_SERVO2
#define 	USE_SONAR

/** --------Serial Config-------- **/
typedef enum {
	SERIAL1 = 0,
	SERIAL2 = 1,
	SERIAL3 = 2,
	SERIAL_END = 3
}Serial_TypeDef; 

#define SERIALn							3

#define RIKI_SERIAL1					USART1
#define RIKI_SERIAL1_IRQ				USART1_IRQn
#define RIKI_SERIAL1_CLK             	RCC_APB2Periph_USART1
#define RIKI_SERIAL1_GPIO_CLK           RCC_APB2Periph_GPIOA
#define RIKI_SERIAL1_GPIO_PORT          GPIOA
#define RIKI_SERIAL1_TX_PIN            	GPIO_Pin_9
#define RIKI_SERIAL1_RX_PIN             GPIO_Pin_10
#define RIKI_SERIAL1_NVIC				1

#define RIKI_SERIAL2					USART2
#define RIKI_SERIAL2_IRQ				USART2_IRQn
#define RIKI_SERIAL2_CLK             	RCC_APB1Periph_USART2
#define RIKI_SERIAL2_GPIO_CLK        	RCC_APB2Periph_GPIOA
#define RIKI_SERIAL2_GPIO_PORT      	GPIOA
#define RIKI_SERIAL2_TX_PIN            	GPIO_Pin_2
#define RIKI_SERIAL2_RX_PIN             GPIO_Pin_3
#define RIKI_SERIAL2_NVIC				2

#define RIKI_SERIAL3									USART3
#define RIKI_SERIAL3_IRQ							USART3_IRQn
#define RIKI_SERIAL3_CLK             	RCC_APB1Periph_USART3
#define RIKI_SERIAL3_GPIO_CLK        	RCC_APB2Periph_GPIOB
#define RIKI_SERIAL3_GPIO_PORT      	GPIOB
#define RIKI_SERIAL3_TX_PIN            	GPIO_Pin_10
#define RIKI_SERIAL3_RX_PIN             GPIO_Pin_11
#define RIKI_SERIAL3_NVIC				3

/** Motor Config **/ 
typedef enum {
	MOTOR1 = 0,
	MOTOR2 = 1,
	MOTOR_END = 2
}Motor_TypeDef; 

#define MOTORn							2
#define RIKI_MOTOR1_A_PIN           GPIO_Pin_5
#define RIKI_MOTOR1_B_PIN           GPIO_Pin_4
#define RIKI_MOTOR1_GPIO_PORT       GPIOA
#define RIKI_MOTOR1_GPIO_CLK        RCC_APB2Periph_GPIOA

#define RIKI_MOTOR2_A_PIN           GPIO_Pin_5
#define RIKI_MOTOR2_B_PIN           GPIO_Pin_4
#define RIKI_MOTOR2_GPIO_PORT       GPIOC
#define RIKI_MOTOR2_GPIO_CLK        RCC_APB2Periph_GPIOC

#define RIKI_MOTOR1_PWM_PIN         GPIO_Pin_6
#define RIKI_MOTOR1_PWM_PORT        GPIOA
#define RIKI_MOTOR1_PWM_CLK         RCC_APB2Periph_GPIOA
#define RIKI_MOTOR1_PWM_TIM         TIM3
#define RIKI_MOTOR1_PWM_TIM_CLK     RCC_APB1Periph_TIM3

#define RIKI_MOTOR2_PWM_PIN         GPIO_Pin_7
#define RIKI_MOTOR2_PWM_PORT        GPIOA
#define RIKI_MOTOR2_PWM_CLK         RCC_APB2Periph_GPIOA
#define RIKI_MOTOR2_PWM_TIM         TIM3
#define RIKI_MOTOR2_PWM_TIM_CLK     RCC_APB1Periph_TIM3


/** Encoder config **/
typedef enum {
	ENCODER1 = 0,
	ENCODER2 = 1,
	ENCODER_END = 2
}Encoder_TypeDef; 

#define ENCODERn 					2

#define ENCODERn                    2

//#define RIKI_ENCODER2_A_PIN         GPIO_Pin_0
//#define RIKI_ENCODER2_B_PIN         GPIO_Pin_1
//#define RIKI_ENCODER2_GPIO_PORT     GPIOA
//#define RIKI_ENCODER2_GPIO_CLK      RCC_APB2Periph_GPIOA

//#define RIKI_ENCODER1_A_PIN         GPIO_Pin_6
//#define RIKI_ENCODER1_B_PIN         GPIO_Pin_7
//#define RIKI_ENCODER1_GPIO_PORT     GPIOB
//#define RIKI_ENCODER1_GPIO_CLK      RCC_APB2Periph_GPIOB

#define RIKI_ENCODER2_TIM           TIM5
#define RIKI_ENCODER2_TIM_CLK       RCC_APB1Periph_TIM5

#define RIKI_ENCODER1_TIM           TIM4
#define RIKI_ENCODER1_TIM_CLK       RCC_APB1Periph_TIM4

//////////////////////////////////////////////// add  将AB相都置为一样 @jinhong
#define RIKI_ENCODER1_A_PIN         GPIO_Pin_6
#define RIKI_ENCODER1_B_PIN         RIKI_ENCODER1_A_PIN
#define RIKI_ENCODER1_GPIO_PORT     GPIOB
#define RIKI_ENCODER1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define RIKI_ENCODER1_A_EXTI_LINE   EXTI_Line6
#define RIKI_ENCODER1_B_EXTI_LINE   RIKI_ENCODER1_A_EXTI_LINE
#define RIKI_ENCODER1_A_IRQ         EXTI9_5_IRQn
#define RIKI_ENCODER1_B_IRQ         RIKI_ENCODER1_A_IRQ
#define RIKI_ENCODER1_A_EXTI_PORT   GPIO_PortSourceGPIOB
#define RIKI_ENCODER1_B_EXTI_PORT   RIKI_ENCODER1_A_EXTI_PORT
#define RIKI_ENCODER1_A_EXTI_PIN    GPIO_PinSource6
#define RIKI_ENCODER1_B_EXTI_PIN    RIKI_ENCODER1_A_EXTI_PIN

#define RIKI_ENCODER2_A_PIN         GPIO_Pin_0
#define RIKI_ENCODER2_B_PIN         RIKI_ENCODER2_A_PIN
#define RIKI_ENCODER2_GPIO_PORT     GPIOA
#define RIKI_ENCODER2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define RIKI_ENCODER2_A_EXTI_LINE   EXTI_Line0
#define RIKI_ENCODER2_B_EXTI_LINE   RIKI_ENCODER2_A_EXTI_LINE
#define RIKI_ENCODER2_A_IRQ         EXTI0_IRQn
#define RIKI_ENCODER2_B_IRQ         RIKI_ENCODER2_A_IRQ
#define RIKI_ENCODER2_A_EXTI_PORT   GPIO_PortSourceGPIOA
#define RIKI_ENCODER2_B_EXTI_PORT   RIKI_ENCODER2_A_EXTI_PORT
#define RIKI_ENCODER2_A_EXTI_PIN    GPIO_PinSource0
#define RIKI_ENCODER2_B_EXTI_PIN    RIKI_ENCODER2_A_EXTI_PIN
//////////////////////////////////////////////////////

/** I2C Config **/

#define RIKI_SDA_PIN                GPIO_Pin_9
#define RIKI_SCL_PIN                GPIO_Pin_8
#define RIKI_I2C_GPIO_PORT          GPIOB
#define RIKI_I2C_GPIO_CLK           RCC_APB2Periph_GPIOB


/** Servo Config **/
typedef enum {
	SERVO1 = 0,
	SERVO2 = 1,
	SERVO_END = 2
}Servo_TypeDef; 

#define SERVOn 					2
#define MAX_ANGLE				270

#define RIKI_SERVO1_PIN				GPIO_Pin_2
#define RIKI_SERVO1_GPIO_PORT		GPIOA
#define RIKI_SERVO1_GPIO_CLK		RCC_APB2Periph_GPIOA
#define RIKI_SERVO1_TIM				TIM2
#define RIKI_SERVO1_TIM_CLK			RCC_APB1Periph_TIM2

#define RIKI_SERVO2_PIN				GPIO_Pin_3
#define RIKI_SERVO2_GPIO_PORT		GPIOA
#define RIKI_SERVO2_GPIO_CLK		RCC_APB2Periph_GPIOA
#define RIKI_SERVO2_TIM				TIM2
#define RIKI_SERVO2_TIM_CLK			RCC_APB1Periph_TIM2

/** LED config **/
#define RIKI_LED_PIN								GPIO_Pin_1
#define RIKI_LED_GPIO_PORT					GPIOC
#define RIKI_LED_GPIO_CLK						RCC_APB2Periph_GPIOC


/** volt adc config **/
#define ADC1_DR_ADDRESS         ((u32)0x4001244C)
#define RIKI_BATTERY_PIN        GPIO_Pin_0
#define RIKI_BATTERY_GPIO_PORT      GPIOC
#define RIKI_BATTERY_GPIO_CLK       RCC_APB2Periph_GPIOC
#define RIKI_BATTERY_ADC_CLK        RCC_APB2Periph_ADC1
#define RIKI_BATTERY_DMA_CLK        RCC_AHBPeriph_DMA1

/** Sonar config **/
#define RIKI_ECHO_PIN               GPIO_Pin_13
#define RIKI_TRIG_PIN               GPIO_Pin_12
#define RIKI_SONAR_GPIO_PORT        GPIOB
#define RIKI_SONAR_GPIO_CLK         RCC_APB2Periph_GPIOB
#define RIKI_SONAR_TIM              TIM6
#define RIKI_SONAR_TIM_CLK          RCC_APB1Periph_TIM6
#define RIKI_SONAR_TIM_IRQ          TIM6_IRQn

#endif // _CONFIG_H_
