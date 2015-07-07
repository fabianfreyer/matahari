/**
 * \addtogroup bootloader Bootloader
 * @{
 * \addtogroup diskio DiskIO
 * @{
 * \file diskio.c
 * \todo Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2014
 */
#include <common/arch.h>
#include <common/code16.h>
#include <common/config.h>

#include <stage2/diskio.h>



DSTATUS disk_initialize(void) {
  DSTATUS stat = 0;
  /// \todo Put your code here
  return stat;
}


DRESULT disk_readp(uint8_t* buff, uint32_t sector, uint32_t offset, uint32_t count) {
  DRESULT res = 0;
  /// \todo Put your code here
  return res;
}




DRESULT disk_writep(const uint8_t* buff, uint32_t sc) {
  DRESULT res = 0;

  if (!buff) {
    if (sc) {
      /// \todo Initiate write process
    } else {
      /// \todo Finalize write process
    }
  } else {
    /// \todo Send data to the disk
  }
  return res;
}

/**@}@}*/
