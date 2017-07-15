/*
function used to check whether a pe is valid. if valid get its infomation
*/

BOOL VerifyPE( HANDLE hFile , PeInfoFromFile* pInfo ){

    IMAGE_DOS_HEADER mz;
    IMAGE_NT_HEADERS nthd;

    DWORD num = 0;
    DWORD offset = 0;
    BOOL result = FALSE;

    DWORD i = 0;
    DWORD size = 0;

    DWORD lMinimal = 0xffffffff;

    PIMAGE_SECTION_HEADER pSectionInfo = NULL;
    PIMAGE_SECTION_HEADER pSection = NULL;

    memset( pInfo, 0, sizeof(PeInfoFromFile) );

    SetFilePointer( hFile, 0, NULL, FILE_BEGIN );
    result = ReadFile( hFile, &mz, sizeof( IMAGE_DOS_HEADER), &num, NULL);

    if ( (!result) || (num != sizeof(IMAGE_DOS_HEADER)) ){
    
        return FALSE;
    }

    if( mz.e_magic != 0x5a4d ){

        return FALSE;
    }

    offset = mz.e_lfanew;
    memset( &nthd, 0, sizeof(IMAGE_NT_HEADERS) );

    SetFilePointer( hFile, offset, NULL, FILE_BEGIN );
    result = ReadFile( hFile, &nthd, sizeof(IMAGE_NT_HEADERS), &num, NULL);

    if ( (!result) || (num != sizeof(IMAGE_NT_HEADERS)) ){
    
        return FALSE;
    }

    if( nthd.Signature != 0x4550l ){

        return FALSE;
    }

    offset = nthd.OptionalHeader.SizeOfHeaders;


    pInfo->Machine = nthd.FileHeader.Machine;
    pInfo->SectionNum = nthd.FileHeader.NumberOfSections;

    pInfo->SizeOfCode  = nthd.OptionalHeader.SizeOfCode;    
    pInfo->EntryOffset = nthd.OptionalHeader.AddressOfEntryPoint;

    pInfo->SizeOfImage  = nthd.OptionalHeader.SizeOfImage;
    pInfo->SizeOfHeaders = nthd.OptionalHeader.SizeOfHeaders;

    size = sizeof(IMAGE_SECTION_HEADER)* pInfo->SectionNum;

    pSection = ( pSectionInfo = (PIMAGE_SECTION_HEADER)malloc( size ) );

    offset = mz.e_lfanew + 0x18l + nthd.FileHeader.SizeOfOptionalHeader;

    SetFilePointer( hFile, offset, NULL, FILE_BEGIN );

    result = ReadFile( hFile, pSectionInfo, size, &num, NULL);

    if( (result == FALSE)||(size != num) ){

        free( pSection );
        return FALSE;
    }

    for( i = 0 ; i < pInfo->SectionNum ; i++, pSectionInfo++ ){

        if ( lMinimal > pSectionInfo->VirtualAddress ){
        
            lMinimal = pSectionInfo->VirtualAddress;
        }

        if ( 
            ( pInfo->EntryOffset >= pSectionInfo->VirtualAddress )
            &&
            ( pInfo->EntryOffset < (pSectionInfo->VirtualAddress+ pSectionInfo->SizeOfRawData) )    
        ){

            pInfo->EntryFound = ( i+1 ) ;
            
            pInfo->VirtualAddress = pSectionInfo->VirtualAddress;

            if ( pSectionInfo->SizeOfRawData && pSectionInfo->PointerToRawData ){

                pInfo->RawDataSize = pSectionInfo->SizeOfRawData;
                pInfo->RawDataOffset = pSectionInfo->PointerToRawData;
            }
            break;  
        }

        if ( pSectionInfo->SizeOfRawData ){
        
            if ( (i ==1)&&(pInfo->EntryOffset < 0x200l) ){

                pInfo->RawDataSize = pSectionInfo->SizeOfRawData;
                pInfo->RawDataOffset = pSectionInfo->PointerToRawData;
                break;
            }
        }
        
        if ( pSectionInfo->SizeOfRawData ){

            if ( (i == 0)&&( pInfo->EntryOffset < pSectionInfo->VirtualAddress) ){
            
                if ( pInfo->EntryOffset >= 0x200l ){

                    pInfo->RawDataSize = pSectionInfo->SizeOfRawData;
                    pInfo->RawDataOffset = pSectionInfo->PointerToRawData;
                    break;  
                }
            }       
        }

    }

    free( pSection );
    pSection = NULL;

    if ( pInfo->EntryOffset < lMinimal ){

    //  printf( "\nthere is a hole\n" );        
    }

    if ( pInfo->EntryFound == pInfo->SectionNum ){
    
    //  if ( pInfo->VirtualAddress != lMinimal ) printf( " may be a suspect\n\n");
    }

    if ( pInfo->RawDataSize == 0 ) return FALSE;

    
    return TRUE;
}

