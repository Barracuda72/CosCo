#ifndef __ERIFILE_H__
#define __ERIFILE_H__

#include "EMC.h"
#include "EntisFile.h"

/* File header - Version */
#define ERI_VERSION 0x00020100 // Version number
#define ERI_VEREX   0x00020200 // Extended version
/* File header - Container */
#define ERI_FULLCOL 0x01       // Fullcolor (or 8-bit) image
#define ERI_PALETTE 0x11       // Image with palette
#define ERI_SEQENCE 0x200      // ORed in case there is a sequence
/* File header - Key frame count */
#define ERI_STILL   0x1        // Still image, no animation
#define ERI_DIFF    0x0        // Images stored as difference between frames
//#define ERI_ONEDIFF all other     // Very vague explanation, some sort of difference

/* Image information - Conversion */
#define ERI_LOSSLESS 0x03020000 // Lossless compression
#define ERI_IRREVERS 0x00000001 // Irreversible compression
/* Image information - Architecture */
/* Image information - Gamma */
#define ERI_GAMMA_ST 0xFFFFFFFF // ERI standart gamma format
#define ERI_GAMMA_CP 0x00000020 // ERI compressed gamma
#define ERI_GAMMA_OT 0xFFFFFFFC // Some other gamma format
/* Image information - Image format */
#define ERI_RGB_IMAGE  0x00000001
#define ERI_GRAY_IMAGE 0x00000002
#define ERI_RGBA_IMAGE 0x04000001
#define ERI_WITH_PALETTE 0x01000000
#define ERI_USE_CLIPPING 0x02000000
/* Image information - Sampling */
#define ERI_SAMPLE_444 0x00040404
#define ERI_SAMPLE_422 0x00040202
#define ERI_SAMPLE_411 0x00040101
/* Image information - time conversion flag*/
#define ERI_TCONV 0x00010000

extern "C" {
#pragma pack(1)
/* File header */
typedef struct {
  uint32_t version;
  uint32_t container;
  uint32_t keyFrameCnt;
  uint32_t frameNumber; // Number of images
  uint32_t allFrameTime; // Time in ms between images
} ERIfileheader;

/* Image information */
typedef struct {
  uint32_t version;
  uint32_t conversion;
  uint32_t architecture;
  uint32_t imageFormat;
  uint32_t imageWidth;
  uint32_t imageHeight;
  uint32_t imageBpp;
  uint32_t imageClip; // Number of transparent pixel in palette
  uint32_t imageSampling;
  uint64_t imageQuantBits;
  uint64_t imageQuantScale;
  uint32_t imageBlock; // Image divided into 2^imageBlock x 2^imageBlock chunks
  uint32_t imageInFrame;
  uint32_t imageTimeConvFlag;
  uint32_t imageTimeConvFact;
} ERIimageinfo;
#pragma pack()
};

class ERIFile : EntisFile
{
protected:
  int imageVersion;
  int imageType;
  int imageSeq;
  int imageGamma;
  int imageFormat;
  int imageWidth;
  int imageHeight;
  int imageBpp;
  int imageClip;
  int imageSampling;
  int imageBlock;
  void processData(const std::vector<char>& filedata) override;
  void processRecordList(emcrecord *record);
  void processFileHdr(emcrecord *record);
  void processImageInfoHdr(emcrecord *record);
  void processSequenceHdr(emcrecord *record);
  void processImageFrameHdr(emcrecord *record);

public:
  ERIFile(const std::string& filename);
  ERIFile(const std::vector<char>& filedata);
};

#endif // __ERIFILE_H__

