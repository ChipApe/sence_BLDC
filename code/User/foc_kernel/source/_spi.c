#include "foc_kernel/include/_spi.h"

#define MISO_R(p)		GPIO_ReadInputDataBit(p->miso_port, p->miso_pin)

#define MOSI_H(p)		GPIO_SetBits(p->mosi_port, p->mosi_pin)
#define MOSI_L(p)		GPIO_ResetBits(p->mosi_port, p->mosi_pin)

#define CLK_H(p)		GPIO_SetBits(p->clk_port, p->clk_pin)
#define CLK_L(p)		GPIO_ResetBits(p->clk_port, p->clk_pin)

#define CS_H(p)			GPIO_SetBits(p->cs_port, p->cs_pin)
#define CS_L(p)			GPIO_ResetBits(p->cs_port, p->cs_pin)

static void SPI_Delay(void)
{
//		__NOP();
}

static void SPI_Start(pSPI p)
{
		CS_L(p);
		p->delay();
}

static void SPI_Stop(pSPI p)
{
		p->delay();
    CS_H(p);
}

#if( SPI_HardWare_STATE == INCLUDE_SPI_HardWare )
static uint8_t SPI_SwapByte_Hard(pSPI p, uint8_t data)
{
}
#endif

static uint8_t SPI_SwapByte_Soft(pSPI p, uint8_t data)
{
}

// 写入寄存器
static void SPI_Write_Reg(pSPI p, uint8_t reg_addr, uint8_t data)
{
}

// 读取寄存器
static uint8_t SPI_Read_Reg(pSPI p, uint8_t reg_addr)
{
}

// 批量写入寄存器
static void SPI_Write_MultiReg(pSPI p, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
}

// 批量读取寄存器
static uint8_t SPI_Read_MultiReg(pSPI p, uint8_t reg_addr, uint8_t *buffer, uint8_t len)
{
}

// SPI软件初始化，GPIO初始化需要在此之前进行
void ca_spi_init(pSPI p, CA_SPI_Mode mode, SPI_Way way)
{
}

void spi_write_reg(pSPI p, uint8_t reg, uint8_t data)
{
}

void spi_write(pSPI p, uint8_t reg, uint8_t *data, uint8_t len)
{
}

uint8_t spi_read_reg(pSPI p, uint8_t reg)
{
}

uint8_t spi_read(pSPI p, uint8_t reg, uint8_t *data, uint8_t len)
{
}
