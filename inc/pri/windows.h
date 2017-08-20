#ifndef WINDOWS
#define WINDOWS

#include "engtypes.h"

typedef struct _IMAE_DOS_HEADER {       //DOS .EXE header                                    position 
    WORD e_magic;                       //Magic number;                                      0x00
    WORD e_cblp;                        //Bytes on last page of file                         0x02
    WORD e_cp;                          //Pages in file                                      0x04
    WORD e_crlc;                        //Relocations                                        0x06
    WORD e_cparhdr;                     //Size of header in paragraphs                       0x08
    WORD e_minalloc;                    //Minimum extra paragraphs needed                    0x0A
    WORD e_maxalloc;                    //Maximum extra paragraphs needed                    0x0C
    WORD e_ss;                          //Initial (relative) SS value                        0x0E
    WORD e_sp;                          //Initial SP value                                   0x10
    WORD e_csum;                        //Checksum                                           0x12
    WORD e_ip;                          //Initial IP value                                   0x14
    WORD e_cs;                          //Initial (relative) CS value                        0x16
    WORD e_lfarlc;                      //File address of relocation table                   0x18
    WORD e_ovno;                        //Overlay number                                     0x1A
    WORD e_res[4];                      //Reserved words                                     0x1C
    WORD e_oemid;                       //OEM identifier (for e_oeminfo)                     0x24
    WORD e_oeminfo;                     //OEM information; e_oemid specific                  0x26 
    WORD e_res2[10];                    //Reserved words                                     0x28
    LONG e_lfanew;                      //File address of new exe header                     0x3C
} IMAGE_DOS-HEADER, *PIMAGE_DOS_HEADER;

typedef struct _IMAGE_FILE_HEADER {
  WORD  Machine;
  WORD  NumberOfSections;
  DWORD TimeDateStamp;
  DWORD PointerToSymbolTable;
  DWORD NumberOfSymbols;
  WORD  SizeOfOptionalHeader;
  WORD  Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

typedef struct _IMAGE_SECTION_HEADER {
  BYTE  Name[IMAGE_SIZEOF_SHORT_NAME];
  union {
    DWORD PhysicalAddress;
    DWORD VirtualSize;
  } Misc;
  DWORD VirtualAddress;
  DWORD SizeOfRawData;
  DWORD PointerToRawData;
  DWORD PointerToRelocations;
  DWORD PointerToLinenumbers;
  WORD  NumberOfRelocations;
  WORD  NumberOfLinenumbers;
  DWORD Characteristics;
} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

typedef struct _IMAGE_DATA_DIRECTORY {
  DWORD VirtualAddress;
  DWORD Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

typedef struct _IMAGE_OPTIONAL_HEADER {
  WORD                 Magic;
  BYTE                 MajorLinkerVersion;
  BYTE                 MinorLinkerVersion;
  DWORD                SizeOfCode;
  DWORD                SizeOfInitializedData;
  DWORD                SizeOfUninitializedData;
  DWORD                AddressOfEntryPoint;
  DWORD                BaseOfCode;
  DWORD                BaseOfData;
  DWORD                ImageBase;
  DWORD                SectionAlignment;
  DWORD                FileAlignment;
  WORD                 MajorOperatingSystemVersion;
  WORD                 MinorOperatingSystemVersion;
  WORD                 MajorImageVersion;
  WORD                 MinorImageVersion;
  WORD                 MajorSubsystemVersion;
  WORD                 MinorSubsystemVersion;
  DWORD                Win32VersionValue;
  DWORD                SizeOfImage;
  DWORD                SizeOfHeaders;
  DWORD                CheckSum;
  WORD                 Subsystem;
  WORD                 DllCharacteristics;
  DWORD                SizeOfStackReserve;
  DWORD                SizeOfStackCommit;
  DWORD                SizeOfHeapReserve;
  DWORD                SizeOfHeapCommit;
  DWORD                LoaderFlags;
  DWORD                NumberOfRvaAndSizes;
  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER, *PIMAGE_OPTIONAL_HEADER;

typedef truct _IMAGE_NT_HEADERS {
  DWORD                 Signature;
  IMAGE_FILE_HEADER     FileHeader;
  IMAGE_OPTIONAL_HEADER OptionalHeader;
} IMAGE_NT_HEADERS, *PIMAGE_NT_HEADERS;

#endif
