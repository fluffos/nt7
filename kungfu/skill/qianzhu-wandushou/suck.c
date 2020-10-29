#include <ansi.h>
inherit F_SSERVER;

string name() { return "练毒"; }

int perform(object me,object target)
{
        int sp, dp, temp;
        int my_skill, my_force, tg_age, skill_count, duli;

        if( query("no_fight", environment(me)) )
                return notify_fail("这里太嘈杂，你不能静下心来修炼。\n");

        if( !objectp(target)
         || query("host_id", target) != query("id", me) )
                return notify_fail("你要吸取什么毒虫的毒素？\n");

        if( query("age", target)<99 )
                return notify_fail("你看清楚点，那东西像是毒虫吗？\n");

        my_skill = (int)me->query_skill("qianzhu-wandushou", 1);
        my_force = (int)me->query_skill("xiuluo-yinshagong", 1);
        tg_age=query("age", target);

        if( my_skill < 100 )
                return notify_fail("你的千蛛万毒手火候太浅，不能用来吸取毒素！\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能修炼千蛛万毒手！\n");

        if( me->is_fighting() )
                return notify_fail("战斗中无法修炼千蛛万毒手！\n");

        if( me->is_busy() )
                return notify_fail("你正忙着呢！\n");

        if( target->is_fighting() || target->is_busy() )
                return notify_fail("毒虫正忙着呢，不能和你配合！\n");

        if( query_temp("wudu_suck", me) )
                return notify_fail("你正在修炼中！\n");

        if (! me->can_improve_skill("qianzhu-wandushou"))
                return notify_fail("你的实战经验不够，无法继续修炼千蛛万毒手！\n");

        if( my_skill < 130 && tg_age > 99 )
                return notify_fail(query("name", target)+"的毒力对你来说太强了，小心把小命送了！\n");

        if( my_skill < 160 && tg_age > 999 )
                return notify_fail(query("name", target)+"的毒力对你来说太强了，小心把小命送了！\n");

        if( my_skill > 140 && my_skill < 170 && tg_age < 999 )
                return notify_fail(query("name", target)+"的毒力对你来说已经太轻微了！\n");

        if( my_skill > 200 && tg_age < 9999 )
                return notify_fail(query("name", target)+"的毒力对你来说已经太轻微了！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力不够，不足以对抗毒气，别把小命送掉。\n");

        if( query("qi", target)<50 )
                return notify_fail(query("name", target)+"已经奄奄一息了，你"
                                    "无法从他体内吸取任何毒素！\n");

        if( query("qi", me)<200 )
                return notify_fail( "你快不行了，再练会送命的！\n");

        tell_object(me,RED"你小心翼翼的将手伸到"+query("name", target)+
                        RED "的面前，它张嘴就咬住了你的中指。你深吸一口\n气，"
                        "面上顿时罩着一股黑气，豆大的汗珠从额头滚了下来。你只"
                        "觉得"+query("name", target)+RED"的\n毒素自伤处"
                        "源源不绝地流了进来，随真气遍布全身。\n\n" NOR );

        target->receive_wound("qi", 5);

        if( tg_age < 999 )
        {
                duli = 3;
        }

        if( tg_age > 999 && tg_age < 9999)
        {
                duli = 5;
        }

        if( tg_age > 9999 )
        {
                duli = 7;
        }

        skill_count = duli * (10 + random((int)me->query_int()));
        me->improve_skill("qianzhu-wandushou", skill_count);
        me->improve_skill("poison", skill_count * 2 / 3);
        tell_object(me, HIC "你的「千蛛万毒手」和「基本毒技」进步了！\n" NOR);

        set_temp("wudu_suck", 1, me);
        call_out("del_wudusuck", 3, me, target);
/*
        switch( random(duli) )
        {
        case 0:
                temp=query("combat_exp", me);
                addn("combat_exp", temp/1000, target);

                if( query("combat_exp", target)>(temp*12/10) )
                            set("combat_exp", temp*12/10, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的经验提高到"+
                        chinese_number(query("combat_exp", target))+"点。\n"NOR);
                break;

        case 1:
                addn_temp("apply/attack", 1, target);

                if( query_temp("apply/attack", target)>300 )
                            set_temp("apply/attack", 300, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的攻击力提高到"+
                        chinese_number(query_temp("apply/attack", target))+"点。\n"NOR);
                break;

        case 2:
                addn_temp("apply/defense", 1, target);

                if( query_temp("apply/defense", target)>300 )
                            set_temp("apply/defense", 300, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的防御力提高到"+
                        chinese_number(query_temp("apply/defense", target))+"点。\n"NOR);
               break;

        case 3:
                addn_temp("apply/armor", 1, target);

                if( query_temp("apply/armor", target)>1500 )
                            set_temp("apply/armor", 1500, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的抗打击能力提高到"+
                        chinese_number(query_temp("apply/armor", target))+"点。\n"NOR);
                break;

        case 4:
                addn("max_qi", 10, target);

                if( query("max_qi", target)>20000 )
                            set("max_qi", 20000, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的生命力提高到"+
                        chinese_number(query("max_qi", target))+"点。\n"NOR);
                break;

        case 5:
                addn("max_jing", 10, target);

                if( query("max_jing", target)>20000 )
                            set("max_jing", 20000, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的精提高到"+
                        chinese_number(query("max_jing", target))+"点。\n"NOR);
                break;

        case 6:
                temp = (int)target->query_skill("dodge", 1);

                target->set_skill("dodge",temp+1);
                if((int)target->query_skill("dodge",1)>300)
                            target->set_skill("dodge",300);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的躲闪技能提高到"+
                        chinese_number((int)target->query_skill("dodge", 1)) +"级。\n"NOR );
        }
*/
        return 1;
}

void del_wudusuck(object me,object target)
{
        if( query_temp("wudu_suck", me) )
        {
                delete_temp("wudu_suck", me);
                tell_object(me, RED "\n只见它的肚子越涨越大，“吧嗒”一声，松"
                                "开口掉在了地上。"+query("name", target)+RED
                                "吸饱了鲜\n血，身上透出一层宝光，身子顿时涨大"
                                "了许多！\n\n\n" NOR,);
                me->receive_damage("qi", 20);
        }

        if (objectp(target)) set_temp("nopoison", 0, target);
}