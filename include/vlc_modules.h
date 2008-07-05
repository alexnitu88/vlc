/*****************************************************************************
 * modules.h : Module descriptor and load functions
 *****************************************************************************
 * Copyright (C) 2001 the VideoLAN team
 * $Id$
 *
 * Authors: Samuel Hocevar <sam@zoy.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

/*****************************************************************************
 * Exported functions.
 *****************************************************************************/

#define module_Need(a,b,c,d) __module_Need(VLC_OBJECT(a),b,c,d)
VLC_EXPORT( module_t *, __module_Need, ( vlc_object_t *, const char *, const char *, bool ) );
#define module_Unneed(a,b) __module_Unneed(VLC_OBJECT(a),b)
VLC_EXPORT( void, __module_Unneed, ( vlc_object_t *, module_t * ) );
#define module_Exists(a,b) __module_Exists(VLC_OBJECT(a),b)
VLC_EXPORT( bool,  __module_Exists, ( vlc_object_t *, const char * ) );

#define module_Find(a,b) __module_Find(VLC_OBJECT(a),b)
VLC_EXPORT( module_t *, __module_Find, ( vlc_object_t *, const char * ) );
VLC_EXPORT( void, module_Put, ( module_t *module ) );

VLC_EXPORT( module_config_t *, module_GetConfig, ( const module_t *, unsigned * ) );
VLC_EXPORT( void, module_PutConfig, ( module_config_t * ) );

/* Return a NULL terminated array with the names of the modules that have a
 * certain capability.
 * Free after uses both the string and the table. */
 #define module_GetModulesNamesForCapability(a,b,c) \
                    __module_GetModulesNamesForCapability(VLC_OBJECT(a),b,c)
VLC_EXPORT(char **, __module_GetModulesNamesForCapability,
                    ( vlc_object_t *p_this, const char * psz_capability,
                      char ***psz_longname ) );

VLC_EXPORT( bool, module_IsCapable, ( const module_t *m, const char *cap ) );
VLC_EXPORT( const char *, module_GetObjName, ( const module_t *m ) );
VLC_EXPORT( const char *, module_GetName, ( const module_t *m, bool long_name ) );
#define module_GetLongName( m ) module_GetName( m, true )
VLC_EXPORT( const char *, module_GetHelp, ( const module_t *m ) );


#define module_GetMainModule(a) __module_GetMainModule(VLC_OBJECT(a))
static inline module_t * __module_GetMainModule( vlc_object_t * p_this )
{
    module_t * p_module;
    module_t * p_main_module = NULL;
    vlc_list_t *p_list = vlc_list_find( p_this, VLC_OBJECT_MODULE,
                                        FIND_ANYWHERE );
    if( !p_list ) return NULL;

    /* Find the main module */
    for( int i = 0; i < p_list->i_count; i++ )
    {
        p_module = (module_t *)p_list->p_values[i].p_object;
        if( strcmp( module_GetObjName( p_module ), "main" ) == 0 )
        {
            p_main_module = p_module;
            vlc_object_yield( (vlc_object_t*)p_main_module );
            break;
        }
    }
    vlc_list_release( p_list );
    return p_main_module;
}

static inline bool module_IsMainModule( module_t * p_module )
{
    return !strcmp( module_GetObjName( p_module ), "main" );
}
