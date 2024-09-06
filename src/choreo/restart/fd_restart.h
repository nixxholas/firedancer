#ifndef HEADER_fd_src_choreo_restart_fd_restart_h
#define HEADER_fd_src_choreo_restart_fd_restart_h

#include "../../flamenco/types/fd_types.h"

#define HEAVIEST_FORK_THRESHOLD_DELTA_PERCENT     38UL
#define REPAIR_THRESHOLD_PERCENT                  42UL
#define WAIT_FOR_SUPERMAJORITY_THRESHOLD_PERCENT  80UL
#define LAST_VOTED_FORK_MAX_SLOTS                 0xFFFF
#define LAST_VOTED_FORK_MAX_BITMAP_BYTES          ( LAST_VOTED_FORK_MAX_SLOTS / sizeof(uchar) + 1 )

void
fd_restart_init( fd_vote_accounts_t const * accs );

void
fd_restart_recv_last_voted_slots( fd_gossip_restart_last_voted_fork_slots_t * last_voted_msg );

#endif
