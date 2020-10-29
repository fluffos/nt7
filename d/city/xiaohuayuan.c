// xiaohuayuan.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short",HIG "小花园" NOR);
        set("long", @LONG
这里一个小花园，这里的肥沃土壤十分适合各种花的生长，特别
地一些十分名贵的花种，这里也可生长。你可以在这里种花(zhonghua)。
花店里可以买到花的种子。
LONG
        );

        set("outdoors", "yangzhou");
        set("region", "yangzhou");
        set("exits", ([
                "south"  : __DIR__"huadian",
        ]));

        set("no_fight", 1);
	set("coor/x", 30);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_jiaoshui", "jiaoshui");
        add_action("do_peiyu", "peiyu");
}

int do_peiyu()
{
        object /*ob,*/me;
        me = this_player();

        if( !query_temp("zhonghua", me) )
        {
                tell_object(me, HIR "你种子都没有，还想种花？\n" NOR);
                return 1;
        }

        if( query_temp("jiaoshui", me) == 1 )
        {
                tell_object(me,HIR "你已经完成了培育这道程序，现在可以浇水(jiaoshui)。\n" NOR);
                return 1;
        }

        if( query("combat_exp", me)>150000 || query("combat_exp", me)<10000 )
        {
                tell_object(me,HIR "以你的身份大概不适合在小花园种花吧！\n" NOR);
                return 1;
        }

        if( query("jing", me)<70 )
        {
                message_vision(HIR "$N一幅气喘吁吁的样子，怎么能种花呢！\n" NOR,me);
                return 1;
        }

        message_vision("$N把土坑周围好好地修整了一下，使土壤更加适合花的生长。\n", me);
        set_temp("peiyu", 1, me);
        set_temp("jiaoshui", 1, me);
        me->start_busy(1 + random(3));
        return 1;
}

int do_jiaoshui()
{
        object me,ob;

        me = this_player();

        if( query("jing", me)<70 )
        {
                tell_object(me,HIR "你气色不好，还是休息休息吧。\n" NOR);
                return 1;
        }

        if (me->is_busy())
        {
                tell_object(me, HIR "你正忙着呢，别着急。\n" NOR);
                return 1;
        }

        if( !query_temp("peiyu", me) == 1 )
        {
                tell_object(me,HIR "你是来捣乱吗？没事干浇什么水啊！\n" NOR);
                return 1;
        }

        if( query_temp("peiyu", me) == 2 )
        {
                if (random(14) == 1)
                {
                        switch (random(5))
                        {
                                case 1 : ob = new("/d/changan/npc/obj/hmeigui"); break;
                                case 2 : ob = new("/d/changan/npc/obj/zi-luolan"); break;
                                case 3 : ob = new("/d/changan/npc/obj/bai-chahua"); break;
                                case 4 : ob = new("/d/changan/npc/obj/huang-meigui"); break;
                                case 0 : ob = new("/d/changan/npc/obj/lan-tiane"); break;
                        }

                        if (random(15) == 1)
                        {
                                if (random(10000) == 1)
                                {
                                        ob = new("/d/shenlong/obj/hua4");
                                        CHANNEL_D->do_channel(this_object(), "rumor",
                                                              query("name", me)+"从小花园种出一朵翡翠兰。");
                                        message_vision(HIR "$N" HIR "得到了翡翠兰。\n" NOR,me);
                                        ob->move(me, 1);
                                        delete_temp("jiaoshui", me);
                                        delete_temp("zhonghua", me);
                                        delete_temp("peiyu", me);
                                        addn("combat_exp", 500, me);
                                        me->improve_potential(100 + random(100));
                                        return 1;
                                }

                                ob = new("/d/shenlong/obj/hua2");
                                addn("combat_exp", 20+random(10), me);
                                me->improve_potential(20 + random(10));
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                                      query("name", me)+"从小花园种出一朵无名花。");
                                return 1;
                        }

                        message_vision(HIC "$N" HIC "十分小心的给小坑里浇了一些水，突然" +
                                       query("long", ob)+"从坑里冒了出来。\n"NOR,me);
                        message_vision(HIR "$N" HIR "把它摘了下来，拿在手里。\n" NOR,me);
                        ob->move(me, 1);
                        delete_temp("jiaoshui", me);
                        delete_temp("peiyu", me);
                        delete_temp("zhonghua", me);
                        addn("combat_exp", 20+random(10), me);
                        me->improve_potential(10 + random(10));
                        return 1;
                }

                message_vision(HIR "$N" HIR "笨手笨脚的拿起水壶给小坑里浇水，结果水"
                               "洒的太多把花给毁了。\n",me);
                delete_temp("jiaoshui", me);
                delete_temp("zhonghua", me);
                delete_temp("peiyu", me);
                addn("jing", -50, me);
                addn("combat_exp", 3, me);
                me->improve_potential(2);
                return 1;
        }

        if( query_temp("jiaoshui", me) == 1 )
        {
                message_vision("$N拿起水壶给小坑浇了一些水。\n",me);
                addn("jing", -70, me);
                set_temp("peiyu", 2, me);
                me->start_busy(1 + random(2));
                return 1;
        }
}