#include <ansi.h>
inherit ROOM;

void create()
{
    	set("short", "菜地");
        set("long", @LONG
这里是块菜地，菜地旁有几口大缸，里面盛满了水，可是
菜地看起来都干裂了，几棵菜蔫蔫的长着，看样子是因为缺水
太多的缘故吧。
LONG);
        set("no_fight", 1);
        set("exits", ([
            	"east" : __DIR__"guofu_houyuan3",
        ]));
        set("objects", ([
           	__DIR__"npc/guanjia6" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_jiao", "jiao");
}

int do_jiao(string arg)
{      
        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/浇完了", me) )
            	return notify_fail(CYN "菜园管事嚷嚷道：喂喂喂，让你去覆命，还留"
                                   "在这里干嘛？\n" NOR);

        if( query_temp("job_name", me) != "浇菜地" )
            	return notify_fail(CYN "菜园管事对你喝道：没事你瞎折腾什么？\n" NOR);

        if (me->is_busy())
		return notify_fail("你现在正忙着呢！\n");

        if (me->is_fighting())
		return notify_fail("你正在战斗中，无法专心干活！\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("id", weapon) != "shui piao" )
                return notify_fail(CYN "菜园管事讥笑道：你想用什么来舀水浇呀，用"
                                   "手吗？\n" NOR);

        if (! arg || arg != "shui" )
		return notify_fail("你要浇什么？\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
              	message_vision(HIR "\n$N" HIR "弯腰到大缸里舀水，结果一失足栽进了缸"
                               "里。\n" NOR, me);
              set("water", 600, 	me);
              	me->unconcious();
              	return 1;
        }

        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);
        me->start_busy(1 + random(2));

        if (! (int)me->query_condition("wuguan_job")
            && query_temp("mark/浇", me)>10+(random(10) )
           && present("caiyuan guanshi", environment(me)))
	{
                set_temp("mark/浇完了", 1, me);
                message_vision(CYN "\n菜园管事对$N" CYN "说：干的不错，好了，你可"
                               "以去向耶律大爷覆命(" HIY "fuming" NOR + CYN ")了"
                               "。\n" NOR, me);
                return 1;
        }

        message_vision(HIG "$N" HIG "用瓢从缸里舀起水，在菜地里浇起水来。\n" NOR, me);
        addn_temp("mark/浇", 1, me);

        if ((int)me->query_skill("whip", 1) < 50
           && (int)me->query_skill("finger", 1) < 50
           && me->can_improve_skill("whip")
           && me->can_improve_skill("finger"))
	{
                write(HIC "你在浇水过程中对鞭法及指法有些体会。\n" NOR);
                me->improve_skill("whip",(query("int", me)/6));
                me->improve_skill("finger",(query("int", me)/6));
        }
        return 1;
}
