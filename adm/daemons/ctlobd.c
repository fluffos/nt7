// /adm/daemons/ctlob_d.c

inherit F_SAVE;

mapping mud_save_obj = ([]);

void create()
{
        seteuid(getuid());
        restore();
}

string query_save_file() { return DATA_DIR+"ctl_ob"; }

int query_save_num(string file)
{
        if( !stringp(file) || file == "" )
                return 0;

        if( undefinedp(mud_save_obj[file]) )
                return 0;

        return (int)mud_save_obj[file];
}

void save_to_mud(string file)
{
        if( !stringp(file) || file == "" )
                return;

        if( undefinedp(mud_save_obj[file]) )
                mud_save_obj += ([ file:1 ]);

        else
                mud_save_obj[file] += 1;

        save();
        return;
}

void delete_from_mud(string file)
{
        int n;

        if( !stringp(file) || file == "" )
                return;

        if( undefinedp(mud_save_obj[file]) )
                return;

        else
        {
                n = (int)mud_save_obj[file];
                if( !n )  /* 应该不会出现这种情况 */
                        return;
                n--;
                if( n<=0 )
                        map_delete(mud_save_obj,file);
                else
                        mud_save_obj[file] = n;
        }

        save();
        return;
}
