// Code of JHSH
// didao.h 
// zhangchi 7/00

#include <ansi.h>

int get_room(string);
int do_dig(string);

void reset()
{
        ::reset();
        
}

int get_room(string dir)
{
        object center;
        int num;

        if (!(center=find_object("/d/mingjiao/mj_center.c")))
                center=load_object("/d/mingjiao/mj_center.c");

        num=query("didao/"+dir, center);

        return num;
}

int do_dig(string dir)
{
        object center;
        object me=this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢！\n");

        if (!dir || dir!=query("valid_dig"))
                return notify_fail("你要往哪挖？\n");

        if (!present("tie qiao",me))
                return notify_fail("你没有趁手的工具。\n");

        if( !query("mingjiao/job", me) || query("mingjiao/job", me) != "tu_didao" )
                return notify_fail("你并没有挖地道的工作。\n");

        if( query_temp("didao_done", me) )
                return notify_fail("你已经完成任务了，赶快回去复命吧！\n");

        if (query("exits/"+dir))
                return notify_fail("这段地道已经挖通了。\n");

        if (get_room(dir) >= 5)
                return notify_fail("你怎么挖也挖不动了。\n");

        if( query("jing", me)<50 || query("qi", me)<30 )
                return notify_fail("你已经精疲力竭了。\n");

        message_vision("$N挥动铁锹，朝前使劲地挖着。\n",me);
        addn("jing", -20, me);
        addn("qi", -30, me);
        addn_temp("wa_times", 1, me);
        me->start_busy(3);
        if( query_temp("wa_times", me)>10+random(10) )
        {
                tell_object(me,HIG"密道终于又向前挖进了一步！\n"NOR);
                delete_temp("wa_times", me);
                set_temp("didao_done", 1, me);
                addn("improved",1);
                if (query("improved") >= 5)
                {
                        if (!(center=find_object("/d/mingjiao/mj_center.c")))
                                center=load_object("/d/mingjiao/mj_center.c");
                        addn("didao/"+dir, 1, center);
                        tell_object(me,HIG"恭喜！你又挖通了一段地道。\n"NOR);
                        addn("combat_exp", 200, me);
                        tell_object(me,HIG"你的经验涨了200点！\n"NOR);
                        load_object(__FILE__);
                }
        }

        return 1;
}