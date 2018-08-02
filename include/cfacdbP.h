/* 
 * Copyright (C) 2013-2015 Evgeny Stambulchik
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef _CFACDBP_H
#define _CFACDBP_H

#include "cfacdb.h"
#include <sqlite3.h>

struct _cfacdb_t {
    sqlite3 *db;
    int db_format;
    
    unsigned int nsessions;
    
    int nele_min;
    int nele_max;
    
    int initialized;
    
    unsigned long int sid;
    
    cfacdb_stats_t stats;
    
    unsigned int anum;
    double mass;
    
    unsigned int id_min;
    unsigned int id_max;

    unsigned int *lmap;
    
    int cached;
    sqlite3 *cache_db;
    
    void *udata;
};

int cfacdb_crates_cached(cfacdb_t *cdb,
    double T, cfacdb_crates_sink_t sink, void *udata);


#endif /* _CFACDBP_H */
