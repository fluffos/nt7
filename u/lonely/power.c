// This program is a part of NT MudLIB
// power.c

#include <ansi.h>
#include <combat.h>

#define LINE  HIC "≡" HIY "────────────────────────" HIC "≡\n" NOR
#define LINE2 HIC "≡" HIY "────────--==平招威力==--────────" HIC "≡\n" NOR
#define LINE3 HIC "≡" HIY "────────--==绝招威力==--────────" HIC "≡\n" NOR

inherit F_CLEAN_UP;
inherit F_SSERVER; 

int main(object me, string arg)
{
        object ob;
        string line;
        int str, damage_bonus;
        int ap1, ap2, ap3, ap4;
        int damage1, damage2, damage3, damage4;
        int pp1, pp2, dp1, dp2;
        object weapon, weapon2;
        mapping action, prepare;
        string *sk;     
        string skill, skill2;

        if( !wizardp(me) && time()-query_temp("last_power", me)<5 ) 
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n"); 

        set_temp("last_power", time(), me);
        MYGIFT_D->check_mygift(me, "newbie_mygift/power"); 
 
        if( arg && wizardp(me) )
        {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("你要察看谁的状态？\n");
        } else
                ob = me;
       
        if( objectp(weapon = query_temp("weapon", ob)) )
        {
                skill = query("skill_type", weapon);
                ap1 = COMBAT_D->skill_power(ob, skill, SKILL_USAGE_ATTACK);
                ap2 = attack_power(ob, skill);
                if ( objectp(weapon2 = query_temp("secondary_weapon", ob)) )
                {
                        skill2 = query("skill_type", weapon2);
                        ap3 = COMBAT_D->skill_power(ob, skill2, SKILL_USAGE_ATTACK);
                        ap4 = attack_power(ob, skill2);
                }
                else
                {
                        // 左手是空手
                        prepare = ob->query_skill_prepare();
                        sk = keys(prepare);
                        
                        if( sizeof(sk) ) skill2 = sk[0];
                        else skill2 = "unarmed";
                        ap3 = COMBAT_D->skill_power(ob, skill2, SKILL_USAGE_ATTACK);
                        ap4 = attack_power(ob, skill2);
                }
        } else
        {
                prepare = ob->query_skill_prepare();

                if( !prepare ) prepare = ([]);
                sk = keys(prepare);
        
                if( sizeof(sk) == 0 )
                        skill = "unarmed";
                else
                {
                        skill  = sk[0];
                        if( sizeof(sk) > 1 ) skill2 = sk[1];
                        else skill2 = "unarmed";
                }
                ap1 = COMBAT_D->skill_power(ob, skill, SKILL_USAGE_ATTACK);
                ap2 = attack_power(ob, skill);
                if( skill2 )
                {
                        ap3 = COMBAT_D->skill_power(ob, skill2, SKILL_USAGE_ATTACK);
                        ap4 = attack_power(ob, skill2);
                }
        }

        pp1 = COMBAT_D->skill_power(ob, "parry", SKILL_USAGE_DEFENSE);
        dp1 = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);
        pp2 = defense_power(ob, "parry");
        dp2 = defense_power(ob, "dodge");

        // 伤害等级
        if( weapon )
        {
                damage1 = ob->query_all_buff("damage");
                damage1 += ob->query_skill(skill, 1);
              
                damage2 = damage_power(ob, skill)+ob->query_all_buff("damage");
                if( skill2 )
                {
                        if( weapon2 )
                        {
                                damage3 = ob->query_all_buff("damage");
                                damage3 += ob->query_skill(skill2, 1);
                                damage4 = damage_power(ob, skill2)+ob->query_all_buff("damage");
                        }
                        else
                        {
                                damage3 = ob->query_all_buff("unarmed_damage");
                                damage3 += ob->query_skill(skill2, 1);
                                damage4 = damage_power(ob, skill2)+ob->query_all_buff("unarmed_damage");
                        }
                }
                
        }
        else
        {
                damage1 = ob->query_all_buff("unarmed_damage");
                damage1 += ob->query_skill(skill, 1);
                
                damage2 = damage_power(ob, skill)+ob->query_all_buff("unarmed_damage");;
                if( skill2 )
                {
                        damage3 = ob->query_all_buff("unarmed_damage");
                        damage3 += ob->query_skill(skill2, 1);
                        damage4 = damage_power(ob, skill2)+ob->query_all_buff("unarmed_damage");
                }
        }
        
        damage1 += query("jiali", ob);
        damage1 += damage1 / 30 * query("str", ob);
        damage3 += query("jiali", ob);
        damage3 += damage3 / 30 * query("str", ob);
                
        action = ob->query_action();
        if( mapp(action) && action["damage"] )
        {
                damage1 += action["damage"] * damage1 / 100;
                damage3 += action["damage"] * damage3 / 100;
        }
        
        if( query("character", ob) == "心狠手辣" ) 
        {
                damage1 += damage1 * 20 / 100;
                damage3 += damage3 * 20 / 100;
        }
                
        if( query("breakup", ob) )
        {
                damage1 += damage1 * 10 / 100;
                damage2 += damage2 * 10 / 100;
                damage3 += damage3 * 10 / 100;
                damage4 += damage4 * 10 / 100;
        }

        // 元神加成
        if( query("yuanshen_level", ob) )
        {
                damage1 += damage1 * query("yuanshen_level", ob) / 1000;
                damage2 += damage2 * query("yuanshen_level", ob) / 1000;
                damage3 += damage3 * query("yuanshen_level", ob) / 1000;
                damage4 += damage4 * query("yuanshen_level", ob) / 1000;
        }
               
        str = ob->query_str();
        
        damage_bonus = str;
        if( mapp(action) && action["force"] )
                damage_bonus += action["force"] * damage_bonus / 100;
         
        damage1 += damage_bonus;
        damage3 += damage_bonus;
               
        damage2 += damage2 / 300 * str;
        damage4 += damage4 / 300 * str;


        line = HIY "\n"+(ob == me ? "你" : ob->name())+"的战斗属性如下\n" NOR;
        line += LINE;
        line += LINE2;
        line += sprintf(NOR + WHT "右手攻击：%-20d左手攻击：%d\n" NOR, 
                        ap1, ap3);
                        
        line += sprintf(NOR + WHT "右手伤害：%-20d左手伤害：%d\n" WHT, 
                        damage1, damage3);
        
        line += sprintf(NOR + WHT "招架防御：%-20d躲闪防御：%d\n" WHT, 
                        pp1, dp1);

        line += LINE;
        line += LINE3;
        
        line += sprintf(NOR + WHT "右手攻击：%-20d左手攻击：%d\n" NOR, 
                        ap2, ap4);
                        
        line += sprintf(NOR + WHT "右手伤害：%-20d左手伤害：%d\n" WHT, 
                        damage2, damage4);
        
        line += sprintf(NOR + WHT "招架防御：%-20d躲闪防御：%d\n" WHT, 
                        pp2, dp2);
        
        line += LINE;

        write(line);

        return 1;       
}
