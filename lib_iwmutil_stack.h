/////////////////////////////////////////////////////////////////////////////////////////
// #define  LIB_IWMUTIL_VERSION   "lib_iwmutil_20200508"
// #define  LIB_IWMUTIL_COPYLIGHT "Copyright (C)2008-2019 iwm-iwama"
/////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------------------
	StackŽÀ‘•
---------------------------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////
/* ŽÀ‘•
	push   F––”ö‚É—v‘f‚ð’Ç‰Á
	unshiftFæ“ª‚É—v‘f‚ð’Ç‰Á
	pop    F––”ö‚Ì—v‘f‚ðŽæ‚èo‚·(=Žæ‚èœ‚­)
	shift  Fæ“ª‚Ì—v‘f‚ðŽæ‚èo‚·(=Žæ‚èœ‚­)
*/
typedef struct{
	UINT size;// Žg—p”
	MBS **ary;// Ši”[æ
} $struct_iStackA;

$struct_iStackA    *iStack_allocA();
VOID     iStack_freeA($struct_iStackA *Stack);
BOOL     iStack_eraseA($struct_iStackA *Stack);

$struct_iStackA *iStack_cloneA($struct_iStackA *Stack);

UINT     iStack_sizeA($struct_iStackA *Stack);

VOID     iStack_IndexChkA($struct_iStackA *Stack,INT *pos);
MBS      *iStack_indexA($struct_iStackA *Stack,INT index);

BOOL     iStack_insertA($struct_iStackA *Stack,INT to,MBS *ptr);
#define  iStack_pushA(Stack,ptr)                 (BOOL)iStack_insertA(Stack,Stack->size,ptr)
#define  iStack_unshiftA(Stack,ptr)              (BOOL)iStack_insertA(Stack,0,ptr)

BOOL     iStack_replaceA($struct_iStackA *Stack,INT to,MBS *ptr);
BOOL     iStack_removeA($struct_iStackA *Stack,INT to);

MBS      *iStack_remove2A($struct_iStackA *Stack,INT to);
#define  iStack_popA(Stack)                      (MBS*)iStack_remove2A(Stack,(Stack->size)-1)
#define  iStack_shiftA(Stack)                    (MBS*)iStack_remove2A(Stack,0)

UINT     iStack_concatA($struct_iStackA *to,$struct_iStackA *from);
BOOL     iStack_rotateA($struct_iStackA *Stack,INT move);

VOID     iStack_swapIndexChkA($struct_iStackA *Stack,INT *from,INT *to);
BOOL     iStack_swapA($struct_iStackA *Stack,INT from,INT to);

UINT     iStack_pushAryA($struct_iStackA *Stack,MBS **ary);

$struct_iStackA    *iStack_fromA(MBS *ptr,MBS *token);
$struct_iStackA    *iStack_fromAryA(MBS **ary);

MBS      *iStack_popStrA($struct_iStackA *Stack,INT from,INT to);

MBS      **iStack_popAryA($struct_iStackA *Stack,INT from,INT to);
#define  iStack_toAryA(Stack)                  (MBS**)iStack_popAryA(Stack,0,(Stack->size)-1)

MBS      *iStack_toA($struct_iStackA *Stack,MBS *token);

#define  iStack_sortAscA(Stack)                  (VOID)iary_sortAsc(Stack->ary)
#define  iStack_sortDescA(Stack)                 (VOID)iary_sortDesc(Stack->ary)

VOID     iStack_printA($struct_iStackA *Stack);

// (’) 0=NULL ‚Æ‚È‚é‚Ì‚ÅŽÀ‘•ã’ˆÓ
typedef struct{
	UINT size;  // Žg—p”
	DOUBLE *ary;// Ši”[æ
} $struct_iStackDBL;

$struct_iStackDBL  *iStack_allocDBL();
VOID     iStack_freeDBL($struct_iStackDBL *Stack);
BOOL     iStack_eraseDBL($struct_iStackDBL *Stack);

$struct_iStackDBL  *iStack_cloneDBL($struct_iStackDBL *Stack);

UINT     iStack_sizeDBL($struct_iStackDBL *Stack);

VOID     iStack_indexChkDBL($struct_iStackDBL *Stack,INT *pos);
DOUBLE   iStack_indexDBL($struct_iStackDBL *Stack,INT index);

BOOL     iStack_insertDBL($struct_iStackDBL *Stack,INT to,DOUBLE num);
#define  iStack_pushDBL(Stack,num)           (BOOL)iStack_insertDBL(Stack,Stack->size,num)
#define  iStack_unshiftDBL(Stack,num)        (BOOL)iStack_insertDBL(Stack,0,num)

BOOL     iStack_replaceDBL($struct_iStackDBL *Stack,INT to,DOUBLE num);
BOOL     iStack_removeDBL($struct_iStackDBL *Stack,INT to);

DOUBLE   iStack_remove2DBL($struct_iStackDBL *Stack,INT to);
#define  iStack_popDBL(Stack)                (DOUBLE)iStack_remove2DBL(Stack,(Stack->size)-1)
#define  iStack_shiftDBL(Stack)              (DOUBLE)iStack_remove2DBL(Stack,0)

UINT     iStack_concatDBL($struct_iStackDBL *to,$struct_iStackDBL *from);
BOOL     iStack_rotateDBL($struct_iStackDBL *Stack,INT move);

VOID     iStack_swapIndex_chkDBL($struct_iStackDBL *Stack,INT *from,INT *to);
BOOL     iStack_swapDBL($struct_iStackDBL *Stack,INT from,INT to);

VOID     iStack_printDBL($struct_iStackDBL *Stack);

BOOL     iStack_switchCaseDBL($struct_iStackDBL *Stack,MBS **aSWitch,MBS **aCase1,MBS **aCase2,UINT aCaseRangeBgn,UINT aCaseRangeEnd);

$struct_iStackDBL  *iStack_AtoDBL(MBS *ptr,DOUBLE dDiff);

$struct_iStackA    *iStack_drivelistA();
