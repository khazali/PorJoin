#include "ElementList.h"
#include "Pore.h"
#include "Throat.h"
#include <stdlib.h>

ElementList::ElementList(void) {
	ListLength=0;
	List=NULL;
}

void ElementList::AddReadyToFillElement(unsigned int ElementIndex, ElementType EType) {
	ListLength++;
	if ((List=(unsigned int*) realloc(List, ListLength*sizeof(int)))==NULL) TerM("Can not allocate memory for element list");
	switch (EType) {
		case PORE:
			List[ListLength-1]=ElementIndex;
			break;
		case THROAT:
			List[ListLength-1]=ElementIndex+PoreNO;
			break;
	}	
}

ElementList::~ElementList(void) {
	if (List!=NULL) {
		free(List);
		List=NULL;
	}
}

void ElementList::DestroyList(void) {
	if (List!=NULL) {
		free(List);
		List=NULL;
	}
	ListLength=0;
}

unsigned int ElementList::GetListContent(unsigned int ListIndex) {
	return List[ListIndex];
}

unsigned int ElementList::GetListLength(void){
	return ListLength;
}

void ElementList::AddElement(unsigned int ElementIndex) {
	ListLength++;
	if ((List=(unsigned int*) realloc(List, ListLength*sizeof(int)))==NULL) TerM("Can not allocate memory for element list");
	List[ListLength-1]=ElementIndex;
}

void ElementList::RemoveElement(unsigned int ElementIndex) {
	register unsigned int i, j;
	register bool cond = false;

	for (i = 0; i < ListLength; i++) if (List[i] == ElementIndex) {
		ListLength--;
		cond = true;
		break;
	}
	for (j = i; j < ListLength; j++) List[i] = List[i + 1];
	if (cond) if ((List = (unsigned int*) realloc(List, ListLength*sizeof(int))) == NULL) TerM("Can not allocate memory for element list");
}