/*
this funtion is dedicated to Windows, because find can be used in linux
*/
void BrowseDir( PCHAR aName, FUNPROCESSFILE aFun, void* aPara ){
    
    DWORD len = 0; CHAR* name = NULL;

    WIN32_FIND_DATAA info;
    HANDLE hFind;

    if ( aName == NULL ){ return; }

    len = strlen( aName ) + MAX_FILE_LEN + 6;

    name = (CHAR*)malloc( len );

    if ( name == NULL ){  return; }

    sprintf( name, "%s%s", aName, "*.*" );

    hFind = FindFirstFile( name, &info);

    if ( hFind == INVALID_HANDLE_VALUE ){

        free( name ); return;
    }

    do{

        if ( !strcmp( info.cFileName, ".") ){  continue; }
        if ( !strcmp( info.cFileName, "..") ){  continue; }

        if ( 
            info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
        ){
        
            sprintf( name, "%s%s\\", aName, info.cFileName );

            BrowseDir( name, aFun, aPara );
            continue;
        }

        sprintf( name, "%s%s", aName, info.cFileName );
        //printf( "%s\n", name );

        if ( aFun ){

            aFun( name, aPara );
        }

    }while ( FindNextFile( hFind, &info) );

    FindClose( hFind);
    free( name );
}

int BuildRaw( PCHAR aSourceDir, PCHAR aWorkingDir ){


}

BOOL MakeFullPath( const PCHAR aSrc, DWORD aSize, PCHAR aDes ){

    DWORD len = 0; BOOL ret = FALSE;
    
    if ( aSrc && aDes && aSize ){

        memset( aDes, 0, aSize );

        len = strlen( aSrc );
        
        if ( aSrc[len-1] == '\\' ){

            if ( aSize > len ) {

                strcpy( aDes, aSrc ); ret = TRUE;
            }

        }else{

            if ( aSize > len+1 ){

                strcpy( aDes, aSrc); strcat( aDes, "\\" );
                ret = TRUE;
            }
        }
    
    }

    return ret; 
}

