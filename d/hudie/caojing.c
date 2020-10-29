// 草径 caojing.c
 
#include <ansi.h>

inherit ROOM;
void create() 
{ 
        set("short", "草径");
        set("long", @LONG
这是一片草地，过了这片草地有七八间茅屋，茅屋的前后左右都
是花圃，看来已经到了蝶谷医仙胡青牛的住处了。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "north" : __DIR__"maowu",
            "west" : __DIR__"maopeng",
            "south" : __DIR__"niupeng",
            "east" : __DIR__"xfang1",
]));

        setup();
}

int get_object(object ob)
{
        return (userp(ob));
}

int valid_leave(object me, string dir)
{
        object *ob, *inv;
        mapping myfam;
        myfam =( mapping)query("family", me);

        inv = deep_inventory(me);
        if (dir == "south"){
          write("南面是一片花圃，里面种满了诸般花草。\n");
          ob = filter_array(inv,(:get_object:));        
          if (myfam && myfam["family_name"] =="明教" && myfam["generation"] == 35 && ! sizeof(ob))
          write("由于你已听闻张教主的教诲，走惯了这片花圃，所以信步走了出去。\n");
          else {
             tell_room(environment(me), me->name()+"往南面的牛棚快步离开。\n"NOR, ({ me }));
             me->move(__DIR__"huapu1");
             tell_room(environment(me), me->name()+"从草径快步走了过来。\n"NOR, ({ me }));
             me->look();
             return notify_fail("");
          }
        }
        return ::valid_leave(me, dir);
}
