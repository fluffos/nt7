// This program is a part of NT MudLIB
// stats cmds

#include <ansi.h>
#include <mudlib.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string sp;

        seteuid(getuid(me));

        if( !wizardp(me) && time()-query_temp("last_stats", me)<5 )
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");

        set_temp("last_stats", time(), me);
        MYGIFT_D->check_mygift(me, "newbie_mygift/istat");

        if( arg && (arg == "-jingmai"
        ||  sscanf(arg, "-jingmai %s", arg)
        ||  sscanf(arg, "%s -jingmai", arg)) )
        {
                if( arg == "-jingmai" )
                        ob = me;
                else
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看谁的状态？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看谁的状态？\n");

                } else
                        return notify_fail("只有巫师能察看别人的状态。\n");

                        sp = HIM + (ob == me ? "你" : ob->name(1)) + "目前的经脉附加属性效果一览\n" NOR;
                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==天赋加成==------------------------------" HIC "≡\n\n" NOR;

                        sp += sprintf(HIC "【臂力附加】" HIG " %9d / %-9d"
                                      HIC "【悟性附加】" HIG " %9d / %d\n"
                                      HIC "【根骨附加】" HIG " %9d / %-9d"
                                      HIC "【身法附加】" HIG " %9d / %d\n\n",
                                      ob->query_jingmai_buff("str"),2000,
                                      ob->query_jingmai_buff("int"),2000,
                                      ob->query_jingmai_buff("con"),2000,
                                      ob->query_jingmai_buff("dex"),2000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==上限加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【潜能上限】" HIM " %9d / %-9d"
                                      HIC "【体会上限】" HIM " %9d / %d\n"
                                      HIC "【内力上限】" HIM " %9d / %-9d"
                                      HIC "【精力上限】" HIM " %9d / %d\n"
                                      HIC "【气血上限】" HIM " %9d / %-9d"
                                      HIC "【精气上限】" HIM " %9d / %d\n\n",
                                      ob->query_jingmai_buff("max_potential"),10000000,
                                      ob->query_jingmai_buff("max_experience"),10000000,
                                      ob->query_jingmai_buff("max_neili"),2000000,
                                      ob->query_jingmai_buff("max_jingli"),1000000,
                                      ob->query_jingmai_buff("max_qi"),2000000,
                                      ob->query_jingmai_buff("max_jing"),1000000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==练功加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【研究次数】" HIY " %9d / %-9d"
                                      HIC "【研究效果】" HIY " %9s / %s\n"
                                      HIC "【练习次数】" HIY " %9d / %-9d"
                                      HIC "【练习效果】" HIY " %9s / %s\n"
                                      HIC "【学习次数】" HIY " %9d / %-9d"
                                      HIC "【学习效果】" HIY " %9s / %s\n"
                                      HIC "【汲取消耗】" HIY " %9d / %-9d"
                                      HIC "【汲取效果】" HIY " %9s / %s\n\n",
                                      ob->query_jingmai_buff("research_times"),2000,
                                      ob->query_jingmai_buff("research_effect")+"%","2000%",
                                      ob->query_jingmai_buff("practice_times"),2000,
                                      ob->query_jingmai_buff("practice_effect")+"%","2000%",
                                      ob->query_jingmai_buff("learn_times"),2000,
                                      ob->query_jingmai_buff("learn_effect")+"%","2000%",
                                      ob->query_jingmai_buff("derive_times"),2000,
                                      ob->query_jingmai_buff("derive_effect")+"%","2000%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==五行加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(RED "【毒 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    毒】" RED " %9s / %s\n"
                                      RED "【魔 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    魔】" RED " %9s / %s\n"
                                      RED "【金 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    金】" RED " %9s / %s\n"
                                      RED "【木 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    木】" RED " %9s / %s\n"
                                      RED "【水 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    水】" RED " %9s / %s\n"
                                      RED "【火 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    火】" RED " %9s / %s\n"
                                      RED "【土 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    土】" RED " %9s / %s\n\n",
                                      ob->query_jingmai_buff("add_poison")+"%","100%",ob->query_jingmai_buff("reduce_poison")+"%","100%",
                                      ob->query_jingmai_buff("add_magic")+"%","100%",ob->query_jingmai_buff("reduce_magic")+"%","100%",
                                      ob->query_jingmai_buff("add_metal")+"%","100%",ob->query_jingmai_buff("reduce_metal")+"%","100%",
                                      ob->query_jingmai_buff("add_wood")+"%","100%",ob->query_jingmai_buff("reduce_wood")+"%","100%",
                                      ob->query_jingmai_buff("add_water")+"%","100%",ob->query_jingmai_buff("reduce_water")+"%","100%",
                                      ob->query_jingmai_buff("add_fire")+"%","100%",ob->query_jingmai_buff("reduce_fire")+"%","100%",
                                      ob->query_jingmai_buff("add_earth")+"%","100%",ob->query_jingmai_buff("reduce_earth")+"%","100%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==状态恢复==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIB "【偷取内力】" HIB " %9s / %-9s"
                                      HIB "【偷取生命】" HIB " %9s / %s\n\n",
                                      ob->query_jingmai_buff("leech_neili")+"%","90%",
                                      ob->query_jingmai_buff("leech_qi")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==战斗加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(WHT "【攻击等级】" HIW " %9d / %-9d" NOR
                                      WHT "【防御等级】" HIW " %9d / %d\n" NOR
                                      WHT "【躲闪等级】" HIW " %9d / %-9d" NOR
                                      WHT "【招架等级】" HIW " %9d / %d\n" NOR
                                      WHT "【绝招命中】" HIW " %9s / %-9s" NOR
                                      WHT "【绝招防御】" HIW " %9s / %s\n" NOR
                                      WHT "【兵器伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【空手伤害】" HIG " %9d / %d\n" NOR
                                      WHT "【绝招伤害】" HIG " %9s / %-9s" NOR
                                      WHT "【战斗保护】" HIG " %9d / %d\n" NOR
                                      /*
                                      WHT "【附加伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【附加保护】" HIG " %9d / %d\n" NOR
                                      WHT "【改造伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【改造保护】" HIG " %9d / %d\n" NOR
                                      */
                                      WHT "【忽视招架】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视躲闪】" HIY " %9s / %s\n" NOR
                                      WHT "【忽视特攻】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视内防】" HIY " %9s / %s\n\n" NOR,
                                      ob->query_jingmai_buff("attack"),9000,
                                      ob->query_jingmai_buff("defense"),9000,
                                      ob->query_jingmai_buff("dodge"),9000,
                                      ob->query_jingmai_buff("parry"),9000,
                                      ob->query_jingmai_buff("ap_power")+"%","120%",
                                      ob->query_jingmai_buff("dp_power")+"%","120%",
                                      ob->query_jingmai_buff("damage"),200000,
                                      ob->query_jingmai_buff("unarmed_damage"),200000,
                                      ob->query_jingmai_buff("da_power")+"%","120%",
                                      ob->query_jingmai_buff("armor"),200000,
                                      //query_temp("apply/damage1", ob),200000,query_temp("apply/armor1", ob),200000,
                                      //query_temp("apply/damage2", ob),200000,query_temp("apply/armor2", ob),200000,
                                      ob->query_jingmai_buff("avoid_parry")+"%","90%",
                                      ob->query_jingmai_buff("avoid_dodge")+"%","90%",
                                      ob->query_jingmai_buff("avoid_attack")+"%","90%",
                                      ob->query_jingmai_buff("avoid_force")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==高级属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIW "【化解忙乱】" HIM " %9d / %-9d"
                                      HIW "【寻 宝 率】" HIM " %9s / %s\n"
                                      HIW "【双倍伤害】" CYN " %9s / %-9s"
                                      HIW "【伤转内力】" CYN " %9s / %s\n"
                                      HIW "【致    盲】" CYN " %9s / %-9s"
                                      HIW "【忽视致盲】" CYN " %9s / %s\n"
                                      HIW "【穿透破甲】" CYN " %9s / %-9s"
                                      HIW "【百毒不侵】" CYN " %9s / %s\n"
                                      HIW "【战神附体】" CYN " %9s / %-9s\n\n",
                                      ob->query_jingmai_buff("reduce_busy"),90,
                                      ob->query_jingmai_buff("magic_find")+"%","300%",
                                      ob->query_jingmai_buff("double_damage")+"%","200%",
                                      ob->query_jingmai_buff("qi_abs_neili")+"%","90%",
                                      ob->query_jingmai_buff("add_blind")+"%","90%",
                                      ob->query_jingmai_buff("avoid_blind")+"%","90%",
                                      ob->query_jingmai_buff("through_armor")+"%","90%",
                                      ob->query_jingmai_buff("avoid_poison")+"%","100%",
                                      ob->query_jingmai_buff("full_self")+"%","90%");

                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==终极属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIY "【冰    冻】" HIM " %9s / %-9s"
                                      HIY "【忽视冰冻】" HIM " %9s / %s\n"
                                      /*
                                      HIY "【眩    晕】" HIM " %9s / %-9s"
                                      HIY "【忽视眩晕】" HIM " %9s / %s\n"
                                      */
                                      HIY "【遗    忘】" HIM " %9s / %-9s"
                                      HIY "【忽视遗忘】" HIM " %9s / %s\n"
                                      HIY "【忙    乱】" HIM " %9d / %-9d"
                                      HIY "【忽视忙乱】" HIM " %9s / %s\n"
                                      HIY "【虚    弱】" HIM " %9s / %-9s"
                                      HIY "【忽视虚弱】" HIM " %9s / %s\n"
                                      HIY "【追加伤害】" HIM " %9s / %-9s"
                                      HIY "【化解伤害】" HIM " %9s / %s\n"
                                      HIY "【伤害反噬】" HIM " %9s / %-9s"
                                      HIY "【浴血重生】" HIM " %9s / %s\n"
                                      HIY "【致命一击】" HIM " %9s / %-9s"
                                      HIY "【提升技能】" HIM " %9d / %d\n\n",
                                      ob->query_jingmai_buff("add_freeze")+"%","90%",ob->query_jingmai_buff("avoid_freeze")+"%","90%",
                                      /*
                                      ob->query_jingmai_buff("add_dizziness")+"%","90%",ob->query_jingmai_buff("avoid_dizziness")+"%","90%",                    ;:207c
                                      */
                                      ob->query_jingmai_buff("add_forget")+"%","90%",ob->query_jingmai_buff("avoid_forget")+"%","90%",
                                      ob->query_jingmai_buff("add_busy"),90,ob->query_jingmai_buff("avoid_busy")+"%","90%",
                                      ob->query_jingmai_buff("add_weak")+"%","90%",ob->query_jingmai_buff("avoid_weak")+"%","90%",
                                      ob->query_jingmai_buff("add_damage")+"%","200%",
                                      ob->query_jingmai_buff("reduce_damage")+"%","90%",
                                      ob->query_jingmai_buff("counter_damage")+"%","90%",ob->query_jingmai_buff("avoid_die")+"%","90%",
                                      ob->query_jingmai_buff("fatal_blow")+"%","90%",ob->query_jingmai_buff("add_skill"),1200);

                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==王者归来==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "在%s里已经历练了 " NOR + HIC "%s\n" NOR,
                                      LOCAL_MUD_NAME(), time_period(query("online_time", ob)));

                        if( MEMBER_D->is_valid_member(ob) )
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "无限制\n" NOR);
                        else
                        {
                                if( query("online_time", ob)/3<query("offline_time", ob) )
                                        set("offline_time",query("online_time",  ob)/3, ob);
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "%s\n" NOR,
                                              time_period(query("online_time", ob)/3-query("offline_time", ob)));
                        }

                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的双倍经验时间还余 " NOR + HIW "%s\n" NOR,
                                      time_period(query("time_reward/quest", ob)));
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的高效练功时间还余 " NOR + HIM "%s\n" NOR,
                                      time_period(query("time_reward/study", ob)));


                        me->start_more(sp);
                        return 1;
        }

        if( arg && (arg == "-yuanshen"
        ||  sscanf(arg, "-yuanshen %s", arg)
        ||  sscanf(arg, "%s -yuanshen", arg)) )
        {
                if( arg == "-yuanshen" )
                        ob = me;
                else
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看谁的状态？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看谁的状态？\n");

                } else
                        return notify_fail("只有巫师能察看别人的状态。\n");

                        sp = HIM + (ob == me ? "你" : ob->name(1)) + "目前的元神附加属性效果一览\n" NOR;
                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==天赋加成==------------------------------" HIC "≡\n\n" NOR;

                        sp += sprintf(HIC "【臂力附加】" HIG " %9d / %-9d"
                                      HIC "【悟性附加】" HIG " %9d / %d\n"
                                      HIC "【根骨附加】" HIG " %9d / %-9d"
                                      HIC "【身法附加】" HIG " %9d / %d\n\n",
                                      ob->query_yuanshen_buff("str"),2000,
                                      ob->query_yuanshen_buff("int"),2000,
                                      ob->query_yuanshen_buff("con"),2000,
                                      ob->query_yuanshen_buff("dex"),2000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==上限加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【潜能上限】" HIM " %9d / %-9d"
                                      HIC "【体会上限】" HIM " %9d / %d\n"
                                      HIC "【内力上限】" HIM " %9d / %-9d"
                                      HIC "【精力上限】" HIM " %9d / %d\n"
                                      HIC "【气血上限】" HIM " %9d / %-9d"
                                      HIC "【精气上限】" HIM " %9d / %d\n\n",
                                      ob->query_yuanshen_buff("max_potential"),10000000,
                                      ob->query_yuanshen_buff("max_experience"),10000000,
                                      ob->query_yuanshen_buff("max_neili"),2000000,
                                      ob->query_yuanshen_buff("max_jingli"),1000000,
                                      ob->query_yuanshen_buff("max_qi"),2000000,
                                      ob->query_yuanshen_buff("max_jing"),1000000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==练功加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【研究次数】" HIY " %9d / %-9d"
                                      HIC "【研究效果】" HIY " %9s / %s\n"
                                      HIC "【练习次数】" HIY " %9d / %-9d"
                                      HIC "【练习效果】" HIY " %9s / %s\n"
                                      HIC "【学习次数】" HIY " %9d / %-9d"
                                      HIC "【学习效果】" HIY " %9s / %s\n"
                                      HIC "【汲取消耗】" HIY " %9d / %-9d"
                                      HIC "【汲取效果】" HIY " %9s / %s\n\n",
                                      ob->query_yuanshen_buff("research_times"),2000,
                                      ob->query_yuanshen_buff("research_effect")+"%","2000%",
                                      ob->query_yuanshen_buff("practice_times"),2000,
                                      ob->query_yuanshen_buff("practice_effect")+"%","2000%",
                                      ob->query_yuanshen_buff("learn_times"),2000,
                                      ob->query_yuanshen_buff("learn_effect")+"%","2000%",
                                      ob->query_yuanshen_buff("derive_times"),2000,
                                      ob->query_yuanshen_buff("derive_effect")+"%","2000%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==五行加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(RED "【毒 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    毒】" RED " %9s / %s\n"
                                      RED "【魔 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    魔】" RED " %9s / %s\n"
                                      RED "【金 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    金】" RED " %9s / %s\n"
                                      RED "【木 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    木】" RED " %9s / %s\n"
                                      RED "【水 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    水】" RED " %9s / %s\n"
                                      RED "【火 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    火】" RED " %9s / %s\n"
                                      RED "【土 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    土】" RED " %9s / %s\n\n",
                                      ob->query_yuanshen_buff("add_poison")+"%","100%",ob->query_yuanshen_buff("reduce_poison")+"%","100%",
                                      ob->query_yuanshen_buff("add_magic")+"%","100%",ob->query_yuanshen_buff("reduce_magic")+"%","100%",
                                      ob->query_yuanshen_buff("add_metal")+"%","100%",ob->query_yuanshen_buff("reduce_metal")+"%","100%",
                                      ob->query_yuanshen_buff("add_wood")+"%","100%",ob->query_yuanshen_buff("reduce_wood")+"%","100%",
                                      ob->query_yuanshen_buff("add_water")+"%","100%",ob->query_yuanshen_buff("reduce_water")+"%","100%",
                                      ob->query_yuanshen_buff("add_fire")+"%","100%",ob->query_yuanshen_buff("reduce_fire")+"%","100%",
                                      ob->query_yuanshen_buff("add_earth")+"%","100%",ob->query_yuanshen_buff("reduce_earth")+"%","100%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==状态恢复==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIB "【偷取内力】" HIB " %9s / %-9s"
                                      HIB "【偷取生命】" HIB " %9s / %s\n\n",
                                      ob->query_yuanshen_buff("leech_neili")+"%","90%",
                                      ob->query_yuanshen_buff("leech_qi")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==战斗加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(WHT "【攻击等级】" HIW " %9d / %-9d" NOR
                                      WHT "【防御等级】" HIW " %9d / %d\n" NOR
                                      WHT "【躲闪等级】" HIW " %9d / %-9d" NOR
                                      WHT "【招架等级】" HIW " %9d / %d\n" NOR
                                      WHT "【绝招命中】" HIW " %9s / %-9s" NOR
                                      WHT "【绝招防御】" HIW " %9s / %s\n" NOR
                                      WHT "【兵器伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【空手伤害】" HIG " %9d / %d\n" NOR
                                      WHT "【绝招伤害】" HIG " %9s / %-9s" NOR
                                      WHT "【战斗保护】" HIG " %9d / %d\n" NOR
                                      /*
                                      WHT "【附加伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【附加保护】" HIG " %9d / %d\n" NOR
                                      WHT "【改造伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【改造保护】" HIG " %9d / %d\n" NOR
                                      */
                                      WHT "【忽视招架】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视躲闪】" HIY " %9s / %s\n" NOR
                                      WHT "【忽视特攻】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视内防】" HIY " %9s / %s\n\n" NOR,
                                      ob->query_yuanshen_buff("attack"),9000,
                                      ob->query_yuanshen_buff("defense"),9000,
                                      ob->query_yuanshen_buff("dodge"),9000,
                                      ob->query_yuanshen_buff("parry"),9000,
                                      ob->query_yuanshen_buff("ap_power")+"%","120%",
                                      ob->query_yuanshen_buff("dp_power")+"%","120%",
                                      ob->query_yuanshen_buff("damage"),200000,
                                      ob->query_yuanshen_buff("unarmed_damage"),200000,
                                      ob->query_yuanshen_buff("da_power")+"%","120%",
                                      ob->query_yuanshen_buff("armor"),200000,
                                      //query_temp("apply/damage1", ob),200000,query_temp("apply/armor1", ob),200000,
                                      //query_temp("apply/damage2", ob),200000,query_temp("apply/armor2", ob),200000,
                                      ob->query_yuanshen_buff("avoid_parry")+"%","90%",
                                      ob->query_yuanshen_buff("avoid_dodge")+"%","90%",
                                      ob->query_yuanshen_buff("avoid_attack")+"%","90%",
                                      ob->query_yuanshen_buff("avoid_force")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==高级属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIW "【化解忙乱】" HIM " %9d / %-9d"
                                      HIW "【寻 宝 率】" HIM " %9s / %s\n"
                                      HIW "【双倍伤害】" CYN " %9s / %-9s"
                                      HIW "【伤转内力】" CYN " %9s / %s\n"
                                      HIW "【致    盲】" CYN " %9s / %-9s"
                                      HIW "【忽视致盲】" CYN " %9s / %s\n"
                                      HIW "【穿透破甲】" CYN " %9s / %-9s"
                                      HIW "【百毒不侵】" CYN " %9s / %s\n"
                                      HIW "【战神附体】" CYN " %9s / %-9s\n\n",
                                      ob->query_yuanshen_buff("reduce_busy"),90,
                                      ob->query_yuanshen_buff("magic_find")+"%","300%",
                                      ob->query_yuanshen_buff("double_damage")+"%","200%",
                                      ob->query_yuanshen_buff("qi_abs_neili")+"%","90%",
                                      ob->query_yuanshen_buff("add_blind")+"%","90%",
                                      ob->query_yuanshen_buff("avoid_blind")+"%","90%",
                                      ob->query_yuanshen_buff("through_armor")+"%","90%",
                                      ob->query_yuanshen_buff("avoid_poison")+"%","100%",
                                      ob->query_yuanshen_buff("full_self")+"%","90%");

                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==终极属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIY "【冰    冻】" HIM " %9s / %-9s"
                                      HIY "【忽视冰冻】" HIM " %9s / %s\n"
                                      /*
                                      HIY "【眩    晕】" HIM " %9s / %-9s"
                                      HIY "【忽视眩晕】" HIM " %9s / %s\n"
                                      */
                                      HIY "【遗    忘】" HIM " %9s / %-9s"
                                      HIY "【忽视遗忘】" HIM " %9s / %s\n"
                                      HIY "【忙    乱】" HIM " %9d / %-9d"
                                      HIY "【忽视忙乱】" HIM " %9s / %s\n"
                                      HIY "【虚    弱】" HIM " %9s / %-9s"
                                      HIY "【忽视虚弱】" HIM " %9s / %s\n"
                                      HIY "【追加伤害】" HIM " %9s / %-9s"
                                      HIY "【化解伤害】" HIM " %9s / %s\n"
                                      HIY "【伤害反噬】" HIM " %9s / %-9s"
                                      HIY "【浴血重生】" HIM " %9s / %s\n"
                                      HIY "【致命一击】" HIM " %9s / %-9s"
                                      HIY "【提升技能】" HIM " %9d / %d\n\n",
                                      ob->query_yuanshen_buff("add_freeze")+"%","90%",ob->query_yuanshen_buff("avoid_freeze")+"%","90%",
                                      /*
                                      ob->query_yuanshen_buff("add_dizziness")+"%","90%",ob->query_yuanshen_buff("avoid_dizziness")+"%","90%",                    ;:207c
                                      */
                                      ob->query_yuanshen_buff("add_forget")+"%","90%",ob->query_yuanshen_buff("avoid_forget")+"%","90%",
                                      ob->query_yuanshen_buff("add_busy"),90,ob->query_yuanshen_buff("avoid_busy")+"%","90%",
                                      ob->query_yuanshen_buff("add_weak")+"%","90%",ob->query_yuanshen_buff("avoid_weak")+"%","90%",
                                      ob->query_yuanshen_buff("add_damage")+"%","200%",
                                      ob->query_yuanshen_buff("reduce_damage")+"%","90%",
                                      ob->query_yuanshen_buff("counter_damage")+"%","90%",ob->query_yuanshen_buff("avoid_die")+"%","90%",
                                      ob->query_yuanshen_buff("fatal_blow")+"%","90%",ob->query_yuanshen_buff("add_skill"),1200);

                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==王者归来==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "在%s里已经历练了 " NOR + HIC "%s\n" NOR,
                                      LOCAL_MUD_NAME(), time_period(query("online_time", ob)));

                        if( MEMBER_D->is_valid_member(ob) )
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "无限制\n" NOR);
                        else
                        {
                                if( query("online_time", ob)/3<query("offline_time", ob) )
                                        set("offline_time",query("online_time",  ob)/3, ob);
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "%s\n" NOR,
                                              time_period(query("online_time", ob)/3-query("offline_time", ob)));
                        }

                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的双倍经验时间还余 " NOR + HIW "%s\n" NOR,
                                      time_period(query("time_reward/quest", ob)));
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的高效练功时间还余 " NOR + HIM "%s\n" NOR,
                                      time_period(query("time_reward/study", ob)));


                        me->start_more(sp);
                        return 1;
        }

        if( arg && (arg == "-skillmix"
        ||  sscanf(arg, "-skillmix %s", arg)
        ||  sscanf(arg, "%s -skillmix", arg)) )
        {
                if( arg == "-skillmix" )
                        ob = me;
                else
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看谁的状态？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看谁的状态？\n");

                } else
                        return notify_fail("只有巫师能察看别人的状态。\n");

                        sp = HIM + (ob == me ? "你" : ob->name(1)) + "目前的技能组合附加属性效果一览\n" NOR;
                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==天赋加成==------------------------------" HIC "≡\n\n" NOR;

                        sp += sprintf(HIC "【臂力附加】" HIG " %9d / %-9d"
                                      HIC "【悟性附加】" HIG " %9d / %d\n"
                                      HIC "【根骨附加】" HIG " %9d / %-9d"
                                      HIC "【身法附加】" HIG " %9d / %d\n\n",
                                      ob->query_skillmix_buff("str"),2000,
                                      ob->query_skillmix_buff("int"),2000,
                                      ob->query_skillmix_buff("con"),2000,
                                      ob->query_skillmix_buff("dex"),2000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==上限加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【潜能上限】" HIM " %9d / %-9d"
                                      HIC "【体会上限】" HIM " %9d / %d\n"
                                      HIC "【内力上限】" HIM " %9d / %-9d"
                                      HIC "【精力上限】" HIM " %9d / %d\n"
                                      HIC "【气血上限】" HIM " %9d / %-9d"
                                      HIC "【精气上限】" HIM " %9d / %d\n\n",
                                      ob->query_skillmix_buff("max_potential"),10000000,
                                      ob->query_skillmix_buff("max_experience"),10000000,
                                      ob->query_skillmix_buff("max_neili"),2000000,
                                      ob->query_skillmix_buff("max_jingli"),1000000,
                                      ob->query_skillmix_buff("max_qi"),2000000,
                                      ob->query_skillmix_buff("max_jing"),1000000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==练功加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【研究次数】" HIY " %9d / %-9d"
                                      HIC "【研究效果】" HIY " %9s / %s\n"
                                      HIC "【练习次数】" HIY " %9d / %-9d"
                                      HIC "【练习效果】" HIY " %9s / %s\n"
                                      HIC "【学习次数】" HIY " %9d / %-9d"
                                      HIC "【学习效果】" HIY " %9s / %s\n"
                                      HIC "【汲取消耗】" HIY " %9d / %-9d"
                                      HIC "【汲取效果】" HIY " %9s / %s\n\n",
                                      ob->query_skillmix_buff("research_times"),2000,
                                      ob->query_skillmix_buff("research_effect")+"%","2000%",
                                      ob->query_skillmix_buff("practice_times"),2000,
                                      ob->query_skillmix_buff("practice_effect")+"%","2000%",
                                      ob->query_skillmix_buff("learn_times"),2000,
                                      ob->query_skillmix_buff("learn_effect")+"%","2000%",
                                      ob->query_skillmix_buff("derive_times"),2000,
                                      ob->query_skillmix_buff("derive_effect")+"%","2000%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==五行加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(RED "【毒 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    毒】" RED " %9s / %s\n"
                                      RED "【魔 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    魔】" RED " %9s / %s\n"
                                      RED "【金 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    金】" RED " %9s / %s\n"
                                      RED "【木 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    木】" RED " %9s / %s\n"
                                      RED "【水 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    水】" RED " %9s / %s\n"
                                      RED "【火 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    火】" RED " %9s / %s\n"
                                      RED "【土 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    土】" RED " %9s / %s\n\n",
                                      ob->query_skillmix_buff("add_poison")+"%","100%",ob->query_skillmix_buff("reduce_poison")+"%","100%",
                                      ob->query_skillmix_buff("add_magic")+"%","100%",ob->query_skillmix_buff("reduce_magic")+"%","100%",
                                      ob->query_skillmix_buff("add_metal")+"%","100%",ob->query_skillmix_buff("reduce_metal")+"%","100%",
                                      ob->query_skillmix_buff("add_wood")+"%","100%",ob->query_skillmix_buff("reduce_wood")+"%","100%",
                                      ob->query_skillmix_buff("add_water")+"%","100%",ob->query_skillmix_buff("reduce_water")+"%","100%",
                                      ob->query_skillmix_buff("add_fire")+"%","100%",ob->query_skillmix_buff("reduce_fire")+"%","100%",
                                      ob->query_skillmix_buff("add_earth")+"%","100%",ob->query_skillmix_buff("reduce_earth")+"%","100%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==状态恢复==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIB "【偷取内力】" HIB " %9s / %-9s"
                                      HIB "【偷取生命】" HIB " %9s / %s\n\n",
                                      ob->query_skillmix_buff("leech_neili")+"%","90%",
                                      ob->query_skillmix_buff("leech_qi")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==战斗加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(WHT "【攻击等级】" HIW " %9d / %-9d" NOR
                                      WHT "【防御等级】" HIW " %9d / %d\n" NOR
                                      WHT "【躲闪等级】" HIW " %9d / %-9d" NOR
                                      WHT "【招架等级】" HIW " %9d / %d\n" NOR
                                      WHT "【绝招命中】" HIW " %9s / %-9s" NOR
                                      WHT "【绝招防御】" HIW " %9s / %s\n" NOR
                                      WHT "【兵器伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【空手伤害】" HIG " %9d / %d\n" NOR
                                      WHT "【绝招伤害】" HIG " %9s / %-9s" NOR
                                      WHT "【战斗保护】" HIG " %9d / %d\n" NOR
                                      /*
                                      WHT "【附加伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【附加保护】" HIG " %9d / %d\n" NOR
                                      WHT "【改造伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【改造保护】" HIG " %9d / %d\n" NOR
                                      */
                                      WHT "【忽视招架】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视躲闪】" HIY " %9s / %s\n" NOR
                                      WHT "【忽视特攻】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视内防】" HIY " %9s / %s\n\n" NOR,
                                      ob->query_skillmix_buff("attack"),9000,
                                      ob->query_skillmix_buff("defense"),9000,
                                      ob->query_skillmix_buff("dodge"),9000,
                                      ob->query_skillmix_buff("parry"),9000,
                                      ob->query_skillmix_buff("ap_power")+"%","120%",
                                      ob->query_skillmix_buff("dp_power")+"%","120%",
                                      ob->query_skillmix_buff("damage"),200000,
                                      ob->query_skillmix_buff("unarmed_damage"),200000,
                                      ob->query_skillmix_buff("da_power")+"%","120%",
                                      ob->query_skillmix_buff("armor"),200000,
                                      //query_temp("apply/damage1", ob),200000,query_temp("apply/armor1", ob),200000,
                                      //query_temp("apply/damage2", ob),200000,query_temp("apply/armor2", ob),200000,
                                      ob->query_skillmix_buff("avoid_parry")+"%","90%",
                                      ob->query_skillmix_buff("avoid_dodge")+"%","90%",
                                      ob->query_skillmix_buff("avoid_attack")+"%","90%",
                                      ob->query_skillmix_buff("avoid_force")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==高级属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIW "【化解忙乱】" HIM " %9d / %-9d"
                                      HIW "【寻 宝 率】" HIM " %9s / %s\n"
                                      HIW "【双倍伤害】" CYN " %9s / %-9s"
                                      HIW "【伤转内力】" CYN " %9s / %s\n"
                                      HIW "【致    盲】" CYN " %9s / %-9s"
                                      HIW "【忽视致盲】" CYN " %9s / %s\n"
                                      HIW "【穿透破甲】" CYN " %9s / %-9s"
                                      HIW "【百毒不侵】" CYN " %9s / %s\n"
                                      HIW "【战神附体】" CYN " %9s / %-9s\n\n",
                                      ob->query_skillmix_buff("reduce_busy"),90,
                                      ob->query_skillmix_buff("magic_find")+"%","300%",
                                      ob->query_skillmix_buff("double_damage")+"%","200%",
                                      ob->query_skillmix_buff("qi_abs_neili")+"%","90%",
                                      ob->query_skillmix_buff("add_blind")+"%","90%",
                                      ob->query_skillmix_buff("avoid_blind")+"%","90%",
                                      ob->query_skillmix_buff("through_armor")+"%","90%",
                                      ob->query_skillmix_buff("avoid_poison")+"%","100%",
                                      ob->query_skillmix_buff("full_self")+"%","90%");

                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==终极属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIY "【冰    冻】" HIM " %9s / %-9s"
                                      HIY "【忽视冰冻】" HIM " %9s / %s\n"
                                      /*
                                      HIY "【眩    晕】" HIM " %9s / %-9s"
                                      HIY "【忽视眩晕】" HIM " %9s / %s\n"
                                      */
                                      HIY "【遗    忘】" HIM " %9s / %-9s"
                                      HIY "【忽视遗忘】" HIM " %9s / %s\n"
                                      HIY "【忙    乱】" HIM " %9d / %-9d"
                                      HIY "【忽视忙乱】" HIM " %9s / %s\n"
                                      HIY "【虚    弱】" HIM " %9s / %-9s"
                                      HIY "【忽视虚弱】" HIM " %9s / %s\n"
                                      HIY "【追加伤害】" HIM " %9s / %-9s"
                                      HIY "【化解伤害】" HIM " %9s / %s\n"
                                      HIY "【伤害反噬】" HIM " %9s / %-9s"
                                      HIY "【浴血重生】" HIM " %9s / %s\n"
                                      HIY "【致命一击】" HIM " %9s / %-9s"
                                      HIY "【提升技能】" HIM " %9d / %d\n\n",
                                      ob->query_skillmix_buff("add_freeze")+"%","90%",ob->query_skillmix_buff("avoid_freeze")+"%","90%",
                                      /*
                                      ob->query_skillmix_buff("add_dizziness")+"%","90%",ob->query_skillmix_buff("avoid_dizziness")+"%","90%",                    ;:207c
                                      */
                                      ob->query_skillmix_buff("add_forget")+"%","90%",ob->query_skillmix_buff("avoid_forget")+"%","90%",
                                      ob->query_skillmix_buff("add_busy"),90,ob->query_skillmix_buff("avoid_busy")+"%","90%",
                                      ob->query_skillmix_buff("add_weak")+"%","90%",ob->query_skillmix_buff("avoid_weak")+"%","90%",
                                      ob->query_skillmix_buff("add_damage")+"%","200%",
                                      ob->query_skillmix_buff("reduce_damage")+"%","90%",
                                      ob->query_skillmix_buff("counter_damage")+"%","90%",ob->query_skillmix_buff("avoid_die")+"%","90%",
                                      ob->query_skillmix_buff("fatal_blow")+"%","90%",ob->query_skillmix_buff("add_skill"),1200);

                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==王者归来==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "在%s里已经历练了 " NOR + HIC "%s\n" NOR,
                                      LOCAL_MUD_NAME(), time_period(query("online_time", ob)));

                        if( MEMBER_D->is_valid_member(ob) )
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "无限制\n" NOR);
                        else
                        {
                                if( query("online_time", ob)/3<query("offline_time", ob) )
                                        set("offline_time",query("online_time",  ob)/3, ob);
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "%s\n" NOR,
                                              time_period(query("online_time", ob)/3-query("offline_time", ob)));
                        }

                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的双倍经验时间还余 " NOR + HIW "%s\n" NOR,
                                      time_period(query("time_reward/quest", ob)));
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的高效练功时间还余 " NOR + HIM "%s\n" NOR,
                                      time_period(query("time_reward/study", ob)));


                        me->start_more(sp);
                        return 1;
        }

        if( arg && (arg == "-ability"
        ||  sscanf(arg, "-ability %s", arg)
        ||  sscanf(arg, "%s -ability", arg)) )
        {
                if( arg == "-ability" )
                        ob = me;
                else
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看谁的状态？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看谁的状态？\n");

                } else
                        return notify_fail("只有巫师能察看别人的状态。\n");

                        sp = HIM + (ob == me ? "你" : ob->name(1)) + "目前的能力进阶附加属性效果一览\n" NOR;
                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==天赋加成==------------------------------" HIC "≡\n\n" NOR;

                        sp += sprintf(HIC "【臂力附加】" HIG " %9d / %-9d"
                                      HIC "【悟性附加】" HIG " %9d / %d\n"
                                      HIC "【根骨附加】" HIG " %9d / %-9d"
                                      HIC "【身法附加】" HIG " %9d / %d\n\n",
                                      ob->query_ability_buff("str"),2000,
                                      ob->query_ability_buff("int"),2000,
                                      ob->query_ability_buff("con"),2000,
                                      ob->query_ability_buff("dex"),2000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==上限加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【潜能上限】" HIM " %9d / %-9d"
                                      HIC "【体会上限】" HIM " %9d / %d\n"
                                      HIC "【内力上限】" HIM " %9d / %-9d"
                                      HIC "【精力上限】" HIM " %9d / %d\n"
                                      HIC "【气血上限】" HIM " %9d / %-9d"
                                      HIC "【精气上限】" HIM " %9d / %d\n\n",
                                      ob->query_ability_buff("max_potential"),10000000,
                                      ob->query_ability_buff("max_experience"),10000000,
                                      ob->query_ability_buff("max_neili"),2000000,
                                      ob->query_ability_buff("max_jingli"),1000000,
                                      ob->query_ability_buff("max_qi"),2000000,
                                      ob->query_ability_buff("max_jing"),1000000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==练功加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【研究次数】" HIY " %9d / %-9d"
                                      HIC "【研究效果】" HIY " %9s / %s\n"
                                      HIC "【练习次数】" HIY " %9d / %-9d"
                                      HIC "【练习效果】" HIY " %9s / %s\n"
                                      HIC "【学习次数】" HIY " %9d / %-9d"
                                      HIC "【学习效果】" HIY " %9s / %s\n"
                                      HIC "【汲取消耗】" HIY " %9d / %-9d"
                                      HIC "【汲取效果】" HIY " %9s / %s\n\n",
                                      ob->query_ability_buff("research_times"),2000,
                                      ob->query_ability_buff("research_effect")+"%","2000%",
                                      ob->query_ability_buff("practice_times"),2000,
                                      ob->query_ability_buff("practice_effect")+"%","2000%",
                                      ob->query_ability_buff("learn_times"),2000,
                                      ob->query_ability_buff("learn_effect")+"%","2000%",
                                      ob->query_ability_buff("derive_times"),2000,
                                      ob->query_ability_buff("derive_effect")+"%","2000%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==五行加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(RED "【毒 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    毒】" RED " %9s / %s\n"
                                      RED "【魔 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    魔】" RED " %9s / %s\n"
                                      RED "【金 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    金】" RED " %9s / %s\n"
                                      RED "【木 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    木】" RED " %9s / %s\n"
                                      RED "【水 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    水】" RED " %9s / %s\n"
                                      RED "【火 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    火】" RED " %9s / %s\n"
                                      RED "【土 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    土】" RED " %9s / %s\n\n",
                                      ob->query_ability_buff("add_poison")+"%","100%",ob->query_ability_buff("reduce_poison")+"%","100%",
                                      ob->query_ability_buff("add_magic")+"%","100%",ob->query_ability_buff("reduce_magic")+"%","100%",
                                      ob->query_ability_buff("add_metal")+"%","100%",ob->query_ability_buff("reduce_metal")+"%","100%",
                                      ob->query_ability_buff("add_wood")+"%","100%",ob->query_ability_buff("reduce_wood")+"%","100%",
                                      ob->query_ability_buff("add_water")+"%","100%",ob->query_ability_buff("reduce_water")+"%","100%",
                                      ob->query_ability_buff("add_fire")+"%","100%",ob->query_ability_buff("reduce_fire")+"%","100%",
                                      ob->query_ability_buff("add_earth")+"%","100%",ob->query_ability_buff("reduce_earth")+"%","100%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==状态恢复==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIB "【偷取内力】" HIB " %9s / %-9s"
                                      HIB "【偷取生命】" HIB " %9s / %s\n\n",
                                      ob->query_ability_buff("leech_neili")+"%","90%",
                                      ob->query_ability_buff("leech_qi")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==战斗加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(WHT "【攻击等级】" HIW " %9d / %-9d" NOR
                                      WHT "【防御等级】" HIW " %9d / %d\n" NOR
                                      WHT "【躲闪等级】" HIW " %9d / %-9d" NOR
                                      WHT "【招架等级】" HIW " %9d / %d\n" NOR
                                      WHT "【绝招命中】" HIW " %9s / %-9s" NOR
                                      WHT "【绝招防御】" HIW " %9s / %s\n" NOR
                                      WHT "【兵器伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【空手伤害】" HIG " %9d / %d\n" NOR
                                      WHT "【绝招伤害】" HIG " %9s / %-9s" NOR
                                      WHT "【战斗保护】" HIG " %9d / %d\n" NOR
                                      /*
                                      WHT "【附加伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【附加保护】" HIG " %9d / %d\n" NOR
                                      WHT "【改造伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【改造保护】" HIG " %9d / %d\n" NOR
                                      */
                                      WHT "【忽视招架】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视躲闪】" HIY " %9s / %s\n" NOR
                                      WHT "【忽视特攻】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视内防】" HIY " %9s / %s\n\n" NOR,
                                      ob->query_ability_buff("attack"),9000,
                                      ob->query_ability_buff("defense"),9000,
                                      ob->query_ability_buff("dodge"),9000,
                                      ob->query_ability_buff("parry"),9000,
                                      ob->query_ability_buff("ap_power")+"%","120%",
                                      ob->query_ability_buff("dp_power")+"%","120%",
                                      ob->query_ability_buff("damage"),200000,
                                      ob->query_ability_buff("unarmed_damage"),200000,
                                      ob->query_ability_buff("da_power")+"%","120%",
                                      ob->query_ability_buff("armor"),200000,
                                      //query_temp("apply/damage1", ob),200000,query_temp("apply/armor1", ob),200000,
                                      //query_temp("apply/damage2", ob),200000,query_temp("apply/armor2", ob),200000,
                                      ob->query_ability_buff("avoid_parry")+"%","90%",
                                      ob->query_ability_buff("avoid_dodge")+"%","90%",
                                      ob->query_ability_buff("avoid_attack")+"%","90%",
                                      ob->query_ability_buff("avoid_force")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==高级属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIW "【化解忙乱】" HIM " %9d / %-9d"
                                      HIW "【寻 宝 率】" HIM " %9s / %s\n"
                                      HIW "【双倍伤害】" CYN " %9s / %-9s"
                                      HIW "【伤转内力】" CYN " %9s / %s\n"
                                      HIW "【致    盲】" CYN " %9s / %-9s"
                                      HIW "【忽视致盲】" CYN " %9s / %s\n"
                                      HIW "【穿透破甲】" CYN " %9s / %-9s"
                                      HIW "【百毒不侵】" CYN " %9s / %s\n"
                                      HIW "【战神附体】" CYN " %9s / %-9s\n\n",
                                      ob->query_ability_buff("reduce_busy"),90,
                                      ob->query_ability_buff("magic_find")+"%","300%",
                                      ob->query_ability_buff("double_damage")+"%","200%",
                                      ob->query_ability_buff("qi_abs_neili")+"%","90%",
                                      ob->query_ability_buff("add_blind")+"%","90%",
                                      ob->query_ability_buff("avoid_blind")+"%","90%",
                                      ob->query_ability_buff("through_armor")+"%","90%",
                                      ob->query_ability_buff("avoid_poison")+"%","100%",
                                      ob->query_ability_buff("full_self")+"%","90%");

                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==终极属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIY "【冰    冻】" HIM " %9s / %-9s"
                                      HIY "【忽视冰冻】" HIM " %9s / %s\n"
                                      /*
                                      HIY "【眩    晕】" HIM " %9s / %-9s"
                                      HIY "【忽视眩晕】" HIM " %9s / %s\n"
                                      */
                                      HIY "【遗    忘】" HIM " %9s / %-9s"
                                      HIY "【忽视遗忘】" HIM " %9s / %s\n"
                                      HIY "【忙    乱】" HIM " %9d / %-9d"
                                      HIY "【忽视忙乱】" HIM " %9s / %s\n"
                                      HIY "【虚    弱】" HIM " %9s / %-9s"
                                      HIY "【忽视虚弱】" HIM " %9s / %s\n"
                                      HIY "【追加伤害】" HIM " %9s / %-9s"
                                      HIY "【化解伤害】" HIM " %9s / %s\n"
                                      HIY "【伤害反噬】" HIM " %9s / %-9s"
                                      HIY "【浴血重生】" HIM " %9s / %s\n"
                                      HIY "【致命一击】" HIM " %9s / %-9s"
                                      HIY "【提升技能】" HIM " %9d / %d\n\n",
                                      ob->query_ability_buff("add_freeze")+"%","90%",ob->query_ability_buff("avoid_freeze")+"%","90%",
                                      /*
                                      ob->query_ability_buff("add_dizziness")+"%","90%",ob->query_ability_buff("avoid_dizziness")+"%","90%",                    ;:207c
                                      */
                                      ob->query_ability_buff("add_forget")+"%","90%",ob->query_ability_buff("avoid_forget")+"%","90%",
                                      ob->query_ability_buff("add_busy"),90,ob->query_ability_buff("avoid_busy")+"%","90%",
                                      ob->query_ability_buff("add_weak")+"%","90%",ob->query_ability_buff("avoid_weak")+"%","90%",
                                      ob->query_ability_buff("add_damage")+"%","200%",
                                      ob->query_ability_buff("reduce_damage")+"%","90%",
                                      ob->query_ability_buff("counter_damage")+"%","90%",ob->query_ability_buff("avoid_die")+"%","90%",
                                      ob->query_ability_buff("fatal_blow")+"%","90%",ob->query_ability_buff("add_skill"),1200);

                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==王者归来==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "在%s里已经历练了 " NOR + HIC "%s\n" NOR,
                                      LOCAL_MUD_NAME(), time_period(query("online_time", ob)));

                        if( MEMBER_D->is_valid_member(ob) )
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "无限制\n" NOR);
                        else
                        {
                                if( query("online_time", ob)/3<query("offline_time", ob) )
                                        set("offline_time",query("online_time",  ob)/3, ob);
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "%s\n" NOR,
                                              time_period(query("online_time", ob)/3-query("offline_time", ob)));
                        }

                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的双倍经验时间还余 " NOR + HIW "%s\n" NOR,
                                      time_period(query("time_reward/quest", ob)));
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的高效练功时间还余 " NOR + HIM "%s\n" NOR,
                                      time_period(query("time_reward/study", ob)));


                        me->start_more(sp);
                        return 1;
        }

        if( arg && (arg == "-equipment"
        ||  sscanf(arg, "-equipment %s", arg)
        ||  sscanf(arg, "%s -equipment", arg)) )
        {
                if( arg == "-equipment" )
                        ob = me;
                else
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看谁的状态？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看谁的状态？\n");

                } else
                        return notify_fail("只有巫师能察看别人的状态。\n");

                        sp = HIM + (ob == me ? "你" : ob->name(1)) + "目前的能力进阶附加属性效果一览\n" NOR;
                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==天赋加成==------------------------------" HIC "≡\n\n" NOR;

                        sp += sprintf(HIC "【臂力附加】" HIG " %9d / %-9d"
                                      HIC "【悟性附加】" HIG " %9d / %d\n"
                                      HIC "【根骨附加】" HIG " %9d / %-9d"
                                      HIC "【身法附加】" HIG " %9d / %d\n\n",
                                      ob->query_equipment_buff("str"),2000,
                                      ob->query_equipment_buff("int"),2000,
                                      ob->query_equipment_buff("con"),2000,
                                      ob->query_equipment_buff("dex"),2000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==上限加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【潜能上限】" HIM " %9d / %-9d"
                                      HIC "【体会上限】" HIM " %9d / %d\n"
                                      HIC "【内力上限】" HIM " %9d / %-9d"
                                      HIC "【精力上限】" HIM " %9d / %d\n"
                                      HIC "【气血上限】" HIM " %9d / %-9d"
                                      HIC "【精气上限】" HIM " %9d / %d\n\n",
                                      ob->query_equipment_buff("max_potential"),10000000,
                                      ob->query_equipment_buff("max_experience"),10000000,
                                      ob->query_equipment_buff("max_neili"),2000000,
                                      ob->query_equipment_buff("max_jingli"),1000000,
                                      ob->query_equipment_buff("max_qi"),2000000,
                                      ob->query_equipment_buff("max_jing"),1000000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==练功加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【研究次数】" HIY " %9d / %-9d"
                                      HIC "【研究效果】" HIY " %9s / %s\n"
                                      HIC "【练习次数】" HIY " %9d / %-9d"
                                      HIC "【练习效果】" HIY " %9s / %s\n"
                                      HIC "【学习次数】" HIY " %9d / %-9d"
                                      HIC "【学习效果】" HIY " %9s / %s\n"
                                      HIC "【汲取消耗】" HIY " %9d / %-9d"
                                      HIC "【汲取效果】" HIY " %9s / %s\n\n",
                                      ob->query_equipment_buff("research_times"),2000,
                                      ob->query_equipment_buff("research_effect")+"%","2000%",
                                      ob->query_equipment_buff("practice_times"),2000,
                                      ob->query_equipment_buff("practice_effect")+"%","2000%",
                                      ob->query_equipment_buff("learn_times"),2000,
                                      ob->query_equipment_buff("learn_effect")+"%","2000%",
                                      ob->query_equipment_buff("derive_times"),2000,
                                      ob->query_equipment_buff("derive_effect")+"%","2000%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==五行加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(RED "【毒 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    毒】" RED " %9s / %s\n"
                                      RED "【魔 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    魔】" RED " %9s / %s\n"
                                      RED "【金 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    金】" RED " %9s / %s\n"
                                      RED "【木 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    木】" RED " %9s / %s\n"
                                      RED "【水 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    水】" RED " %9s / %s\n"
                                      RED "【火 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    火】" RED " %9s / %s\n"
                                      RED "【土 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    土】" RED " %9s / %s\n\n",
                                      ob->query_equipment_buff("add_poison")+"%","100%",ob->query_equipment_buff("reduce_poison")+"%","100%",
                                      ob->query_equipment_buff("add_magic")+"%","100%",ob->query_equipment_buff("reduce_magic")+"%","100%",
                                      ob->query_equipment_buff("add_metal")+"%","100%",ob->query_equipment_buff("reduce_metal")+"%","100%",
                                      ob->query_equipment_buff("add_wood")+"%","100%",ob->query_equipment_buff("reduce_wood")+"%","100%",
                                      ob->query_equipment_buff("add_water")+"%","100%",ob->query_equipment_buff("reduce_water")+"%","100%",
                                      ob->query_equipment_buff("add_fire")+"%","100%",ob->query_equipment_buff("reduce_fire")+"%","100%",
                                      ob->query_equipment_buff("add_earth")+"%","100%",ob->query_equipment_buff("reduce_earth")+"%","100%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==状态恢复==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIB "【偷取内力】" HIB " %9s / %-9s"
                                      HIB "【偷取生命】" HIB " %9s / %s\n\n",
                                      ob->query_equipment_buff("leech_neili")+"%","90%",
                                      ob->query_equipment_buff("leech_qi")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==战斗加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(WHT "【攻击等级】" HIW " %9d / %-9d" NOR
                                      WHT "【防御等级】" HIW " %9d / %d\n" NOR
                                      WHT "【躲闪等级】" HIW " %9d / %-9d" NOR
                                      WHT "【招架等级】" HIW " %9d / %d\n" NOR
                                      WHT "【绝招命中】" HIW " %9s / %-9s" NOR
                                      WHT "【绝招防御】" HIW " %9s / %s\n" NOR
                                      WHT "【兵器伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【空手伤害】" HIG " %9d / %d\n" NOR
                                      WHT "【绝招伤害】" HIG " %9s / %-9s" NOR
                                      WHT "【战斗保护】" HIG " %9d / %d\n" NOR
                                      /*
                                      WHT "【附加伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【附加保护】" HIG " %9d / %d\n" NOR
                                      WHT "【改造伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【改造保护】" HIG " %9d / %d\n" NOR
                                      */
                                      WHT "【忽视招架】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视躲闪】" HIY " %9s / %s\n" NOR
                                      WHT "【忽视特攻】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视内防】" HIY " %9s / %s\n\n" NOR,
                                      ob->query_equipment_buff("attack"),9000,
                                      ob->query_equipment_buff("defense"),9000,
                                      ob->query_equipment_buff("dodge"),9000,
                                      ob->query_equipment_buff("parry"),9000,
                                      ob->query_equipment_buff("ap_power")+"%","120%",
                                      ob->query_equipment_buff("dp_power")+"%","120%",
                                      ob->query_equipment_buff("damage"),200000,
                                      ob->query_equipment_buff("unarmed_damage"),200000,
                                      ob->query_equipment_buff("da_power")+"%","120%",
                                      ob->query_equipment_buff("armor"),200000,
                                      //query_temp("apply/damage1", ob),200000,query_temp("apply/armor1", ob),200000,
                                      //query_temp("apply/damage2", ob),200000,query_temp("apply/armor2", ob),200000,
                                      ob->query_equipment_buff("avoid_parry")+"%","90%",
                                      ob->query_equipment_buff("avoid_dodge")+"%","90%",
                                      ob->query_equipment_buff("avoid_attack")+"%","90%",
                                      ob->query_equipment_buff("avoid_force")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==高级属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIW "【化解忙乱】" HIM " %9d / %-9d"
                                      HIW "【寻 宝 率】" HIM " %9s / %s\n"
                                      HIW "【双倍伤害】" CYN " %9s / %-9s"
                                      HIW "【伤转内力】" CYN " %9s / %s\n"
                                      HIW "【致    盲】" CYN " %9s / %-9s"
                                      HIW "【忽视致盲】" CYN " %9s / %s\n"
                                      HIW "【穿透破甲】" CYN " %9s / %-9s"
                                      HIW "【百毒不侵】" CYN " %9s / %s\n"
                                      HIW "【战神附体】" CYN " %9s / %-9s\n\n",
                                      ob->query_equipment_buff("reduce_busy"),90,
                                      ob->query_equipment_buff("magic_find")+"%","300%",
                                      ob->query_equipment_buff("double_damage")+"%","200%",
                                      ob->query_equipment_buff("qi_abs_neili")+"%","90%",
                                      ob->query_equipment_buff("add_blind")+"%","90%",
                                      ob->query_equipment_buff("avoid_blind")+"%","90%",
                                      ob->query_equipment_buff("through_armor")+"%","90%",
                                      ob->query_equipment_buff("avoid_poison")+"%","100%",
                                      ob->query_equipment_buff("full_self")+"%","90%");

                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==终极属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIY "【冰    冻】" HIM " %9s / %-9s"
                                      HIY "【忽视冰冻】" HIM " %9s / %s\n"
                                      /*
                                      HIY "【眩    晕】" HIM " %9s / %-9s"
                                      HIY "【忽视眩晕】" HIM " %9s / %s\n"
                                      */
                                      HIY "【遗    忘】" HIM " %9s / %-9s"
                                      HIY "【忽视遗忘】" HIM " %9s / %s\n"
                                      HIY "【忙    乱】" HIM " %9d / %-9d"
                                      HIY "【忽视忙乱】" HIM " %9s / %s\n"
                                      HIY "【虚    弱】" HIM " %9s / %-9s"
                                      HIY "【忽视虚弱】" HIM " %9s / %s\n"
                                      HIY "【追加伤害】" HIM " %9s / %-9s"
                                      HIY "【化解伤害】" HIM " %9s / %s\n"
                                      HIY "【伤害反噬】" HIM " %9s / %-9s"
                                      HIY "【浴血重生】" HIM " %9s / %s\n"
                                      HIY "【致命一击】" HIM " %9s / %-9s"
                                      HIY "【提升技能】" HIM " %9d / %d\n\n",
                                      ob->query_equipment_buff("add_freeze")+"%","90%",ob->query_equipment_buff("avoid_freeze")+"%","90%",
                                      /*
                                      ob->query_equipment_buff("add_dizziness")+"%","90%",ob->query_equipment_buff("avoid_dizziness")+"%","90%",                    ;:207c
                                      */
                                      ob->query_equipment_buff("add_forget")+"%","90%",ob->query_equipment_buff("avoid_forget")+"%","90%",
                                      ob->query_equipment_buff("add_busy"),90,ob->query_equipment_buff("avoid_busy")+"%","90%",
                                      ob->query_equipment_buff("add_weak")+"%","90%",ob->query_equipment_buff("avoid_weak")+"%","90%",
                                      ob->query_equipment_buff("add_damage")+"%","200%",
                                      ob->query_equipment_buff("reduce_damage")+"%","90%",
                                      ob->query_equipment_buff("counter_damage")+"%","90%",ob->query_equipment_buff("avoid_die")+"%","90%",
                                      ob->query_equipment_buff("fatal_blow")+"%","90%",ob->query_equipment_buff("add_skill"),1200);

                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==王者归来==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "在%s里已经历练了 " NOR + HIC "%s\n" NOR,
                                      LOCAL_MUD_NAME(), time_period(query("online_time", ob)));

                        if( MEMBER_D->is_valid_member(ob) )
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "无限制\n" NOR);
                        else
                        {
                                if( query("online_time", ob)/3<query("offline_time", ob) )
                                        set("offline_time",query("online_time",  ob)/3, ob);
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "%s\n" NOR,
                                              time_period(query("online_time", ob)/3-query("offline_time", ob)));
                        }

                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的双倍经验时间还余 " NOR + HIW "%s\n" NOR,
                                      time_period(query("time_reward/quest", ob)));
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的高效练功时间还余 " NOR + HIM "%s\n" NOR,
                                      time_period(query("time_reward/study", ob)));


                        me->start_more(sp);
                        return 1;
        }

        if( arg && (arg == "-talent"
        ||  sscanf(arg, "-talent %s", arg)
        ||  sscanf(arg, "%s -talent", arg)) )
        {
                if( arg == "-talent" )
                        ob = me;
                else
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看谁的状态？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看谁的状态？\n");

                } else
                        return notify_fail("只有巫师能察看别人的状态。\n");

                        sp = HIM + (ob == me ? "你" : ob->name(1)) + "目前的能力进阶附加属性效果一览\n" NOR;
                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==天赋加成==------------------------------" HIC "≡\n\n" NOR;

                        sp += sprintf(HIC "【臂力附加】" HIG " %9d / %-9d"
                                      HIC "【悟性附加】" HIG " %9d / %d\n"
                                      HIC "【根骨附加】" HIG " %9d / %-9d"
                                      HIC "【身法附加】" HIG " %9d / %d\n\n",
                                      ob->query_talent_buff("str"),2000,
                                      ob->query_talent_buff("int"),2000,
                                      ob->query_talent_buff("con"),2000,
                                      ob->query_talent_buff("dex"),2000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==上限加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【潜能上限】" HIM " %9d / %-9d"
                                      HIC "【体会上限】" HIM " %9d / %d\n"
                                      HIC "【内力上限】" HIM " %9d / %-9d"
                                      HIC "【精力上限】" HIM " %9d / %d\n"
                                      HIC "【气血上限】" HIM " %9d / %-9d"
                                      HIC "【精气上限】" HIM " %9d / %d\n\n",
                                      ob->query_talent_buff("max_potential"),10000000,
                                      ob->query_talent_buff("max_experience"),10000000,
                                      ob->query_talent_buff("max_neili"),2000000,
                                      ob->query_talent_buff("max_jingli"),1000000,
                                      ob->query_talent_buff("max_qi"),2000000,
                                      ob->query_talent_buff("max_jing"),1000000);
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==练功加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIC "【研究次数】" HIY " %9d / %-9d"
                                      HIC "【研究效果】" HIY " %9s / %s\n"
                                      HIC "【练习次数】" HIY " %9d / %-9d"
                                      HIC "【练习效果】" HIY " %9s / %s\n"
                                      HIC "【学习次数】" HIY " %9d / %-9d"
                                      HIC "【学习效果】" HIY " %9s / %s\n"
                                      HIC "【汲取消耗】" HIY " %9d / %-9d"
                                      HIC "【汲取效果】" HIY " %9s / %s\n\n",
                                      ob->query_talent_buff("research_times"),2000,
                                      ob->query_talent_buff("research_effect")+"%","2000%",
                                      ob->query_talent_buff("practice_times"),2000,
                                      ob->query_talent_buff("practice_effect")+"%","2000%",
                                      ob->query_talent_buff("learn_times"),2000,
                                      ob->query_talent_buff("learn_effect")+"%","2000%",
                                      ob->query_talent_buff("derive_times"),2000,
                                      ob->query_talent_buff("derive_effect")+"%","2000%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==五行加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(RED "【毒 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    毒】" RED " %9s / %s\n"
                                      RED "【魔 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    魔】" RED " %9s / %s\n"
                                      RED "【金 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    金】" RED " %9s / %s\n"
                                      RED "【木 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    木】" RED " %9s / %s\n"
                                      RED "【水 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    水】" RED " %9s / %s\n"
                                      RED "【火 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    火】" RED " %9s / %s\n"
                                      RED "【土 伤 害】" RED " %9s / %-9s"
                                      RED "【抗    土】" RED " %9s / %s\n\n",
                                      ob->query_talent_buff("add_poison")+"%","100%",ob->query_talent_buff("reduce_poison")+"%","100%",
                                      ob->query_talent_buff("add_magic")+"%","100%",ob->query_talent_buff("reduce_magic")+"%","100%",
                                      ob->query_talent_buff("add_metal")+"%","100%",ob->query_talent_buff("reduce_metal")+"%","100%",
                                      ob->query_talent_buff("add_wood")+"%","100%",ob->query_talent_buff("reduce_wood")+"%","100%",
                                      ob->query_talent_buff("add_water")+"%","100%",ob->query_talent_buff("reduce_water")+"%","100%",
                                      ob->query_talent_buff("add_fire")+"%","100%",ob->query_talent_buff("reduce_fire")+"%","100%",
                                      ob->query_talent_buff("add_earth")+"%","100%",ob->query_talent_buff("reduce_earth")+"%","100%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==状态恢复==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIB "【偷取内力】" HIB " %9s / %-9s"
                                      HIB "【偷取生命】" HIB " %9s / %s\n\n",
                                      ob->query_talent_buff("leech_neili")+"%","90%",
                                      ob->query_talent_buff("leech_qi")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==战斗加成==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(WHT "【攻击等级】" HIW " %9d / %-9d" NOR
                                      WHT "【防御等级】" HIW " %9d / %d\n" NOR
                                      WHT "【躲闪等级】" HIW " %9d / %-9d" NOR
                                      WHT "【招架等级】" HIW " %9d / %d\n" NOR
                                      WHT "【绝招命中】" HIW " %9s / %-9s" NOR
                                      WHT "【绝招防御】" HIW " %9s / %s\n" NOR
                                      WHT "【兵器伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【空手伤害】" HIG " %9d / %d\n" NOR
                                      WHT "【绝招伤害】" HIG " %9s / %-9s" NOR
                                      WHT "【战斗保护】" HIG " %9d / %d\n" NOR
                                      /*
                                      WHT "【附加伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【附加保护】" HIG " %9d / %d\n" NOR
                                      WHT "【改造伤害】" HIG " %9d / %-9d" NOR
                                      WHT "【改造保护】" HIG " %9d / %d\n" NOR
                                      */
                                      WHT "【忽视招架】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视躲闪】" HIY " %9s / %s\n" NOR
                                      WHT "【忽视特攻】" HIY " %9s / %-9s" NOR
                                      WHT "【忽视内防】" HIY " %9s / %s\n\n" NOR,
                                      ob->query_talent_buff("attack"),9000,
                                      ob->query_talent_buff("defense"),9000,
                                      ob->query_talent_buff("dodge"),9000,
                                      ob->query_talent_buff("parry"),9000,
                                      ob->query_talent_buff("ap_power")+"%","120%",
                                      ob->query_talent_buff("dp_power")+"%","120%",
                                      ob->query_talent_buff("damage"),200000,
                                      ob->query_talent_buff("unarmed_damage"),200000,
                                      ob->query_talent_buff("da_power")+"%","120%",
                                      ob->query_talent_buff("armor"),200000,
                                      //query_temp("apply/damage1", ob),200000,query_temp("apply/armor1", ob),200000,
                                      //query_temp("apply/damage2", ob),200000,query_temp("apply/armor2", ob),200000,
                                      ob->query_talent_buff("avoid_parry")+"%","90%",
                                      ob->query_talent_buff("avoid_dodge")+"%","90%",
                                      ob->query_talent_buff("avoid_attack")+"%","90%",
                                      ob->query_talent_buff("avoid_force")+"%","90%");
                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==高级属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIW "【化解忙乱】" HIM " %9d / %-9d"
                                      HIW "【寻 宝 率】" HIM " %9s / %s\n"
                                      HIW "【双倍伤害】" CYN " %9s / %-9s"
                                      HIW "【伤转内力】" CYN " %9s / %s\n"
                                      HIW "【致    盲】" CYN " %9s / %-9s"
                                      HIW "【忽视致盲】" CYN " %9s / %s\n"
                                      HIW "【穿透破甲】" CYN " %9s / %-9s"
                                      HIW "【百毒不侵】" CYN " %9s / %s\n"
                                      HIW "【战神附体】" CYN " %9s / %-9s\n\n",
                                      ob->query_talent_buff("reduce_busy"),90,
                                      ob->query_talent_buff("magic_find")+"%","300%",
                                      ob->query_talent_buff("double_damage")+"%","200%",
                                      ob->query_talent_buff("qi_abs_neili")+"%","90%",
                                      ob->query_talent_buff("add_blind")+"%","90%",
                                      ob->query_talent_buff("avoid_blind")+"%","90%",
                                      ob->query_talent_buff("through_armor")+"%","90%",
                                      ob->query_talent_buff("avoid_poison")+"%","100%",
                                      ob->query_talent_buff("full_self")+"%","90%");

                        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==终极属性==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIY "【冰    冻】" HIM " %9s / %-9s"
                                      HIY "【忽视冰冻】" HIM " %9s / %s\n"
                                      /*
                                      HIY "【眩    晕】" HIM " %9s / %-9s"
                                      HIY "【忽视眩晕】" HIM " %9s / %s\n"
                                      */
                                      HIY "【遗    忘】" HIM " %9s / %-9s"
                                      HIY "【忽视遗忘】" HIM " %9s / %s\n"
                                      HIY "【忙    乱】" HIM " %9d / %-9d"
                                      HIY "【忽视忙乱】" HIM " %9s / %s\n"
                                      HIY "【虚    弱】" HIM " %9s / %-9s"
                                      HIY "【忽视虚弱】" HIM " %9s / %s\n"
                                      HIY "【追加伤害】" HIM " %9s / %-9s"
                                      HIY "【化解伤害】" HIM " %9s / %s\n"
                                      HIY "【伤害反噬】" HIM " %9s / %-9s"
                                      HIY "【浴血重生】" HIM " %9s / %s\n"
                                      HIY "【致命一击】" HIM " %9s / %-9s"
                                      HIY "【提升技能】" HIM " %9d / %d\n\n",
                                      ob->query_talent_buff("add_freeze")+"%","90%",ob->query_talent_buff("avoid_freeze")+"%","90%",
                                      /*
                                      ob->query_talent_buff("add_dizziness")+"%","90%",ob->query_talent_buff("avoid_dizziness")+"%","90%",                    ;:207c
                                      */
                                      ob->query_talent_buff("add_forget")+"%","90%",ob->query_talent_buff("avoid_forget")+"%","90%",
                                      ob->query_talent_buff("add_busy"),90,ob->query_talent_buff("avoid_busy")+"%","90%",
                                      ob->query_talent_buff("add_weak")+"%","90%",ob->query_talent_buff("avoid_weak")+"%","90%",
                                      ob->query_talent_buff("add_damage")+"%","200%",
                                      ob->query_talent_buff("reduce_damage")+"%","90%",
                                      ob->query_talent_buff("counter_damage")+"%","90%",ob->query_talent_buff("avoid_die")+"%","90%",
                                      ob->query_talent_buff("fatal_blow")+"%","90%",ob->query_talent_buff("add_skill"),1200);

                        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
                        sp += HIC "≡" HIY "------------------------------==王者归来==------------------------------" HIC "≡\n\n" NOR;
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "在%s里已经历练了 " NOR + HIC "%s\n" NOR,
                                      LOCAL_MUD_NAME(), time_period(query("online_time", ob)));

                        if( MEMBER_D->is_valid_member(ob) )
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "无限制\n" NOR);
                        else
                        {
                                if( query("online_time", ob)/3<query("offline_time", ob) )
                                        set("offline_time",query("online_time",  ob)/3, ob);
                                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "%s\n" NOR,
                                              time_period(query("online_time", ob)/3-query("offline_time", ob)));
                        }

                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的双倍经验时间还余 " NOR + HIW "%s\n" NOR,
                                      time_period(query("time_reward/quest", ob)));
                        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的高效练功时间还余 " NOR + HIM "%s\n" NOR,
                                      time_period(query("time_reward/study", ob)));


                        me->start_more(sp);
                        return 1;
        }

        if (arg && arg != "")
        {
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看谁的状态？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看谁的状态？\n");

                } else
                        return notify_fail("只有巫师能察看别人的状态。\n");
        } else
                ob = me;

        sp = HIM + (ob == me ? "你" : ob->name(1)) + "目前的各附加属性效果一览\n" NOR;
        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
        sp += HIC "≡" HIY "------------------------------==天赋加成==------------------------------" HIC "≡\n\n" NOR;

        sp += sprintf(HIC "【臂力附加】" HIG " %9d / %-9d"
                      HIC "【悟性附加】" HIG " %9d / %d\n"
                      HIC "【根骨附加】" HIG " %9d / %-9d"
                      HIC "【身法附加】" HIG " %9d / %d\n\n",
                      ob->query_all_buff("str"),2000,
                      ob->query_all_buff("int"),2000,
                      ob->query_all_buff("con"),2000,
                      ob->query_all_buff("dex"),2000);
        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
        sp += HIC "≡" HIY "------------------------------==上限加成==------------------------------" HIC "≡\n\n" NOR;
        sp += sprintf(HIC "【潜能上限】" HIM " %9d / %-9d"
                      HIC "【体会上限】" HIM " %9d / %d\n"
                      HIC "【内力上限】" HIM " %9d / %-9d"
                      HIC "【精力上限】" HIM " %9d / %d\n"
                      HIC "【气血上限】" HIM " %9d / %-9d"
                      HIC "【精气上限】" HIM " %9d / %d\n\n",
                      ob->query_all_buff("max_potential"),10000000,
                      ob->query_all_buff("max_experience"),10000000,
                      ob->query_all_buff("max_neili"),2000000,
                      ob->query_all_buff("max_jingli"),1000000,
                      ob->query_all_buff("max_qi"),2000000,
                      ob->query_all_buff("max_jing"),1000000);
        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
        sp += HIC "≡" HIY "------------------------------==练功加成==------------------------------" HIC "≡\n\n" NOR;
        sp += sprintf(HIC "【研究次数】" HIY " %9d / %-9d"
                      HIC "【研究效果】" HIY " %9s / %s\n"
                      HIC "【练习次数】" HIY " %9d / %-9d"
                      HIC "【练习效果】" HIY " %9s / %s\n"
                      HIC "【学习次数】" HIY " %9d / %-9d"
                      HIC "【学习效果】" HIY " %9s / %s\n"
                      HIC "【汲取消耗】" HIY " %9d / %-9d"
                      HIC "【汲取效果】" HIY " %9s / %s\n\n",
                      ob->query_all_buff("research_times"),2000,
                      ob->query_all_buff("research_effect")+"%","2000%",
                      ob->query_all_buff("practice_times"),2000,
                      ob->query_all_buff("practice_effect")+"%","2000%",
                      ob->query_all_buff("learn_times"),2000,
                      ob->query_all_buff("learn_effect")+"%","2000%",
                      ob->query_all_buff("derive_times"),2000,
                      ob->query_all_buff("derive_effect")+"%","2000%");
        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
        sp += HIC "≡" HIY "------------------------------==五行加成==------------------------------" HIC "≡\n\n" NOR;
        sp += sprintf(RED "【毒 伤 害】" RED " %9s / %-9s"
                      RED "【抗    毒】" RED " %9s / %s\n"
                      RED "【魔 伤 害】" RED " %9s / %-9s"
                      RED "【抗    魔】" RED " %9s / %s\n"
                      RED "【金 伤 害】" RED " %9s / %-9s"
                      RED "【抗    金】" RED " %9s / %s\n"
                      RED "【木 伤 害】" RED " %9s / %-9s"
                      RED "【抗    木】" RED " %9s / %s\n"
                      RED "【水 伤 害】" RED " %9s / %-9s"
                      RED "【抗    水】" RED " %9s / %s\n"
                      RED "【火 伤 害】" RED " %9s / %-9s"
                      RED "【抗    火】" RED " %9s / %s\n"
                      RED "【土 伤 害】" RED " %9s / %-9s"
                      RED "【抗    土】" RED " %9s / %s\n\n",
                      ob->query_all_buff("add_poison")+"%","100%",ob->query_all_buff("reduce_poison")+"%","100%",
                      ob->query_all_buff("add_magic")+"%","100%",ob->query_all_buff("reduce_magic")+"%","100%",
                      ob->query_all_buff("add_metal")+"%","100%",ob->query_all_buff("reduce_metal")+"%","100%",
                      ob->query_all_buff("add_wood")+"%","100%",ob->query_all_buff("reduce_wood")+"%","100%",
                      ob->query_all_buff("add_water")+"%","100%",ob->query_all_buff("reduce_water")+"%","100%",
                      ob->query_all_buff("add_fire")+"%","100%",ob->query_all_buff("reduce_fire")+"%","100%",
                      ob->query_all_buff("add_earth")+"%","100%",ob->query_all_buff("reduce_earth")+"%","100%");
        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
        sp += HIC "≡" HIY "------------------------------==状态恢复==------------------------------" HIC "≡\n\n" NOR;
        sp += sprintf(HIB "【偷取内力】" HIB " %9s / %-9s"
                      HIB "【偷取生命】" HIB " %9s / %s\n\n",
                      ob->query_all_buff("leech_neili")+"%","90%",
                      ob->query_all_buff("leech_qi")+"%","90%");
        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
        sp += HIC "≡" HIY "------------------------------==战斗加成==------------------------------" HIC "≡\n\n" NOR;
        sp += sprintf(WHT "【攻击等级】" HIW " %9d / %-9d" NOR
                      WHT "【防御等级】" HIW " %9d / %d\n" NOR
                      WHT "【躲闪等级】" HIW " %9d / %-9d" NOR
                      WHT "【招架等级】" HIW " %9d / %d\n" NOR
                      WHT "【绝招命中】" HIW " %9s / %-9s" NOR
                      WHT "【绝招防御】" HIW " %9s / %s\n" NOR
                      WHT "【兵器伤害】" HIG " %9d / %-9d" NOR
                      WHT "【空手伤害】" HIG " %9d / %d\n" NOR
                      WHT "【绝招伤害】" HIG " %9s / %-9s" NOR
                      WHT "【战斗保护】" HIG " %9d / %d\n" NOR
                      /*
                      WHT "【附加伤害】" HIG " %9d / %-9d" NOR
                      WHT "【附加保护】" HIG " %9d / %d\n" NOR
                      WHT "【改造伤害】" HIG " %9d / %-9d" NOR
                      WHT "【改造保护】" HIG " %9d / %d\n" NOR
                      */
                      WHT "【忽视招架】" HIY " %9s / %-9s" NOR
                      WHT "【忽视躲闪】" HIY " %9s / %s\n" NOR
                      WHT "【忽视特攻】" HIY " %9s / %-9s" NOR
                      WHT "【忽视内防】" HIY " %9s / %s\n\n" NOR,
                      ob->query_all_buff("attack"),9000,
                      ob->query_all_buff("defense"),9000,
                      ob->query_all_buff("dodge"),9000,
                      ob->query_all_buff("parry"),9000,
                      ob->query_all_buff("ap_power")+"%","120%",
                      ob->query_all_buff("dp_power")+"%","120%",
                      ob->query_all_buff("damage"),200000,
                      ob->query_all_buff("unarmed_damage"),200000,
                      ob->query_all_buff("da_power")+"%","120%",
                      ob->query_all_buff("armor"),200000,
                      //query_temp("apply/damage1", ob),200000,query_temp("apply/armor1", ob),200000,
                      //query_temp("apply/damage2", ob),200000,query_temp("apply/armor2", ob),200000,
                      ob->query_all_buff("avoid_parry")+"%","90%",
                      ob->query_all_buff("avoid_dodge")+"%","90%",
                      ob->query_all_buff("avoid_attack")+"%","90%",
                      ob->query_all_buff("avoid_force")+"%","90%");
        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
        sp += HIC "≡" HIY "------------------------------==高级属性==------------------------------" HIC "≡\n\n" NOR;
        sp += sprintf(HIW "【化解忙乱】" HIM " %9d / %-9d"
                      HIW "【寻 宝 率】" HIM " %9s / %s\n"
                      HIW "【双倍伤害】" CYN " %9s / %-9s"
                      HIW "【伤转内力】" CYN " %9s / %s\n"
                      HIW "【致    盲】" CYN " %9s / %-9s"
                      HIW "【忽视致盲】" CYN " %9s / %s\n"
                      HIW "【穿透破甲】" CYN " %9s / %-9s"
                      HIW "【百毒不侵】" CYN " %9s / %s\n"
                      HIW "【战神附体】" CYN " %9s / %-9s\n\n",
                      ob->query_all_buff("reduce_busy"),90,
                      ob->query_all_buff("magic_find")+"%","300%",
                      ob->query_all_buff("double_damage")+"%","200%",
                      ob->query_all_buff("qi_abs_neili")+"%","90%",
                      ob->query_all_buff("add_blind")+"%","90%",
                      ob->query_all_buff("avoid_blind")+"%","90%",
                      ob->query_all_buff("through_armor")+"%","90%",
                      ob->query_all_buff("avoid_poison")+"%","100%",
                      ob->query_all_buff("full_self")+"%","90%");

        sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
        sp += HIC "≡" HIY "------------------------------==终极属性==------------------------------" HIC "≡\n\n" NOR;
        sp += sprintf(HIY "【冰    冻】" HIM " %9s / %-9s"
                      HIY "【忽视冰冻】" HIM " %9s / %s\n"
                      /*
                      HIY "【眩    晕】" HIM " %9s / %-9s"
                      HIY "【忽视眩晕】" HIM " %9s / %s\n"
                      */
                      HIY "【遗    忘】" HIM " %9s / %-9s"
                      HIY "【忽视遗忘】" HIM " %9s / %s\n"
                      HIY "【忙    乱】" HIM " %9d / %-9d"
                      HIY "【忽视忙乱】" HIM " %9s / %s\n"
                      HIY "【虚    弱】" HIM " %9s / %-9s"
                      HIY "【忽视虚弱】" HIM " %9s / %s\n"
                      HIY "【追加伤害】" HIM " %9s / %-9s"
                      HIY "【化解伤害】" HIM " %9s / %s\n"
                      HIY "【伤害反噬】" HIM " %9s / %-9s"
                      HIY "【浴血重生】" HIM " %9s / %s\n"
                      HIY "【致命一击】" HIM " %9s / %-9s"
                      HIY "【提升技能】" HIM " %9d / %d\n\n",
                      ob->query_all_buff("add_freeze")+"%","90%",ob->query_all_buff("avoid_freeze")+"%","90%",
                      /*
                      ob->query_all_buff("add_dizziness")+"%","90%",ob->query_all_buff("avoid_dizziness")+"%","90%",                    ;:207c
                      */
                      ob->query_all_buff("add_forget")+"%","90%",ob->query_all_buff("avoid_forget")+"%","90%",
                      ob->query_all_buff("add_busy"),90,ob->query_all_buff("avoid_busy")+"%","90%",
                      ob->query_all_buff("add_weak")+"%","90%",ob->query_all_buff("avoid_weak")+"%","90%",
                      ob->query_all_buff("add_damage")+"%","200%",
                      ob->query_all_buff("reduce_damage")+"%","90%",
                      ob->query_all_buff("counter_damage")+"%","90%",ob->query_all_buff("avoid_die")+"%","90%",
                      ob->query_all_buff("fatal_blow")+"%","90%",ob->query_all_buff("add_skill"),1200);

        //sp += HIC "≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
        sp += HIC "≡" HIY "------------------------------==王者归来==------------------------------" HIC "≡\n\n" NOR;
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "在%s里已经历练了 " NOR + HIC "%s\n" NOR,
                        LOCAL_MUD_NAME(), time_period(query("online_time", ob)));

        if (MEMBER_D->is_valid_member(ob))
                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "无限制\n" NOR);
        else
        {
                if( query("online_time", ob)/3<query("offline_time", ob) )
                        set("offline_time",query("online_time",  ob)/3, ob);
                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "%s\n" NOR,
                              time_period(query("online_time", ob)/3-query("offline_time", ob)));
        }

        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "下线保留物品时间还剩下 " NOR + HIW "%s\n" NOR,
                      (query("srv/quit_save", ob)-time()) > 0 ? time_period(query("srv/quit_save", ob)-time()) : "零秒");

        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的双倍经验时间还余 " NOR + HIW "%s\n" NOR,
                      time_period(query("time_reward/quest", ob)));
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的高效练功时间还余 " NOR + HIM "%s\n" NOR,
                      time_period(query("time_reward/study", ob)));


        me->start_more(sp);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：istat [-jingmai] [-yuanshen] [-ability] [-skillmix] [-equipment] [-talent]
          istat [-jingmai] [-yuanshen] [-ability] [-skillmix] [-equipment] [-talent] <对象名称>  （巫师专用）

这个指令可以显示你或指定对象的各种附加状态等数值。

HELP);
        return 1;
}
