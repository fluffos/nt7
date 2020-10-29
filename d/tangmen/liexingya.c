//liexingya.c                四川唐门—裂星崖

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "裂星崖");
        set("long",
"这里是莲藕小筑后山的裂星崖。据说唐门的开山祖师？？？就是在这\n"
"里静坐五年，夜观星变，终于悟出了威镇江湖的唐门暗器绝技？？？？，\n"
"一株万年古松自山崖外长了上来，高耸入云。\n"
);
//？？，一株万年古松(shu)自山崖外长了上来，高耸入云。
        set("exits", ([
                        "southdown" : __DIR__"shandao5",
        ]));
        set("item_desc", ([
                "shu" : "这株古松据说是万年前盘古开天时生长而成的。\n",
        ]));
        set("area", "tangmen");
        setup();
}

void init()
{
        add_action("do_climb","climb");
        add_action("do_climb","pa");
}

int do_climb(string arg)
{
        object ob;
        ob = this_player();

        if ( arg && arg == "shu" )
        {
                if ( (int)ob->query_skill("dodge", 1) < 21 && (int)ob->query_skill("finger", 1) < 21 )
                {
                        tell_object(ob, HIR "你的功夫还不够高，爬上去恐怕会摔死的。\n" NOR, ob);
                        return 1;
                }

                message_vision(HIC "$N攀着繁茂的树枝一步步爬了上去。\n" NOR, ob);
                ob->move(__DIR__"shugan1");
                return 1;
        }
        else
                return notify_fail("你要向哪里爬？\n");
}