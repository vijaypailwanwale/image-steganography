# image-steganography

1 - check what opration type from input arg
    1.1 -    check argv[1] is it -e (use strcmp) then its encode
    1.1.2 -  check argv[1] is it -d (use strcmp) then its decode
    1.1.3 -  check argv[1] is it NULL or anyother(use strcmp) then its unsupported  argument stop program 


2 - if its opration is encode
    2.1   - check now other passed agrguments are correct verify it and store in our structure of file 

    2.1.1 - check .bmp file (use strcmp) if present get its name  not present stop main program
    2.1.2 - check  secret file is give (we dont know extenstion what user gona provide so just check .is present use strchr) 
    2.1.3 - check  output file name is given (we dont know file what user gona provide so just check .is present use strchr) 

3 - if its opration is decode 