// jiujian_qi_damage.c 独孤九剑破气式伤势


#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        int t, level, hm_stat, lj_stat, status, flag;
        string skill;

        t = me->query_condition("jiujian_qi_damage");

        if( query_temp("dugu/force", me)){
                skill = me->query_skill_mapped("force");

                if ( skill != 0 ) {
                        message_vision("$N突然觉得一阵血气翻涌，丝毫用不上勉强提聚的"+to_chinese(skill)+"！\n", me);
                        me->map_skill("force");
                }
        }

        if( query_temp("dugu/reverse", me) || query_temp("dugu/hamapowerup", me)){
                if( query_temp("dugu/force", me) && skill == ""){
                        level = me->query_skill("force") + me->query_skill("hamagong", 1);
                }
                else {
                        level = me->query_skill("force");
                }
        
                hm_stat=query_temp("dugu/reverse", me)+query_temp("dugu/hamapowerup", me);

                if( !query_temp("reverse", me)){
                        addn_temp("apply/dodge", level/2, me);
                        delete_temp("dugu/reverse", me);
                        status++;
                }

                if( !query_temp("powerup", me)){
                        addn_temp("apply/attack", level/4, me);
                        addn("eff_qi", level*5/2, me);
                        addn("qi", level, me);
                        delete_temp("dugu/hamapowerup", me);
                        status++;
                }
        }
        else if( query_temp("dugu/powerup", me) && !query_temp("powerup", me)){
                if( query_temp("dugu/force", me) && skill == ""){
                        level = me->query_skill("force") + me->query_skill("huntian-qigong", 1);
                }
                else {
                        level = me->query_skill("force");
                }

                addn_temp("apply/dodge", level/3, me);
                addn_temp("apply/attack", level/3, me);
                delete_temp("dugu/powerup", me);
                status++;
        }
        else if( query_temp("dugu/shield", me) && !query_temp("shielded", me)){
                if( query_temp("dugu/force", me) && skill == ""){
                        level = me->query_skill("force") + me->query_skill("longxiang-banruo", 1);
                }
                else {
                        level = me->query_skill("force");
                }

                addn_temp("apply/armor", level/2, me);
                addn_temp("apply/defense", level/2, me);
                delete_temp("dugu/shield", me);
                status++;
        }
        else if( query_temp("dugu/wuzhuan", me) && !query_temp("wuzhuan", me)){
                level = me->query_skill("qimen-dunjia",1);
                addn_temp("apply/dodge", level/5, me);
                addn_temp("apply/dex", level/10, me);
                addn_temp("apply/speed", level/30, me);
                delete_temp("dugu/wuzhuan", me);
                status++;        
        }
        else if( query_temp("dugu/tiandi", me) || query_temp("dugu/zhixin", me )
        || query_temp("dugu/fengyun", me) || query_temp("dugu/daxiao", me)){
                level = me->query_skill("linji-zhuang", 1);
        
                if( query_temp("dugu/zhixin", me))lj_stat++;
                if( query_temp("dugu/daxiao", me))lj_stat++;
                lj_stat+=query_temp("dugu/tiandi", me)+query_temp("dugu/fengyun", me);

                if( !query_temp("linji/tiandi", me)){
                        addn("max_qi", level, me);
                        addn("max_jing", level, me);
 //                     me->addn("max_jingli", level);
                        me->receive_curing("qi", level);
                        me->receive_curing("jing", level);
                        me->receive_heal("jingli", level);
                        delete_temp("dugu/tiandi", me);
                        status++;
                }

                if( !query_temp("linji/zhixin", me)){
                        addn_temp("apply/int",query_temp("dugu/zhixin",  me), me);
                        delete_temp("dugu/zhixin", me);
                        status++;
                }

                if( !query_temp("linji/fengyun", me)){
                        addn_temp("apply/dex", level, me);
                        addn_temp("apply/attack", -level, me);
                        delete_temp("dugu/fengyun", me);
                        status++;
                }

                if( !query_temp("linji/daxiao", me)){
                        addn("max_qi",query_temp("dugu/daxiao",  me), me);
                        addn("max_jing", -query_temp("dugu/daxiao", me), me);
                        me->receive_curing("qi",query_temp("dugu/daxiao", me));
                        if( query("eff_jing", me)>query("max_jing", me) )
                                set("eff_jing",query("max_jing",  me), me);
                        delete_temp("dugu/daxiao", me);
                        status++;
                }
        }

        if ( hm_stat > status ) flag = 1;
        else if ( lj_stat > status ) flag = 1;
        else if ( status == 0 ) flag = 1;
        else flag = 0;

        if ( t ) {
                me->apply_condition("jiujian_qi_damage", duration - 1);
        }
        else if( flag && !query_temp("dugu", me)){
                me->apply_condition("jiujian_qi_damage", 0 );
        }
        else if ( flag ) {
                if( query_temp("dugu/force", me))delete_temp("dugu/force", me);
                me->apply_condition("jiujian_qi_damage", 1 );
        }

        return CND_CONTINUE;
}