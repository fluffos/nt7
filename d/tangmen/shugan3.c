//shugan3.c                四川唐门—裂星崖古树

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "参天古树");
        set("long",
      "这是万年古松的树顶。当年祖师爷？？？曾在这里日观云动，夜观星\n" 
      "变，最终悟出了？？？？的唐门绝学，因此很多弟子常常在这里日夜静坐。\n" 
      ); 
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
        object ob, room;

        ob = this_player();

        if ( arg && arg=="up" )
        {
                message_vision(HIC "$N攀着繁茂的树枝一步步爬了上去。\n" NOR, ob);

                if ( (int)ob->query_skill("dodge", 1) < 51 && (int)ob->query_skill("finger", 1) < 51 )
                {
                        message_vision(HIR "$N脚下一滑，手上没抓紧，仰天摔了下来。\n" NOR, ob);
                        addn("qi", -10, ob);
                        return 1;
                }

                ob->move(__DIR__"shuding");
                return 1;
        }
        else
                if ( arg && arg=="down" )
                {
                        message_vision(HIC "$N攀着繁茂的树枝小心翼翼的爬了下去。\n" NOR, ob);
                        ob->move(__DIR__"shugan2");
                        return 1;
                }
                else
                        return notify_fail("你要向哪里爬？\n");
}