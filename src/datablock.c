
/* functions used to build a continuous datablock */

void InitMemAlloc( PMemAlloc aPtr ){

	if ( aPtr == NULL )return;

	aPtr->pMemBase = NULL;
	aPtr->BytesAlloced = 0;
	aPtr->BytesTotal = 0;

	aPtr->AllocTag = 0;
	aPtr->info.allocBytes = 0;
	aPtr->info.allocTimes = 0;

}

BOOL BuildMemAlloc( PMemAlloc aPtr ){
	
	if ( aPtr == NULL )return FALSE;

	if( ( aPtr->info.allocBytes != 0 )&& (aPtr->info.allocTimes == 0) ){
	
		aPtr->pMemBase = (CHAR*)malloc( aPtr->info.allocBytes );

		if( aPtr->pMemBase ){
		
			aPtr->BytesTotal = aPtr->info.allocBytes;
			aPtr->AllocTag = 1;

			return TRUE;
		}
	}
	return FALSE;
}

void DestroyMemAlloc( PMemAlloc aPtr ){

	if ( aPtr == NULL )return;

	if ( aPtr->pMemBase ){ free(aPtr->pMemBase); }

	aPtr->pMemBase = NULL;
	aPtr->BytesAlloced = 0;
	aPtr->BytesTotal = 0;

	aPtr->AllocTag = 0;
	aPtr->info.allocBytes = 0;
	aPtr->info.allocTimes = 0;
}

void* MallocMem( PMemAlloc aPtr, DWORD aSize ){

	void* p = NULL;

	if ( aPtr == NULL) return NULL;

	if ( aPtr->AllocTag == 0 ){
	
		p = malloc( aSize );

		if ( p ){
		
			aPtr->info.allocBytes += aSize;
			aPtr->info.allocTimes++;
		}

	}else{

		if ( aPtr->pMemBase && (aPtr->BytesAlloced < aPtr->BytesTotal) ){
		
			p = (void*)(aPtr->pMemBase + aPtr->BytesAlloced);
			aPtr->BytesAlloced += aSize;
		}
	
	}

	return p;
}

void FreeMem( PMemAlloc aPtr, void* aMem ){

	if ( aPtr == NULL ) return;

	if ( aPtr->AllocTag == 0 ){ 
		
		free(aMem); 
		aPtr->info.allocTimes--;

	}else{
				
	}
}

