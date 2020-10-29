#include <room.h>
inherit ROOM;

void create()
{
        set("short", "后堂");
        set("long", @long
这里是书场的后堂，里面有一张桌子和一张矮床，墙上的窗户半掩
着，墙上挂着一副年画(picture)。
long);
        set("item_desc", ([
                "picture" : "这一张寻常农家过年时贴的年画。\n",
        ]));
        set("exits", ([
                "out" : __DIR__"shuchang",
        ]));
        create_door("out", "小门", "enter", DOOR_CLOSED);
	set("coor/x", 1089);
	set("coor/y", -1051);
	set("coor/z", -1);
	setup();
}
void init()
{
        add_action("do_jie","jie");
        add_action("do_jump","jump");
}
        
int do_jie(string arg)
{
        object me=this_player();
        
        if (!arg) return 0;
        if (arg !="picture") return 0;
        if (arg=="picture")
        {
                write("你揭开年画，发现墙上有个洞，恰好能容纳一个人，你忍不住想跳(jump)下去。\n");
                set_temp("marks/揭1", 1, me);
                return 1;
        }
}
int do_jump(string arg)
{
        object me;
        me=this_player();
        if( query_temp("marks/揭1", me) )
        {
                message("vision", me->name() + "钻进了墙上的洞，跳了下去，只听的“乒”的一声响。\n", environment(me), ({me}) );
                me->move(__DIR__"szyunhe");
                message("vision", me->name() + "突然间从上面摔了下来。\n", environment(me), ({me}) );
                delete_temp("marks/揭1", me);
                return 1;
        }
}