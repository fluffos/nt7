#include <ansi.h>
inherit ROOM;

void create()
{
    	set("short", "菜地");
    	set("long", @LONG
这里是块菜地，由于长期得不到良好的照顾，菜地里杂草
丛生，种的菜都长势不好，蔫蔫的，地都荒了。
LONG);
        set("no_fight", 1);
        set("exits", ([
             	"west" : __DIR__"guofu_houyuan3",
        ]));
        set("objects", ([
           	__DIR__"npc/guanjia5" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_chu", "chu");
}

int do_chu(string arg)
{
        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/锄完了", me) )
            	return notify_fail(CYN "菜园管事嚷嚷道：喂喂喂，让你去覆命，还留"
                                   "在这里干嘛？\n" NOR);

        if( query_temp("job_name", me) != "锄草" )
            	return notify_fail(CYN "菜园管事对你喝道：没事你瞎折腾什么？\n" NOR);

        if (me->is_busy())
		return notify_fail("你现在正忙着呢！\n");

        if (me->is_fighting())
		return notify_fail("你正在战斗中，无法专心干活！\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("id", weapon) != "chu tou" )
                return notify_fail(CYN "菜园管事讥笑道：你是想用什么来锄草呀，用"
                                   "手吗？\n" NOR);

        if (! arg || arg != "cao" )
		return notify_fail("你要锄什么？\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
        	message_vision(HIR "\n$N" HIR "锄着锄着，结果不小心手一滑，锄在"
                               "了自己的脚上。\n" NOR, me);
                me->unconcious();
                return 1;
        }

        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);       
        me->start_busy(1 + random(2));

        if (! (int)me->query_condition("wuguan_job")
            && query_temp("mark/锄", me)>10+(random(10) )
           && present("caiyuan guanshi", environment(me)))
	{
                set_temp("mark/锄完了", 1, me);
                message_vision(CYN "\n菜园管事对$N" CYN "说：干的不错，好了，你可"
                               "以去向耶律大爷覆命(" HIY "fuming" NOR + CYN ")了"
                               "。\n" NOR, me);
                return 1;
        }

        message_vision(HIY "$N" HIY "挥起锄头，对着地上的杂草锄了起来。\n" NOR, me);
        addn_temp("mark/锄", 1, me);

        if ((int)me->query_skill("staff", 1) < 50
           && (int)me->query_skill("cuff", 1) < 50
           && me->can_improve_skill("staff")
           && me->can_improve_skill("cuff"))
	{  
                write(HIC "你在锄草过程中对于杖法及拳法有些体会。\n" NOR);
                me->improve_skill("staff",(query("int", me)/6));
                me->improve_skill("cuff",(query("int", me)/6));
        }
        return 1;
}
