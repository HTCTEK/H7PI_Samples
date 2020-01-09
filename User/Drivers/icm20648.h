#ifndef __ICM20648_H__
#define __ICM20648_H__

#include "stm32h7xx_hal.h"
#include "irq.h"


//
//define external
extern  I2C_HandleTypeDef hi2c1;

#define ICM20648_I2C hi2c1

#define ICM20648_AD0     0
#define ICM20648_USE_DMA 0
#define ICM20648_USE_OS  1

#if ICM20648_USE_OS==1
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#endif


#if  ICM20648_AD0==0
#define ICM20648_REG_ADDRESS (0X68<<1)
#elif ICM20648_AD0==1
#define ICM20648_REG_ADDRESS (0X69<<1)
#endif
/**************************************************************************//**
* @name ICM20648 register banks
* @{
******************************************************************************/
#define ICM20648_BANK_0                     ((0 << 5)<<7)                    /**< Register bank 0    */
#define ICM20648_BANK_1                     ((1 << 5)<<7)                    /**< Register bank 1    */
#define ICM20648_BANK_2                     ((2 << 5)<<7)                    /**< Register bank 2    */
#define ICM20648_BANK_3                     ((3 << 5)<<7)                    /**< Register bank 3    */

/***********************/
/* Bank 0 register map */
/***********************/
#define ICM20648_REG_WHO_AM_I               (ICM20648_BANK_0 | 0x00)    /**< Device ID register                                     */

#define ICM20648_REG_USER_CTRL              (ICM20648_BANK_0 | 0x03)    /**< User control register                                  */
#define ICM20648_BIT_DMP_EN                 0x80                        /**< DMP enable bit                                         */
#define ICM20648_BIT_FIFO_EN                0x40                        /**< FIFO enable bit                                        */
#define ICM20648_BIT_I2C_MST_EN             0x20                        /**< I2C master I/F enable bit                              */
#define ICM20648_BIT_I2C_IF_DIS             0x10                        /**< Disable I2C, enable SPI bit                            */
#define ICM20648_BIT_DMP_RST                0x08                        /**< DMP module reset bit                                   */
#define ICM20648_BIT_DIAMOND_DMP_RST        0x04                        /**< SRAM module reset bit                                  */

#define ICM20648_REG_LP_CONFIG              (ICM20648_BANK_0 | 0x05)    /**< Low Power mode config register                         */
#define ICM20648_BIT_I2C_MST_CYCLE          0x40                        /**< I2C master cycle mode enable                           */
#define ICM20648_BIT_ACCEL_CYCLE            0x20                        /**< Accelerometer cycle mode enable                        */
#define ICM20648_BIT_GYRO_CYCLE             0x10                        /**< Gyroscope cycle mode enable                            */

#define ICM20648_REG_PWR_MGMT_1             (ICM20648_BANK_0 | 0x06)    /**< Power Management 1 register                            */
#define ICM20648_BIT_H_RESET                0x80                        /**< Device reset bit                                       */
#define ICM20648_BIT_SLEEP                  0x40                        /**< Sleep mode enable bit                                  */
#define ICM20648_BIT_LP_EN                  0x20                        /**< Low Power feature enable bit                           */
#define ICM20648_BIT_TEMP_DIS               0x08                        /**< Temperature sensor disable bit                         */
#define ICM20648_BIT_CLK_PLL                0x01                        /**< Auto clock source selection setting                    */

#define ICM20648_REG_PWR_MGMT_2             (ICM20648_BANK_0 | 0x07)    /**< Power Management 2 register                            */
#define ICM20648_BIT_PWR_ACCEL_STBY         0x38                        /**< Disable accelerometer                                  */
#define ICM20648_BIT_PWR_GYRO_STBY          0x07                        /**< Disable gyroscope                                      */
#define ICM20648_BIT_PWR_ALL_OFF            0x7F                        /**< Disable both accel and gyro                            */

#define ICM20648_REG_INT_PIN_CFG            (ICM20648_BANK_0 | 0x0F)    /**< Interrupt Pin Configuration register                   */
#define ICM20648_BIT_INT_ACTL               0x80                        /**< Active low setting bit                                 */
#define ICM20648_BIT_INT_OPEN               0x40                        /**< Open collector configuration bit                       */
#define ICM20648_BIT_INT_LATCH_EN           0x20                        /**< Latch enable bit                                       */

#define ICM20648_REG_INT_ENABLE             (ICM20648_BANK_0 | 0x10)    /**< Interrupt Enable register                              */
#define ICM20648_BIT_WOM_INT_EN             0x08                        /**< Wake-up On Motion enable bit                           */

#define ICM20648_REG_INT_ENABLE_1           (ICM20648_BANK_0 | 0x11)    /**< Interrupt Enable 1 register                            */
#define ICM20648_BIT_RAW_DATA_0_RDY_EN      0x01                        /**< Raw data ready interrupt enable bit                    */

#define ICM20648_REG_INT_ENABLE_2           (ICM20648_BANK_0 | 0x12)    /**< Interrupt Enable 2 register                            */
#define ICM20648_BIT_FIFO_OVERFLOW_EN_0     0x01                        /**< FIFO overflow interrupt enable bit                     */

#define ICM20648_REG_INT_ENABLE_3           (ICM20648_BANK_0 | 0x13)    /**< Interrupt Enable 2 register                            */

#define ICM20648_REG_INT_STATUS             (ICM20648_BANK_0 | 0x19)    /**< Interrupt Status register                              */
#define ICM20648_BIT_WOM_INT                0x08                        /**< Wake-up on motion interrupt bit                        */
#define ICM20648_BIT_PLL_RDY                0x04                        /**< PLL ready interrupt bit                                */

#define ICM20648_REG_INT_STATUS_1           (ICM20648_BANK_0 | 0x1A)    /**< Interrupt Status 1 register                            */
#define ICM20648_BIT_RAW_DATA_0_RDY_INT     0x01                        /**< Raw data ready interrupt bit                           */

#define ICM20648_REG_INT_STATUS_2           (ICM20648_BANK_0 | 0x1B)    /**< Interrupt Status 2 register                            */

#define ICM20648_REG_ACCEL_XOUT_H_SH        (ICM20648_BANK_0 | 0x2D)    /**< Accelerometer X-axis data high byte                    */
#define ICM20648_REG_ACCEL_XOUT_L_SH        (ICM20648_BANK_0 | 0x2E)    /**< Accelerometer X-axis data low byte                     */
#define ICM20648_REG_ACCEL_YOUT_H_SH        (ICM20648_BANK_0 | 0x2F)    /**< Accelerometer Y-axis data high byte                    */
#define ICM20648_REG_ACCEL_YOUT_L_SH        (ICM20648_BANK_0 | 0x30)    /**< Accelerometer Y-axis data low byte                     */
#define ICM20648_REG_ACCEL_ZOUT_H_SH        (ICM20648_BANK_0 | 0x31)    /**< Accelerometer Z-axis data high byte                    */
#define ICM20648_REG_ACCEL_ZOUT_L_SH        (ICM20648_BANK_0 | 0x32)    /**< Accelerometer Z-axis data low byte                     */

#define ICM20648_REG_GYRO_XOUT_H_SH         (ICM20648_BANK_0 | 0x33)    /**< Gyroscope X-axis data high byte                        */
#define ICM20648_REG_GYRO_XOUT_L_SH         (ICM20648_BANK_0 | 0x34)    /**< Gyroscope X-axis data low byte                         */
#define ICM20648_REG_GYRO_YOUT_H_SH         (ICM20648_BANK_0 | 0x35)    /**< Gyroscope Y-axis data high byte                        */
#define ICM20648_REG_GYRO_YOUT_L_SH         (ICM20648_BANK_0 | 0x36)    /**< Gyroscope Y-axis data low byte                         */
#define ICM20648_REG_GYRO_ZOUT_H_SH         (ICM20648_BANK_0 | 0x37)    /**< Gyroscope Z-axis data high byte                        */
#define ICM20648_REG_GYRO_ZOUT_L_SH         (ICM20648_BANK_0 | 0x38)    /**< Gyroscope Z-axis data low byte                         */

#define ICM20648_REG_TEMPERATURE_H          (ICM20648_BANK_0 | 0x39)    /**< Temperature data high byte                             */
#define ICM20648_REG_TEMPERATURE_L          (ICM20648_BANK_0 | 0x3A)    /**< Temperature data low byte                              */

#define ICM20648_REG_EXT_SLV_SENS_DATA_00   (ICM20648_BANK_0 | 0x3B)    /**< First sensor data byte read from external I2C devices through I2C master interface */

#define ICM20648_REG_TEMP_CONFIG            (ICM20648_BANK_0 | 0x53)    /**< Temperature Configuration register                     */

#define ICM20648_REG_FIFO_EN_1              (ICM20648_BANK_0 | 0x66)    /**< FIFO Enable 1 register                                 */

#define ICM20648_REG_FIFO_EN_2              (ICM20648_BANK_0 | 0x67)    /**< FIFO Enable 2 register                                 */
#define ICM20648_BIT_ACCEL_FIFO_EN          0x10                        /**< Enable writing acceleration data to FIFO bit           */
#define ICM20648_BITS_GYRO_FIFO_EN          0x0E                        /**< Enable writing gyroscope data to FIFO bit              */

#define ICM20648_REG_FIFO_RST               (ICM20648_BANK_0 | 0x68)    /**< FIFO Reset register                                    */
#define ICM20648_REG_FIFO_MODE              (ICM20648_BANK_0 | 0x69)    /**< FIFO Mode register                                     */

#define ICM20648_REG_FIFO_COUNT_H           (ICM20648_BANK_0 | 0x70)    /**< FIFO data count high byte                              */
#define ICM20648_REG_FIFO_COUNT_L           (ICM20648_BANK_0 | 0x71)    /**< FIFO data count low byte                               */
#define ICM20648_REG_FIFO_R_W               (ICM20648_BANK_0 | 0x72)    /**< FIFO Read/Write register                               */

#define ICM20648_REG_DATA_RDY_STATUS        (ICM20648_BANK_0 | 0x74)    /**< Data Ready Status register                             */
#define ICM20648_BIT_RAW_DATA_0_RDY         0x01                        /**< Raw Data Ready bit                                     */

#define ICM20648_REG_FIFO_CFG               (ICM20648_BANK_0 | 0x76)    /**< FIFO Configuration register                            */
#define ICM20648_BIT_MULTI_FIFO_CFG         0x01                        /**< Interrupt status for each sensor is required           */
#define ICM20648_BIT_SINGLE_FIFO_CFG        0x00                        /**< Interrupt status for only a single sensor is required  */

/***********************/
/* Bank 1 register map */
/***********************/
#define ICM20648_REG_XA_OFFSET_H            (ICM20648_BANK_1 | 0x14)    /**< Acceleration sensor X-axis offset cancellation high byte   */
#define ICM20648_REG_XA_OFFSET_L            (ICM20648_BANK_1 | 0x15)    /**< Acceleration sensor X-axis offset cancellation low byte    */
#define ICM20648_REG_YA_OFFSET_H            (ICM20648_BANK_1 | 0x17)    /**< Acceleration sensor Y-axis offset cancellation high byte   */
#define ICM20648_REG_YA_OFFSET_L            (ICM20648_BANK_1 | 0x18)    /**< Acceleration sensor Y-axis offset cancellation low byte    */
#define ICM20648_REG_ZA_OFFSET_H            (ICM20648_BANK_1 | 0x1A)    /**< Acceleration sensor Z-axis offset cancellation high byte   */
#define ICM20648_REG_ZA_OFFSET_L            (ICM20648_BANK_1 | 0x1B)    /**< Acceleration sensor Z-axis offset cancellation low byte    */

#define ICM20648_REG_TIMEBASE_CORR_PLL      (ICM20648_BANK_1 | 0x28)    /**< PLL Timebase Correction register                           */

/***********************/
/* Bank 2 register map */
/***********************/
#define ICM20648_REG_GYRO_SMPLRT_DIV        (ICM20648_BANK_2 | 0x00)    /**< Gyroscope Sample Rate Divider register     */

#define ICM20648_REG_GYRO_CONFIG_1          (ICM20648_BANK_2 | 0x01)    /**< Gyroscope Configuration 1 register         */
#define ICM20648_BIT_GYRO_FCHOICE           0x01                        /**< Gyro Digital Low-Pass Filter enable bit    */
#define ICM20648_SHIFT_GYRO_FS_SEL          0x01                        /**< Gyro Full Scale Select bit shift           */
#define ICM20648_SHIFT_GYRO_DLPCFG          0x03                        /**< Gyro DLPF Config bit shift                 */
#define ICM20648_MASK_GYRO_FULLSCALE        0x06                        /**< Gyro Full Scale Select bit mask            */
#define ICM20648_MASK_GYRO_BW               0x39                        /**< Gyro Bandwidth Select bit mask             */
#define ICM20648_GYRO_FULLSCALE_250DPS      (0x00 << ICM20648_SHIFT_GYRO_FS_SEL)    /**< Gyro Full Scale = 250 deg/s  */
#define ICM20648_GYRO_FULLSCALE_500DPS      (0x01 << ICM20648_SHIFT_GYRO_FS_SEL)    /**< Gyro Full Scale = 500 deg/s  */
#define ICM20648_GYRO_FULLSCALE_1000DPS     (0x02 << ICM20648_SHIFT_GYRO_FS_SEL)    /**< Gyro Full Scale = 1000 deg/s */
#define ICM20648_GYRO_FULLSCALE_2000DPS     (0x03 << ICM20648_SHIFT_GYRO_FS_SEL)    /**< Gyro Full Scale = 2000 deg/s */
#define ICM20648_GYRO_BW_12100HZ            (0x00 << ICM20648_SHIFT_GYRO_DLPCFG)                                    /**< Gyro Bandwidth = 12100 Hz */
#define ICM20648_GYRO_BW_360HZ              ( (0x07 << ICM20648_SHIFT_GYRO_DLPCFG) | ICM20648_BIT_GYRO_FCHOICE)     /**< Gyro Bandwidth = 360 Hz   */
#define ICM20648_GYRO_BW_200HZ              ( (0x00 << ICM20648_SHIFT_GYRO_DLPCFG) | ICM20648_BIT_GYRO_FCHOICE)     /**< Gyro Bandwidth = 200 Hz   */
#define ICM20648_GYRO_BW_150HZ              ( (0x01 << ICM20648_SHIFT_GYRO_DLPCFG) | ICM20648_BIT_GYRO_FCHOICE)     /**< Gyro Bandwidth = 150 Hz   */
#define ICM20648_GYRO_BW_120HZ              ( (0x02 << ICM20648_SHIFT_GYRO_DLPCFG) | ICM20648_BIT_GYRO_FCHOICE)     /**< Gyro Bandwidth = 120 Hz   */
#define ICM20648_GYRO_BW_51HZ               ( (0x03 << ICM20648_SHIFT_GYRO_DLPCFG) | ICM20648_BIT_GYRO_FCHOICE)     /**< Gyro Bandwidth = 51 Hz    */
#define ICM20648_GYRO_BW_24HZ               ( (0x04 << ICM20648_SHIFT_GYRO_DLPCFG) | ICM20648_BIT_GYRO_FCHOICE)     /**< Gyro Bandwidth = 24 Hz    */
#define ICM20648_GYRO_BW_12HZ               ( (0x05 << ICM20648_SHIFT_GYRO_DLPCFG) | ICM20648_BIT_GYRO_FCHOICE)     /**< Gyro Bandwidth = 12 Hz    */
#define ICM20648_GYRO_BW_6HZ                ( (0x06 << ICM20648_SHIFT_GYRO_DLPCFG) | ICM20648_BIT_GYRO_FCHOICE)     /**< Gyro Bandwidth = 6 Hz     */

#define ICM20648_REG_GYRO_CONFIG_2          (ICM20648_BANK_2 | 0x02)    /**< Gyroscope Configuration 2 register                     */
#define ICM20648_BIT_GYRO_CTEN              0x38                        /**< Gyroscope Self-Test Enable bits                        */

#define ICM20648_REG_XG_OFFS_USRH           (ICM20648_BANK_2 | 0x03)    /**< Gyroscope sensor X-axis offset cancellation high byte  */
#define ICM20648_REG_XG_OFFS_USRL           (ICM20648_BANK_2 | 0x04)    /**< Gyroscope sensor X-axis offset cancellation low byte   */
#define ICM20648_REG_YG_OFFS_USRH           (ICM20648_BANK_2 | 0x05)    /**< Gyroscope sensor Y-axis offset cancellation high byte  */
#define ICM20648_REG_YG_OFFS_USRL           (ICM20648_BANK_2 | 0x06)    /**< Gyroscope sensor Y-axis offset cancellation low byte   */
#define ICM20648_REG_ZG_OFFS_USRH           (ICM20648_BANK_2 | 0x07)    /**< Gyroscope sensor Z-axis offset cancellation high byte  */
#define ICM20648_REG_ZG_OFFS_USRL           (ICM20648_BANK_2 | 0x08)    /**< Gyroscope sensor Z-axis offset cancellation low byte   */

#define ICM20648_REG_ODR_ALIGN_EN           (ICM20648_BANK_2 | 0x09)    /**< Output Data Rate start time alignment                  */

#define ICM20648_REG_ACCEL_SMPLRT_DIV_1     (ICM20648_BANK_2 | 0x10)    /**< Acceleration Sensor Sample Rate Divider 1 register     */
#define ICM20648_REG_ACCEL_SMPLRT_DIV_2     (ICM20648_BANK_2 | 0x11)    /**< Acceleration Sensor Sample Rate Divider 2 register     */

#define ICM20648_REG_ACCEL_INTEL_CTRL       (ICM20648_BANK_2 | 0x12)    /**< Accelerometer Hardware Intelligence Control register   */
#define ICM20648_BIT_ACCEL_INTEL_EN         0x02                        /**< Wake-up On Motion enable bit                           */
#define ICM20648_BIT_ACCEL_INTEL_MODE       0x01                        /**< WOM algorithm selection bit                            */

#define ICM20648_REG_ACCEL_WOM_THR          (ICM20648_BANK_2 | 0x13)    /**< Wake-up On Motion Threshold register                   */

#define ICM20648_REG_ACCEL_CONFIG           (ICM20648_BANK_2 | 0x14)    /**< Accelerometer Configuration register                   */
#define ICM20648_BIT_ACCEL_FCHOICE          0x01                        /**< Accel Digital Low-Pass Filter enable bit               */
#define ICM20648_SHIFT_ACCEL_FS             0x01                        /**< Accel Full Scale Select bit shift                      */
#define ICM20648_SHIFT_ACCEL_DLPCFG         0x03                        /**< Accel DLPF Config bit shift                            */
#define ICM20648_MASK_ACCEL_FULLSCALE       0x06                        /**< Accel Full Scale Select bit mask                       */
#define ICM20648_MASK_ACCEL_BW              0x39                        /**< Accel Bandwidth Select bit mask                        */
#define ICM20648_ACCEL_FULLSCALE_2G         (0x00 << ICM20648_SHIFT_ACCEL_FS)   /**< Accel Full Scale = 2 g     */
#define ICM20648_ACCEL_FULLSCALE_4G         (0x01 << ICM20648_SHIFT_ACCEL_FS)   /**< Accel Full Scale = 4 g     */
#define ICM20648_ACCEL_FULLSCALE_8G         (0x02 << ICM20648_SHIFT_ACCEL_FS)   /**< Accel Full Scale = 8 g     */
#define ICM20648_ACCEL_FULLSCALE_16G        (0x03 << ICM20648_SHIFT_ACCEL_FS)   /**< Accel Full Scale = 16 g    */
#define ICM20648_ACCEL_BW_1210HZ            (0x00 << ICM20648_SHIFT_ACCEL_DLPCFG)                                    /**< Accel Bandwidth = 1210 Hz  */
#define ICM20648_ACCEL_BW_470HZ             ( (0x07 << ICM20648_SHIFT_ACCEL_DLPCFG) | ICM20648_BIT_ACCEL_FCHOICE)    /**< Accel Bandwidth = 470 Hz   */
#define ICM20648_ACCEL_BW_246HZ             ( (0x00 << ICM20648_SHIFT_ACCEL_DLPCFG) | ICM20648_BIT_ACCEL_FCHOICE)    /**< Accel Bandwidth = 246 Hz   */
#define ICM20648_ACCEL_BW_111HZ             ( (0x02 << ICM20648_SHIFT_ACCEL_DLPCFG) | ICM20648_BIT_ACCEL_FCHOICE)    /**< Accel Bandwidth = 111 Hz   */
#define ICM20648_ACCEL_BW_50HZ              ( (0x03 << ICM20648_SHIFT_ACCEL_DLPCFG) | ICM20648_BIT_ACCEL_FCHOICE)    /**< Accel Bandwidth = 50 Hz    */
#define ICM20648_ACCEL_BW_24HZ              ( (0x04 << ICM20648_SHIFT_ACCEL_DLPCFG) | ICM20648_BIT_ACCEL_FCHOICE)    /**< Accel Bandwidth = 24 Hz    */
#define ICM20648_ACCEL_BW_12HZ              ( (0x05 << ICM20648_SHIFT_ACCEL_DLPCFG) | ICM20648_BIT_ACCEL_FCHOICE)    /**< Accel Bandwidth = 12 Hz    */
#define ICM20648_ACCEL_BW_6HZ               ( (0x06 << ICM20648_SHIFT_ACCEL_DLPCFG) | ICM20648_BIT_ACCEL_FCHOICE)    /**< Accel Bandwidth = 6 Hz     */

#define ICM20648_REG_ACCEL_CONFIG_2         (ICM20648_BANK_2 | 0x15)    /**< Accelerometer Configuration 2 register             */
#define ICM20648_BIT_ACCEL_CTEN             0x1C                        /**< Accelerometer Self-Test Enable bits                */

/***********************/
/* Bank 3 register map */
/***********************/
#define ICM20648_REG_I2C_MST_ODR_CONFIG     (ICM20648_BANK_3 | 0x00)    /**< I2C Master Output Data Rate Configuration register */

#define ICM20648_REG_I2C_MST_CTRL           (ICM20648_BANK_3 | 0x01)    /**< I2C Master Control register                        */
#define ICM20648_BIT_I2C_MST_P_NSR          0x10                        /**< Stop between reads enabling bit                    */
#define ICM20648_I2C_MST_CTRL_CLK_400KHZ    0x07                        /**< I2C_MST_CLK = 345.6 kHz (for 400 kHz Max)          */

#define ICM20648_REG_I2C_MST_DELAY_CTRL     (ICM20648_BANK_3 | 0x02)    /**< I2C Master Delay Control register                  */
#define ICM20648_BIT_SLV0_DLY_EN            0x01                        /**< I2C Slave0 Delay Enable bit                        */
#define ICM20648_BIT_SLV1_DLY_EN            0x02                        /**< I2C Slave1 Delay Enable bit                        */
#define ICM20648_BIT_SLV2_DLY_EN            0x04                        /**< I2C Slave2 Delay Enable bit                        */
#define ICM20648_BIT_SLV3_DLY_EN            0x08                        /**< I2C Slave3 Delay Enable bit                        */

#define ICM20648_REG_I2C_SLV0_ADDR          (ICM20648_BANK_3 | 0x03)    /**< I2C Slave0 Physical Address register               */
#define ICM20648_REG_I2C_SLV0_REG           (ICM20648_BANK_3 | 0x04)    /**< I2C Slave0 Register Address register               */
#define ICM20648_REG_I2C_SLV0_CTRL          (ICM20648_BANK_3 | 0x05)    /**< I2C Slave0 Control register                        */
#define ICM20648_REG_I2C_SLV0_DO            (ICM20648_BANK_3 | 0x06)    /**< I2C Slave0 Data Out register                       */

#define ICM20648_REG_I2C_SLV1_ADDR          (ICM20648_BANK_3 | 0x07)    /**< I2C Slave1 Physical Address register               */
#define ICM20648_REG_I2C_SLV1_REG           (ICM20648_BANK_3 | 0x08)    /**< I2C Slave1 Register Address register               */
#define ICM20648_REG_I2C_SLV1_CTRL          (ICM20648_BANK_3 | 0x09)    /**< I2C Slave1 Control register                        */
#define ICM20648_REG_I2C_SLV1_DO            (ICM20648_BANK_3 | 0x0A)    /**< I2C Slave1 Data Out register                       */

#define ICM20648_REG_I2C_SLV2_ADDR          (ICM20648_BANK_3 | 0x0B)    /**< I2C Slave2 Physical Address register               */
#define ICM20648_REG_I2C_SLV2_REG           (ICM20648_BANK_3 | 0x0C)    /**< I2C Slave2 Register Address register               */
#define ICM20648_REG_I2C_SLV2_CTRL          (ICM20648_BANK_3 | 0x0D)    /**< I2C Slave2 Control register                        */
#define ICM20648_REG_I2C_SLV2_DO            (ICM20648_BANK_3 | 0x0E)    /**< I2C Slave2 Data Out register                       */

#define ICM20648_REG_I2C_SLV3_ADDR          (ICM20648_BANK_3 | 0x0F)    /**< I2C Slave3 Physical Address register               */
#define ICM20648_REG_I2C_SLV3_REG           (ICM20648_BANK_3 | 0x10)    /**< I2C Slave3 Register Address register               */
#define ICM20648_REG_I2C_SLV3_CTRL          (ICM20648_BANK_3 | 0x11)    /**< I2C Slave3 Control register                        */
#define ICM20648_REG_I2C_SLV3_DO            (ICM20648_BANK_3 | 0x12)    /**< I2C Slave3 Data Out register                       */

#define ICM20648_REG_I2C_SLV4_ADDR          (ICM20648_BANK_3 | 0x13)    /**< I2C Slave4 Physical Address register               */
#define ICM20648_REG_I2C_SLV4_REG           (ICM20648_BANK_3 | 0x14)    /**< I2C Slave4 Register Address register               */
#define ICM20648_REG_I2C_SLV4_CTRL          (ICM20648_BANK_3 | 0x15)    /**< I2C Slave4 Control register                        */
#define ICM20648_REG_I2C_SLV4_DO            (ICM20648_BANK_3 | 0x16)    /**< I2C Slave4 Data Out register                       */
#define ICM20648_REG_I2C_SLV4_DI            (ICM20648_BANK_3 | 0x17)    /**< I2C Slave4 Data In register                        */

#define ICM20648_BIT_I2C_SLV_READ           0x80                        /**< I2C Slave Read bit                                 */
#define ICM20648_BIT_I2C_SLV_EN             0x80                        /**< I2C Slave Enable bit                               */
#define ICM20648_BIT_I2C_BYTE_SW            0x40                        /**< I2C Slave Byte Swap enable bit                     */
#define ICM20648_BIT_I2C_REG_DIS            0x20                        /**< I2C Slave Do Not Write Register Value bit          */
#define ICM20648_BIT_I2C_GRP                0x10                        /**< I2C Slave Group bit                                */
#define ICM20648_BIT_I2C_READ               0x80                        /**< I2C Slave R/W bit                                  */

/* Register common for all banks */
#define ICM20648_REG_BANK_SEL               0x7F                        /**< Bank Select register                               */

#define ICM20648_DEVICE_ID                  0xEA                        /**< Device ID value                                    */

#endif


