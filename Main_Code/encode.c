#include <stdio.h>
#include "encode.h"
#include "types.h"


OperationType check_operation_type(char *argv[])
{
  if(strcmp(argv[1], "-e") == 0)
  {
    return e_encode;
  }
  else if(strcmp(argv[1], "-d") == 0)
  {
    return e_decode;
  }
  else
  {
    return e_unsupported;
  }
}

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    if(argv[2] == NULL || argv[3] == NULL)
    {
        return e_failure;
    }
    if(strcmp(argv[2], ".bmp") == NULL)
    {
        printf("Invalid image file format\n");
        return e_failure;
    }

   encInfo->src_image_fname = argv[2];

   if(strchr(argv[3], '.') == NULL)
   {
       printf("Invalid secret file format\n");
       return e_failure;
   }
   encInfo->secret_fname = argv[3];

   if(argv[4] == NULL)
   {
       printf("Output file name not provided\n");
       return e_failure;
   }
   else
   {
    if(strcmp(argv[4], ".bmp") == NULL)
    {
        printf("Invalid output file format\n");
        return e_failure;
    }
   }
   encInfo->stego_image_fname = "stego.bmp";

    return e_success;
}