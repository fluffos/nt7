#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大雄宝殿");
        set("long", @LONG
这里是少林寺的大雄宝殿。正中供奉着如来三宝，左右各是文殊、
普贤菩萨。一群青衣小和尚们正在佛像前的地上诵经。缕缕香烟与梵
唱交错在一起，仰视佛祖拈花浅笑的面容，令人顿时生起几分脱俗之
感。身边经常有一队队僧人鱼贯而入，看他们手持戒刀，似乎是巡寺
的僧人。
LONG );
        set("exits", ([
                "southdown" : __DIR__"guangchang2",
        ]));
        set("valid_startroom",1);
        set("book_count",1);
        set("objects",([
                CLASS_D("shaolin") + "/dao-zheng" : 1,
                CLASS_D("shaolin") + "/first" : 1,
                __DIR__"npc/xiang-ke" : 1,
        ]));
        setup();
        "/clone/board/bonze_b"->foo();
}

void init()
{
        set_temp("ketou_times", 50, this_player());
        add_action("do_ketou", "ketou");
}

int do_ketou()
{
        object me, ob;

        me = this_player();

        if( query("jing", me)<30 )
                return notify_fail("突然你感到一阵恍惚，看来再难以继续磕头。\n");

        if( query_temp("ketou_times", me) == 0 )
        {
                message_vision(HIR "\n$N" HIR "磕头磕得晕了过去。\n" NOR, me);
                set_temp("ketou_times", random(50), me);
                me->unconcious();
                return 1;
        }

        addn_temp("ketou_times", -1, me);

        message_vision(CYN "$N" CYN "虔诚地跪下来，在如来佛祖面"
                       "前磕头。\n" NOR, me);

        if (random(100) == 37 &&
            ! present("silk", me) &&
            query("book_count") >= 1)
        {
                addn("book_count", -1);
                ob=new("/clone/book/book-silk");
                ob->move("/d/shaolin/dxbdian");
                tell_object(me, HIM "\n突然你面前「啪」地一声掉"
                                "下一束羊皮线穿起来的薄绢。\n" NOR);
        }

        if ((int)me->query_skill("force", 1) >= 30 &&
            (int)me->query_skill("force", 1) <= 100 &&
            present("silk", me) )
        {
                me->receive_damage("jing", 20);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force",1+random(query("con", me)));
                if (random(5) == 0)
                tell_object(me, HIY "冥冥之中，你似乎觉得佛祖在"
                                "点拨你在内功方面的疑难。\n" NOR);
        }
        return 1;

}

int valid_leave(object me, string dir)
{
        if( query_temp("ketou_times", me) >= 0)delete_temp("ketou_times", me);

        return ::valid_leave();
}
