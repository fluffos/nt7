// /inherit/room/house_base.c 建房地块继承文件
// By Alf, Last Update 2003.0712

#include <ansi.h>
#include <dbase.h>

inherit F_DBASE;
inherit F_CLEAN_UP;
inherit F_SAVE;

int is_house_base()
{
    return 1;
}

int query_max_encumbrance()
{
    return 100000000000;
}

string query_save_file()
{
    string file = base_name(this_object());
    return DATA_DIR + file;
}

int save()
{
    string file;

    if(stringp(file = this_object()->query_save_file()))
    {
        assure_file(file + __SAVE_EXTENSION__);
        return save_object(file);
    }
    return 0;
}

int restore()
{
    string file;

    if(stringp(file = this_object()->query_save_file())
        && file_size(file + __SAVE_EXTENSION__) > 0 )
            return restore_object(file);
    return 0;
}

void reset()
{
    object *inv;
    int i, j = 0;

    inv = all_inventory(this_object());

    if(sizeof(inv) < 5)
        return;

    for(i = 0; i < sizeof(inv); i++)
    {
        if(inv[i]->is_character())
            continue;
        if(j++ < 5)
            continue;
        if(random(3) == 1)
            destruct(inv[i]);
    }
}

void setup()
{
    seteuid(getuid());
    this_object()->reset();
}

int valid_leave(object me, string dir)
{
	return 1;
}
