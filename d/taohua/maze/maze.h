// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <localtime.h>

int check_count(object me, int count)
{
        int age, tmp1, tmp2, tmp, lvl, qmwx, bonus;
        mixed *local;

        age=query("age", me);
        local=localtime((query("birthday", me)-14*365*24*60)*60);
        tmp1 = (local[LT_YEAR] % 10 + local[LT_YEAR] % 12 + local[LT_MON] + local[LT_MDAY]) % 8;
        tmp2 = (((local[LT_HOUR] + 1) % 24) / 2) % 8;
        tmp = tmp1 * 8 + tmp2;
        qmwx = me->query_skill("qimen-wuxing", 1);
        lvl = 1 + random(qmwx) / 20;

        if (tmp == count)
        {
                if( query_temp("taohua/count", me) == 2080 )
                {
                        tell_object(me,HIW"\n\n
四周景物突然变得模糊起来，你觉得头脑一阵晕眩......
你定了定神，发现自己成功了！
\n\n"NOR);
                        /*
                        tell_object(me,
                                HIR "四周景物突然变得模糊起来，你觉得头脑一阵晕眩......你在一阵烟雾中消失了。\n\n" NOR);
                        */
                        if( !query("taohua_maze", me) )
                        {
                                if ( qmwx < 1000) bonus = 10000;
                                else bonus = qmwx*10;
                                addn("combat_exp", bonus, me);
                                addn("potential", bonus/2, me);
                                addn("int", 1, me);
                                set("taohua_maze", age, me);
                                delete_temp("taohua/count", me);
                                tell_object(me,sprintf(HIY"你获得了%d点经验、%d点潜能，1点先天悟性！\n"NOR,
                                                bonus,
                                                bonus*2));
                                // me->move("/d/taohua/xiangzhong");
                                me->move("/d/taohua/mudi");
                        }
                } else
                {
                        tell_object(me,
                                HIW "你脚下一虚，不由自主的向下飞坠......你的意识渐渐模糊起来......\n\n" NOR);
                        if (userp(me))
                        me->unconcious();
                        delete_temp("taohua/count", me);
                        me->move("/d/taohua/enter_m");
                }
        } else
        if( query_temp("/taohua/count", me)>2100 )
        {
                tell_object(me,
                        HIW "忽见得一阵狂风挂来，天空中乌云密布，一阵阴冷的浓雾瞬间把你裹住......\n\n" NOR);
                if (userp(me))
                me->unconcious();
                delete_temp("taohua/count", me);
                me->move("/d/taohua/enter_m");
        }

        return 1;
}

void remove_effect(object me, int level)
{
        addn_temp("apply/int", -level, me);
        tell_object(me, HIB "你心中一动，脑海中空空荡荡，似乎有什麽东西正离你而去。\n" NOR);
}
