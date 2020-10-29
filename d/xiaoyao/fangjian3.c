// fangjian3.c
// Modified by Lonely June.25 2000

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "房间");
        set("long", @LONG
你只觉得眼前陡然一亮，一个宫装的美女，正拿着一把长剑，对准
了你的胸膛！。。。。一场虚惊之后，你才发现原来只是个白玉雕成的
玉像，但是看上去却与真人一般无异。玉像的一双眸子莹然有光，神采
飞扬。你此时只觉得神驰目眩，竟如着魔中邪，眼光再也离不开玉像。
。。。
LONG );
        set("exits", ([
                "east"    : __DIR__"tongmen",
                "northup" : __DIR__"shiji4",
        ]));
        set("objects",([
                __DIR__"obj/putuan" : 1,
        ]));
//        set("no_clean_up", 0);
        set("book_count",1);
        set("coor/x", -50010);
        set("coor/y", -21020);
        set("coor/z", -40);
        setup();
}

void init()
{
        set_temp("ketou_times", 50, this_player());
        add_action("do_kneel", "kneel");
        add_action("do_ketou", "ketou");
}

int do_kneel(string arg)
{
        object me,room,weapon;
        me = this_player();
        if ( !arg || arg == "") return 0;
        if ( arg != "putuan") return 0;
        if (!present("putuan",environment(me))) return 0;
        if( query_temp("marks/kneel", me) == 1 )
                return notify_fail("你已经跪下来了。\n");
        message_vision("$N双膝一屈，跪了下来。\n", me);
        addn_temp("marks/kneel", 1, me);
        return 1;
}

int do_ketou()
{
        object me, ob;

        me = this_player();
        if( !query_temp("marks/kneel", me))return 0;
        if (!present("putuan",environment(me))) return 0;
        if( query_temp("ketou_times", me) == 0 )
        {
                message_vision("$N磕头太拼命了。\n", me);
                set_temp("ketou_times", random(50), me);
                me->unconcious();
                return 1;
        }

        addn_temp("ketou_times", -1, me);

        message_vision("$N恭恭敬敬地给玉像磕头。咚、咚、咚。。。。\n", me);

        if ( random(100) == 37 
        && !present("bojuan", me)
        && query("book_count") >= 1)
        {
                addn("book_count", -1);
                ob=new("/clone/book/bojuan");
                if (ob->violate_unique()) {destruct(ob);return 1;}
                ob->move(me);
message("channel:rumor",MAG"【谣言】某人："+query("name", this_player())+"取到了北冥神功帛卷啦。\n"NOR,users());
                tell_object(me, "突然，你发现小蒲团面上的一层薄薄的蒲草已然破裂，露出下面有物！\n");
                tell_object(me, "你急忙把它拿了出来。\n");
        }

        return 1;

}

int valid_leave(object me, string dir)
{
        if( query_temp("ketou_times", me) >= 0)delete_temp("ketou_times", me);
        if( query_temp("marks/kneel", me))delete_temp("marks/kneel", me);
        return ::valid_leave();
}