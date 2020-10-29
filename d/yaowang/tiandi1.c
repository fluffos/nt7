#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "田地");
        set("long", @LONG
这是药王谷用来种植草药的田地，你可以拿草药种籽在这里种植草药(zhong)。
等草药种成了就可以挖(dig)起来。
LONG );
        set("no_clean_up", 1);
        set("yaotian",1);
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"door",

        ]));

        setup();
}

void init()
{
        add_action("do_dig", "dig");
        add_action("do_work", "get");
}

int do_dig(string arg)
{
        object ob, me;
        me = this_player();

        if( query("family/family_name", me) != "药王谷"
                || me->query_skill("medical",1) < 60 )
                return notify_fail("你不会种植草药！更不会挖草药！\n");

        if(me->is_fighting() && me->is_busy())
                return notify_fail("你很忙，没时间。\n");

        if( !arg || !ob = present(arg, environment(me)) )
                return notify_fail("指令格式：dig <草药ID> \n");

        if( query("owner", ob) != query("id", me) )
                return notify_fail("这个东西好象不是你的啊？？\n"); 

        message_vision("$N轻轻将$n挖了起来。\n", me, ob);

        delete("no_get", ob);
        ob->move(me);
        delete("dig", ob);
        return 1;
}

int do_work(string arg) 

{
        return notify_fail("这里不能使用这个指令！\n");
}
