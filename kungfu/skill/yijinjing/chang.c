// This program is a part of NT MudLIB
// chang.c 梵唱

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, j, skill, damage;

        skill = me->query_skill("force");
        if( query("neili", me) < skill*3 )
                return notify_fail("你的内力不够。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为不够。\n");

        if( query("shen", me)<10000 )
                return notify_fail("佛门梵唱需要高深的定力，你气色不正，难以施展！\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("在这里不能攻击他人。\n");

        if( me->query_skill("buddhism", 1) < 100 )
                return notify_fail("你连禅宗心法还未完全领悟，何以施展佛门梵唱绝学？\n");

        if( me->query_skill("yijinjing", 1) < 100 )
                return notify_fail("你连易筋经还未完全领悟，何以施展佛门梵唱绝学？\n");

        addn("neili", -skill/2, me);

        message_combatd(YEL"\n$N深深地吸一口气，面露宝象，一声"BLINK+HIY"阿…弥…陀…佛…"YEL"梵音回旋环绕，所有人都为之一震！\n\n" NOR, me);

        if( intp(j=query_temp("yueyin", me) )
        && me->query_skill("yijinjing", 1) > 200
        && me->query_skill("buddhism", 1) > 200 )
        {
                addn_temp("apply/dex", j, me);
                addn_temp("apply/defense", j*2, me);
                me->clear_condition("no_perform");
                delete_temp("yueyin", me);
                message_combatd(HIW"$N心情於瞬息之间接连数变，恢复了明智！\n\n"NOR, me);
        }

        ob = all_inventory(environment(me));

        for(i=0; i<sizeof(ob); i++) {
                if( !ob[i]->is_character() || !living(ob[i]) || ob[i]==me ) continue;
                if( skill < ob[i]->query_skill("force")/2 ) continue;
                if( intp(j=query_temp("yueyin", ob[i]) )
                && me->query_skill("yijinjing", 1) > 200
                && me->query_skill("buddhism", 1) > 200 ){
                        addn_temp("apply/dex", j, ob[i]);
                        addn_temp("apply/defense", j*2, ob[i]);
                        ob[i]->clear_condition("no_perform");
                        delete_temp("yueyin", ob[i]);
                        tell_object(ob[i], HIW"你心情於瞬息之间接连数变，恢复了明智！\n\n"NOR);
                        continue;
                }

                if( ob[i]->is_fighting() && !ob[i]->is_killing()){
                        if( query("shen", ob[i])>0){
                                ob[i]->remove_all_enemy();
                                message_vision("\n$N受到$n感招，身行向后一跃，跳出战圈不打了。\n", ob[i], me);
                                continue;
                        }
                        else if( query("shen", ob[i])>-10000 && query("combat_exp", me)>query("combat_exp", ob[i])){
                                ob[i]->remove_all_enemy();
                                addn("shen", skill*10, ob[i]);
                                message_vision("\n$N全身一震，脸上邪气稍减，跳出战圈不打了。\n", ob[i], me);
                                continue;
                        }
                        else if( query("combat_exp", me)>query("combat_exp", ob[i])*2){
                                ob[i]->remove_all_enemy();
                                message_vision("\n$N向后一跳，哈哈道：$n多心了，我们不过切磋切磋罢了。\n", ob[i], me);
                                continue;
                        }
                }

                damage = skill * 2;
                if( random(skill)>ob[i]->query_skill("force")/2 && query("shen", ob[i])<0){
                        ob[i]->receive_damage("jing", damage/2, me);
                        if( query("jing", ob[i])<10)set("jing", 10, ob[i]);
                        addn("neili", -damage, ob[i]);
                        if( query("neili", ob[i])<20)set("neili", 20, ob[i]);
                        tell_object(ob[i], "你觉得心神一震，全身出了一身的冷汗！\n");
                }
                if( ob[i]->is_killing(query("id", me))){
                        if( random(2) == 1 )
                                ob[i]->apply_condition("no_perform", 2+random(2)+ob[i]->query_condition("no_perform"));
                        else    ob[i]->apply_condition("no_exert", 2+ob[i]->query_condition("no_exert"));
                        tell_object(ob[i], "你一惊，总觉得这梵唱有一股说不出的压迫感，使你感到很不舒服！\n");
                        continue;
                }

                if( userp(ob[i]) && query("shen", ob[i])<0 && random(3) == 1){
                        message_vision("$N大喝一声：快闭嘴！惹得"+RANK_D->query_self_rude(ob[i])+"火起！\n", ob[i]);
                        COMBAT_D->do_attack(ob[i],me,query_temp("weapon", ob[i]),1);
                }

        }
        me->start_busy(1);
        return 1;
}

int help(object me)
{
        write(HIY"\n易筋经之「金刚梵唱」："NOR"\n");
        write(@HELP
        金刚，坚利之意，历百劫千生，流转六道，而觉性不坏。即以金刚之坚，喻
        般若体；以金刚之利，喻般若用。梵唱乃是将一口真气以祥合之意唱出，内
        夹伏魔神功，能抗拒心魔，清心明志，使人悬崖勒马。

        要求：  易筋经等级 100 以上；
                易筋经等级 100 以上；
                正气 10000 以上；
                最大内力 1500 以上；
                内力为内功等级三倍以上。
HELP
        );
        return 1;
}