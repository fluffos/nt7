#include <ansi.h>
inherit ROOM;

void create()
{
    	set("short", "柴房");
    	set("long", @LONG
这间屋里叮叮哐哐的，你进屋内仔细一看，几个人在劈柴
火，屋子特别大，屋子一边堆满了已经锯短的木头，但另一边
劈好的柴火却没有多少。
LONG);
        set("no_fight", 1);
        set("exits", ([
              	"west" : __DIR__"guofu_houyuan",
        ]));
        set("objects", ([
           	__DIR__"npc/guanjia1" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_pi", "pi");

}

int do_pi(string arg)
{

        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/劈完了", me) )
            	return notify_fail(CYN "柴房管事嚷嚷道：喂喂喂，让你去覆命，还留"
                                   "在这里干嘛？\n" NOR);

        if( query_temp("job_name", me) != "劈柴" )
            	return notify_fail(CYN "柴房管事对你喝道：没事你瞎折腾什么？\n" NOR);

        if (me->is_busy())
		return notify_fail("你现在正忙着呢！\n");

        if (me->is_fighting())
		return notify_fail("你正在战斗中，无法专心干活！\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("id", weapon) != "chai dao" )
                return notify_fail(CYN "柴房管事讥笑道：你准备用什么来劈柴呀，用"
                                   "手吗？\n" NOR);

        if (! arg || arg != "chai" )
		return notify_fail("你要劈什么？\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
                message_vision(HIR "\n$N" HIR "手一歪，一不小心柴刀竟然劈在自己"
                               "的腿上。\n" NOR, me);
                me->unconcious();
                return 1;
        }
        
        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);       
        me->start_busy(1 + random(2));

        if (! (int)me->query_condition("wuguan_job")
            && query_temp("mark/劈", me)>10+random(10 )
           && present("chaifang guanshi", environment(me)))
	{
                set_temp("mark/劈完了", 1, me);
                message_vision(CYN "\n柴房管事对$N" CYN "说：干的不错，好了，你可"
                               "以去向耶律大爷覆命(" HIY "fuming" NOR + CYN ")了"
                               "。\n" NOR, me);
                return 1;
        }

        message_vision(HIW "$N" HIW "摆正一块木头，一刀劈去，将木头劈为两片。\n" NOR, me);
        addn_temp("mark/劈", 1, me);

        if ((int)me->query_skill("blade", 1) < 50
           && (int)me->query_skill("strike", 1) < 50
           && me->can_improve_skill("blade")
           && me->can_improve_skill("strike"))
	{  
                write(HIC "你在劈柴过程中对于刀法及掌法有些体会。\n" NOR);
                me->improve_skill("blade",(query("int", me)/6));
                me->improve_skill("strike",(query("int", me)/6));
        }
        return 1;
}
