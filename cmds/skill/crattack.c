// crattack.c

#include <ansi.h>

inherit F_CLEAN_UP;

void hate_attack(object me, object target);
void shout_message(string msg);

int main(object me, string arg)
{
        object target;
        int craze;
        string msg;
        int attack;
        int damage;

        if( query("no_fight", environment(me)) )
                return notify_fail("这里不能战斗。\n");

        if (me->is_busy())
                return notify_fail("( 你上一个动作还没有完成，不能施用愤怒一击。)\n");

        if (! arg)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        } else
                target = present(arg, environment(me));

        if (! target || ! me->is_fighting(target))
                return notify_fail("愤怒一击只能对战斗中的对手使用。\n");

        if (! living(target))
                return notify_fail("人家都已经这个样子了，你"
                                   "还用得着这么费力气么？\n");

        if ((craze = me->query_craze()) < 500)
                return notify_fail("你现在心平气和，谈不上什么愤怒。\n");

        if (craze < 1000)
                return notify_fail("你现在还不够愤怒，无法施展愤怒必杀绝技。\n");

        if( query("qi", me)*100/query("max_qi", me)<50 )
                return notify_fail("你现在体力太虚弱，无法施展愤怒必杀绝技。\n");

        if( query("qi", me)<200 )
                return notify_fail("你现在气息不够强，难以施展爆烈的愤怒必杀绝技。\n");

        me->receive_damage("qi",random(query("max_qi", me)/4));

        if (me->is_most_craze())
        {
                int second;

                if( me->is_hating(query("id", target)) )
                {
                        hate_attack(me, target);
                        return 1;
                }

                if( query("gender", me) == "女性" )
                        msg = HIR "$N" HIR "眼神犹如利刃，冷冷的扫过$n"
                              HIR "，让他不禁打了个寒战。只见$P低声喝"
                              "道：“" + RANK_D->query_rude(target) +
                              "，你去死吧！”\n" NOR;
                else
                        msg = HIR "$N" HIR "咆哮如雷，有如疯狂，对$n"
                              HIR "狂喝道：“" + RANK_D->query_rude(target) +
                              "，你还不快快纳命来？”\n" NOR;
                message_combatd(msg, me, target);

                // first attack
                attack = craze / 50;
                damage = craze / 20;
                if (attack > me->query_skill("force") + 10)
                        attack = me->query_skill("force") + 10;
                if (damage > me->query_str() * 8)
                        damage = me->query_str() * 8;
                addn_temp("apply/attack", attack, me);
                addn_temp("apply/damage", damage, me);
                addn_temp("apply/unarmed_damage", damage, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                msg = HIR "\n$N" HIR "一招攻出，竟不罢休，随即舍身扑上又是一招！\n" NOR;
                if (! me->is_fighting(target) && living(target))
                {
                        msg += HIY "$n" HIY "见$N" HIY "舍生忘死，全然"
                               "不顾自己已经认输做罢，不由大吃一惊，慌"
                               "忙抵挡。\n" NOR;
                }
                message_combatd(msg, me, target);

                // second attack
                second=query("str", me);
                attack += second;
                damage += second;
                addn_temp("apply/attack", second, me);
                addn_temp("apply/damage", second, me);
                addn_temp("apply/unarmed_damage", second, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                addn_temp("apply/attack", -attack, me);
                addn_temp("apply/damage", -damage, me);
                addn_temp("apply/unarmed_damage", -damage, me);
                me->cost_craze(craze / 4 + random(craze / 2));
                me->start_busy(2);
                return 1;
        }

        if( query("gender", me) == "女性" )
                msg = HIR "$N" HIR "一声娇嗔，遥指$n" HIR "喝道：“" +
                      RANK_D->query_rude(target) + "，看招！”\n" NOR;
        else
                msg = HIR "$N" HIR "一声大吼，如同晴空霹雳，对$n" HIR
                      HIR "暴喝道：“" + RANK_D->query_rude(target) +
                      "，你还不快快受死？”\n" NOR;

        message_combatd(msg, me, target);
        attack = craze / 60;
        damage = craze / 30;
        if (attack > me->query_skill("force") + 10)
                attack = me->query_skill("force") + 10;
        if (damage > me->query_str() * 8)
                damage = me->query_str() * 8;

        addn_temp("apply/attack", attack, me);
        addn_temp("apply/damage", damage, me);
        addn_temp("apply/uanrmed_damage", damage, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        addn_temp("apply/attack", -attack, me);
        addn_temp("apply/damage", -damage, me);
        addn_temp("apply/uanrmed_damage", -damage, me);
        me->cost_craze(craze / 4 + random(craze / 2));
        me->start_busy(1);
        return 1;
}

void hate_attack(object me, object target)
{
        int craze;
        int attack;
        int damage;

        craze = me->query_craze();
        attack = craze / 40;
        damage = craze / 18;
        if (attack > me->query_skill("force") + 10)
                attack = me->query_skill("force") + 10;
        if (damage > me->query_str() * 8)
                damage = me->query_str() * 8;

        if (random(2))
                shout_message(me->name(1) + "对" + target->name() + HIR "厉声喝道：" +
                              RANK_D->query_rude(target) + "，今日" +
                              RANK_D->query_self(me) + "要你血债血偿！接招！");
        else
                shout_message(me->name(1) + "对" + target->name() + HIR "怒喝道：" +
                              RANK_D->query_rude(target) + "，自古杀人偿命！" +
                              "今天我就要你的狗命！来吧！");

        me->want_kill(target);
        me->kill_ob(target);
        addn_temp("apply/attack", attack, me);
        addn_temp("apply/damage", damage, me);
        addn_temp("apply/unarmed_damage", damage, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：" + target->name() +
                       "，你再看我上一招！\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：" + RANK_D->query_rude(target) +
                      "，你再看我下一招！\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：好！你再接我左一招！\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：休走！你再接我右一招！\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：看清楚我这当中穿心一招！\n" NOR, me);
        damage+=query("str", me);
        attack+=query("str", me);
        addn_temp("apply/attack",query("str",  me), me);
        addn_temp("apply/damage",query("str",  me), me);
        addn_temp("apply/unarmed_damage",query("str",  me), me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：还没完，看我最后一招！！！\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        addn_temp("apply/attack", -attack, me);
        addn_temp("apply/damage", -damage, me);
        addn_temp("apply/unarmed_damage", -damage, me);

        if( query("qi", target) >= 0 && 
            query("jing", target) >= 0 )
        {
                if (random(2))
                        shout_message(target->name(1) + "呵呵大笑道：这位" +
                                      RANK_D->query_respect(me) + "，你好"
                                      "厉害啊！不过又岂能奈我何？");
                else
                        shout_message(target->name(1) + "哈哈大笑道：你的" +
                                      "来势好凶啊，可惜本事太差，也罢，也罢，哈哈！");

                tell_object(me, HIR "你目眦俱裂，心中燃起的重重怒火，丝毫没有减弱。\n" NOR);
        } else
        {
                if (random(2))
                        shout_message(target->name(1) + "惨叫道：我的天！");
                else
                        shout_message(target->name(1) + "惨声呼号：天啊，报应来得好快！");

                me->cost_craze(craze);
                me->craze_defeated(query("id", target));
                tell_object(me, HIC "你长舒一口气，心情平静了许多。\n" NOR);
        }
        me->start_busy(2);
}

void shout_message(string msg)
{
        message("channel:chat", HIR "【报仇" HIW "雪" HIR "恨】" +
                                msg + "\n" NOR,
                                all_interactive());
}

int help (object me)
{
        write(@HELP
指令格式：crattack <对象>

如果你处于愤怒状态，就可以利用自己的愤怒充分发挥自己的能力，
予以正在交手的对手沉重的打击。当然你还得使用刚猛或是杀伤力高
的武功才能收到良好的效果。你的怒气达到了顶峰的时候，威力更是
不同凡响。

如果你被人打晕或是杀死，则打晕你和杀死你的人将成为你憎恨的对
象，当你愤怒达到顶级的时候，就可以对你憎恨的对象施展出索命必
杀绝技，只能对一个憎恨的对象运用一次。

HELP );
        return 1;
}