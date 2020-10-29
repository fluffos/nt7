//开始阅读文件：/kungfu/skill/tangshi-jian.c
// tangshi-jian.c 唐诗剑法
// redl 2014

#include <ansi.h>;
#include <combat.h>

inherit SKILL;

int is_pbsk() { return 1; }

string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N手中$w自左上方斜劈向下，跟着向后挺剑刺出，一招"HIC"「孤鸿海上来，池潢不敢顾」"NOR"，手中$w更不回头，一剑剑点向$n的$l。",
        "lvl" : 0,
        "skill_name" : "孤鸿海上来，池潢不敢顾"
]),
([        "action" : "$N退了两步，$w大开大阖，一声吆喝，横削三剑，一招"HIB"「哥翁喊上来，是横不敢过」"NOR"直刺$n的$l",
        "lvl" : 10,
        "skill_name"  : "哥翁喊上来，是横不敢过"
]),
([        "action" : "突然间嗤嗤嗤三声，$N向$n连刺三剑，一式"HIG"「俯听闻惊风，连山若波涛」"NOR"，剑刃在$n的$l边堪堪掠过，$n只觉$l凉飕飕地，大吃一惊，急忙倒退。",
        "lvl" : 20,
        "skill_name" : "俯听闻惊风，连山若波涛"
]),
([        "action" : "$N手中$w递出，一个虚招指向$n的左肩，反手却使出一式"HIY"「落日照大旗，马鸣风萧萧」"NOR"，由下而上$w疾刺$n的$l",
        "lvl" : 30,
        "skill_name" :"落日照大旗，马鸣风萧萧"
]),
([        "action" : "$N一招"HIW"「举头望明月，低头思故乡」"NOR"，身子前倾，忽地回剑斜削，手中$w平平地向$n的$l挥去",
        "lvl" : 40,
        "skill_name" : "举头望明月，低头思故乡"
]),
([        "action" : "$N上身往左侧一拧，一招"BLU"「长安一片月，万户捣衣声」"NOR"，右手$w反手向$n的$l挥去",
        "lvl" : 50,
        "skill_name" : "长安一片月，万户捣衣声"
]),
([        "action" : "$N左一招"MAG"「万国仰宗周」"NOR"，右一招"HIM"「衣冠拜冕旒」"NOR"，剑锋平指，一气呵成横扫$n的$l",
        "lvl" : 60,
        "skill_name" : "万国仰宗周 衣冠拜冕旒"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力不够。\n");
        if( me->query_skill("literate",1 )<600 )
                return notify_fail("你的读书写字不够。\n");
        if( me->query_skill("sword-cognize",1 )<200 )
                return notify_fail("你的剑道修养不够。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
        if( query("qi", me)<30 || query("neili", me)<10 )
                return notify_fail("你的内力或气不够练唐诗剑法。\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 40;
        int d_e2 = 60;
        int p_e1 = 10;
        int p_e2 = 30;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 10;
        int m_e2 = 110;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("tangshi-jian", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割伤" : "刺伤",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string *shi = ({HIG "「花间一壶酒，独酌无相亲。」" HIW,HIG "「举杯邀明月，对影成三人。」" HIW,HIG "「月既不解饮，影徒随我身。」" HIW,HIG "「暂伴月将影，行乐须及春。」" HIW,
                                HIG "「我歌月徘徊，我舞影零乱。」" HIW,HIG "「醒时同交欢，醉后各分散。」" HIW,HIG "「永结无情游，相期邈云汉。」" HIW});
string *ship = ({HIW "\n$N仗剑沉吟道###，霎时一股剑气，化作透明丝线袭向$n" HIW "。\n" NOR,
                                HIW "\n$N身法陡快，忽念到###，突然间剑势大变，缠向$n" HIW "。\n" NOR,
                                HIW "\n$N清吟###，手里剑气犹如银色月光泻地，遍布夜空将$n" HIW "笼罩。\n" NOR,
                                HIW "\n$N黯然低吟###，猛然挥剑封住西面八方，$n" HIW "大惊失色。\n" NOR});

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
//      mixed result;
        string msg;
        int lvl , flagli = 0;
        int idx,idx2,ap,dp,damage,damage2;
        int num = 200;
        object weapon=query_temp("weapon", me);
        object *obs;

        if( ( userp(me) && query("tianyishenjiu_time", me)<1 ) || 
                me->query_skill("literate",1 )<600 ||
                me->query_skill("sword-cognize",1 )<200
                )
               return 0;

             if( !objectp(weapon) || query("skill_type", weapon) != "sword"
                 || me->query_skill_mapped("sword") != "tangshi-jian")
                         return 0;
        if (query("id", me)=="li bai")
                flagli = 1;
                if (!flagli) {        
                if (query_temp("tsj_cd_time", me) >= time())
                        return 0;
                set_temp("tsj_cd_time", time() + 2, me);
        }

        ap=attack_power(me,"sword")+me->query_int()*50+me->query_skill("sword-cognize", 1);
        ap+=ap*(query("tianyishenjiu_time", me)/50);
        damage = damage_power(me, "sword");
        damage += damage * query("jiali", me) / 1000;
        damage += damage * (me->query_skill("literate",1 )) / 3500;
        damage += damage * (me->query_skill("sword-cognize",1 )) / 2500;
        damage +=damage*(query("tianyishenjiu_time", me)/25);
        
        lvl = me->query_skill("tangshi-jian", 1) + me->query_skill("literate",1 ) + me->query_skill("sword-cognize",1 );
        lvl = lvl / 6000;
                if ((!flagli) && lvl > query("tianyishenjiu_time", me)) lvl = query("tianyishenjiu_time", me);
                if (lvl < 1) lvl = 1;
                if (lvl > 6) lvl = 6;
                idx2 = lvl + 1;         
                while (lvl--) {
                num --;
                if (!num) break;
                if (flagli && random(5)) lvl++;
                obs = me->query_enemy();        
                if (!obs || !arrayp(obs) || !sizeof(obs))
                        break;
                else   
                        victim = obs[random(sizeof(obs))];
                if (! me->is_fighting(victim)) continue;
                idx = random(idx2);
                damage2 = damage + damage * idx / 2;
        message_combatd(( replace_string(ship[random(sizeof(ship))], "###", shi[idx]) ), me, victim);
        dp=defense_power(victim,"parry")+victim->query_int()*50+victim->query_skill("sword-cognize",1 );
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, victim, ((!random(3)) ? REMOTE_ATTACK : WEAPON_ATTACK), damage2, 60 + random(query("int",me) * 2),
                                          HIY"只闻「噗嗤」！一声，" + weapon->name() + HIY "已穿透$n" HIY "的胸膛，鲜血不断涌出。\n" NOR, me , victim);
        } else
        {
                msg = HIC "$n" HIC "会心一笑，看出$N" HIC "这招中的破绽，随意施招竟将这招化去。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, victim);
        }
        return 1;

}


int help(object me)
{
        write(HIC"\n唐诗剑法："NOR"\n");
        write(@HELP

    铁骨墨萼梅念笙传给他三个徒弟五云手万震山，陆地神龙言达
平，铁锁横江戚长发的剑法。
    传说诗仙利用深厚的文学造诣和剑道修养，将此剑法发挥到了
极致。当然，也离不开酒的功劳。

        学习要求：
                内力1000
                读书写字600
                剑道修养200
HELP
        );
        return 1;
}