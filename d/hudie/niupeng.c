// 牛棚 niupeng.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "牛棚");
        set("long", @LONG
这里是蝴蝶谷的牛棚，据说因倒毙在这里的人不计其数，使得『
见死不救』胡青牛的大名天下闻名。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "south" : __DIR__"kongdi",
            "northdown" : __DIR__"caojing",
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
        if (dir == "northdown"){
          write("北面是一片花圃，里面种满了诸般花草。\n");
          ob = filter_array(inv,(:get_object:));        
          if (myfam && myfam["family_name"] =="明教" && myfam["generation"] == 35 && ! sizeof(ob))
          write("由于你已听闻张教主的教诲，走惯了这片花圃，所以信步走了进去。\n");
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
