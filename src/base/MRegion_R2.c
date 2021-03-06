#define _H_MRegion_Private

#include <stdlib.h>
#include "MRegion.h"
#include "MRegion_jmp.h"
#include "MSTK_private.h"

#ifdef __cplusplus
extern "C" {
#endif

  void MR_Set_RepType_R2(MRegion_ptr r) {
    MRegion_Adj_R2 *adj;

    r->adj = (MRegion_Adj_R2 *) malloc(sizeof(MRegion_Adj_R2));
    adj = (MRegion_Adj_R2 *) r->adj;
    adj->rvertices = NULL;
    adj->fvtemplate = NULL;
    adj->aregions = List_New(0);
  }

  void MR_Delete_R2(MRegion_ptr r, int keep) {
    MRegion_Adj_R2 *adj;
    int idx;
    MVertex_ptr v;
    MRegion_ptr r2;

    adj = (MRegion_Adj_R2 *) r->adj;

    if (MEnt_Dim((MEntity_ptr) r) != MDELETED) {
      if (adj) {
	idx = 0;
	while ((v = List_Next_Entry(adj->rvertices,&idx)))
	  MV_Rem_Region(v,r);
      }
      
      if (adj) {
	idx = 0;
	while ((r2 = List_Next_Entry(adj->aregions,&idx)))
	  MR_Rem_AdjRegion_R2(r,r2);
      }
    }

    if (!keep) {
      if (adj) {
	if (adj->rvertices)
	  List_Delete(adj->rvertices);
	if (adj->fvtemplate) {
	  int nf = adj->fvtemplate[0][0], i;
	  for (i = 0; i < nf; i++)
	    free(adj->fvtemplate[i]);
	  free(adj->fvtemplate);
	}
	if (adj->aregions)
	  List_Delete(adj->aregions);
	free(adj);
      }
      
    }
  }

  void MR_Restore_R2(MRegion_ptr r) {
    MRegion_Adj_R2 *adj;
    int idx, i;
    MVertex_ptr v;
    MRegion_ptr r2;

    adj = (MRegion_Adj_R2 *) r->adj;
    idx = 0;
    while ((v = List_Next_Entry(adj->rvertices,&idx)))
      MV_Add_Region(v,r);

    idx = 0; i = 0;
    while ((r2 = List_Next_Entry(adj->aregions,&idx))) {
      MR_Add_AdjRegion_R2(r,i,r2);
      i++;
    }
  }


  void MR_Destroy_For_MESH_Delete_R2(MRegion_ptr r) {
    MRegion_Adj_R2 *adj;

    adj = (MRegion_Adj_R2 *) r->adj;
    if (adj) {
      if (adj->rvertices)
	List_Delete(adj->rvertices);
      if (adj->fvtemplate) {
	int nf = adj->fvtemplate[0][0], i;
	for (i = 0; i < nf; i++)
	  free(adj->fvtemplate[i]);
	free(adj->fvtemplate);
      }
      if (adj->aregions)
	List_Delete(adj->aregions);
      free(adj);
    }
    
  }


  void MR_Add_AdjRegion_R2(MRegion_ptr r, int facenum, MRegion_ptr aregion) {
    MRegion_Adj_R2 *adj;

    /* Is r->adj allocated ? */
    /* We should make use of the facenum info */
    adj = (MRegion_Adj_R2 *) r->adj;
    List_Add(adj->aregions,aregion);
  }

  void MR_Rem_AdjRegion_R2(MRegion_ptr r, MRegion_ptr aregion) {
    MRegion_Adj_R2 *adj;

    adj = (MRegion_Adj_R2 *) r->adj;
    List_Rem(adj->aregions,aregion);
  }

  void MR_Set_Faces_R2(MRegion_ptr r, int nf, MFace_ptr *mfaces, int *dirs) {
#ifdef DEBUG
    MSTK_Report("MR_Set_Faces_R2",
		"Function call not suitable for this representation",MSTK_WARN);
#endif
  }

  void MR_Rem_Face_R2(MRegion_ptr r, MFace_ptr f) {
#ifdef DEBUG
    MSTK_Report("MR_Rem_Face_R2",
		"Function call not suitable for this representation",MSTK_WARN);
#endif
  }

  void MR_Replace_Faces_R2(MRegion_ptr r, int nold, MFace_ptr *oldf, 
                           int nnu, MFace_ptr *nuf, int *dir) {
#ifdef DEBUG
    MSTK_Report("MR_Replace_Face_R2",
		"Function call not suitable for this representation",MSTK_WARN);
#endif
  }

  void MR_Replace_Face_R2(MRegion_ptr r, MFace_ptr f, MFace_ptr nuf, 
                          int dir) {
#ifdef DEBUG
    MSTK_Report("MR_Replace_Face_R2",
		"Function call not suitable for this representation",MSTK_WARN);
#endif
  }

  void MR_Replace_Face_i_R2(MRegion_ptr r, int i, MFace_ptr nuf, 
                            int dir) {
#ifdef DEBUG
    MSTK_Report("MR_Replace_Face_i_R2",
		"Function call not suitable for this representation",MSTK_WARN);
#endif
  }

  int MR_Num_AdjRegions_R2(MRegion_ptr r) {
    List_ptr adjregs = ((MRegion_Adj_R2 *) r->adj)->aregions;
    return List_Num_Entries(adjregs);
  }


  List_ptr MR_AdjRegions_R2(MRegion_ptr r) {
    MRegion_Adj_R2 *adj;

    adj = (MRegion_Adj_R2 *) r->adj;
    return List_Copy(adj->aregions);
  }


  void MR_AdjRegionIDs_R2(MRegion_ptr r, int *nradj, int *adjregids) {
    int i;
    MRegion_Adj_R2 *adj = (MRegion_Adj_R2 *) r->adj;
 
    *nradj = List_Num_Entries(adj->aregions);
    for (i = 0; i < *nradj; i++)
      adjregids[i] = MEnt_ID(List_Entry(adj->aregions,i));
  }

#ifdef __cplusplus
}
#endif
