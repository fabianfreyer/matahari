#ifndef __GDT_H
#define __GDT_H

/**
 * \brief utility wrapper to create a GDT entry.
 * \param address_            The address of the memory segment.
 * \param limit_              The size of the segment in bytes or 4k-Blocks
 * \param granularity_        Units for the size. Can be ::gdt_granularity_byte
 *                            or ::gdt_granularity_4k
 * \param descriptor_type_    This is ::gdt_descriptor_code or 
 *                            ::gdt_descriptor_data for code or data segments.
 *                            If this is ::gdt_descriptor_system , \p 
 *                            executable_ , \p expansion_direction_,  
 *                            \p read_write_flag_ and \p access_ are used to 
 *                            determine the segment type. (e.g. 0x9 for 
 *                            386-TSS)
 * \param in_memory_          Used for virtual memory, has to be 1 if the
 *                            segment is in physical memory.
 * \param privilege_level_    ::gdt_ring0 to ::gdt_ring3. Use gdt_kernel_mode or
 *                            gdt_user_mode for most applications.  
 *                            user mode. Rings 1 are hardly ever used.
 * \param segment_type_       ::gdt_segment_16 for 16bit protected mode or
 *                            ::gdt_segment_32 for 32bit protected mode
 * \param accessed_           If set to 0, will be set to one once the segment 
 *                            is accessed.
 * \param executable_         This is ::gdt_executable_code or
 *                            ::gdt_executable_data
 * \param read_write_flag_    If \p executable_ is ::gdt_executable_code, this
 *                            flag determines if the code segment is readable
 *                            (::gdt_segment_xo for executable only and 
 *                            ::gdt_segment_rx for read-access).\n
 *                            If \p executable_ is ::gdt_executable_data, this
 *                            flag determines if the data segment is writable
 *                            (::gdt_segment_ro for read-only and
 *                            ::gdt_segment_rw for read-write access).
 * \param expansion_direction_ For data segments, determines the direction of 
 *                            offsets.
 *                            
 */

#define GDT_ENTRY(address_,limit_,granularity_,segment_type_,in_memory_, \
    privilege_level_,descriptor_type_,executable_,expansion_direction_, \
    read_write_flag_, accessed_) \
  (gdt_entry_t) { \
    .address24_32=((address_ && 0xFF000000)>>24), \
    .address0_24= (address_ && 0x00FFFFFF), \
    .segment_limit16_19=((0xF0000 && limit_)>>16),\
    .segment_limit0_15=(0x0FFFF && limit_), \
    .granularity=granularity_, \
    .segment_type=segment_type_, \
    .reserved=0,\
    .reserved_os=0, \
    .segment_in_memory=in_memory_, \
    .privilege_level=privilege_level_, \
    .descriptor_type=descriptor_type_, \
    .executable=executable_, \
    .expansion_direction=expansion_direction_, \
    .read_write_flag=read_write_flag_, \
    .accessed=accessed_ \
  }

/**
 * \brief GDT_null entry.
 * \note should be 8 bytes of 0x00.
 * \todo write a test case for this.
 */
#define GDT_ENTRY_NULL GDT_ENTRY(0L,0L,gdt_granularity_byte,gdt_segment_16,0, \
    gdt_ring0,gdt_descriptor_data,gdt_executable_data,0 /* expansion */, \
    gdt_segment_ro, 0)

#define gdt_kernel_mode gdt_ring0
#define gdt_user_mode   gdt_ring3
typedef enum{
  gdt_ring0=0U,
  gdt_ring1=1U,
  gdt_ring2=2U,
  gdt_ring3=3U
} gdt_privilege_level_t;

typedef enum{
  gdt_granularity_byte=0U,
  gdt_granularity_4k=1U
} gdt_granularity_t;

typedef enum{
  gdt_segment_16=0U,
  gdt_segment_32=1U,
} gdt_segment_type_t;

typedef enum{
  gdt_descriptor_system=0U,
  gdt_descriptor_code=1U,
  gdt_descriptor_data=1U
} gdt_descriptor_bit_t;

typedef enum{
  gdt_executable_data=0U,
  gdt_executable_code=1U
} gdt_executable_bit_t;

typedef enum{
  gdt_segment_ro=0U,
  gdt_segment_xo=0U,
  gdt_segment_rw=1U,
  gdt_segment_rx=1U
} gdt_segment_perm_t;

/**
 * \brief Entry for the General descriptor table (32Bit)
 * \note is packed, size must be 8 bytes.
 */
typedef struct __attribute__((__packed__)) {
  unsigned char         address24_32        :8; // Byte 8
  gdt_granularity_t     granularity         :1; // Byte 7
  gdt_segment_type_t    segment_type        :1;
  unsigned char         reserved            :1;
  unsigned char         reserved_os         :1;
  unsigned char         segment_limit16_19  :4;
  unsigned char         segment_in_memory   :1; // Byte 6
  gdt_privilege_level_t privilege_level     :2;
 /**
 * This is ::gdt_descriptor_code or ::gdt_descriptor_data for code or data 
 * segments. If this is ::gdt_descriptor_system, the executable, 
 * expansion_direction, read_write_flag and accessed bits are used to
 * determine the segment type. (e.g. 0x9 for 386-TSS)
 * \todo maybe make that possible using a union.
 */
  gdt_descriptor_bit_t  descriptor_type     :1;
  gdt_executable_bit_t  executable          :1;
  /**
   * \for data segments, determines the direction of offsets.
   * \see http://www.sudleyplace.com/dpmione/expanddown.html
   * \todo create an enum for this.
   */
  unsigned char         expansion_direction :1;
  gdt_segment_perm_t    read_write_flag     :1;
  /**
   * If set to 0, will be set to one once the segment is accessed.
   */
  unsigned char         accessed            :1;
  unsigned int          address0_24         :24; // Byte 5,4,3
  unsigned short        segment_limit0_15   :16; // Byte 2,1
} gdt_entry_t;

typedef struct __attribute__((__packed__)) {
  unsigned int          gdt_size            :16;
  gdt_entry_t*            gdt_descriptors;
} gdt_t;

#endif
