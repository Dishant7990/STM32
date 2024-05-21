#ifndef I2C_H
#define I2C_H

#define I2C_PERIPH_CLOCK_FREQ_8MHZ				8000000
#define I2C_STANDARD_MODE_8MHZ_CCR				40
#define I2C_STANDARD_MODE_8MHZ_TRISE			9

extern void I2C_Init(I2C_TypeDef* i2cPort, uint32_t i2cClock, 
																					 uint32_t i2cCCR,
																					 uint32_t i2cTRISE);

extern void I2C_WriteByte(I2C_TypeDef* i2cPort, uint8_t slaveAddr, 
																								uint8_t regAddr,
																								uint8_t data);

extern void I2C_WriteMultiByte(I2C_TypeDef* i2cPort, 
															 uint8_t slaveAddr,
															 uint8_t regAddr,
															 uint8_t* pData,
															 uint32_t length);

extern void I2C_ReadByte(I2C_TypeDef* i2cPort, uint8_t slaveAddr,
																				uint8_t regAddr,
																				uint8_t* pData);

extern void I2C_Read2Bytes(I2C_TypeDef* i2cPort, uint8_t slaveAddr,
																					uint8_t regAddr,
																					uint8_t* pData);

extern void I2C_ReadMultipleBytes(I2C_TypeDef* i2cPort, uint8_t slaveAddr,
																					uint8_t regAddr,
																					uint8_t* pData,
																					uint8_t length);



#endif /* I2C_H */
