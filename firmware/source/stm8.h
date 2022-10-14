#ifndef STM8
#define STM8

#include <stdint.h>

// GPIO

typedef struct {
	volatile uint8_t ODR; // Output data register
	volatile uint8_t IDR; // Pin input register
	volatile uint8_t DDR; // Data direction register
	volatile uint8_t CR1; // Control register 1
	volatile uint8_t CR2; // Control register 2
} GPIO_T;

#define GPIOA ((GPIO_T *) 0x5000)
#define GPIOB ((GPIO_T *) 0x5005)
#define GPIOC ((GPIO_T *) 0x500A)
#define GPIOD ((GPIO_T *) 0x500F)

// External interrupt controller

typedef struct {
	volatile uint8_t CR1; // Control register 1
	volatile uint8_t CR2; // Control register 2
} EXTI_T;

#define EXTI ((EXTI_T *) 0x50A0)

// Window watchdog

typedef struct {
	volatile uint8_t CR; // Control register
	volatile uint8_t WR; // Window register
} WWDG_T;

#define WWDG ((WWDG_T *) 0x50D1)

// Clock controller

typedef struct {
	volatile uint8_t ICKR; // Internal clock register
	volatile uint8_t ECKR; // External clock register
	uint8_t RESERVED1;
	volatile uint8_t CMSR; // Clock master status register
	volatile uint8_t SWR; // Clock master switch register
	volatile uint8_t SWCR; // Switch control register
	volatile uint8_t CKDIVR; // Clock divider register
	volatile uint8_t PCKENR1; // Peripheral clock gating register 1
	volatile uint8_t CSSR; // Clock security system register
	volatile uint8_t CCOR; // Configurable clock output register
	volatile uint8_t PCKENR2; // Peripheral clock gating register 2
	uint8_t RESERVED2;
	volatile uint8_t HSITRIMR; // HSI clock calibration trimming register
	volatile uint8_t SWIMCCR; // SWIM clock control register
} CLK_T;

#define CLK ((CLK_T *) 0x50C0)

// Flash

typedef struct {
	volatile uint8_t CR1; // Control register 1
	volatile uint8_t CR2; // Control register 2
	volatile uint8_t NCR2; // Complementary control register 2
	volatile uint8_t FPR; // Flash protection register
	volatile uint8_t NFPR; // Complementary flash protection register
	volatile uint8_t IAPSR; // Flash status register
	uint8_t RESERVED1;
	uint8_t RESERVED2;
	volatile uint8_t PUKR; // Flash program memory unprotecting key register
	uint8_t RESERVED3;
	volatile uint8_t DUKR; // Data EEPROM unprotection key register
} FLASH_T;

#define FLASH ((FLASH_T *) 0x505A)

// ADC 1

typedef struct {
	volatile uint8_t DB0RH; // Data buffer register 0 high
	volatile uint8_t DB0RL; // Data buffer register 0 low
	volatile uint8_t DB1RH; // Data buffer register 1 high
	volatile uint8_t DB1RL; // Data buffer register 1 low
	volatile uint8_t DB2RH; // Data buffer register 2 high
	volatile uint8_t DB2RL; // Data buffer register 2 low
	volatile uint8_t DB3RH; // Data buffer register 3 high
	volatile uint8_t DB3RL; // Data buffer register 3 low
	volatile uint8_t DB4RH; // Data buffer register 4 high
	volatile uint8_t DB4RL; // Data buffer register 4 low
	volatile uint8_t DB5RH; // Data buffer register 5 high
	volatile uint8_t DB5RL; // Data buffer register 5 low
	volatile uint8_t DB6RH; // Data buffer register 6 high
	volatile uint8_t DB6RL; // Data buffer register 6 low
	volatile uint8_t DB7RH; // Data buffer register 7 high
	volatile uint8_t DB7RL; // Data buffer register 7 low
	volatile uint8_t DB8RH; // Data buffer register 8 high
	volatile uint8_t DB8RL; // Data buffer register 8 low
	volatile uint8_t DB9RH; // Data buffer register 9 high
	volatile uint8_t DB9RL; // Data buffer register 9 low
	uint8_t RESERVED[12];
	volatile uint8_t CSR; // Control status register
	volatile uint8_t CR1; // Configuration register 1
	volatile uint8_t CR2; // Configuration register 2
	volatile uint8_t CR3; // Configuration register 3
	volatile uint8_t DRH; // Data register high
	volatile uint8_t DRL; // Data register low
	volatile uint8_t TDRH; // Schmitt trigger disable register high
	volatile uint8_t TDRL; // Schmitt trigger disable register low
	volatile uint8_t HTRH; // High threshold register high
	volatile uint8_t HTRL; // High threshold register low
	volatile uint8_t LTRH; // Low threshold register high
	volatile uint8_t LTRL; // Low threshold register low
	volatile uint8_t AWSRH; // Watchdog status register high
	volatile uint8_t AWSRL; // Watchdog status register low
	volatile uint8_t AWCRH; // Watchdog control register high
	volatile uint8_t AWCRL; // Watchdog control register low
} ADC1_T;

#define ADC1 ((ADC1_T *) 0x53E0)

// Timer 1

typedef struct {
	volatile uint8_t CR1; // Control register 1
	volatile uint8_t CR2; // Control register 2
	volatile uint8_t SMCR; // Slave mode control register
	volatile uint8_t ETR; // External trigger register
	volatile uint8_t IER; // Interrupt enable register
	volatile uint8_t SR1; // Status register 1
	volatile uint8_t SR2; // Status register 2
	volatile uint8_t EGR; // Event generation register
	volatile uint8_t CCMR1; // Capture compare mode register 1
	volatile uint8_t CCMR2; // Capture compare mode register 2
	volatile uint8_t CCMR3; // Capture compare mode register 3
	volatile uint8_t CCMR4; // Capture compare mode register 4
	volatile uint8_t CCER1; // Capture/compare enable register 1
	volatile uint8_t CCER2; // Capture/compare enable register 2
	volatile uint8_t CNTRH; // Counter high
	volatile uint8_t CNTRL; // Counter low
	volatile uint8_t PSCRH; // Prescaler high
	volatile uint8_t PSCRL; // Prescaler low
	volatile uint8_t ARRH; // Auto reload register high
	volatile uint8_t ARRL; // Auto reload register low
	volatile uint8_t RCR; // Repetition counter register
	volatile uint8_t CCR1H; // Capture compare register 1 high
	volatile uint8_t CCR1L; // Capture compare register 1 low
	volatile uint8_t CCR2H; // Capture compare register 2 high
	volatile uint8_t CCR2L; // Capture compare register 2 low
	volatile uint8_t CCR3H; // Capture compare register 3 high
	volatile uint8_t CCR3L; // Capture compare register 3 low
	volatile uint8_t CCR4H; // Capture compare register 4 high
	volatile uint8_t CCR4L; // Capture compare register 4 low
	volatile uint8_t BKR; // Break register
	volatile uint8_t DTR; // Deadtime register
	volatile uint8_t OISR; // Output idle state register
} TIM1_T;

#define TIM1 ((TIM1_T *) 0x5250)

// Timer 2

typedef struct {
	volatile uint8_t CR1; // Control register 1
	uint8_t RESERVED1;
	uint8_t RESERVED2;
	volatile uint8_t IER; // Interrupt enable register
	volatile uint8_t SR1; // Status register 1
	volatile uint8_t SR2; // Status register 2
	volatile uint8_t EGR; // Event generation register
	volatile uint8_t CCMR1; // Capture compare mode register 1
	volatile uint8_t CCMR2; // Capture compare mode register 2
	volatile uint8_t CCMR3; // Capture compare mode register 3
	volatile uint8_t CCER1; // Capture compare enable register 1
	volatile uint8_t CCER2; // Capture compare enable register 2
	volatile uint8_t CNTRH; // Counter high
	volatile uint8_t CNTRL; // Counter low
	volatile uint8_t PSCR; // Prescaler register
	volatile uint8_t ARRH; // Auto reload register high
	volatile uint8_t ARRL; // Auto reload register low
	volatile uint8_t CCR1H; // Capture compare register 1 high
	volatile uint8_t CCR1L; // Capture compare register 1 low
	volatile uint8_t CCR2H; // Capture compare register 2 high
	volatile uint8_t CCR2L; // Capture compare register 2 low
	volatile uint8_t CCR3H; // Capture compare register 3 high
	volatile uint8_t CCR3L; // Capture compare register 3 low
} TIM2_T;

#define TIM2 ((TIM2_T *) 0x5300)

// Timer 4

typedef struct {
	volatile uint8_t CR1; // Control register 1
	uint8_t RESERVED1;
	uint8_t RESERVED2;
	volatile uint8_t IER; // Interrupt enable register
	volatile uint8_t SR1; // Status register 1
	volatile uint8_t EGR; // Event generation register
	volatile uint8_t CNTR; // Counter
	volatile uint8_t PSCR; // Prescaler register
	volatile uint8_t ARR; // Auto reload register
} TIM4_T;

#define TIM4 ((TIM4_T *) 0x5340)

#endif