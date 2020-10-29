// This program is a part of NT MudLIB
// suxing.c 素心诀

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "素心决"; }
string *hbmsg = ({
HBMAG "\n$N" HBMAG "大喝一声，双手分使两招，一起攻出。\n" NOR,
HBMAG "\n$N" HBMAG "双手齐出，分使不同招式，令人眼花缭乱。\n" NOR,
HBMAG "\n$N" HBMAG "左右手分使两招，毫不停滞，宛如两人同时攻出。\n" NOR,
HBMAG "\n$N" HBMAG "左手一招，右手一招，两招来路各异，令人难以低档！\n" NOR,
});

int perform(object me, object target)
{
        string msg, pmsg;
        object weapon;
        int damage,ap,dp,married;
        int fmsk,delta;

        if( query("gender", me) != "女性" && wiz_level(me) < 2)
                return notify_fail("玉女素心只能是女的用！\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("素心诀只能对战斗中的对手使用。\n");

        if( me->query_skill_mapped("force") != "yunv-xinfa" )
                return notify_fail("你所用的并非玉女心法，无法施展素心诀！\n");

        if( me->query_skill("yunv-xinfa", 1) < 200 )
                return notify_fail("你的玉女心法火候未到，无法施展素心诀！\n");

        if( me->query_skill("yunv-jian", 1) < 200 )
                return notify_fail("你的玉女素心剑法火候未到，无法施展素心诀！\n");

        if( !(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的兵器不对。\n");

        if( me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("你必须激发玉女素心剑作为剑法才能够使用素心诀。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的内力不够使用玉女素心！\n");

        if( query("jingli", me)<500 )
                return notify_fail("你的精力不够使用玉女素心！\n");

        msg = HIW "$N突然面色庄重，双目清澄，手中" +query("name", weapon)+HIW+"蒙上了一层白霜，寒气逼人！\n"NOR;
        msg+= HIW "$N腾身而起，姿态无比婀娜飘逸，挥剑向$n"NOR+HIW"直刺过去，快愈流星！\n"NOR;

        ap = attack_power(me, "sword") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        fmsk = me->query_skill("taishang-wangqing",1);
        
        if( mapp(query("family", target)) && query("family/family_name", target) == "全真教" )
                ap += ap/3;

        if( query("can_learn/yunv-xinfa/wall", me) )
                ap *= 2;
                                
        delta = ABILITY_D->check_ability(me, "ap_power-hubo"); // 门派ab, 左右互博的命中＋５％   
        if( delta ) ap += ap*delta/100;
                
        if (ap/2 + random(ap) > dp || !living(target))
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                damage+= me->query_all_buff("damage");
                damage+= damage / 300 * me->query_str();
                damage += damage/100 * (fmsk/100)* 5;
                
                if( query("can_learn/yunv-xinfa/wall", me) ) damage *= 3;
                //判断结婚次数和发生性行为的次数
                if( !mapp(query("couple", me)))married = 1;
                else married = query("couple/married", me);
                if( mapp(query("sex", me))) married += query("sex/times", me);
                damage -= (damage/5) * (married - 1);
                if (damage < 10) damage = 10;
                
                if(BUFF_D->check_buff(me, "ynxf_wang"))
                {
                    msg+= HIW "$N" HIW "蓦然回首，忧郁眼神淡如清水，完全不将外界事物放在心上，\n"
                          HIW "剑招突变，一会儿，情意绵绵，一会儿却舍命相拼，意欲寻死，\n"
                          HIW "一招一式若神来之笔，拿捏的异常准确！\n" NOR;
                          
                    damage*= 2;
                }           
                message_combatd(msg, me, target);

                pmsg=HIW"只听$n一声惨呼，已然给$N的"+NOR+query("name", weapon)+HIR+
                      "重重的刺中，浑身上下凝结上一层白色冰霜，冷的瑟瑟发抖！\n"NOR;
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200+fmsk/5, pmsg);
                
                if (me->query_skill("zuoyou-hubo",1) > 500 
                && me->query_family()=="古墓派"&&random(3)
                && (query("int", me)<25 || query("int", me)>39)
                && (!me->query_skill("count",1) || query("special_skill/capture", me))
                && living(target))
                {               
                    msg += hbmsg[random(sizeof(hbmsg))];
                    if( me->query_skill("quanzhen-jian",1) > me->query_skill("yunv-jian",1)-100)
                    {
                        msg += HIG"$N"HIG"突然间双剑一交，"HIW"玉女剑法"HIG"与"HIC"全真剑法"HIG"分手使出，攻守骤然大增！\n";
                        damage*= 2;
                     }
                    msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 200+fmsk/5,pmsg);                      
                }
                     
                if (!target->is_busy())
                    target->start_busy(1+random(2));
                me->start_busy(2+random(3));
    
        } else
        {
                msg = HIY "$n见状大惊失色，双足点地，抽身急退，堪堪避过$N的这记素心诀，已是大汗淋漓。\n"NOR;
                me->start_busy(2+random(4));
        }
        message_combatd(msg, me, target);
        return 1;
}

