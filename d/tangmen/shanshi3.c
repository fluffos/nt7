//shanshi6


#include <ansi.h>
inherit ROOM;

int do_qiao(string arg);

void create ()
{
        set ("short", "山道");
        set ("long", @LONG
这里是后山一条昏暗的山道。山道的两旁已不象刚才那么树木繁
茂，反而是光秃秃的没有一棵植物，这里的山石竟发出深深的赤红色
光泽，不知与处别的石头有什么不同，空气中飘这一股腥臊的气味，
可能有毒物潜伏在附近，离开这里吧。
LONG);
        set("area","tangmen");
        set("outdoors", "tangmen");
        set("exits", ([
                "northwest" : __DIR__"shanshi2",
                "southdown" : __DIR__"shanshi4",
        ]));
        set("shi", 5);
        setup();
}

void init()
{
        add_action("do_qiao","knock");
}

int do_qiao(string arg)
{
        object me, enemy;
       object weapon;
        int jingli_cost;

        me = this_player();
        weapon=query_temp("weapon", me);
        jingli_cost = (-1) * (10 + random(15));

        if ( !arg || ( arg != "shi" ) )
                return notify_fail("你想干什么？\n");

        if( !(query_temp("biao", me)) )
                        return notify_fail("你没事做吗？乱敲什么呀！\n");
        if( !weapon || (query("id", weapon) != "hammer") )
                return notify_fail("你手上没有铁锤，难道用手？\n");
        if( query_temp("find", me) )
                return notify_fail("你已经找到一块精铁矿石了，没有力气再带一块！\n");

        if( query("jingli", me) <= (-jingli_cost) )
                return notify_fail("你太疲劳了，没有精力再继续敲凿了。\n");

        if ( (int)query("shi") >= 1 )
        {
                message_vision(YEL"$N扬起手中的铁锤重重的砸在道旁的山石上。\n"NOR, me);
                if( random(1+query("kar", me)-10) >= 3 )
                {
                        message_vision(HIG"$N听到山石发出清脆的碎裂声，终于给你敲下来了一大块！\n$N低头刚要抱起矿石，突然一只毒蝎从石后爬了出来！\n"NOR, me);
                        enemy = new(__DIR__"npc/xiezi");
                        enemy->move(this_object());
                        new(__DIR__"obj/kuangshi")->move(this_object());
                        enemy->kill_ob(me);
                        me->fight_ob(enemy);
                        set_temp("find", 1, me);
                }

                addn("jingli", jingli_cost, me);
                addn("shi",-1);
        }
        else
                return notify_fail("山道边的山石都被砸碎了，没有可以用的了。\n");

        return 1;
}

int valid_leave(object me, string dir)
{
        object ob;
        int true;
        if ( objectp( present("duxie", environment(me))) )
        {
                ob = present("duxie", environment(me));
                true = 1;
        }
        else 
                true = 0;
        if ( ( (dir == "southeast") || (dir == "northup") ) && objectp( present("kuang shi", me))  && true && living(ob))
                return notify_fail("毒蝎挡住了你离开的道路，看来只有杀了它才能走了！\n");
        else
                return ::valid_leave(me, dir);
}