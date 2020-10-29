#include <ansi.h>
inherit ROOM;

void create()
{
    	set("short", "木房");
    	set("long", @LONG
一进屋，你就被巨大的轰鸣声吵住了，这里堆了好多长的
木头，准备要做柴火用的，但是在送去柴房前先得把长木头锯
短成一截截的。你看见几个人在费力的锯着。
LONG);
        set("no_fight", 1);
        set("exits", ([
             	"west" : __DIR__"guofu_houyuan2",
        ]) );
        set("objects", ([
           	__DIR__"npc/guanjia2" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_pi", "ju");
}

int do_pi(string arg)
{ 
        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/锯完了", me) )
            	return notify_fail(CYN "木房管事嚷嚷道：喂喂喂，让你去覆命，还留"
                                   "在这里干嘛？\n" NOR);

        if( query_temp("job_name", me) != "锯木头" )
            	return notify_fail(CYN "木房管事对你喝道：没事你瞎折腾什么？\n" NOR);

        if (me->is_busy())
		return notify_fail("你现在正忙着呢。\n");

        if (me->is_fighting())
		return notify_fail("你正在战斗中，无法专心干活！\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("id", weapon) != "ju zi" )
                return notify_fail(CYN "木房管事讥笑道：你想用什么来锯木头，用手"
                                   "掰吗？\n" NOR);

        if (! arg || arg != "mutou")
		return notify_fail("你要锯什么？\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
        	message_vision(HIR "\n突然间木头竟然断了，弹起的半截木头正砸在$N"
                               HIR "头上。\n", me);
                me->unconcious();
                return 1;
        }

        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);
        me->start_busy(1 + random(2));

        if (! (int)me->query_condition("wuguan_job")
            && query_temp("mark/锯", me)>10+random(10 )
           && present("mufang guanshi", environment(me)))
	{
                set_temp("mark/锯完了", 1, me);
                message_vision(CYN "\n木房管事对$N" CYN "说：干的不错，好了，你可"
                               "以去向耶律大爷覆命(" HIY "fuming" NOR + CYN ")了"
                               "。\n" NOR, me);
                return 1;
        }

        message_vision(HIM "$N" HIM "摆正一根木头，慢慢锯了起来。\n" NOR, me);
        addn_temp("mark/锯", 1, me);

        if ((int)me->query_skill("hand", 1) < 50
           && (int)me->query_skill("sword", 1) < 50
           && me->can_improve_skill("hand")
           && me->can_improve_skill("sword"))
	{
                write(HIC "你在锯木头的推拉中对手法及剑法有些体会。\n" NOR);
                me->improve_skill("hand",(query("int", me)/6));
                me->improve_skill("sword",(query("int", me)/6));
        }
        return 1;
}
