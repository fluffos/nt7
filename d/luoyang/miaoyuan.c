#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "苗园");
        set("long", @LONG
这里是苗铺主人用来养花的花棚，一个大大的温室，将各种样的奇花
异草呵护在其中，当然花丛中更多的是牡丹，只见那牡丹红的，白的，黑
的，紫的，黄的，各色各样，争奇斗艳，娇艳欲滴，不愧和白马寺一起成
为了洛阳的象征。你也可以在这里种花。
LONG);
        set("outdoors", "luoyang");
        set("no_fight",1);
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"miaopu",
        ]));

	set("coor/x", -6970);
	set("coor/y", 2110);
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
        object /*ob,*/ me;
        me = this_player();

        if( !query_temp("zhonghua", me) )
        {
                tell_object(me, "你种子都没有，还想种花？\n"); 
                return 1;
        }

        if( query_temp("jiaoshui", me) == 1 )
        {
                tell_object(me, "你已经完成了培育这道程序，现在可以浇水"
                                HIY "(jiaoshui)" NOR "。\n");
                return 1;
        }

        if( query("combat_exp", me)<8000 )
        {
                tell_object(me, "你的经验尚浅，还是先到处多走动走动吧。\n");
                return 1;
        }

        if( query("combat_exp", me)>30000 )
        {
                tell_object(me, "以你的身份大概不适合种花了吧。\n");
                return 1;
        }

        if( query("jing", me)<70 )
        {
                tell_object(me, "你已经很疲惫了，休息一下再接着种吧。\n");
                return 1;
        }

        message_vision(HIC "$N" HIC "把土坑周围好好地修整了一下，使土壤更加"
                       "适合花的生长。\n" NOR, me); 
        set_temp("peiyu", 1, me);
        set_temp("jiaoshui", 1, me);
        me->start_busy(1 + random(3));
        return 1;
}

int do_jiaoshui()
{
        object me, ob;
        int exp, pot;

        me = this_player();

        if( query("jing", me)<70 )
        {
                tell_object(me, "你已经很疲惫了，休息一下再接着种吧。\n");
                return 1;
        }
        if (me->is_busy())
        {
                tell_object(me, "你正忙着呢，别着急。\n");
                return 1;
        }
        if( !query_temp("peiyu", me) == 1 )
        {
                tell_object(me, "你没事干浇什么水啊！\n");
                return 1;
        }
        if( query_temp("peiyu", me) == 2 )
        {
                if (random(14) < 4)
                {
                        switch (random(5))
                        {
                                case 1 : ob = new("/clone/megazine/obj/hmeigui"); break;
                                case 2 : ob = new("/d/changan/npc/obj/zi-luolan"); break;
                                case 3 : ob = new("/d/changan/npc/obj/bai-chahua"); break;
                                case 4 : ob = new("/d/changan/npc/obj/huang-meigui"); break;
                                case 0 : ob = new("/d/changan/npc/obj/lan-tiane"); break;
                        }

                        if (random(15) == 1)
                        {
                                if (random(10000) == 8)
                                {
                                        ob = new("/d/shenlong/obj/hua4");
                                        message_vision(HIY "$N" HIY "种出了一朵翡翠兰。\n"
                                                       NOR, me);
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
                                message_vision(HIY "$N" HIY "种出了一朵无名花。\n" NOR,me);
                                return 1;
                        }
                        message_vision(HIC "$N" HIC "十分小心的给小坑里浇了一些"
                                       "水，突然一朵"+query("name", ob)+HIC
                                       "从坑里冒了出来。\n" NOR, me);   
                        message_vision(HIY "$N" HIY "把它摘了下来，拿在手里。\n" NOR, me);
                        ob->move(me, 1);
                        delete_temp("jiaoshui", me);
                        delete_temp("peiyu", me);
                        delete_temp("zhonghua", me);

                        exp = 10 + random(10);
                        pot = 2 + random(3);

                        if( query("potential", me)>me->query_potential_limit() )
                                pot = 1;

                        addn("combat_exp", exp, me);
                        me->improve_potential(pot);

                        tell_object(me, HIC "通过这次训练，你获得了" + chinese_number(exp)
                                        + "点经验和" + chinese_number(pot) + "点潜能。\n"
                                        NOR);
                        return 1; 
                }
                message_vision(HIR "$N" HIR "笨手笨脚的拿起水壶给小坑里浇水，结"
                               "果水洒的太多把花给毁了。\n", me); 
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
                message_vision(HIC "$N" HIC "拿起水壶给小坑浇了一些水。\n" NOR, me); 
                addn("jing", -70, me);
                set_temp("peiyu", 2, me);
                me->start_busy(1 + random(2)); 
                return 1;
        }
}