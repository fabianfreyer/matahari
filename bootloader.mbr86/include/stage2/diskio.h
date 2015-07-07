/**
 * \addtogroup bootloader Bootloader
 * @{
 * \addtogroup diskio DiskIO
 * @{
 *
 * \file diskio.h
 * \brief PFF - Low level disk interface modlue include file
 * \author (C)ChaN, 2014
 */

#ifndef _DISKIO_DEFINED
#define _DISKIO_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

#include <common/types.h>

/**Status of Disk Functions */
typedef uint8_t	DSTATUS;


/** Results of Disk Functions */
typedef enum {
  RES_OK = 0,		/**< Function succeeded */
  RES_ERROR,		/**< Disk error */
  RES_NOTRDY,		/**< Not ready */
  RES_PARERR		/**< Invalid parameter */
} DRESULT;


/**
 * \defgroup diskio_api API
 * @{
 */

/**
 * \brief Initialize Disk Drive
 */
DSTATUS disk_initialize (void);

/**
 * \brief Read Partial Sector
 * \param	buff	Pointer to the destination object
 * \param	sector	Sector number (LBA)
 * \param	offset	Offset in the sector
 * \param	count	Byte count (bit15:destination)
 */
DRESULT disk_readp (uint8_t* buff, uint32_t sector, uint32_t offset, uint32_t count);

/**
 * \brief Write Partial Sector
 * \param	buff	Pointer to the data to be written, NULL:Initiate/Finalize write operation
 * \param	sc	Sector number (LBA) or Number of bytes to send
 */
DRESULT disk_writep (const uint8_t* buff, uint32_t sc);
/**@}*/

/** Drive not initialized */
#define STA_NOINIT		0x01

/** No medium in the drive */
#define STA_NODISK		0x02

#ifdef __cplusplus
}
#endif

#endif	/* _DISKIO_DEFINED */
/**@}@}*/
