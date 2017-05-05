#ifndef __EMC_H__
#define __EMC_H__

#include <cstdint>

/* Record types */
#define EMC_INFO_HDR 0x2020726564616548 // "Header  "
#define EMC_FILE_HDR 0x20726448656C6946 // "FileHdr "
#define EMC_IINF_HDR 0x666E496567616D49 // "ImageInf"
#define EMC_SEQN_HDR 0x65636E6575716553 // "Sequence"
#define EMC_STRM_HDR 0x20206D6165727453 // "Stream  "
#define EMC_IFRM_HDR 0x6D72466567616D49 // "ImageFrm"
#define EMC_CPRT_HDR 0x7468676972797063 // "cpyright"
#define EMC_DSPT_HDR 0x7470697263736564 // "descript"

extern "C" {
#pragma pack(1)
typedef struct {
  char magic[8]; // "Entis\1A\00\00"
  uint32_t fileId; // Type of file
  uint32_t info;  // Information
  char type[40]; // Different types of file, sometimes can overlap with next fields
  uint32_t dataSize; // dataSize+0x40 = size of file
  char pad3[4]; // Zero pad
} emcheader;

typedef struct {
  uint64_t type; // Type of record
  uint64_t length; // Length of record
  char data[0]; // Data
} emcrecord;
#pragma pack()
};

#endif // __EMC_H__
