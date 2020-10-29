#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "迎客亭"); 
        set("long", @LONG
通过四雅清风，你来到了梅庄的迎客亭，这里虽然只有一张石桌
(table) 和几个石凳，但却是一尘不染，石凳和石桌之间的空隙很大，
显是方便来客与主人相互寒暄。
LONG );
        set("exits", ([
                "south" : __DIR__"dating",
                "north" : __DIR__"senlin1",
        ]));

        set("objects", ([
                CLASS_D("meizhuang") + "/ding" : 1,
        ]));

        set("no_clean_up", 0);

        setup();
}

void init()
{
        add_action("do_zuan", "zuan");
}

int do_zuan(string arg)
{
        object ob;
        string dir;
        object me = this_player();

        if (arg != "table")
        {
                write("你要往哪儿钻？\n");
                return 1;
        }

        if (objectp(ob = present("shi lingwei", this_object())) &&
            living(ob))
        {
                write("你偷偷的看了看" + ob->name() + "，不敢乱来。\n");
                return 1;
        }

        write("你蹑手蹑脚的绕到石桌的后面，钻进了下面的一个小洞。\n");
        if((int)me->query_skill("dodge",1) >= 30)
        {
              write("你费尽九牛二虎之力，发现自己到了一个很神秘的地道里。\n");
              me->move(__DIR__"didao1");
              return 1;
        }
        write("你试着钻了一下后面的一个小洞，发现钻不进去。\n");
        addn("jing", -10, me);
        addn("qi", -10, me);

        return 1;
}


int valid_leave(object me, string dir)
{
        object ding;

        if (dir != "north" ||
            ! objectp(ding = present("ding jian", this_object())))
                return ::valid_leave(me, dir);

        return ding->permit_pass(me, dir);
}