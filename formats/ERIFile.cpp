#include <iostream>

#include "ERIFile.h"

ERIFile::ERIFile(const std::string& filename)
{
  init(filename);
}

ERIFile::ERIFile(const std::vector<char>& filedata)
{
  init(filedata);
}

void ERIFile::processData(const std::vector<char>& filedata)
{
  char* data = (char*)filedata.data() + sizeof(emcheader);

  /* Read info header */
  emcrecord *infoHeader = (emcrecord*)data;
  processRecordList(infoHeader);

  /* Read stream header */
  emcrecord *streamHeader = (emcrecord*)(data + infoHeader->length + sizeof(emcrecord));
  processRecordList(streamHeader);
}

void ERIFile::processRecordList(emcrecord *record)
{
  char *data = record->data;

  for (int i = 0; i < record->length; i += sizeof(emcrecord))
  {
    emcrecord *rec = (emcrecord*)(data + i);

    switch (rec->type)
    {
      case EMC_CPRT_HDR:
      case EMC_DSPT_HDR:
        /* Skip */
        break;

      case EMC_FILE_HDR:
        processFileHdr(rec);
        break;

      case EMC_IINF_HDR:
        processImageInfoHdr(rec);
        break;

      case EMC_SEQN_HDR:
        processSequenceHdr(rec);
        break;

      case EMC_IFRM_HDR:
        processImageFrameHdr(rec);
        //std::cout << "Supported record type " << std::hex << rec->type << " size " << rec->length << std::endl;
        break;
      default:
        std::cout << "UNSUPPORTED record type " << std::hex << rec->type << " size " << rec->length << std::endl;
        break;
    }

    i += rec->length;
  }
}

void ERIFile::processFileHdr(emcrecord *record)
{
  ERIfileheader *fh = (ERIfileheader*)record->data;
  if (fh->version != ERI_VERSION)
    std::cout << "UNSUPPORTED file version: " << fh->version << std::endl;

  imageSeq = fh->container & ERI_SEQENCE;
  imageType = fh->container & 0xFF;
  if (imageType != ERI_FULLCOL && imageType != ERI_PALETTE)
    std::cout << "UNSUPPORTED image format: " << imageType << std::endl;

  if (fh->keyFrameCnt != ERI_STILL && fh->frameNumber != 1)
    std::cout << "Only STILL (static) images are supported, but provided image is animated" << std::endl;
}

void ERIFile::processImageInfoHdr(emcrecord *record)
{
  ERIimageinfo *inf = (ERIimageinfo*)record->data;

  if (inf->version != ERI_VERSION && inf->version != ERI_VEREX)
    std::cout << "UNSUPPORTED image info version: " << inf->version << std::endl;

  imageVersion = inf->version;
  imageGamma = inf->architecture;
  imageFormat = inf->imageFormat;
  imageWidth = inf->imageWidth;
  imageHeight = inf->imageHeight;
  imageBpp = inf->imageBpp;
  imageClip = inf->imageClip;
  imageSampling = inf->imageSampling;
  imageBlock = inf->imageBlock;

  std::cout <<
  "imageVersion: " << std::hex << imageVersion << std::endl <<
  "imageGamma: " << std::hex << imageGamma << std::endl <<
  "imageFormat: " << std::hex << imageFormat << std::endl <<
  "imageWidth: " << std::dec << imageWidth << std::endl <<
  "imageHeight: " << std::dec << imageHeight << std::endl <<
  "imageBpp: " << std::dec << imageBpp << std::endl <<
  "imageClip: " << std::hex << imageClip << std::endl <<
  "imageSampling: " << std::hex << imageSampling << std::endl <<
  "imageBlock: " << std::hex << imageBlock << std::endl <<
  std::endl;
}

void ERIFile::processSequenceHdr(emcrecord *record)
{
  // TODO! Skip for now
}

void ERIFile::processImageFrameHdr(emcrecord *record)
{
}

