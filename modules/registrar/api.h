/*
 * $Id$
 *
 * Functions that process REGISTER message 
 * and store data in usrloc
 *
 * Copyright (C) 2010 Daniel-Constantin Mierla (asipto.com)
 *
 * This file is part of Kamailio, a free SIP server.
 *
 * Kamailio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Kamailio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */


#ifndef _REGISTRAR_API_H_
#define _REGISTRAR_API_H_

#include "../../sr_module.h"
#include "../../parser/msg_parser.h"

typedef int (*regapi_save_f)(struct sip_msg *msg, char *table, int flags);
int regapi_save(struct sip_msg *msg, char *table, int flags);

typedef int (*regapi_save_uri_f)(struct sip_msg *msg, char *table, int flags, str *uri);
int regapi_save_uri(struct sip_msg *msg, char *table, int flags, str *uri);

typedef int (*regapi_lookup_f)(struct sip_msg *msg, char *table);
int regapi_lookup(struct sip_msg *msg, char *table);

typedef int (*regapi_lookup_uri_f)(struct sip_msg *msg, char *table, str *uri);
int regapi_lookup_uri(struct sip_msg *msg, char *table, str *uri);

typedef int (*regapi_set_q_override_f)(struct sip_msg *msg, str *new_q);
int regapi_set_q_override(struct sip_msg *msg, str *new_q);

/**
 * @brief REGISTRAR API structure
 */
typedef struct registrar_api {
	regapi_save_f       save;
	regapi_save_uri_f   save_uri;
	regapi_lookup_f     lookup;
	regapi_lookup_uri_f lookup_uri;
	regapi_lookup_f     registered;
	regapi_set_q_override_f set_q_override;
} registrar_api_t;

typedef int (*bind_registrar_f)(registrar_api_t* api);
int bind_registrar(registrar_api_t* api);

/**
 * @brief Load the REGISTRAR API
 */
static inline int registrar_load_api(registrar_api_t *api)
{
	bind_registrar_f bindregistrar;

	bindregistrar = (bind_registrar_f)find_export("bind_registrar", 0, 0);
	if(bindregistrar == 0) {
		LM_ERR("cannot find bind_registrar\n");
		return -1;
	}
	if (bindregistrar(api) < 0)
	{
		LM_ERR("cannot bind registrar api\n");
		return -1;
	}
	return 0;
}


#endif
