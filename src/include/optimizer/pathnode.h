/*-------------------------------------------------------------------------
 *
 * pathnode.h
 *	  prototypes for pathnode.c, relnode.c.
 *
 *
 * Portions Copyright (c) 2023, HashData Technology Limited.
 * Portions Copyright (c) 2005-2008, Greenplum inc
 * Portions Copyright (c) 2012-Present VMware, Inc. or its affiliates.
 * Portions Copyright (c) 1996-2021, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/optimizer/pathnode.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef PATHNODE_H
#define PATHNODE_H

#include "cdb/cdbdef.h"                 /* CdbVisitOpt */
#include "nodes/bitmapset.h"
#include "nodes/pathnodes.h"


/*
 * prototypes for pathnode.c
 */

extern int	compare_path_costs(Path *path1, Path *path2,
							   CostSelector criterion);
extern int	compare_fractional_path_costs(Path *path1, Path *path2,
										  double fraction);
extern void set_cheapest(RelOptInfo *parent_rel);
extern void add_path(RelOptInfo *parent_rel, Path *new_path, PlannerInfo *root);
extern Path *create_seqscan_path(PlannerInfo *root, RelOptInfo *rel,
					Relids required_outer, int parallel_workers);
extern AppendOnlyPath *create_appendonly_path(PlannerInfo *root, RelOptInfo *rel,
					Relids required_outer);
extern AOCSPath *create_aocs_path(PlannerInfo *root, RelOptInfo *rel,
					Relids required_outer);
extern bool add_path_precheck(RelOptInfo *parent_rel,
							  Cost startup_cost, Cost total_cost,
							  List *pathkeys, Relids required_outer);
extern void add_partial_path(RelOptInfo *parent_rel, Path *new_path);
extern bool add_partial_path_precheck(RelOptInfo *parent_rel,
									  Cost total_cost, List *pathkeys);

extern Path *create_samplescan_path(PlannerInfo *root, RelOptInfo *rel,
									Relids required_outer);
extern IndexPath *create_index_path(PlannerInfo *root,
									IndexOptInfo *index,
									List *indexclauses,
									List *indexorderbys,
									List *indexorderbycols,
									List *pathkeys,
									ScanDirection indexscandir,
									bool indexonly,
									Relids required_outer,
									double loop_count,
									bool partial_path);
extern BitmapHeapPath *create_bitmap_heap_path(PlannerInfo *root,
											   RelOptInfo *rel,
											   Path *bitmapqual,
											   Relids required_outer,
											   double loop_count,
											   int parallel_degree);
extern BitmapAndPath *create_bitmap_and_path(PlannerInfo *root,
											 RelOptInfo *rel,
											 List *bitmapquals);
extern BitmapOrPath *create_bitmap_or_path(PlannerInfo *root,
										   RelOptInfo *rel,
										   List *bitmapquals);
extern TidPath *create_tidscan_path(PlannerInfo *root, RelOptInfo *rel,
                                    List *tidquals, Relids required_outer);

extern TidRangePath *create_tidrangescan_path(PlannerInfo *root,
											  RelOptInfo *rel,
											  List *tidrangequals,
											  Relids required_outer);
extern AppendPath *create_append_path(PlannerInfo *root, RelOptInfo *rel,
									  List *subpaths, List *partial_subpaths,
									  List *pathkeys, Relids required_outer,
									  int parallel_workers, bool parallel_aware,
									  double rows);

extern MergeAppendPath *create_merge_append_path(PlannerInfo *root,
												 RelOptInfo *rel,
												 List *subpaths,
												 List *pathkeys,
												 Relids required_outer);
extern GroupResultPath *create_group_result_path(PlannerInfo *root,
												 RelOptInfo *rel,
												 PathTarget *target,
												 List *havingqual);

extern MaterialPath *create_material_path(RelOptInfo *rel, Path *subpath);
extern MemoizePath *create_memoize_path(PlannerInfo *root,
										RelOptInfo *rel,
										Path *subpath,
										List *param_exprs,
										List *hash_operators,
										bool singlerow,
										bool binary_mode,
										double calls);

extern UniquePath *create_unique_path(PlannerInfo *root, RelOptInfo *rel,
									  Path *subpath, SpecialJoinInfo *sjinfo);
extern UniquePath *create_unique_rowid_path(PlannerInfo *root,
											RelOptInfo *rel,
											Path *subpath,
											Relids required_outer,
											int rowidexpr_id);
extern GatherPath *create_gather_path(PlannerInfo *root,
									  RelOptInfo *rel, Path *subpath, PathTarget *target,
									  Relids required_outer, double *rows);
extern GatherMergePath *create_gather_merge_path(PlannerInfo *root,
												 RelOptInfo *rel,
												 Path *subpath,
												 PathTarget *target,
												 List *pathkeys,
												 Relids required_outer,
												 double *rows);
extern SubqueryScanPath *create_subqueryscan_path(PlannerInfo *root,
												  RelOptInfo *rel, Path *subpath,
												  List *pathkeys, CdbPathLocus locus,
												  Relids required_outer);
extern Path *create_functionscan_path(PlannerInfo *root, RelOptInfo *rel,
									  RangeTblEntry *rte,
									  List *pathkeys, Relids required_outer);
extern TableFunctionScanPath *create_tablefunction_path(PlannerInfo *root,
						  RelOptInfo *rel, Path *subpath,
						  List *pathkeys, Relids required_outer);
extern Path *create_valuesscan_path(PlannerInfo *root, RelOptInfo *rel,
									RangeTblEntry *rte,
									Relids required_outer);
extern Path *create_tablefuncscan_path(PlannerInfo *root, RelOptInfo *rel,
									   Relids required_outer);
extern Path *create_ctescan_path(PlannerInfo *root, RelOptInfo *rel,
								 Path *subpath, CdbPathLocus locus,
								 List *pathkeys,
								 Relids required_outer);
extern Path *create_namedtuplestorescan_path(PlannerInfo *root, RelOptInfo *rel,
											 Relids required_outer);
extern Path *create_resultscan_path(PlannerInfo *root, RelOptInfo *rel,
									Relids required_outer);
extern Path *create_worktablescan_path(PlannerInfo *root, RelOptInfo *rel,
									   CdbPathLocus ctelocus,
									   Relids required_outer);
extern ForeignPath *create_foreignscan_path(PlannerInfo *root, RelOptInfo *rel,
											PathTarget *target,
											double rows, Cost startup_cost, Cost total_cost,
											List *pathkeys,
											Relids required_outer,
											Path *fdw_outerpath,
											List *fdw_private);
extern ForeignPath *create_foreign_join_path(PlannerInfo *root, RelOptInfo *rel,
											 PathTarget *target,
											 double rows, Cost startup_cost, Cost total_cost,
											 List *pathkeys,
											 Relids required_outer,
											 Path *fdw_outerpath,
											 List *fdw_private);
extern ForeignPath *create_foreign_upper_path(PlannerInfo *root, RelOptInfo *rel,
											  PathTarget *target,
											  double rows, Cost startup_cost, Cost total_cost,
											  List *pathkeys,
											  Path *fdw_outerpath,
											  List *fdw_private);

extern Relids calc_nestloop_required_outer(Relids outerrelids,
										   Relids outer_paramrels,
										   Relids innerrelids,
										   Relids inner_paramrels);
extern Relids calc_non_nestloop_required_outer(Path *outer_path, Path *inner_path);

extern bool path_contains_inner_index(Path *path);

extern Path *create_nestloop_path(PlannerInfo *root,
									  RelOptInfo *joinrel,
									  JoinType jointype,
									  JoinType orig_jointype,		/* CDB */
									  JoinCostWorkspace *workspace,
									  JoinPathExtraData *extra,
									  Path *outer_path,
									  Path *inner_path,
									  List *restrict_clauses,
									  List *redistribution_clauses,    /*CDB*/
									  List *pathkeys,
									  Relids required_outer);

extern Path *create_mergejoin_path(PlannerInfo *root,
										RelOptInfo *joinrel,
										JoinType jointype,
										JoinType orig_jointype,		/* CDB */
										JoinCostWorkspace *workspace,
										JoinPathExtraData *extra,
										Path *outer_path,
										Path *inner_path,
										List *restrict_clauses,
										List *pathkeys,
										Relids required_outer,
										List *mergeclauses,
										List *redistribution_clauses,    /*CDB*/
										List *outersortkeys,
										List *innersortkeys);

extern Path *create_hashjoin_path(PlannerInfo *root,
									  RelOptInfo *joinrel,
									  JoinType jointype,
									  JoinType orig_jointype,		/* CDB */
									  JoinCostWorkspace *workspace,
									  JoinPathExtraData *extra,
									  Path *outer_path,
									  Path *inner_path,
									  bool parallel_hash,
									  List *restrict_clauses,
									  Relids required_outer,
									  List *redistribution_clauses,    /*CDB*/
									  List *hashclauses,
									  bool uninterested_broadcast); /* GPDB parallel */

extern ProjectionPath *create_projection_path(PlannerInfo *root,
											  RelOptInfo *rel,
											  Path *subpath,
											  PathTarget *target);
extern ProjectionPath *create_projection_path_with_quals(PlannerInfo *root,
														 RelOptInfo *rel,
														 Path *subpath,
														 PathTarget *target,
														 List *restrict_clauses,
														 bool need_param);
extern Path *apply_projection_to_path(PlannerInfo *root,
									  RelOptInfo *rel,
									  Path *path,
									  PathTarget *target);
extern ProjectSetPath *create_set_projection_path(PlannerInfo *root,
												  RelOptInfo *rel,
												  Path *subpath,
												  PathTarget *target);
extern SortPath *create_sort_path(PlannerInfo *root,
								  RelOptInfo *rel,
								  Path *subpath,
								  List *pathkeys,
								  double limit_tuples);
extern IncrementalSortPath *create_incremental_sort_path(PlannerInfo *root,
														 RelOptInfo *rel,
														 Path *subpath,
														 List *pathkeys,
														 int presorted_keys,
														 double limit_tuples);
extern GroupPath *create_group_path(PlannerInfo *root,
									RelOptInfo *rel,
									Path *subpath,
									List *groupClause,
									List *qual,
									double numGroups);
extern UpperUniquePath *create_upper_unique_path(PlannerInfo *root,
                                                 RelOptInfo *rel,
                                                 Path *subpath,
                                                 int numCols,
                                                 double numGroups);
struct HashAggTableSizes; /* defined in execHHashagg.h */
extern AggPath *create_agg_path(PlannerInfo *root,
				RelOptInfo *rel,
				Path *subpath,
				PathTarget *target,
				AggStrategy aggstrategy,
				AggSplit aggsplit,
				bool streaming,
				List *groupClause,
				List *qual,
				const AggClauseCosts *aggcosts,
				double numGroups);
extern TupleSplitPath *create_tup_split_path(PlannerInfo *root,
                                             RelOptInfo *rel,
                                             Path *subpath,
                                             PathTarget *target,
                                             List *groupClause,
											 List *dqa_expr_lst);
extern AggPath *create_agg_sorted_path(PlannerInfo *root,
									   RelOptInfo *rel,
									   Path *subpath,
									   RelAggInfo *agg_info);
extern AggPath *create_agg_hashed_path(PlannerInfo *root,
									   RelOptInfo *rel,
									   Path *subpath,
									   RelAggInfo *agg_info);
extern GroupingSetsPath *create_groupingsets_path(PlannerInfo *root,
												  RelOptInfo *rel,
												  Path *subpath,
												  AggSplit aggsplit,
												  List *having_qual,
												  AggStrategy aggstrategy,
												  List *rollups,
												  const AggClauseCosts *agg_costs);
extern MinMaxAggPath *create_minmaxagg_path(PlannerInfo *root,
											RelOptInfo *rel,
											PathTarget *target,
											List *mmaggregates,
											List *quals);
extern WindowAggPath *create_windowagg_path(PlannerInfo *root,
											RelOptInfo *rel,
											Path *subpath,
											PathTarget *target,
											List *windowFuncs,
											WindowClause *winclause);
extern SetOpPath *create_setop_path(PlannerInfo *root,
									RelOptInfo *rel,
									Path *subpath,
									SetOpCmd cmd,
									SetOpStrategy strategy,
									List *distinctList,
									AttrNumber flagColIdx,
									int firstFlag,
									double numGroups,
									double outputRows);
extern RecursiveUnionPath *create_recursiveunion_path(PlannerInfo *root,
													  RelOptInfo *rel,
													  Path *leftpath,
													  Path *rightpath,
													  PathTarget *target,
													  List *distinctList,
													  int wtParam,
													  double numGroups);
extern LockRowsPath *create_lockrows_path(PlannerInfo *root, RelOptInfo *rel,
										  Path *subpath, List *rowMarks, int epqParam);
extern ModifyTablePath *create_modifytable_path(PlannerInfo *root,
												RelOptInfo *rel,
												Path *subpath,
												CmdType operation, bool canSetTag,
												Index nominalRelation, Index rootRelation,
												bool partColsUpdated,
												bool splitUpdate,
												List *resultRelations,
												List *updateColnosLists,
												List *withCheckOptionLists, List *returningLists,
												List *rowMarks, OnConflictExpr *onconflict,
												int epqParam);
extern Path *create_limit_path(PlannerInfo *root, RelOptInfo *rel,
									Path *subpath,
									Node *limitOffset, Node *limitCount,
									LimitOption limitOption,
									int64 offset_est, int64 count_est);
extern void adjust_limit_rows_costs(double *rows,
									Cost *startup_cost, Cost *total_cost,
									int64 offset_est, int64 count_est);

extern Path *reparameterize_path(PlannerInfo *root, Path *path,
								 Relids required_outer,
								 double loop_count);
extern Path *reparameterize_path_by_child(PlannerInfo *root, Path *path,
										  RelOptInfo *child_rel);

/*
 * prototypes for relnode.c
 */
extern void setup_simple_rel_arrays(PlannerInfo *root);
extern void expand_planner_arrays(PlannerInfo *root, int add_size);
extern RelOptInfo *build_simple_rel(PlannerInfo *root, int relid,
									RelOptInfo *parent);
extern RelOptInfo *find_base_rel(PlannerInfo *root, int relid);
extern RelOptInfo *find_join_rel(PlannerInfo *root, Relids relids);
extern RelOptInfo *build_join_rel(PlannerInfo *root,
								  Relids joinrelids,
								  RelOptInfo *outer_rel,
								  RelOptInfo *inner_rel,
								  SpecialJoinInfo *sjinfo,
								  List **restrictlist_ptr,
								  RelAggInfo *agg_info);
extern RelOptInfo *build_base_grouped_rel(PlannerInfo *root, RelOptInfo *rel,
											RelAggInfo **agg_info_p);
extern void add_grouped_rel_agg_info(PlannerInfo *root, RelOptInfo *rel,
									 RelAggInfo *agginfo);
extern RelAggInfo *find_grouped_rel_agg_info(PlannerInfo *root, Relids relids);
extern RelAggInfo *get_grouped_rel_agg_info(PlannerInfo *root,
											RelOptInfo *joinrel_plain);
extern RelOptInfo *find_grouped_rel(PlannerInfo *root, Relids relids);
extern RelOptInfo *get_grouped_rel(PlannerInfo *root, RelOptInfo *rel);
extern Relids min_join_parameterization(PlannerInfo *root,
										Relids joinrelids,
										RelOptInfo *outer_rel,
										RelOptInfo *inner_rel);

extern RelOptInfo *fetch_upper_rel(PlannerInfo *root, UpperRelationKind kind,
								   Relids relids);
extern Relids find_childrel_parents(PlannerInfo *root, RelOptInfo *rel);
extern ParamPathInfo *get_baserel_parampathinfo(PlannerInfo *root,
												RelOptInfo *baserel,
												Relids required_outer);
extern ParamPathInfo *get_joinrel_parampathinfo(PlannerInfo *root,
												RelOptInfo *joinrel,
												Path *outer_path,
												Path *inner_path,
												SpecialJoinInfo *sjinfo,
												Relids required_outer,
												List **restrict_clauses);
extern ParamPathInfo *get_appendrel_parampathinfo(RelOptInfo *appendrel,
												  Relids required_outer);
extern ParamPathInfo *find_param_path_info(RelOptInfo *rel,
										   Relids required_outer);
extern RelOptInfo *build_child_join_rel(PlannerInfo *root,
										RelOptInfo *outer_rel, RelOptInfo *inner_rel,
										RelOptInfo *parent_joinrel, List *restrictlist,
										SpecialJoinInfo *sjinfo, JoinType jointype);

extern RelAggInfo *create_rel_agg_info(PlannerInfo *root, RelOptInfo *rel);

#endif							/* PATHNODE_H */
