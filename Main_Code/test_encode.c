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
    ret = do_encoding(&encInfo);

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
