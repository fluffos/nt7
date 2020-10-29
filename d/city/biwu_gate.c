#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"演武大门"NOR);
        set("long", @LONG
这是一个金色的门廊，往北是一个宽阔的走廊，尽头就是比武大
厅。泥潭的顶级高手通过擂台比武一争高低，比武大厅是泥潭所有武
者心中的圣地。如果能够跻身十大高手金榜，更是无上荣誉，风光至
极。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);

    set("exits", ([
        "north" : "/d/city/biwu_road",
        "south" : "/d/city/wudao1",
    ]));

    set("no_clean_up", 0);
	set("coor/x", -60);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
	int i;
        mapping conditions;
        object *inv;
 
        if (dir != "north") return 1;

        if (mapp(conditions = me->query_condition()))
               return notify_fail("对不起，你的身体状况不好，不能进入！\n");

        if( query("eff_qi", me)<query("max_qi", me) )
               return notify_fail("对不起，你的气血受伤了，不能进入！\n");

        if( query("eff_jing", me)<query("max_jing", me) )
               return notify_fail("对不起，你的精气受伤了，不能进入！\n");

        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i])) continue;
                tell_object(me, "你背的是谁？还不快快放下！\n");
                return 0;
        }

        inv = 0;
        return 1;
}