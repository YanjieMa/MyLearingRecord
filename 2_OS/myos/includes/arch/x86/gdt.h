#ifndef __GDT_H__
#define __GDT_H__

//The GDT is pointed to by the value in the GDTR register. This is loaded using the LGDT assembly instruction, whose argument is a pointer to a GDT Descriptor structure:


/*
**Segment Desscriptor
63  56 55   52 51   48 47           40 39      32
Base    Flags   Limit   Access Byte     Base
31                  16 15                       0
Base                    Limit

**Access Byte
7   6   5   4   3   2   1   0
P   DPL     S   E   DC

P: Present bit. Allows an entry to refer to a valid segment. 任何有效的segment需要设置为1
DPL: 描述符权限级别字段。包含CPU特权级别的segment. 0:最高权限（内核），3：最低权限（用户应用程序）
S: 描述符类型bit，0：system segment ; 1: code or data segment
E: 可执行bit，0: data segment ; 1: code segment(可执行)
DC:  for data selectors: direction bit. 0: segment grows up, 
                                        1: segment grows down
     for code selectors: conforming bit.    0: code in this segment can only be executed from the ring set in DPL
                                            1: code in this segment can be executed from an equal or lower privilege level
RW: For code segments: Readable bit. 
        0: read access for this segment is not allowed. 1: read access is allowed. Write access is never allowed for code segments.
    For data segments: Writeable bit.
        0: write access for this segment is not allowed. 1: write access is allowed. Read access is always allowed for data segments.
A: Accessed bit. Best left clear (0), the CPU will set it when the segment is accessed.

**Flags
3   2   1   0
G   DB  L   Resvered

G: 0 Limit 1Byte blocks; 1 4KiB blocks
DB: 0 16-bit protected mode segment; 1 32-bit protected mode segment
L: 1 64-bit code segment; 0:any other type of segment

**System Segment Descriptor
**Access Byte
7	6	5	4	3	2	1	0
P   DPL	    S	Type
Type: Type of system segment.
Types available in 32-bit protected mode:

0x1: 16-bit TSS (Available)
0x2: LDT
0x3: 16-bit TSS (Busy)
0x9: 32-bit TSS (Available)
0xB: 32-bit TSS (Busy)


*/




// Used for creating GDT segment descriptors in 64-bit integer form.
 
 
// Each define here is for a specific flag in the descriptor.
// Refer to the intel documentation for a description of what each one does.
#define SEG_DESCTYPE(x)  ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)      ((x) << 0x07) // Present
#define SEG_SAVL(x)      ((x) << 0x0C) // Available for system use
#define SEG_LONG(x)      ((x) << 0x0D) // Long mode
#define SEG_SIZE(x)      ((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)      ((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)     (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)
 
#define SD_TYPE(x)              (x << 8)
#define SD_CODE_DATA(x)         (x << 12)
#define SD_DPL(x)               (x << 13)
#define SD_PRESENT(x)           (x << 15)
#define SD_AVL(x)               (x << 20)
#define SD_64BITS(x)            (x << 21)
#define SD_32BITS(x)            (x << 22)
#define SD_4K_GRAN(x)           (x << 23)


#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed
 
#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWR
 
#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWR
 

#define SEG_LIM_L(x)            (x & 0x0ffff)
#define SEG_LIM_H(x)            (x & 0xf0000)
#define SEG_BASE_L(x)           ((x & 0x0000ffff) << 16)
#define SEG_BASE_M(x)           ((x & 0x00ff0000) >> 16)
#define SEG_BASE_H(x)            (x & 0xff000000)


#define SEG_R0_CODE         SD_TYPE(SEG_CODE_EXRD) | SD_CODE_DATA(1) | SD_DPL(0) | \
                            SD_PRESENT(1) | SD_AVL(0) | SD_64BITS(0) | SD_32BITS(1) | \
                            SD_4K_GRAN(1)

#define SEG_R0_DATA         SD_TYPE(SEG_DATA_RDWR) | SD_CODE_DATA(1) | SD_DPL(0) | \
                            SD_PRESENT(1) | SD_AVL(0) | SD_64BITS(0) | SD_32BITS(1) | \
                            SD_4K_GRAN(1)

#define SEG_R3_CODE         SD_TYPE(SEG_CODE_EXRD) | SD_CODE_DATA(1) | SD_DPL(3) | \
                            SD_PRESENT(1) | SD_AVL(0) | SD_64BITS(0) | SD_32BITS(1) | \
                            SD_4K_GRAN(1)

#define SEG_R3_DATA         SD_TYPE(SEG_DATA_RDWR) | SD_CODE_DATA(1) | SD_DPL(3) | \
                            SD_PRESENT(1) | SD_AVL(0) | SD_64BITS(0) | SD_32BITS(1) | \
                            SD_4K_GRAN(1)

#define SEG_TSS             SD_TYPE(9) | SD_DPL(0) | SD_PRESENT(1)


#endif