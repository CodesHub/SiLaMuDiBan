#include "encoder.h"

GPIO_TypeDef*  ENCODER_PORT[ENCODERn] = {RIKI_ENCODER1_GPIO_PORT, RIKI_ENCODER2_GPIO_PORT};
TIM_TypeDef*   ENCODER_TIM[ENCODERn] = {RIKI_ENCODER1_TIM, RIKI_ENCODER2_TIM};
const uint16_t ENCODER_A_PIN[ENCODERn] = {RIKI_ENCODER1_A_PIN, RIKI_ENCODER2_A_PIN};
const uint16_t ENCODER_B_PIN[ENCODERn] = {RIKI_ENCODER1_B_PIN, RIKI_ENCODER2_B_PIN};
const uint32_t ENCODER_PORT_CLK[ENCODERn] = {RIKI_ENCODER1_GPIO_CLK, RIKI_ENCODER2_GPIO_CLK};
const uint32_t ENCODER_TIM_CLK[ENCODERn] = {RIKI_ENCODER1_TIM_CLK, RIKI_ENCODER2_TIM_CLK};

Encoder::Encoder(Encoder_TypeDef _encoder, uint32_t _arr, uint32_t _psc, uint32_t _counts_per_rev)
{
	encoder = _encoder;
	arr = _arr;
	psc = _psc;
	counts_per_rev = _counts_per_rev;

	position = 0;
	last_timer = 0;
	last_timer_diff = 0;
}

void encoder_init(Encoder_TypeDef encoder);
void Encoder::init()
{
	//change 取消编码器模式 @jinhong
	/*
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;

	RCC_APB2PeriphClockCmd(ENCODER_PORT_CLK[this->encoder], ENABLE);
	GPIO_InitStructure.GPIO_Pin = ENCODER_A_PIN[this->encoder] | ENCODER_B_PIN[this->encoder];
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ENCODER_PORT[this->encoder], &GPIO_InitStructure);

	
	RCC_APB1PeriphClockCmd(ENCODER_TIM_CLK[this->encoder], ENABLE);
	TIM_DeInit(ENCODER_TIM[this->encoder]);  
	TIM_TimeBaseInit(ENCODER_TIM[this->encoder], &TIM_TimeBaseStructure); 

	TIM_TimeBaseStructure.TIM_Period = this->arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = this->psc;     //设置预分频：  
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;  //设置时钟分频系数：不分频 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式   

	TIM_TimeBaseInit(ENCODER_TIM[this->encoder], &TIM_TimeBaseStructure);

	
	if(this->encoder == ENCODER1){
		TIM_EncoderInterfaceConfig(ENCODER_TIM[this->encoder], TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
	} else {
		TIM_EncoderInterfaceConfig(ENCODER_TIM[this->encoder], TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Rising);
	}

	TIM_ICStructInit(&TIM_ICInitStructure); //TIM_ICInitStruct->TIM_Channel = TIM_Channel_1
	TIM_ICInitStructure.TIM_ICFilter = 6; 
	TIM_ICInit(ENCODER_TIM[this->encoder], &TIM_ICInitStructure);
	
	
	
	TIM_ClearFlag(ENCODER_TIM[this->encoder], TIM_FLAG_Update); 
	TIM_ITConfig(ENCODER_TIM[this->encoder], TIM_IT_Update, ENABLE); 

	TIM_SetCounter(ENCODER_TIM[this->encoder], 0);

	TIM_Cmd(ENCODER_TIM[this->encoder], ENABLE); */
	
	//①change 外部脉冲计数模式 需要TIMx_ETR引脚,而非TIMx_CHx引脚 （×） @jinhong 
	
	//②add 外部中断模式 需要中断 （√）
	encoder_init(this->encoder);
}

void encoder_init(Encoder_TypeDef encoder)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure; 

	//把AB相的参数都设为一样的，就是单相编码器， RIKI_ENCODER1_A_PIN = RIKI_ENCODER1_B_PIN @jinhnog
	if(encoder == ENCODER1) {
		RCC_APB2PeriphClockCmd(RIKI_ENCODER1_GPIO_CLK , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

		GPIO_InitStructure.GPIO_Pin = RIKI_ENCODER1_A_PIN | RIKI_ENCODER1_B_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RIKI_ENCODER1_GPIO_PORT, &GPIO_InitStructure);

		GPIO_EXTILineConfig(RIKI_ENCODER1_A_EXTI_PORT, RIKI_ENCODER1_A_EXTI_PIN);  
		GPIO_EXTILineConfig(RIKI_ENCODER1_B_EXTI_PORT, RIKI_ENCODER1_B_EXTI_PIN); 

		EXTI_InitStructure.EXTI_Line = RIKI_ENCODER1_A_EXTI_LINE | RIKI_ENCODER1_B_EXTI_LINE ;  
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;  
		EXTI_Init(&EXTI_InitStructure);  
      
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		NVIC_InitStructure.NVIC_IRQChannel = RIKI_ENCODER1_A_IRQ;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = RIKI_ENCODER1_B_IRQ;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
		NVIC_Init(&NVIC_InitStructure);
        
	}

	if(encoder == ENCODER2){
		RCC_APB2PeriphClockCmd(RIKI_ENCODER2_GPIO_CLK, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

		GPIO_InitStructure.GPIO_Pin = RIKI_ENCODER2_A_PIN | RIKI_ENCODER2_B_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RIKI_ENCODER2_GPIO_PORT, &GPIO_InitStructure);

        GPIO_EXTILineConfig(RIKI_ENCODER2_A_EXTI_PORT, RIKI_ENCODER2_A_EXTI_PIN);  
		GPIO_EXTILineConfig(RIKI_ENCODER2_B_EXTI_PORT, RIKI_ENCODER2_B_EXTI_PIN); 
        
		EXTI_InitStructure.EXTI_Line = RIKI_ENCODER2_A_EXTI_LINE | RIKI_ENCODER2_B_EXTI_LINE ;  
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;  
		EXTI_Init(&EXTI_InitStructure);  
        
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		NVIC_InitStructure.NVIC_IRQChannel = RIKI_ENCODER2_A_IRQ;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = RIKI_ENCODER2_B_IRQ;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
		NVIC_Init(&NVIC_InitStructure);

	}	
}

//change @jinhong
#include "motor.h"
#include "encoder.h"

extern Motor motor1;
extern Motor motor2;

extern Encoder encoder1;
extern Encoder encoder2;

void EXTI9_5_IRQHandler(void)   
{  
	if(EXTI_GetITStatus(RIKI_ENCODER1_A_EXTI_LINE) != RESET){
		if(motor1.pwm < 0)
			encoder1.en_cnt --;
		else
			encoder1.en_cnt ++;

		EXTI_ClearITPendingBit(RIKI_ENCODER1_A_EXTI_LINE);
		EXTI_ClearFlag(RIKI_ENCODER1_A_EXTI_LINE);
	}
}

void EXTI0_IRQHandler(void)   
{
	if(EXTI_GetITStatus(RIKI_ENCODER2_A_EXTI_LINE) != RESET){
		//add 单相编码器正反转识别 @jinhong
		if(motor2.pwm < 0)
			encoder2.en_cnt --;
		else
			encoder2.en_cnt ++;
		
		EXTI_ClearITPendingBit(RIKI_ENCODER2_A_EXTI_LINE);
		EXTI_ClearFlag(RIKI_ENCODER2_A_EXTI_LINE);
	}
}	

	

int32_t Encoder::read()
{
	//获取编码器计数 @jinhong
	uint16_t timer_value = en_cnt ;//uint16_t timer_value = TIM_GetCounter(ENCODER_TIM[this->encoder]);
	
	last_timer_diff = timer_value - last_timer;	
	
	last_timer = timer_value;

	position += (int32_t) last_timer_diff;

	return position;
}

int32_t Encoder::getRPM()
{
		long encoder_ticks = read();
		//this function calculates the motor's RPM based on encoder ticks and delta time
		unsigned long current_time = millis();
		unsigned long dt = current_time - prev_update_time_;

		//convert the time from milliseconds to minutes
		double dtm = (double)dt / 60000;
		double delta_ticks = encoder_ticks - prev_encoder_ticks_;

		//calculate wheel's speed (RPM)

		prev_update_time_ = current_time;
		prev_encoder_ticks_ = encoder_ticks;
		
		return (delta_ticks / counts_per_rev) / dtm;
}


void Encoder::set_pos(int32_t pos)
{
	position = pos;
}
