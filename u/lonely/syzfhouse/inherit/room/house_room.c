// /inherit/room/house_room.c 自建屋宅继承文件
// By Alf, Last Update 2003.0712

#include <ansi.h>
#include <dbase.h>

inherit F_DBASE;
inherit F_CLEAN_UP;
inherit F_SAVE;

int do_short(string arg);
int do_long(string arg);

int is_house_room()
{
    return 1;
}

int query_max_encumbrance()
{
    return 100000000000;
}

void init()
{
    object me = this_player();

    if(query("type") == "bang")
    {
        if(me->query("bang/class") == 1
            && me->query("id") == query("owner"))
        {
            add_action("do_short", "setname");
            add_action("do_long",  "setlong");
            add_action("do_item",  "setitem");
            add_action("do_invite", ({"invite", "yaoqing"}));
        }
    }

    if(query("type") == "user" || query("type") == "xian")
    {
        if(me->query("id") == query("owner")
            || me->query("couple/couple_id") == query("owner"))
        {
            add_action("do_short", "setname");
            add_action("do_long",  "setlong");
            add_action("do_item",  "setitem");
            add_action("do_invite", ({"invite", "yaoqing"}));
        }
    }
}

int do_short(string arg)
{
    return HOUSE_D->do_short(this_player(), arg);
}

int do_long(string arg)
{
    return HOUSE_D->do_long(this_player(), arg);
}

int do_item(string arg)
{
    return HOUSE_D->do_item(this_player(), arg);
}

int do_invite(string arg)
{
    return HOUSE_D->invite_guest(this_player(), arg);
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

object make_inventory(string file)
{
    object ob = new(file);
    ob->move(this_object());
    ob->set("startroom", base_name(this_object()));
    return ob;
}

void reset()
{
    object ob, *inv;
    string ob_list;
    int i, j = 0;

    inv = all_inventory(this_object());
    if(sizeof(inv) > 5)
    {
        for(i = 0; i < sizeof(inv); i++)
        {
            if(inv[i]->is_character())
                continue;
            if(inv[i]->is_board())
                continue;
            if(j++ < 5)
                continue;
            destruct(inv[i]);
        }
    }

    ob_list = query("objects");
    ob = query_temp("objects");

    if(!stringp(ob_list))
        return;

    if(!objectp(ob))
        ob = make_inventory(ob_list);

    if(environment(ob) != this_object())
        ob->move(this_object());
    set_temp("objects", ob);
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
