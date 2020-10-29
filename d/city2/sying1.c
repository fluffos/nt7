// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>
#include <command.h>

#define RIDE_CMD        "/cmds/std/ride"

inherit ROOM;


void create()
{
        set("short", HIW"元帅帐营"NOR);
        set("long", @LONG
这里就是「大宋」元帅的帐营，两边分立着众将领军士，大宋元
帅在这里负责调兵遣将，抗击蒙古军的入侵，不时有传令兵匆忙地进
出，传递着前线的军情。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
              "north" :   __DIR__"sying",
              "south" :   __DIR__"sying4",
              "west"  :   __DIR__"sying2",
              "east"  :   __DIR__"sying3",
        ]));

        setup();
}

void init()
{
        object me = this_player();

        if (me == WAR_D->query_marshal())
        {
                message_vision(HIW "帐中的将士看见$N走了进来，连忙将身体站得笔直，尊敬地向$N行礼致敬！\n" NOR, me);

                add_action("do_assign", ({ "appoint", "paiqian", "assign" }));
                add_action("do_convene", ({ "convene", "dianjiang" }));
        }
}

// recruit 招募
int do_assign(string arg)
{
        object me;

        me = this_player();
        tell_object(me, WAR_D->do_assign(me, arg));
        return 1;
}

int do_convene(string arg)
{
        object ob, me;
        object *total;
        int i;

        me = this_player();
        message_vision(HIR "$N召来传令兵，下令道：火速传令各营统领到本帅帐前候令！！\n", me);

        total = WAR_D->query_generals();
        for (i = 0; i < sizeof(total); i++)
        {
                if (! objectp(total[i])) continue;

                ob = total[i];
                if( query_temp("warquest/guard", ob) || 
                    query_temp("warquest/recon", ob) || 
                    query_temp("warquest/purchase", ob) || 
                    query_temp("warquest/battle", ob) )
                        continue;

                if (sscanf(base_name(environment(ob)), "/d/city2/sy%*s"))
                {
                        message_vision(HIR "一位传令兵急匆匆得赶来对$N道：三军将领" +
                                       "火速至元帅帐营侯令！！\n" NOR, ob);

                        ob->start_call_out((: call_other, __FILE__, "go_back", ob :), 5);
                }
        }

        return 1;
}

void go_back(object ob)
{
        if (! objectp(ob)) return;

        message_vision(HIY "$N赶忙批盔带甲，赶至元帅帐营，还好没误了时辰。\n" NOR, ob);
        ob->move(__DIR__"sying1");

        return;
}


