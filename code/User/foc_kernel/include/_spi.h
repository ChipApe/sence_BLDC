#ifndef __HXH_SPI_H__
#define	__HXH_SPI_H__

#include "lks32mc03x_lib.h"

//#pragma anon_unions		// 使能匿名联合体

#define	INCLUDE_SPI_HardWare		(1)
#define EXCLUDE_SPI_HardWare		(2)
#define	SPI_HardWare_STATE		( EXCLUDE_SPI_HardWare )		// 是否包含硬件IIC代码

typedef enum {
	SPI_Soft = 0,		// 软件SPI
#if(SPI_HardWare_STATE == INCLUDE_SPI_HardWare)
	SPI_Hard				// 硬件SPI
#endif
} SPI_Way;

typedef enum {
	SPI_MODE_0 = 0,
//	SPI_MODE_1,
//	SPI_MODE_2,
	SPI_MODE_3
} CA_SPI_Mode;

typedef struct _SPI_t {
	// 片选引脚定义
	GPIO_TypeDef 	*cs_port;
	uint16_t			cs_pin;

	SPI_Way		way;		// spi方式
	
	// spi回调函数
	void		(*delay)			(void);													// 延时函数
	
	void		(*start)			(struct _SPI_t *);							// 开始一次通信前回调
	void		(*stop)				(struct _SPI_t *);							// 一次通信结束后回调
	
	uint8_t	(*swap_byte)	(struct _SPI_t *, uint8_t);			// 交换一个字节
	
	void		(*write_reg)	(struct _SPI_t *, uint8_t reg, uint8_t data);
	uint8_t	(*read_reg)		(struct _SPI_t *, uint8_t reg);
	
	void		(*write_multi_reg)	(struct _SPI_t *, uint8_t reg, uint8_t *data, uint8_t len);
	uint8_t	(*read_multi_reg)		(struct _SPI_t *, uint8_t reg, uint8_t *data, uint8_t len);
	
	union {
		struct {				// 软件SPI
			CA_SPI_Mode	mode;		// SPI的模式
			
			// spi接口
			GPIO_TypeDef 		*miso_port,	*mosi_port,		*clk_port;
			uint16_t				miso_pin,		mosi_pin,			clk_pin;
		};
		
#if( SPI_HardWare_STATE == INCLUDE_SPI_HardWare )
		struct {				// 硬件SPI
			uint32_t	time_out;
			void	*		hal_spi_handler;
		};
#endif
	};
} SPI_t;
typedef SPI_t * pSPI;

void ca_spi_init(pSPI p, CA_SPI_Mode mode, SPI_Way way);
void spi_write_reg(pSPI p, uint8_t reg, uint8_t data);
void spi_write(pSPI p, uint8_t reg, uint8_t *data, uint8_t len);
uint8_t spi_read_reg(pSPI p, uint8_t reg);
uint8_t spi_read(pSPI p, uint8_t reg, uint8_t *data, uint8_t len);

/* Basic Function*/

#endif
