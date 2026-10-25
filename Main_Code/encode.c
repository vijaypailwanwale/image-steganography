#include <stdio.h>
#include "encode.h"
#include "types.h"
#include "common.h"


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
    if(strstr(argv[2], ".bmp") == NULL)
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
    if(strstr(argv[4], ".bmp") == NULL)
    {
        printf("Invalid output file format\n");
        return e_failure;
    }
   }
   encInfo->stego_image_fname = "stego.bmp";

    return e_success;
    
}

Status do_encoding(EncodeInfo *encInfo)
{
 int result = open_files(encInfo);
 if(result == e_failure)
 {
  printf("files opening failed\n");
  return e_failure;
 }

  result = check_capacity(encInfo);
  if(result == e_failure)
  {
    printf("Source image Capacity is insufficient\n");
    return e_failure;
  }

}

Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "rb");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "wb");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

      // Close the already opened files
      fclose(encInfo->fptr_src_image);
      fclose(encInfo->fptr_secret);

      // Set the file pointers to NULL
      encInfo->fptr_src_image = NULL;
      encInfo->fptr_secret = NULL;

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

Status check_capacity(EncodeInfo *encInfo)
{
    uint file_size;
    uint required_bytes;

    // Get secret file extension
    strcpy(encInfo->extn_secret_file,strrchr(encInfo->secret_fname, '.'));

    // Get secret file extension size
    encInfo->size_secret_file_extn = strlen(encInfo->extn_secret_file);

    // Get secret file size
    if (fseek(encInfo->fptr_secret, 0, SEEK_END) != 0)
    {
        printf("ERROR: Unable to seek to the end of secret file.\n");
        return e_failure;
    }

    file_size = ftell(encInfo->fptr_secret);

    if (file_size < 0)
    {
        printf("ERROR: Unable to determine secret file size.\n");
        return e_failure;
    }

    encInfo->size_secret_file = file_size;

    // Reset secret file position
    if (fseek(encInfo->fptr_secret, 0, SEEK_SET) != 0)
    {
        printf("ERROR: Unable to reset secret file position.\n");
        return e_failure;
    }

    // Get image capacity
    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);

    if (encInfo->image_capacity == 0)
    {
        printf("ERROR: Unable to determine BMP image capacity.\n");
        return e_failure;
    }

    // Calculate required bytes:
    // 54-byte BMP header is copied directly.
    // Each secret bit requires one image byte.
    required_bytes =
          54
        + (strlen(MAGIC_STRING)
        + sizeof(int)
        + encInfo->size_secret_file_extn
        + sizeof(int)
        + encInfo->size_secret_file) * 8;

    // Check image capacity
    if (encInfo->image_capacity < required_bytes)
    {
        printf("ERROR: Insufficient image capacity.\n");
        printf("Required bytes: %u\n", required_bytes);
        printf("Available bytes: %u\n", encInfo->image_capacity);

        return e_failure;
    }

    return e_success;
}

uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}