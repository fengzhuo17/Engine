

BOOL MakeFullPath( const PCHAR aSrc, DWORD aSize, PCHAR aDes ){

    DWORD len = 0; BOOL ret = FALSE;
    
    if ( aSrc && aDes && aSize ){

        memset( aDes, 0, aSize );

        len = strlen( aSrc );
        
        if ( aSrc[len-1] == PATH_SEPERATOR_CHAR ){

            if ( aSize > len ) {

                strcpy( aDes, aSrc ); ret = TRUE;
            }

        }else{

            if ( aSize > len+1 ){

                strcpy( aDes, aSrc); strcat( aDes, PATH_SEPERATOR_STR );
                ret = TRUE;
            }
        }
    }
    return ret; 
}

#ifdef WINDOWS
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
        
            sprintf( name, "%s%s", aName, info.cFileName );
            strcat( name, PATH_SEPERATOR_STR );

            BrowseDir( name, aFun, aPara );
            continue;
        }

        sprintf( name, "%s%s", aName, info.cFileName );

        if ( aFun ){

            aFun( name, aPara );
        }

    }while ( FindNextFile( hFind, &info) );

    FindClose( hFind);
    free( name );
}

int BuildRaw( PCHAR aSourceDir, PCHAR aWorkingDir ){


}


#else

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "errno.h"
#include <fcntl.h>
#include <time.h>

void
BrowseDir( char* aPathName, FUNPROCESSFILE aFun, void* aPara ){

    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    char *p_full= NULL;
    unsigned long len = 0;
    long res = 0;
    
    if ( !aPathName ) return;

    if((dp = opendir(aPathName)) == NULL) {

        return;
    }else{
        printf( "%s\n", aPathName );
    }

    while( (entry = readdir(dp)) != NULL ) {

        if( strcmp( ".", entry->d_name) == 0 || strcmp( "..", entry->d_name) == 0 )
            continue;

        len = strlen( aPathName )+ strlen( entry->d_name ) + 4; 

        p_full =  new char[ len ];

        if (  p_full ){

            memset( p_full, 0, len );
            strcpy( p_full, aPathName );
            strcat( p_full, PATH_SEPERATOR_STR );
            strcat( p_full, entry->d_name );

            memset( &statbuf, 0, sizeof( struct stat ) );
            res = lstat( p_full, &statbuf );

            if( S_ISDIR(statbuf.st_mode) ) {

                BrowseDir( p_full, aFun, aPara );

            }else {
                len = strlen( entry->d_name );
                
                if ( 1/*entry->d_name[ len-1 ] == '^'*/ ){

                }
            }

            delete[] p_full;
        }
    }

    closedir(dp);
}

#endif
