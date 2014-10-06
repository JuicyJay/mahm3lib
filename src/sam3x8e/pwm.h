/**
 * @file pwm.h
 * @anchor <pwm>
 * @brief Pulse Width Modulation (PWM)
 * @details {An API for controling the PWM peripheral inside a SAM3X8E MCU.
 * This peripheral is an embedded macrocell within the MCU and all of its 44
 * registers are physically mapped on this macrocell, therefore modifying the
 * register requires that the peripheral clock is enabled in PMC. However, when
 * modified, the register values are stored even it the peripheral clock is
 * turned off and the peripheral will continue its operation when the clock is
 * turned back on.
 * This API implements all 8 independent channels and their change of polarity,
 * alignment, PWM frequency and handles the pin multiplexing for all 16 outputs
 * of the peripheral. The API does not stop any clock once it has started them.}
 * @author {Saeed Ghasemi}
 * @date {28 sep 2014}
 * @pre {The API handles all of its dependencies on other peripherals
 * internally and will start other clocks in order to properly operate.}
 * @bug {Manually tested all functions to comply with all demands.
 * The only problem is that the register set defined below is not working when
 * implemented. The register mapping currently working is non conventional.}
 */

#ifndef PWM_H_
#define PWM_H_

/**
 * @def (PWM channels)
 * These defines are masks for the PWM channels and can be used as the channel
 * input of every function.
 */
#define PWM_CHANNEL_0_MASK				(1<<0)
#define PWM_CHANNEL_1_MASK				(1<<1)
#define PWM_CHANNEL_2_MASK				(1<<2)
#define PWM_CHANNEL_3_MASK				(1<<3)
#define PWM_CHANNEL_4_MASK				(1<<4)
#define PWM_CHANNEL_5_MASK				(1<<5)
#define PWM_CHANNEL_6_MASK				(1<<6)
#define PWM_CHANNEL_7_MASK				(1<<7)
#define PWM_CHANNEL_ALL_MASK			(0xFF)
/**
 * @def (Register masks)
 * These are masks for the PWM_CLK registers two parameter settings controlling
 * the CLKx (A and B).
 *
 * MASKs are being defined like this:
 * [PERIPHERAL]_[REGISTER]_[SECTION]_MASK
 */
#define PWM_CLK_PREA_MASK				(0x00000F00)
#define PWM_CLK_PREB_MASK				(0x0F000000)
#define PWM_CLK_DIVA_MASK				(0x000000FF)
#define PWM_CLK_DIVB_MASK				(0x00FF0000)
/**
 * @def (Register masks)
 * These are masks for the PWM_CMRx registers many parameters that configure a
 * PWM channel.
 *
 * MASKs are being defined like this:
 * [PERIPHERAL]_[REGISTER]_[SECTION]_MASK
 */
#define PWM_CMRx_CPRE_MASK				(0x0000000F)
#define PWM_CMRx_CALG_MASK				(1 << 8)
#define PWM_CMRx_CPOL_MASK				(1 << 9)
#define PWM_CMRx_CES_MASK				(1 << 10)
#define PWM_CMRx_DTE_MASK				(1 << 16)
#define PWM_CMRx_DTHI_MASK				(1 << 17)
#define PWM_CMRx_DTLI_MASK				(1 << 18)
/**
 * @def (Register masks)
 * These are masks for the PWM_CDTYx and PWM_CDTYUPDx's one parameter that can
 * set the channel duty cycle.
 *
 * MASKs are being defined like this:
 * [PERIPHERAL]_[REGISTER]_[SECTION]_MASK
 */
#define PWM_CDTYx_CDTY_MASK				(0x0000FFFF)
#define PWM_CDTYUPDx_CDTYUPD_MASK		(0x0000FFFF)
/**
 * @def (Register masks)
 * These are masks for the PWM_CPRDx and PWM_CPRDUPDx's one parameter that can
 * set the channel period.
 *
 * MASKs are being defined like this:
 * [PERIPHERAL]_[REGISTER]_[SECTION]_MASK
 */
#define PWM_CPRDx_CPRD_MASK				(0x0000FFFF)
#define PWM_CPRDUPDx_CPRDUPD_MASK		(0x0000FFFF)

//PESCALLERS FOR CHANNEL MODE AND CLOCK REGISTER
/**
 * @def (Channel and clock prescalers)
 * PESCALLERS FOR CHANNEL MODE AND CLOCK REGISTER.
 * These can be used with both PWM_CMRx and PWM_CLK registers.
 * The last two defined prescalers are exclusively meant for PWM_CMRx.
 *
 * Parameters are being defined like this:
 * [PERIPHERAL]_[SECTION]_VALUE
 */
#define PWM_PRES_MCK_DIV_1				(0b0000) ///sdfs
#define PWM_PRES_MCK_DIV_2				(0b0001)
#define PWM_PRES_MCK_DIV_4				(0b0010)
#define PWM_PRES_MCK_DIV_8				(0b0011)
#define PWM_PRES_MCK_DIV_16				(0b0100)
#define PWM_PRES_MCK_DIV_32				(0b0101)
#define PWM_PRES_MCK_DIV_64				(0b0110)
#define PWM_PRES_MCK_DIV_128			(0b0111)
#define PWM_PRES_MCK_DIV_256			(0b1000)
#define PWM_PRES_MCK_DIV_512			(0b1001)
#define PWM_PRES_MCK_DIV_1024			(0b1010)
#define PWM_PRES_CLOCKA					(0b1011)
#define PWM_PRES_CLOCKB					(0b1100)
/**
 * @def
 * DIVIDERS FOR CLKA AND CLKB.
 * Dividsors for the CLKx are all values between 0 and 255. But here only the
 * first is defined.
 *
 * Parameters are being defined like this:
 * [PERIPHERAL]_[REGISTER]_[PARAMETER]_VALUE
 */
#define PWM_CLK_DIVx_TURNOFF			0
/**
 * @typedef
 * This structure is used with pwm_init() to set the settings for the clocks A
 * and B of the PWM peripheral.
 * @param clkA_prescaler {This is the prescaler for clock A.
 * Parameter prefix: PWM_CLK_PRES_}
 * @param clkA_divisor {This is the divisor for clock A. Set this between 0 and
 * 255. 0 will turn the clock off.}
 * @param clkB {This is the prescaler for clock B.
 * Parameter prefix: PWM_CLK_PRES_}
 * @param clkA_divisor {This is the divisor for clock B. Set this between 0 and
 * 255. 0 will turn the clock off.}
 */
typedef struct pwm_clk_setting{
	uint32_t clkA_prescaler;
	uint32_t clkA_divisor;
	uint32_t clkB_prescaler;
	uint32_t clkB_divisor;
}pwm_clk_setting;
/**
 * @typedef (pwm_channel_setting)
 * This structure is used with pwm_init_channel() to set the settings of a
 * channel.
 *
 * @param channel {The channel to be initialized. Prefix: PWM_CHANNEL_}
 * @param polarity {Sets the polarity of the channel.
 * Parameter prefix: PWM_POLARITY_}
 * @param alignment {Sets the alignment of the channel.
 * Parameter prefix: PWM_ALIGN_}
 * @param duty_cycle {The initial duty cycle of the channel. (Optional)}
 * @param use_CLKx {Must be 1 or 0 to indicate whether to use one of the CLKx
 * clocks to set the frequency or just the channel prescalers and period must
 * be used.}
 * @param frequency {The frequency of the PWM waveform for this channel.}
 * @param clock_ID {In case that use_CLKx is set to 1, then clock_ID must
 * specify which CLKx can be used for this purpose. Prefix: PWM_CLK_ID_}
 */
typedef struct pwm_channel_setting{
	uint32_t channel;
	uint32_t polarity;
	uint32_t alignment;
	uint32_t duty_cycle;
	uint32_t use_CLKx;
	uint32_t frequency;
	uint32_t clock_ID;
}pwm_channel_setting;
/**
 * @def (Initialization parameters)
 * These are parameters used in conjunction with initializing a PWM channel.
 *
 * Parameters are being defined like this:
 * [PERIPHERAL]_CHANNEL_[PARAMETER]_VALUE
 */
#define PWM_CHANNEL_POLARITY_HIGH		1
#define PWM_CHANNEL_POLARITY_LOW		0
#define PWM_CHANNEL_ALIGN_LEFT			0
#define PWM_CHANNEL_ALIGN_CENTER		1
/**
 * @def
 * These are parameters used in conjunction with turning of clkA and B.
 */
#define PWM_CLK_ID_CLKA					0
#define PWM_CLK_ID_CLKB					1

///@cond
// Pointer to registers of the PWM peripheral.
#define PWM ((pwm_reg_t *) 0x40094000U)
///@endcond

/**
 * @typedef (Register mapping)
 * This structure defines the register mapping of the PWM peripheral.
 */
// Currently bugged (be hold! -> 137 registers. Don't go in there!)
typedef struct {
	// PWM Clock Register, offset 0x000
	uint32_t PWM_CLK;
	// PWM Enable Register, offset 0x004
	uint32_t PWM_ENA;
	// PWM Disable Register, offset 0x008
	uint32_t PWM_DIS;
	// PWM Status Register, offset 0x00C
	uint32_t PWM_SR;
	// Not used
	uint32_t PWM_IER1;
	// Not used
	uint32_t PWM_IDR1;
	// Not used
	uint32_t PWM_IMR1;
	// Not used
	uint32_t PWM_ISR1;
	// Not used
	uint32_t PWM_SCM;
	// Not used
	uint32_t reserved0;
	// Not used
	uint32_t PWM_SCUC;
	// Not used
	uint32_t PWM_SCUP;
	// Not used
	uint32_t PWM_SCUPUPD;
	// Not used
	uint32_t PWM_IER2;
	// Not used
	uint32_t PWM_IDR2;
	// Not used
	uint32_t PWM_IMR2;
	// Not used
	uint32_t PWM_ISR2;
	// Not used
	uint32_t PWM_OOV;
	// Not used
	uint32_t PWM_OS;
	// Not used
	uint32_t PWM_OSS;
	// Not used
	uint32_t PWM_OSC;
	// Not used
	uint32_t PWM_OSSUPD;
	// Not used
	uint32_t PWM_OSCUPD;
	// Not used
	uint32_t PWM_FMR;
	// Not used
	uint32_t PWM_FSR;
	// Not used
	uint32_t PWM_FCR;
	// Not used
	uint32_t PWM_FPV;
	// Not used
	uint32_t PWM_FPE1;
	// Not used
	uint32_t PWM_FPE2;
	// Not used
	uint32_t reserved1[2];
	// Not used
	uint32_t PWM_ELMR0;
	// Not used
	uint32_t PWM_ELMR1;
	// Not used
	uint32_t reserved2[10];
	// Not used
	uint32_t PWM_SMMR;
	// Not used
	uint32_t reserved3[11];
	// Not used
	uint32_t PWM_WPCR;
	// Not used
	uint32_t PWM_WPSR;
	// Not used
	uint32_t reserved4[4];
	// Not used
	uint32_t reserved5[10];
	//Not used
	uint32_t reserved6;
	// Not used
	uint32_t PWM_CMPV0;
	// Not used
	uint32_t PWM_CMPVUPD0;
	// Not used
	uint32_t PWM_CMPM0;
	// Not used
	uint32_t PWM_CMPMUPD0;
	// Not used
	uint32_t PWM_CMPV1;
	// Not used
	uint32_t PWM_CMPVUPD1;
	// Not used
	uint32_t PWM_CMPM1;
	// Not used
	uint32_t PWM_CMPMUPD1;
	// Not used
	uint32_t PWM_CMPV2;
	// Not used
	uint32_t PWM_CMPVUPD2;
	// Not used
	uint32_t PWM_CMPM2;
	// Not used
	uint32_t PWM_CMPMUPD2;
	// Not used
	uint32_t PWM_CMPV3;
	// Not used
	uint32_t PWM_CMPVUPD3;
	// Not used
	uint32_t PWM_CMPM3;
	// Not used
	uint32_t PWM_CMPMUPD3;
	// Not used
	uint32_t PWM_CMPV4;
	// Not used
	uint32_t PWM_CMPVUPD4;
	// Not used
	uint32_t PWM_CMPM4;
	// Not used
	uint32_t PWM_CMPMUPD4;
	// Not used
	uint32_t PWM_CMPV5;
	// Not used
	uint32_t PWM_CMPVUPD5;
	// Not used
	uint32_t PWM_CMPM5;
	// Not used
	uint32_t PWM_CMPMUPD5;
	// Not used
	uint32_t PWM_CMPV6;
	// Not used
	uint32_t PWM_CMPVUPD6;
	// Not used
	uint32_t PWM_CMPM6;
	// Not used
	uint32_t PWM_CMPMUPD6;
	// Not used
	uint32_t PWM_CMPV7;
	// Not used
	uint32_t PWM_CMPVUPD7;
	// Not used
	uint32_t PWM_CMPM7;
	// Not used
	uint32_t PWM_CMPMUPD7;
	// Not used
	uint32_t reserved7[19];

	// PWM Channel Mode Register (Channel 0)
	uint32_t PWM_CMR0;
	// PWM Channel Duty Cycle Register (Channel 0)
	uint32_t PWM_CDTY0;
	// PWM Channel Duty Cycle Update Register (Channel 0)
	uint32_t PWM_CDTYUPD0;
	// PWM Channel Period Register (Channel 0)
	uint32_t PWM_CPRD0;
	// PWM Channel Period Update Register (Channel 0)
	uint32_t PWM_CPRDUPD0;
	// PWM Channel Counter Register (Channel 0)
	uint32_t PWM_CCNT0;
	// PWM Channel Dead Time Register (Channel 0)
	uint32_t PWM_DT0;
	// PWM Channel Dead Time Update Register (Channel 0)
	uint32_t PWM_DTUPD0;

	// PWM Channel Mode Register (Channel 1)
	uint32_t PWM_CMR1;
	// PWM Channel Duty Cycle Register (Channel 1)
	uint32_t PWM_CDTY1;
	// PWM Channel Duty Cycle Update Register (Channel 1)
	uint32_t PWM_CDTYUPD1;
	// PWM Channel Period Register (Channel 1)
	uint32_t PWM_CPRD1;
	// PWM Channel Period Update Register (Channel 1)
	uint32_t PWM_CPRDUPD1;
	// PWM Channel Counter Register (Channel 1)
	uint32_t PWM_CCNT1;
	// PWM Channel Dead Time Register (Channel 1)
	uint32_t PWM_DT1;
	// PWM Channel Dead Time Update Register (Channel 1)
	uint32_t PWM_DTUPD1;

	// PWM Channel Mode Register (Channel 2)
	uint32_t PWM_CMR2;
	// PWM Channel Duty Cycle Register (Channel 2)
	uint32_t PWM_CDTY2;
	// PWM Channel Duty Cycle Update Register (Channel 2)
	uint32_t PWM_CDTYUPD2;
	// PWM Channel Period Register (Channel 2)
	uint32_t PWM_CPRD2;
	// PWM Channel Period Update Register (Channel 2)
	uint32_t PWM_CPRDUPD2;
	// PWM Channel Counter Register (Channel 2)
	uint32_t PWM_CCNT2;
	// PWM Channel Dead Time Register (Channel 2)
	uint32_t PWM_DT2;
	// PWM Channel Dead Time Update Register (Channel 2)
	uint32_t PWM_DTUPD2;

	// PWM Channel Mode Register (Channel 3)
	uint32_t PWM_CMR3;
	// PWM Channel Duty Cycle Register (Channel 3)
	uint32_t PWM_CDTY3;
	// PWM Channel Duty Cycle Update Register (Channel 3)
	uint32_t PWM_CDTYUPD3;
	// PWM Channel Period Register (Channel 3)
	uint32_t PWM_CPRD3;
	// PWM Channel Period Update Register (Channel 3)
	uint32_t PWM_CPRDUPD3;
	// PWM Channel Counter Register (Channel 3)
	uint32_t PWM_CCNT3;
	// PWM Channel Dead Time Register (Channel 3)
	uint32_t PWM_DT3;
	// PWM Channel Dead Time Update Register (Channel 3)
	uint32_t PWM_DTUPD3;

	// PWM Channel Mode Register (Channel 4)
	uint32_t PWM_CMR4;
	// PWM Channel Duty Cycle Register (Channel 4)
	uint32_t PWM_CDTY4;
	// PWM Channel Duty Cycle Update Register (Channel 4)
	uint32_t PWM_CDTYUPD4;
	// PWM Channel Period Register (Channel 4)
	uint32_t PWM_CPRD4;
	// PWM Channel Period Update Register (Channel 4)
	uint32_t PWM_CPRDUPD4;
	// PWM Channel Counter Register (Channel 4)
	uint32_t PWM_CCNT4;
	// PWM Channel Dead Time Register (Channel 4)
	uint32_t PWM_DT4;
	// PWM Channel Dead Time Update Register (Channel 4)
	uint32_t PWM_DTUPD4;

	// PWM Channel Mode Register (Channel 5)
	uint32_t PWM_CMR5;
	// PWM Channel Duty Cycle Register (Channel 5)
	uint32_t PWM_CDTY5;
	// PWM Channel Duty Cycle Update Register (Channel 5)
	uint32_t PWM_CDTYUPD5;
	// PWM Channel Period Register (Channel 5)
	uint32_t PWM_CPRD5;
	// PWM Channel Period Update Register (Channel 5)
	uint32_t PWM_CPRDUPD5;
	// PWM Channel Counter Register (Channel 5)
	uint32_t PWM_CCNT5;
	// PWM Channel Dead Time Register (Channel 5)
	uint32_t PWM_DT5;
	// PWM Channel Dead Time Update Register (Channel 5)
	uint32_t PWM_DTUPD5;

	// PWM Channel Mode Register (Channel 6)
	uint32_t PWM_CMR6;
	// PWM Channel Duty Cycle Register (Channel 6)
	uint32_t PWM_CDTY6;
	// PWM Channel Duty Cycle Update Register (Channel 6)
	uint32_t PWM_CDTYUPD6;
	// PWM Channel Period Register (Channel 6)
	uint32_t PWM_CPRD6;
	// PWM Channel Period Update Register (Channel 6)
	uint32_t PWM_CPRDUPD6;
	// PWM Channel Counter Register (Channel 6)
	uint32_t PWM_CCNT6;
	// PWM Channel Dead Time Register (Channel 6)
	uint32_t PWM_DT6;
	// PWM Channel Dead Time Update Register (Channel 6)
	uint32_t PWM_DTUPD6;

	// PWM Channel Mode Register (Channel 7)
	uint32_t PWM_CMR7;
	// PWM Channel Duty Cycle Register (Channel 7)
	uint32_t PWM_CDTY7;
	// PWM Channel Duty Cycle Update Register (Channel 7)
	uint32_t PWM_CDTYUPD7;
	// PWM Channel Period Register (Channel 7)
	uint32_t PWM_CPRD7;
	// PWM Channel Period Update Register (Channel 7)
	uint32_t PWM_CPRDUPD7;
	// PWM Channel Counter Register (Channel 7)
	uint32_t PWM_CCNT7;
	// PWM Channel Dead Time Register (Channel 7)
	uint32_t PWM_DT7;
	// PWM Channel Dead Time Update Register (Channel 7)
	uint32_t PWM_DTUPD7;
} pwm_reg_t;


// Function Prototypes
/**
 * Default initialization for the PWM peripheral
 * This leaves clkA and clkB off and starts the peripheral clock.
 *
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 * @pre {This function requires the PMC API.}
 */
uint8_t pwm_init_peripheral_default(void);
/**
 * Initialize the PWM peripheral with a structure containing clock_settings.
 * This function controls clkA and clkB and starts the peripheral clock.
 * It is recommended to use pwm_set_channel_frequency() to select a clock.
 *
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 * @pre {This function requires the PMC API.}
 */
uint8_t pwm_init_peripheral(struct pwm_clk_setting clk_settings);
/**
 * Initialize the PWM peripheral with channel- polarity, alignment, prescaler
 * and initial duty cycle. Set use_CLKx to 1 if you want these clocks to be used
 * otherwise set it to 0 to use the channel prescalers only to achieve the
 * frequency. Using the prescaler should be considered first, because enabling
 * the CLKx clocks consumes more power.
 * See pwm_set_channel_frequency() for more details.
 * This function will disable the channel but re-enable it if it was enabled to
 * begin with.
 *
 * The frequency must be set between 2 and 84 MHz.
 *
 * @param channel {The channel-instance of type pwm_channel_setting,
 * (See typedef pwm_channel_setting for more details.)}
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_init_channel(struct pwm_channel_setting channel);
/**
 * This function will enable the selected channel, identified with predefined
 * values, like: PWM_CHANNEL_x_MASK
 *
 * Alternatively use PWM_CHANNEL_ALL_MASK to enable all channel at once.
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @return {error Will always return 1 = SUCCESS}
 */
uint8_t pwm_channel_enable(uint32_t channel);
/**
 * This function will disable the selected channel, identified with predefined
 * values, like: PWM_CHANNEL_x_MASK.
 *
 * Alternatively use PWM_CHANNEL_ALL_MASK to disable all channel at once.
 *
 * @param channel {The channel to be disabled, use prefix: PWM_CHANNEL_}
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_channel_disable(uint32_t channel);
/**
 * This function will return the state of the PWM channel.
 *
 * @param channel {the channel to get the status for}
 * @return {1 if the channel is enabled, 0 if it is disabled}
 */
uint8_t pwm_channel_status(uint32_t channel);
/**
 * Set the channel polarity.
 * This can reverse the duty cycle. Important when using the PWMLx pins.
 *
 * @param channel {The channel to set the polarity for. ex PWM_CHANNEL_0_MASK}
 * @return
 */
uint8_t pwm_set_channel_polarity(uint32_t channel, uint32_t pwm_polarity);
/**
 * Set the channel alignment. Do not change the alignment after having set the
 * channel frequency or set the channel frequency again.
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @return
 */
uint8_t pwm_set_channel_alignment(uint32_t channel, uint32_t PWM_ALIGN_);
/**
 * Set the channel prescaler
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @param prescaler {This is the prescaler to be set.
 * Use one of the predefined. prefix: PWM_CMRx_PRES_}
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_set_channel_prescaler(uint32_t channel, uint32_t prescaler);
/**
 * This function will set the period value used by a given PWM channel.
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @param period {The period of the channel. t must be between 0 and 65535.}
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_set_channel_period(uint32_t channel, uint32_t period);
/**
 * This function will calculate the necessary register values and set everything
 * up for the given channel if successful. The function will seek to deliver
 * the highest resolution possible for the given frequency. It will not use any
 * of the CLKx (A and B) clocks for this purpose.
 * This function will re-enable the channel if it was enabled to begin with.
 * This function will also set the period.
 * Do not change the channel alignment after having set the channel frequency
 * or you will need to run this function again. Changing the alignment will
 * halfthe frequency if going from left-alignment to center-alignment and
 * double it the other way around.
 *
 * If an error is received then the frequency was too high.
 * Highest frequency achievable is 84MHz.
 *
 * @param channel {The channel to set the frequency for}
 * @param frequency {The wanted channel frequency between 2 and 84MHz}
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_set_channel_frequency(uint32_t channel, uint32_t frequency);
/**
 * This function will automatically select the necessary prescaler and divider
 * for the chosen clock based on frequency. The clocks can either be clkA or
 * clkB. This function also updates the necessary register for these clocks.
 * This function will re-enable the channel if it was enabled to begin with.
 * This function will also set the period.
 *
 * The frequency set will be the nearest to the chosen frequency as possible
 * but not exactly.
 * Caution: This is the CLKx frequency, not the channel frequency.
 * If you want channel frequency to be exact, then use:
 * pwm_set_channel_frequency()
 *
 * This function will return an error if it can't find a setting for the
 * frequency. In case of error, the function will not have modified any
 * registers.
 *
 * @param channel {The channel to set the frequency for}
 * @param frequency {The frequency to calculate for}
 * @param pwm_clk_id {the ID for the clock you want to modify,
 * ex: PWM_CLK_ID_CLKA}
 * @return {error, 1 = SUCCESS and 0 = FAIL - This indicates whether a setting
 * could be found for the chosen frequency.}
 */
uint8_t pwm_set_clkx_frequency(uint32_t channel, uint32_t frequency,
		uint32_t pwm_clk_id);
/**
 * The PWM peripheral has 13 different clocks. Among those, 11 are scaled down
 * clocks of the system clock and the two others are the more flexible clocks
 * that can be set to much lower freuencies than the prescalers. These clock go
 * by the name Clock A and Clock B. They are derived by the SYS_CLK_FREQ which
 * they prescale and the outcome of that they can further divide with a divisor
 * and achieve lower frequencies for the PWM peripheral. These clocks can be
 * turned off when not needed.
 *
 * This function will set the prescaler and divisor for the indicated clock.
 * If the prescaler is other than 0, the clock will be turned on.
 *
 * @param clock_id {The id for the clock to be set. Use prefix: PWM_CLK_ID_}
 * @param prescaler {Use one of the predefined prescalers.
 * Prefix: PWM_CLK_PRES_}
 * @param divisor {Use a value between 1 and 255.}
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_set_clkx(uint32_t clock_id, uint32_t prescaler, uint32_t divisor);
/**
 * Read what was earlier written to the channel
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @return {Previously set duty cycle (if 0 is received then it could mean
 * error)}
 */
uint32_t pwm_read(uint32_t channel);
/**
 * Writes an output to a given channel by setting the channel duty cycle.
 * The duty cycle may not exceed the value of period (CPRD) in PWM_CPRDx.
 * Use pwm_get_channel_period() to read this register and get the maximum
 * duty cycle allowed.
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @param duty_cycle {must be between 0 and period.}
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_set_channel_duty_cycle(uint32_t channel, uint32_t duty_cycle);
/**
 * This function will return the maximum value that the duty cycle can be set
 * to. The highest value that this function can return is 65535.
 *
 * @return {Maximum value that the channel duty cycle can be set to.}
 */
uint32_t pwm_get_channel_period(uint32_t channel);
/**
 * This function will return the current alignment of the chosen channel.
 *
 * @return {Can be either PWM_CHANNEL_ALIGN_CENTER or PWM_CHANNEL_ALIGN_LEFT}
 */
uint32_t pwm_get_channel_alignment(uint32_t channel);
/**
 * Turns off one of two clocks in PWM that are called clkA and clkB.
 *
 * @param clock_id
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_turn_off_clkx(uint8_t clock_id);
/**
 * Shuts down the peripheral but keeps all settings
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_shutdown(void);
/**
 * Resets the peripheral and disables all channels
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_reset(void);
/**
 * Reset and turns off the peripheral
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_close(void);


#endif /* PWM_H_ */
