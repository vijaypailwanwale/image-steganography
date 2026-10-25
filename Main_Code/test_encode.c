#include <stdio.h>
#include "encode.h"
#include "types.h"

int main(int argc, char *argv[])
{
  EncodeInfo encInfo;  
  int operation = check_operation_type(argv);

  if(operation == e_encode)
  {
    //encoding
    int ret = read_and_validate_encode_args(argv, &encInfo); 
    if(ret == e_failure)
    {
        printf("argument validation failed\n");
        return 0;
    }
    // all set to perform encoding
    int result = do_encoding(&encInfo);
    
    if(result == e_success)
    {
        printf("encoding successful\n");
    }
    else
    {
        printf("encoding failed\n");
    }

  }
  else if(operation == e_decode)
  {
    //decoding 
    printf("decoding\n");
    return 0;
  }
  else
  {
    printf("invalid opration type\n");
    return 0;
  }











    return 0;
}
