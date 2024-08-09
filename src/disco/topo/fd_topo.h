#ifndef HEADER_fd_src_disco_topo_fd_topo_h
#define HEADER_fd_src_disco_topo_fd_topo_h

#include "../mux/fd_mux.h"
#include "../quic/fd_tpu.h"
#include "../../tango/fd_tango.h"

/* Maximum number of workspaces that may be present in a topology. */
#define FD_TOPO_MAX_WKSPS         (256UL)
/* Maximum number of links that may be present in a topology. */
#define FD_TOPO_MAX_LINKS         (256UL)
/* Maximum number of tiles that may be present in a topology. */
#define FD_TOPO_MAX_TILES         (256UL)
/* Maximum number of objects that may be present in a topology. */
#define FD_TOPO_MAX_OBJS          (4096UL)
/* Maximum number of links that may go into any one tile in the
   topology. */
#define FD_TOPO_MAX_TILE_IN_LINKS  ( 128UL)
/* Maximum number of links that a tile may write to in addition
   to the primary output link. */
#define FD_TOPO_MAX_TILE_OUT_LINKS ( 32UL)
/* Maximum number of objects that a tile can use. */
#define FD_TOPO_MAX_TILE_OBJS      ( 256UL)

/* A workspace is a Firedance specific memory management structure that
   sits on top of 1 or more memory mapped gigantic or huge pages mounted
   to the hugetlbfs. */
typedef struct {
  ulong id;           /* The ID of this workspace.  Indexed from [0, wksp_cnt).  When placed in a topology, the ID must be the index of the workspace in the workspaces list. */
  char  name[ 13UL ]; /* The name of this workspace, like "pack".  There can be at most one of each workspace name in a topology. */

  ulong numa_idx;     /* The index of the NUMA node on the system that this workspace should be allocated from. */

  /* Computed fields.  These are not supplied as configuration but calculated as needed. */
  struct {
    ulong page_sz;  /* The size of the pages that this workspace is backed by.  One of FD_PAGE_SIZE_*. */
    ulong page_cnt; /* The number of pages that must be mapped to this workspace to store all the data needed by consumers. */
    ulong part_max; /* The maximum number of partitions in the underlying workspace.  There can only be this many allocations made at any one time. */

    fd_wksp_t * wksp;            /* The workspace memory in the local process. */
    ulong       known_footprint; /* Total size in bytes of all data in Firedancer that will be stored in this workspace at startup. */
    ulong       total_footprint; /* Total size in bytes of all data in Firedancer that could be stored in this workspace, includes known data and loose data. */
  };
} fd_topo_wksp_t;

/* A link is an mcache in a workspace that has one producer and one or
   more consumers. A link may optionally also have a dcache, that holds
   fragments referred to by the mcache entries.

   A link belongs to exactly one workspace.  A link has exactly one
   producer, and 1 or more consumers.  Each consumer is either reliable
   or not reliable.  A link has a depth and a MTU, which correspond to
   the depth and MTU of the mcache and dcache respectively.  A MTU of
   zero means no dcache is needed, as there is no data. */
typedef struct {
  ulong id;           /* The ID of this link.  Indexed from [0, link_cnt).  When placed in a topology, the ID must be the index of the link in the links list. */
  char  name[ 13UL ]; /* The name of this link, like "pack_bank". There can be multiple of each link name in a topology. */
  ulong kind_id;      /* The ID of this link within its name.  If there are N links of a particular name, they have IDs [0, N).  The pair (name, kind_id) uniquely identifies a link, as does "id" on its own. */

  int   is_reasm; /* If the link is a reassembly buffer. */
  ulong depth;    /* The depth of the mcache representing the link. */
  ulong mtu;      /* The MTU of data fragments in the mcache.  A value of 0 means there is no dcache. */
  ulong burst;    /* The max amount of MTU sized data fragments that might be bursted to the dcache. */

  ulong mcache_obj_id;
  ulong dcache_obj_id;
  ulong reasm_obj_id;

  /* Computed fields.  These are not supplied as configuration but calculated as needed. */
  struct {
    fd_frag_meta_t * mcache; /* The mcache of this link. */
    void *           dcache; /* The dcache of this link, if it has one. */
    fd_tpu_reasm_t * reasm;  /* The reassembly buffer of this link, if it has one. */
  };
} fd_topo_link_t;

/* A tile is a unique process that is spawned by Firedancer to represent
   one thread of execution.  Firedancer sandboxes all tiles to their own
   process for security reasons.

   A tile belongs to exactly one workspace.  A tile is a consumer of 0
   or more links, it's inputs.  A tile is a producer of 0 or more output
   links.  Either zero or one of the output links is considered the
   primary output, which will be managed automatically by the tile
   infrastructure.

   All input links will be automatically polled by the tile
   infrastructure, but only the primary output will be written to. */
typedef struct {
  ulong id;                     /* The ID of this tile.  Indexed from [0, tile_cnt).  When placed in a topology, the ID must be the index of the tile in the tiles list. */
  char  name[ 7UL ];            /* The name of this tile.  There can be multiple of each tile name in a topology. */
  ulong kind_id;                /* The ID of this tile within its name.  If there are n tile of a particular name, they have IDs [0, N).  The pair (name, kind_id) uniquely identifies a tile, as does "id" on its own. */
  int   is_agave;               /* If the tile needs to run in the Agave (Anza) address space or not. */

  ulong cpu_idx;                /* The CPU index to pin the tile on.  A value of ULONG_MAX or more indicates the tile should be floating and not pinned to a core. */

  ulong in_cnt;                 /* The number of links that this tile reads from. */
  ulong in_link_id[ FD_TOPO_MAX_TILE_IN_LINKS ];       /* The link_id of each link that this tile reads from, indexed in [0, in_cnt). */
  int   in_link_reliable[ FD_TOPO_MAX_TILE_IN_LINKS ]; /* If each link that this tile reads from is a reliable or unreliable consumer, indexed in [0, in_cnt). */
  int   in_link_poll[ FD_TOPO_MAX_TILE_IN_LINKS ];     /* If each link that this tile reads from should be polled by the tile infrastructure, indexed in [0, in_cnt).
                                   If the link is not polled, the tile will not receive frags for it and the tile writer is responsible for
                                   reading from the link.  The link must be marked as unreliable as it is not flow controlled. */

  ulong out_link_id_primary;    /* The link_id of the primary link that this tile writes to.  A value of ULONG_MAX means there is no primary output link. */

  ulong out_cnt;                /* The number of non-primary links that this tile writes to. */
  ulong out_link_id[ FD_TOPO_MAX_TILE_OUT_LINKS ]; /* The link_id of each non-primary link that this tile writes to, indexed in [0, link_cnt). */

  ulong tile_obj_id;
  ulong cnc_obj_id;
  ulong metrics_obj_id;
  ulong in_link_fseq_obj_id[ FD_TOPO_MAX_TILE_IN_LINKS ];

  ulong uses_obj_cnt;
  ulong uses_obj_id[ FD_TOPO_MAX_TILE_OBJS ];
  int   uses_obj_mode[ FD_TOPO_MAX_TILE_OBJS ];

  /* Computed fields.  These are not supplied as configuration but calculated as needed. */
  struct {
    fd_cnc_t * cnc;
    ulong *    metrics; /* The shared memory for metrics that this tile should write.  Consumer by monitoring and metrics writing tiles. */

    /* The fseq of each link that this tile reads from.  Multiple fseqs
       may point to the link, if there are multiple consumers.  An fseq
       can be uniquely identified via (link_id, tile_id), or (link_kind,
       link_kind_id, tile_kind, tile_kind_id) */
    ulong *    in_link_fseq[ FD_TOPO_MAX_TILE_IN_LINKS ];
  };

  /* Configuration fields.  These are required to be known by the topology so it can determine the
     total size of Firedancer in memory. */
  union {
    struct {
      char   interface[ 16 ];
      ulong  xdp_rx_queue_size;
      ulong  xdp_tx_queue_size;
      ulong  xdp_aio_depth;
      char   xdp_mode[4];
      int    zero_copy;
      uint   src_ip_addr;
      uchar  src_mac_addr[6];

      ushort shred_listen_port;
      ushort quic_transaction_listen_port;
      ushort legacy_transaction_listen_port;
      ushort gossip_listen_port;
      ushort repair_intake_listen_port;
      ushort repair_serve_listen_port;
    } net;

    struct {
      ulong  depth;
      uint   reasm_cnt;
      ulong  max_concurrent_connections;
      ulong  max_concurrent_handshakes;
      ulong  max_inflight_quic_packets;
      ulong  max_concurrent_streams_per_connection;
      ulong  stream_pool_cnt;
      uint   ip_addr;
      uchar  src_mac_addr[ 6 ];
      ushort quic_transaction_listen_port;
      ulong  idle_timeout_millis;
      char   identity_key_path[ PATH_MAX ];
      int    retry;
    } quic;

    struct {
      ulong tcache_depth;
    } dedup;

    struct {
      ulong max_pending_transactions;
      ulong bank_tile_count;
      int   larger_max_cost_per_block;
      int   larger_shred_limits_per_block;
      int   use_consumed_cus;
      char  identity_key_path[ PATH_MAX ];
    } pack;

    struct {
      ulong bank_cnt;
      char   identity_key_path[ PATH_MAX ];
    } poh;

    struct {
      ulong  depth;
      uint   ip_addr;
      uchar  src_mac_addr[ 6 ];
      ulong  fec_resolver_depth;
      char   identity_key_path[ PATH_MAX ];
      ushort shred_listen_port;
      int    larger_shred_limits_per_block;
      ulong  expected_shred_version;
    } shred;

    struct {
      ulong disable_blockstore_from_slot;
    } store;

    struct {
      char   identity_key_path[ PATH_MAX ];
    } sign;

    struct {
      ushort prometheus_listen_port;
    } metric;

    struct {

      /* specified by [tiles.replay] */

      char  blockstore_checkpt[ PATH_MAX ];
      int   blockstore_publish;
      int   tx_metadata_storage;
      char  capture[ PATH_MAX ];
      char  funk_checkpt[ PATH_MAX ];
      ulong funk_rec_max;
      ulong funk_sz_gb;
      ulong funk_txn_max;
      char  genesis[ PATH_MAX ];
      char  incremental[ PATH_MAX ];
      char  slots_replayed[ PATH_MAX ];
      char  snapshot[ PATH_MAX ];
      char  status_cache[ PATH_MAX ];
      ulong tpool_thread_count;
      char  cluster_version[ 32 ];

      /* not specified by [tiles.replay] */

      char  identity_key_path[ PATH_MAX ];
      uint  ip_addr;
      uchar src_mac_addr[ 6 ];
      int   vote;
      char  vote_account_path[ PATH_MAX ];
      ulong bank_tile_count;
    } replay;

    struct {
      ushort send_to_port;
      uint   send_to_ip_addr;
      ulong  conn_cnt;
      int    no_quic;
    } benchs;

    struct {
      ushort rpc_port;
      uint   rpc_ip_addr;
    } bencho;

    struct {
      ulong accounts_cnt;
      int   mode;
      float contending_fraction;
      float cu_price_spread;
    } benchg;

    /* Firedancer-only tile configs */

    struct {
      ushort  gossip_listen_port;
      ulong   entrypoints_cnt;
      uint    entrypoints[16];
      ulong   peer_ports_cnt;
      ushort  peer_ports[16];

      uint    ip_addr;
      uchar   src_mac_addr[ 6 ];
      char    identity_key_path[ PATH_MAX ];
      ushort  tvu_port;
      ushort  tvu_fwd_port;
      ushort  tpu_port;
      ushort  tpu_vote_port;
      ushort  repair_serve_port;
      ulong   expected_shred_version;
    } gossip;

    struct {
      ushort  repair_intake_listen_port;
      ushort  repair_serve_listen_port;

      /* non-config */

      uint    ip_addr;
      uchar   src_mac_addr[ 6 ];
      char    identity_key_path[ PATH_MAX ];
    } repair;

    struct {
      char  blockstore_restore[ PATH_MAX ];
      char  slots_pending[PATH_MAX];

      /* non-config */

      char  identity_key_path[ PATH_MAX ];
      char  shred_cap_archive[ PATH_MAX ];
      char  shred_cap_replay[ PATH_MAX ];
    } store_int;

    struct {
      ushort  tpu_listen_port;

      /* non-config */

      uint    ip_addr;
      uchar   src_mac_addr[ 6 ];
      char  identity_key_path[ PATH_MAX ];
    } sender;
  };
} fd_topo_tile_t;

typedef struct {
  ulong id;
  char  name[ 13UL ];
  ulong wksp_id;

  ulong offset;
  ulong footprint;
} fd_topo_obj_t;

/* An fd_topo_t represents the overall structure of a Firedancer
   configuration, describing all the workspaces, tiles, and links
   between them. */
typedef struct fd_topo_t {
  char           app_name[ 256UL ];
  uchar          props[ 16384UL ];

  ulong          wksp_cnt;
  ulong          link_cnt;
  ulong          tile_cnt;
  ulong          obj_cnt;

  fd_topo_wksp_t workspaces[ FD_TOPO_MAX_WKSPS ];
  fd_topo_link_t links[ FD_TOPO_MAX_LINKS ];
  fd_topo_tile_t tiles[ FD_TOPO_MAX_TILES ];
  fd_topo_obj_t  objs[ FD_TOPO_MAX_OBJS ];
} fd_topo_t;

typedef struct {
  char const *                  name;

  ulong                         mux_flags;
  ulong                         burst;
  int                           keep_host_networking;
  ulong                         rlimit_file_cnt;
  int                           for_tpool;
  void * (*mux_ctx           )( void * scratch );

  fd_mux_during_housekeeping_fn * mux_during_housekeeping;
  fd_mux_before_credit_fn       * mux_before_credit;
  fd_mux_after_credit_fn        * mux_after_credit;
  fd_mux_before_frag_fn         * mux_before_frag;
  fd_mux_during_frag_fn         * mux_during_frag;
  fd_mux_after_frag_fn          * mux_after_frag;
  fd_mux_metrics_write_fn       * mux_metrics_write;

  long  (*lazy                    )( fd_topo_tile_t * tile );
  ulong (*populate_allowed_seccomp)( void * scratch, ulong out_cnt, struct sock_filter * out );
  ulong (*populate_allowed_fds    )( void * scratch, ulong out_fds_sz, int * out_fds );
  ulong (*scratch_align           )( void );
  ulong (*scratch_footprint       )( fd_topo_tile_t const * tile );
  ulong (*loose_footprint         )( fd_topo_tile_t const * tile );
  void  (*privileged_init         )( fd_topo_t * topo, fd_topo_tile_t * tile, void * scratch );
  void  (*unprivileged_init       )( fd_topo_t * topo, fd_topo_tile_t * tile, void * scratch );
  int   (*main                    )( void );
} fd_topo_run_tile_t;

FD_PROTOTYPES_BEGIN

FD_FN_CONST static inline ulong
fd_topo_workspace_align( void ) {
  /* This needs to be the max( align ) of all the child members that
     could be aligned into this workspace, otherwise our footprint
     calculation will not be correct.  For now just set to 4096 but this
     should probably be calculated dynamically, or we should reduce
     those child aligns if we can. */
  return 4096UL;
}

FD_FN_PURE static inline void *
fd_topo_obj_laddr( fd_topo_t const * topo,
                   ulong             obj_id ) {
  fd_topo_obj_t const * obj = &topo->objs[ obj_id ];
  return (void *)((ulong)topo->workspaces[ obj->wksp_id ].wksp + obj->offset);
}

FD_FN_PURE static inline ulong
fd_topo_tile_name_cnt( fd_topo_t const * topo,
                       char const *      name ) {
  ulong cnt = 0;
  for( ulong i=0; i<topo->tile_cnt; i++ ) {
    if( FD_UNLIKELY( !strcmp( topo->tiles[ i ].name, name ) ) ) cnt++;
  }
  return cnt;
}

/* Finds the workspace of a given name in the topology.  Returns
   ULONG_MAX if there is no such workspace.  There can be at most one
   workspace of a given name. */

FD_FN_PURE static inline ulong
fd_topo_find_wksp( fd_topo_t const * topo,
                   char const *      name ) {
  for( ulong i=0; i<topo->wksp_cnt; i++ ) {
    if( FD_UNLIKELY( !strcmp( topo->workspaces[ i ].name, name ) ) ) return i;
  }
  return ULONG_MAX;
}

/* Find the tile of a given name and kind_id in the topology, there will
   be at most one such tile, since kind_id is unique among the name.
   Returns ULONG_MAX if there is no such tile. */

FD_FN_PURE static inline ulong
fd_topo_find_tile( fd_topo_t const * topo,
                   char const *      name,
                   ulong             kind_id ) {
  for( ulong i=0; i<topo->tile_cnt; i++ ) {
    if( FD_UNLIKELY( !strcmp( topo->tiles[ i ].name, name ) ) && topo->tiles[ i ].kind_id == kind_id ) return i;
  }
  return ULONG_MAX;
}

/* Find the link of a given name and kind_id in the topology, there will
   be at most one such link, since kind_id is unique among the name.
   Returns ULONG_MAX if there is no such link. */

FD_FN_PURE static inline ulong
fd_topo_find_link( fd_topo_t const * topo,
                   char const *      name,
                   ulong             kind_id ) {
  for( ulong i=0; i<topo->link_cnt; i++ ) {
    if( FD_UNLIKELY( !strcmp( topo->links[ i ].name, name ) ) && topo->links[ i ].kind_id == kind_id ) return i;
  }
  return ULONG_MAX;
}

FD_FN_PURE static inline ulong
fd_topo_find_tile_in_link( fd_topo_t const *      topo,
                           fd_topo_tile_t const * tile,
                           char const *           name,
                           ulong                  kind_id ) {
  for( ulong i=0; i<tile->in_cnt; i++ ) {
    if( FD_UNLIKELY( !strcmp( topo->links[ tile->in_link_id[ i ] ].name, name ) )
        && topo->links[ tile->in_link_id[ i ] ].kind_id == kind_id ) return i;
  }
  return ULONG_MAX;
}

FD_FN_PURE static inline ulong
fd_topo_find_tile_out_link( fd_topo_t const *      topo,
                           fd_topo_tile_t const * tile,
                           char const *           name,
                           ulong                  kind_id ) {
  for( ulong i=0; i<tile->out_cnt; i++ ) {
    if( FD_UNLIKELY( !strcmp( topo->links[ tile->out_link_id[ i ] ].name, name ) )
        && topo->links[ tile->out_link_id[ i ] ].kind_id == kind_id ) return i;
  }
  return ULONG_MAX;
}

/* Find the id of the tile which is a producer for the given link.  If
   no tile is a producer for the link, returns ULONG_MAX.  This should
   not be possible for a well formed and validated topology.  */
FD_FN_PURE static inline ulong
fd_topo_find_link_producer( fd_topo_t const *      topo,
                            fd_topo_link_t const * link ) {
  for( ulong i=0; i<topo->tile_cnt; i++ ) {
    fd_topo_tile_t const * tile = &topo->tiles[ i ];

    if( FD_UNLIKELY( tile->out_link_id_primary == link->id ) ) return i;
    for( ulong j=0; j<tile->out_cnt; j++ ) {
      if( FD_UNLIKELY( tile->out_link_id[ j ] == link->id ) ) return i;
    }
  }
  return ULONG_MAX;
}

/* Given a link, count the number of consumers of that link among all
   the tiles in the topology. */
FD_FN_PURE static inline ulong
fd_topo_link_consumer_cnt( fd_topo_t const *      topo,
                           fd_topo_link_t const * link ) {
  ulong cnt = 0;
  for( ulong i=0; i<topo->tile_cnt; i++ ) {
    fd_topo_tile_t const * tile = &topo->tiles[ i ];
    for( ulong j=0; j<tile->in_cnt; j++ ) {
      if( FD_UNLIKELY( tile->in_link_id[ j ] == link->id ) ) cnt++;
    }
  }

  return cnt;
}

/* Given a link, count the number of reliable consumers of that link
   among all the tiles in the topology. */
FD_FN_PURE static inline ulong
fd_topo_link_reliable_consumer_cnt( fd_topo_t const *      topo,
                                    fd_topo_link_t const * link ) {
  ulong cnt = 0;
  for( ulong i=0; i<topo->tile_cnt; i++ ) {
    fd_topo_tile_t const * tile = &topo->tiles[ i ];
    for( ulong j=0; j<tile->in_cnt; j++ ) {
      if( FD_UNLIKELY( tile->in_link_id[ j ] == link->id && tile->in_link_reliable[ j ] ) ) cnt++;
    }
  }

  return cnt;
}

/* Join (map into the process) all shared memory (huge/gigantic pages)
   needed by the tile, in the given topology.  All memory associated
   with the tile (aka. used by links that the tile either produces to or
   consumes from, or used by the tile itself for its cnc) will be
   attached (mapped into the process).

   This is needed to play nicely with the sandbox.  Once a process is
   sandboxed we can no longer map any memory. */
void
fd_topo_join_tile_workspaces( fd_topo_t *      topo,
                              fd_topo_tile_t * tile );

/* Join (map into the process) the shared memory (huge/gigantic pages)
   for the given workspace.  Mode is one of
   FD_SHMEM_JOIN_MODE_READ_WRITE or FD_SHMEM_JOIN_MODE_READ_ONLY and
   determines the prot argument that will be passed to mmap when mapping
   the pages in (PROT_WRITE or PROT_READ respectively). */
void
fd_topo_join_workspace( fd_topo_t *      topo,
                        fd_topo_wksp_t * wksp,
                        int              mode );

/* Join (map into the process) all shared memory (huge/gigantic pages)
   needed by all tiles in the topology.  Mode is one of
   FD_SHMEM_JOIN_MODE_READ_WRITE or FD_SHMEM_JOIN_MODE_READ_ONLY and
   determines the prot argument that will be passed to mmap when
   mapping the pages in (PROT_WRITE or PROT_READ respectively). */
void
fd_topo_join_workspaces( fd_topo_t *  topo,
                         int          mode );

/* Leave (unmap from the process) the shared memory needed for the
   given workspace in the topology, if it was previously mapped.

   topo and wksp are assumed non-NULL.  It is OK if the workspace
   has not been previously joined, in which case this is a no-op. */

void
fd_topo_leave_workspace( fd_topo_t *      topo,
                         fd_topo_wksp_t * wksp );

/* Leave (unmap from the process) all shared memory needed by all
   tiles in the topology, if each of them was mapped.

   topo is assumed non-NULL.  Only workspaces which were previously
   joined are unmapped. */

void
fd_topo_leave_workspaces( fd_topo_t * topo );

/* Create the given workspace needed by the topology on the system.
   This does not "join" the workspaces (map their memory into the
   process), but only creates the .wksp file and formats it correctly
   as a workspace.

   Returns 0 on success and -1 on failure, with errno set to the error.
   The only reason for failure currently that will be returned is
   ENOMEM, as other unexpected errors will cause the program to exit.

   If update_existing is 1, the workspace will not be created from
   scratch but it will be assumed that it already exists from a prior
   run and needs to be maybe resized and then have the header
   structures reinitialized.  This can save a very expensive operation
   of zeroing all of the workspace pages.  This is dangerous in
   production because it can leave stray memory from prior runs around,
   and should only be used in development environments. */

int
fd_topo_create_workspace( fd_topo_t *      topo,
                          fd_topo_wksp_t * wksp,
                          int              update_existing );

/* Join the standard IPC objects needed by the topology of this particular
   tile */

void
fd_topo_fill_tile( fd_topo_t *      topo,
                   fd_topo_tile_t * tile );

/* Same as fd_topo_fill_tile but fills in all the objects for a
   particular workspace with the given mode. */
void
fd_topo_workspace_fill( fd_topo_t *      topo,
                        fd_topo_wksp_t * wksp );

/* Apply a function to every object that is resident in the given
   workspace in the topology. */

void
fd_topo_wksp_apply( fd_topo_t *      topo,
                    fd_topo_wksp_t * wksp,
                    void (* fn )( fd_topo_t const * topo, fd_topo_obj_t const * obj ) );

/* Same as fd_topo_fill_tile but fills in all tiles in the topology. */

void
fd_topo_fill( fd_topo_t * topo );

/* fd_topo_tile_stack_join joins a huge page optimized stack for the
   provided tile.  The stack is assumed to already exist at a known
   path in the hugetlbfs mount. */

void *
fd_topo_tile_stack_join( char const * app_name,
                         char const * tile_name,
                         ulong        tile_kind_id );

/* fd_topo_run_single_process runs all the tiles in a single process
   (the calling process).  This spawns a thread for each tile, switches
   that thread to the given UID and GID and then runs the tile in it.
   Each thread will never exit, as tiles are expected to run forever.
   An error is logged and the application will exit if a tile exits.
   The function itself does return after spawning all the threads.

   The threads will not be sandboxed in any way, except switching to the
   provided UID and GID, so they will share the same address space, and
   not have any seccomp restrictions or use any Linux namespaces.  The
   calling thread will also switch to the provided UID and GID before
   it returns.

   In production, when running with an Agave child process this is
   used for spawning certain tiles inside the Agave address space.
   It's also useful for tooling and debugging, but is not how the main
   production Firedancer process runs.  For production, each tile is run
   in its own address space with a separate process and full security
   sandbox.

   The agave argument determines which tiles are started.  If the
   argument is 0 or 1, only non-agave (or only agave) tiles are started.
   If the argument is any other value, all tiles in the topology are
   started regardless of if they are Agave tiles or not. */

void
fd_topo_run_single_process( fd_topo_t * topo,
                            int         agave,
                            uint        uid,
                            uint        gid,
                            fd_topo_run_tile_t (* tile_run )( fd_topo_tile_t * tile ),
                            int *       done_futex );

/* fd_topo_run_tile runs the given tile directly within the current
   process (and thread).  The function will never return, as tiles are
   expected to run forever.  An error is logged and the application will
   exit if the tile exits.

   The sandbox argument determines if the current process will be
   sandboxed fully before starting the tile.  The thread will switch to
   the UID and GID provided before starting the tile, even if the thread
   is not being sandboxed.  Although POSIX specifies that all threads in
   a process must share a UID and GID, this is not the case on Linux.
   The thread will switch to the provided UID and GID without switching
   the other threads in the process.

   If keep_controlling_terminal is set to 0, and the sandbox is enabled
   the controlling terminal will be detached as an additional sandbox
   measure, but you will not be able to send Ctrl+C or other signals
   from the terminal.  See fd_sandbox.h for more information.

   The allow_fd argument is only used if sandbox is true, and is a file
   descriptor which will be allowed to exist in the process.  Normally
   the sandbox code rejects and aborts if there is an unexpected file
   descriptor present on boot.  This is helpful to allow a parent
   process to be notified on termination of the tile by waiting for a
   pipe file descriptor to get closed.

   wait and debugger are both used in debugging.  If wait is non-NULL,
   the runner will wait until the value pointed to by wait is non-zero
   before launching the tile.  Likewise, if debugger is non-NULL, the
   runner will wait until a debugger is attached before setting the
   value pointed to by debugger to non-zero.  These are intended to be
   used as a pair, where many tiles share a waiting reference, and then
   one of the tiles (a tile you want to attach the debugger to) has the
   same reference provided as the debugger, so all tiles will stop and
   wait for the debugger to attach to it before proceeding. */

void
fd_topo_run_tile( fd_topo_t *          topo,
                  fd_topo_tile_t *     tile,
                  int                  sandbox,
                  int                  keep_controlling_terminal,
                  uint                 uid,
                  uint                 gid,
                  int                  allow_fd,
                  volatile int *       wait,
                  volatile int *       debugger,
                  fd_topo_run_tile_t * tile_run );

/* This is for determining the value of RLIMIT_MLOCK that we need to
   successfully run all tiles in separate processes.  The value returned
   is the maximum amount of memory that will be locked with mlock() by
   any individual process in the tree.  Specifically, if we have three
   tile processes, and they each need to lock 5, 9, and 2 MiB of memory
   respectively, RLIMIT_MLOCK needs to be 9 MiB to allow all three
   process mlock() calls to succeed.

   Tiles lock memory in three ways.  Any workspace they are using, they
   lock the entire workspace.  Then each tile uses huge pages for the
   stack which are also locked, and finally some tiles use private
   locked mmaps outside the workspace for storing key material.  The
   results here include all of this memory together.

   The result is not necessarily the amount of memory used by the tile
   process, although it will be quite close.  Tiles could potentially
   allocate memory (eg, with brk) without needing to lock it, which
   would not need to included, and some kernel memory that tiles cause
   to be allocated (for example XSK buffers) is also not included.  The
   actual amount of memory used will not be less than this value. */
FD_FN_PURE ulong
fd_topo_mlock_max_tile( fd_topo_t * topo );

/* Same as fd_topo_mlock_max_tile, but for loading the entire topology
   topology into one process, rather than a separate process per tile.
   This is used, for example, by the configuration code when it creates
   all the workspaces, or the monitor that maps the entire system into
   one address space. */
FD_FN_PURE ulong
fd_topo_mlock( fd_topo_t * topo );

/* This returns the number of gigantic pages needed by the topology on
   the provided numa node.  It includes pages needed by the workspaces,
   as well as additional allocations like huge pages for process stacks
   and private key storage. */

FD_FN_PURE ulong
fd_topo_gigantic_page_cnt( fd_topo_t * topo,
                           ulong       numa_idx );

/* This returns the number of huge pages in the application needed by
   the topology on the provided numa node.  It includes pages needed by
   things placed in the hugetlbfs (workspaces, process stacks).  If
   include_anonymous is true, it also includes anonymous hugepages which
   are needed but are not placed in the hugetlbfs. */

FD_FN_PURE ulong
fd_topo_huge_page_cnt( fd_topo_t * topo,
                       ulong       numa_idx,
                       int         include_anonymous );

/* Check all invariants of the given topology to make sure it is valid.
   An invalid topology will cause the program to abort with an error
   message. */
void
fd_topo_validate( fd_topo_t const * topo );

/* Prints a message describing the topology to an output stream.  If
   stdout is true, will be written to stdout, otherwise will be written
   as a NOTICE log message to the log file. */
void
fd_topo_print_log( int         stdout,
                   fd_topo_t * topo );

FD_PROTOTYPES_END

#endif /* HEADER_fd_src_disco_topo_fd_topo_h */
