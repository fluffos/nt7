// yijinjing.c 少林 易筋经神功

#include <ansi.h>
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force) { return 1; }
int is_pbsk() { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("yijinjing", 1);
        return (lvl / 20) * (lvl / 10) * 25 * 15 /100;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if( query("con", me)<20 )
                return notify_fail("你研究了一会儿，只觉得眼前金星乱冒，太阳穴突突的跳。\n");

        if (me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功火候不够，无法学习易筋经神功！\n");

        /*
        if (me->query_skill("freezing-force", 1))
                return notify_fail("你已经将易筋经神功和冰蚕寒毒合炼成了一门新内功了。\n");
        */

        if (me->query_skill("force", 1) < me->query_skill("yijinjing", 1))
                return notify_fail("你的基本内功水平不够，难以领悟更高深的易筋经神功！\n");

        if( query("gender", me) != "男性" )
                return notify_fail("你不是男性，无法练习易筋经神功。\n");

        return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("易筋经神功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"yijinjing/" + func;
}
/*
void skill_improved(object me)
{
        int skill, lit;

        skill = me->query_skill("yijinjing", 1);
        lit = me->query_skill("literate", 1);

        if( skill == 200 && !query("sl/yijinjing", me) )
        {
                tell_object(me, HIW "\n忽然，你感道体内内息奔走，越转越快，瞬时间已经在全身上下运行了一周天，复汇聚于丹田之中！\n" NOR);
                addn("max_neili", random(lit+skill), me);

                if( query("max_neili", me)>me->query_neili_limit() )
                        set("max_neili", me->query_neili_limit(), me);

                set("sl/yijinjing", 1, me);
        }
        if (skill == 400)
        {
                tell_object(me, HIW "\n忽然，你感道体内内息奔走，越转越快，瞬时间已经在全身上下运行了十周天，复汇聚于丹田之中！\n" NOR);
                tell_object(me, HIW "你修炼成百毒不侵神功了。\n" NOR);
                set_temp("nopoison", 1, me);
        }
}
*/

string *fanzhen_msg = ({
        "只震得$N胸内腹中，有如五脏一齐翻转！\n",
        "抢先反震，将$N震得脸如白纸，全无血色！\n",
        "震得$N心肺欲裂，腾腾腾连退数步！\n",
        "功力已布满全身，将$N的力量反震回去！\n",
        "震得$N天旋地转，腾腾腾连退七八步！\n",
        "和$N一撞，只震的$p胸口气血翻涌！\n",
        "$N便如撞在一堵棉花作面，钢铁为里的厚墙上一般，震退数步！\n",
        "$N刚碰到$p，突然身子一震，登时飞了出去！\n",
});
/*
mixed valid_damage(object me,object victim,int damage_bonus,int factor)

//factor= 加力 damage_bonus=臂力 .
{
        int ap,dp;
//内功相差太多(至少2倍以上),内力伤害全部抵消,基本上不出现
        ap=me->query_skill("force");
        dp=victim->query_skill("force");
        if( random(ap/2)>dp && query("neili", me)>2000 )
        {

                if (random(10)==1) tell_object(victim, "你只觉得如同击在金属上，头脑里闪过一个念头：金属罩！\n");
                else tell_object(victim,HIY"你只觉得劲力如同击在金属罩，根本无法伤他分毫！\n"NOR);
                tell_object(me, HIY"你只觉得劲力袭体，急忙运起金钟罩神功，一股真气弥漫全身！\n"NOR);
                addn("neili", -2*damage_bonus, me);
                return -damage_bonus;
        }
        else if( (random(ap*2)>dp) && query("neili", me)>1500 )
        {
                if (random(10)==1) tell_object(victim,HIY"你只觉得如同击在金属上，头脑里闪过一个念头：“金属罩”！\n"NOR);
                else tell_object(victim,HIY"你只觉得劲力如同击在金属上，虎口隐隐作痛！\n"NOR);
                tell_object(me, HIY"你只觉得劲力袭体，勉力运起金钟罩，一股真气弥漫全身！\n"NOR);
                addn("neili", -damage_bonus, me);
                return -random(damage_bonus);
        }
        return 0;
}
*/
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        string msg;
        int ap, dp;
        int jiali;
        object weapon1;

        if( query("family/family_name", me) != "少林派" )
                return;

        if ((int) me->query_skill("yijinjing", 1) < 200 ||
            ! living(me))
                return;

        if( (jiali=query("jiali", ob))<1 )
                return;

        ap=ob->query_skill("force")+query("neili", ob)+
             ob->query_skill("count", 1);
        dp=me->query_skill("force")+query("neili", me);

        if (ap / 2 + random(ap) < dp)
        {
                if( !objectp(weapon1=query_temp("weapon", ob)) )
                {
                        result = ([ "damage" : -damage ]);

                        msg = random(2) ? HIR "$n身上生出一股反震之力，" : HIR "$n身上金刚不坏体神功随心而起，";

                        msg += fanzhen_msg[random(sizeof(fanzhen_msg))] + NOR;

                        ob->receive_damage("qi", damage / 10, me);
                        ob->receive_wound("qi", damage / 20, me);

                        result += ([ "msg" : msg ]);

                        return result;
                } else
                {
                        result = ([ "damage" : -damage ]);

                        switch (random(5))
                        {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                                result += ([ "msg" : HIR "好似有一堵无形的墙在$n面前阻挡着，结果"
                                                     "$N" HIR "一下子被反弹，震得$N"
                                                     HIR "手臂发麻！\n" NOR ]);
                                break;
                        default:
                                result += ([ "msg" : HIR "结果$n身上生出一股反震之力，$N只觉虎口一热，" +
                                                     weapon1->name() + HIR "顿时脱手而出，飞出丈外！\n" NOR]);
                                weapon1->unequip();
                                weapon1->move(environment(ob));
                                ob->reset_action();
                                if (! ob->is_busy())
                                        ob->start_busy(1);
                                break;
                        }

                        return result;
                }
        }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int skill;
        int i,j;

        if( query("family/family_name", me) != "少林派" )
                return;

        if (me->query_skill("yijinjing", 1) < 400 ||
            me->is_busy())
                return;

        skill = me->query_skill("force");

        i = damage_bonus * (skill + 1) / 1000;
        i = i/2+ random(i);
        if( query_temp("weapon", me) )
                i = i*3;
        if( query_temp("apply/damage", me) >= 1000 )
                i = i/3;

        j = me->query_skill("yijinjing", 1) / 2;
        i += j;
        message_combatd(HIR"$N"+HIR+"高喧一声佛号，将体内九阳真气聚于双臂，狭雷霆之势攻向$n！\n" NOR, me,victim);

        return i;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

string query_description()
{
        return
        "易筋经乃少林寺头等绝技，由内及外，为无上伏魔神功。此内功是少林镇寺"
        "之宝，毅力一般者无法学成，其三阶段分别为：0-200，200-400，>400。初"
        "级易筋经可强身健体，提高修为；中级可降妖伏魔，成金刚之体；高级可砍"
        "妖除魔于无形，御力修身，百毒不侵。";
}

int help(object me)
{
        write(HIC"\n易筋经神功："NOR"\n");
        write(@HELP

    《易筋》，《洗髓》二经向为少林镇寺之宝，相传为达摩祖师
所创，载有不少天竺高僧的瑜伽秘术，但由于其习练艰难，须得勘
破“我相，人相”，心中不存修习武功之念，故历代弟子罕有练成
者。
    《洗髓》记载天下所有武功的精要，《易筋》则是一门极其高
深的内功心法书籍。

        学习要求：
                未破色戒的童男之身
                未犯戒
                混元一气功100级
                相应级别的禅宗心法
HELP
        );
        return 1;
}
