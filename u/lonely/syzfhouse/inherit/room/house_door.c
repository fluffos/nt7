// /inherit/room/house_door.c 自建屋宅大门继承文件
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
    if(this_player()->query("id") == query("owner"))
    {
        add_action("do_short", "setname");
        add_action("do_long",  "setlong");
        add_action("do_jiagu", "jiagu");
    }
    add_action("do_push", "push");
    add_action("do_look", "look");
    add_action("do_break", "break");
}

int do_short(string arg)
{
    return HOUSE_D->do_short(this_player(), arg);
}

int do_long(string arg)
{
    return HOUSE_D->do_long(this_player(), arg);
}

int do_look(string arg)
{
    return HOUSE_D->look_house_door(arg, this_player(), this_object());
}

int do_jiagu(string arg)
{
    return HOUSE_D->jiagu_house_door(arg, this_player(), this_object());
}

int do_push(string arg)
{
    return HOUSE_D->push_house_door(arg, this_player(), this_object());
}

int do_break(string arg)
{
    return HOUSE_D->break_house_door(arg, this_player(), this_object());
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
    object ob;
    ob = new(file);
    ob->move(this_object());
    ob->set("startroom", base_name(this_object()));
    return ob;
}

void reset()
{
    object ob, *inv;
    string ob_list;
    mapping exits;
    int i, j = 0;

    ob_list = query("huyuan");
    if(!stringp(ob_list))
        return;
    ob = query_temp("huyuan");
    if(!objectp(ob))
        ob = make_inventory(ob_list);
    if(environment(ob) != this_object())
        ob->return_home(this_object());
    set_temp("huyuan", ob);

    exits = query("exits");
    if(sizeof(exits) > 1)
    {
        map_delete(exits, query("set_exits"));
        set("exits", exits);
    }
    set("now_laodu", query("max_laodu"));

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
