// sheshenya.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "舍身崖");
        set("long", @LONG
这是一段极窄极险的山崖，四周云雾飞绕，下面渊深无底。如不
小心，一失足掉下去，只怕连骨头都找不到。边上有个小山洞(dong)。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "eastdown" : __DIR__"canglong",
        ]));
        set("item_desc", ([
                "dong" : "紧靠飞崖下石壁的小洞，黑呼呼的不知有多深。\n",
        ]));
        set("outdoors", "huashan" );

        setup();
}

void init()
{
        object me = this_player();
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
        if( query_temp("xunshan", me) )
                set_temp("xunshan/sheshen", 1, me);
        return;
}

int do_enter(string arg)
{
        object me;
        mapping fam;

        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( arg=="dong" )
        {
                if( (fam=query("family", me)) && fam["family_name"] == "丐帮" )
                {
                        message("vision",
                                me->name() + "运起丐帮缩骨功，一弯腰往洞里钻了进去。",
                                environment(me), ({me}) );
                        me->move("/d/gaibang/undertre");
                        message("vision",
                                me->name() + "从洞里走了进来。\n",
                                environment(me), ({me}) );
                                return 1;
                } else  
                        return notify_fail("这么小的洞，你钻得进去吗？\n");
        }
}

