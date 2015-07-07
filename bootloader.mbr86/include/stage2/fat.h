/**
 * \addtogroup bootloader Bootloader
 * @{
 * \addtogroup pff Petit FatFs
 * @{
 *
 * \file fat.h
 * \brief Petit FatFs - FAT file system module include file
 * \version R0.03 (C)ChaN, 2014
 *
 * Petit FatFs module is an open source software to implement FAT file system to
 * small embedded systems. This is a free software and is opened for education,
 * research and commercial developments under license policy of following trems.
 *
 * \copyright Copyright (C) 2014, ChaN, all right reserved.
 *
 * * The Petit FatFs module is a free software and there is NO WARRANTY.
 * * No restriction on use. You can use, modify and redistribute it for
 *   personal, non-profit or commercial use UNDER YOUR RESPONSIBILITY.
 * * Redistributions of source code must retain the above copyright notice.
 *
 */


#ifndef _PFATFS

/** Revision ID */
#define _PFATFS 4004

#ifdef __cplusplus
extern "C" {
#endif

#include <common/types.h>
#include <common/pffconf.h>

#if _PFATFS != _PFFCONF
#error Wrong configuration file (pffconf.h).
#endif

#if _FS_FAT32
#define CLUST uint32_t
#else
#define CLUST uint16_t
#endif


/** File system object structure */
typedef struct {
  uint8_t fs_type;/**< FAT sub type */
  uint8_t flag;/**< File status flags */
  uint8_t csize;/**< Number of sectors per cluster */
  uint8_t pad1;
  uint16_t n_rootdir;/**< Number of root directory entries (0 on FAT32) */
  CLUST n_fatent;/**< Number of FAT entries (= number of clusters + 2) */
  uint32_t fatbase;/**< FAT start sector */
  uint32_t dirbase;/**< Root directory start sector (Cluster# on FAT32) */
  uint32_t database;/**< Data start sector */
  uint32_t fptr;/**< File R/W pointer */
  uint32_t fsize;/**< File size */
  CLUST org_clust;/**< File start cluster */
  CLUST curr_clust;/**< File current cluster */
  uint32_t dsect;/**< File current data sector */
} FATFS;



/** Directory object structure */
typedef struct {
  uint16_t index;/**< Current read/write index number */
  uint8_t* fn;/**< Pointer to the SFN (in/out) {file[8],ext[3],status[1]} */
  CLUST sclust;/**< Table start cluster (0:Static table) */
  CLUST clust;/**< Current cluster */
  uint32_t sect;/**< Current sector */
} DIR;



/** File status structure */
typedef struct {
  uint32_t fsize;/**< File size */
  uint16_t fdate;/**< Last modified date */
  uint16_t ftime;/**< Last modified time */
  uint8_t fattrib;/**< Attribute */
  char fname[13];/**< File name */
} FILINFO;



/** File function return code (FRESULT) */
typedef enum {
  FR_OK = 0,
  FR_DISK_ERR,
  FR_NOT_READY,
  FR_NO_FILE,
  FR_NOT_OPENED,
  FR_NOT_ENABLED,
  FR_NO_FILESYSTEM
} FRESULT;



/**
 * \defgroup pff_api API
 * @{
 */

/**
* \brief Mount/Unmount a Locical Drive
* \param	fs	Pointer to the new file system object
*/
FRESULT pf_mount (FATFS* fs);

/**
* \brief Open or Create a File
* \param	path	Pointer to the file name
*/
FRESULT pf_open (const char* path);

/**
* \brief Read File
* \param	buff	Pointer to the read buffer (NULL:Forward data to the stream)
* \param	btr	Number of bytes to read
* \param	br	Pointer to number of bytes read
*/
FRESULT pf_read (void* buff, uint32_t btr, uint32_t* br);

/**
* \brief Write File
* \param	buff	Pointer to the data to be written
* \param	btw	Number of bytes to write (0:Finalize the current write operation)
* \param	bw	Pointer to number of bytes written
*/
FRESULT pf_write (const void* buff, uint32_t btw, uint32_t* bw);

/*
* \brief Seek File R/W Pointer
* \param	ofs	File pointer from top of file
*/
FRESULT pf_lseek (uint32_t ofs);

/**
 * \brief Create a Directroy Object
 * \param	dj	Pointer to the directory object to create
 * \param	path	Pointer to the directory path
 */
FRESULT pf_opendir (DIR* dj, const char* path);

/**
 * \brief Read Directory Entry in Sequence
 * \param	dj	Pointer to the open directory object
 * \param	fno	Pointer to file information to return
 */
FRESULT pf_readdir (DIR* dj, FILINFO* fno);
/**@}*/


/**
 * \defgroup pff_flags Flags and offset address
 * @{
 */

/**
 * \defgroup pff_flags_fsflag File status flag (FATFS.flag)
 * @{
 */
#define FA_OPENED 0x01
#define FA_WPRT 0x02
#define FA__WIP 0x40
/**@}*/

/**
 * \defgroup pff_flags_type FAT sub type (FATFS.fs_type)
 * @{
 */
#define FS_FAT12 1
#define FS_FAT16 2
#define FS_FAT32 3
/**@}*/

/**
 * \defgroup pff_flags_attr File attribute bits for directory entry
 * @{
 */
#define AM_RDO 0x01/**< Read only */
#define AM_HID 0x02/**< Hidden */
#define AM_SYS 0x04/**< System */
#define AM_VOL 0x08/**< Volume label */
#define AM_LFN 0x0F/**< LFN entry */
#define AM_DIR 0x10/**< Directory */
#define AM_ARC 0x20/**< Archive */
#define AM_MASK 0x3F/**< Mask of defined bits */
/**@}*/

/**@}*/


/**
 * \defgroup pff_flags_wordaccess Multi-byte word access macros
 * @{
 */
#if _uint16_t_ACCESS == 1/* Enable word access to the FAT structure */
#define LD_uint16_t(ptr) (uint16_t)(*(uint16_t*)(uint8_t*)(ptr))
#define LD_uint32_t(ptr) (uint32_t)(*(uint32_t*)(uint8_t*)(ptr))
#define ST_uint16_t(ptr,val) *(uint16_t*)(uint8_t*)(ptr)=(uint16_t)(val)
#define ST_uint32_t(ptr,val) *(uint32_t*)(uint8_t*)(ptr)=(uint32_t)(val)
#else /* Use byte-by-byte access to the FAT structure */
#define LD_uint16_t(ptr) (uint16_t)(((uint16_t)*((uint8_t*)(ptr)+1)<<8)|(uint16_t)*(uint8_t*)(ptr))
#define LD_uint32_t(ptr) (uint32_t)(((uint32_t)*((uint8_t*)(ptr)+3)<<24)|((uint32_t)*((uint8_t*)(ptr)+2)<<16)|((uint16_t)*((uint8_t*)(ptr)+1)<<8)|*(uint8_t*)(ptr))
#define ST_uint16_t(ptr,val) *(uint8_t*)(ptr)=(uint8_t)(val); *((uint8_t*)(ptr)+1)=(uint8_t)((uint16_t)(val)>>8)
#define ST_uint32_t(ptr,val) *(uint8_t*)(ptr)=(uint8_t)(val); *((uint8_t*)(ptr)+1)=(uint8_t)((uint16_t)(val)>>8); *((uint8_t*)(ptr)+2)=(uint8_t)((uint32_t)(val)>>16); *((uint8_t*)(ptr)+3)=(uint8_t)((uint32_t)(val)>>24)
#endif
/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* _PFATFS */

/**@}@}*/
