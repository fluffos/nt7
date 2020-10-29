// /kungfu/skill/beidou-zhenfa.c

#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return usage=="array"; }

string *position = ({
        "天权","天枢","天璇","天玑","玉衡","开阳","摇光"
});

string *sword = ({
        "踏奇门，走偏锋，剑尖颤了几颤，一招巧妙无比的「分花拂柳」，似左实右往空中刺去。",
        "使一招「琴心三叠」，身形向上飘起，手中剑虚虚实实幻出三点寒光射向空中。",
        "身形一转，猛然一式「罡风扫叶」，舞出满天剑影，挟着劲风向前扫去。",
        "仰天长笑，身形飘然而起，在半空中身子一旋，一式「狂歌痛饮」狂风般地击向空中。",
        "左手捏着剑诀，右足踏开一招“定阳针”向上斜刺。",
        "向前迈去一大步，使出「探海屠龙」，手中剑舞成一个光球，迅若奔雷击出。",
        "运力一抖剑，一时「马蹴落花」，剑幻出点点剑花，飘然刺出。",
        "手中剑一指，纵起丈余，一时「横行漠北」，雷霆般击出。",
        "身形向上飘起，突然一转身，头下脚上，手握剑，一招「絮坠无声」，无声无息地攻出。",
        "大喝一声，一招「白虹经天」，剑闪电般划出一道大圆弧劈下。",
        "忽然身形高高跃起，使出「浪迹天涯」，手中剑幻出漫天花瓣，迅如雷霆射出。"
});

string *zhen =  ({
        "天罡北斗阵法滚滚推动，攻势连绵不绝，瞬间将敌人围在垓心。",
        "天罡北斗阵气势宏大，前攻后击，连环相接，让人眼花撩乱，方寸顿失。",
        "只见天罡北斗阵暗合五行八卦之理，阵中人步法精妙，攻守配合得天衣无缝。",
        "天罡北斗阵越缩越小，无形剑气象浪潮一般逼向中央，令人有窒息之感。"
});


void start_beidouzhen(object ob, int mypos,int beidou_time,int bd_power );
int beidouzhen(object me);
int halt_beidou(object me);
void out_beidou(object me);

int valid_learn(object me)
{
        if( query("gender", me) == "无性" && 
        (int)me->query_skill("beidou-zhenfa", 1) > 49)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的天罡北斗阵法。\n");

        if ((int)me->query_skill("array", 1) <= (int)me->query_skill("beidou-zhenfa",1))
                return notify_fail("你的基本阵法火候还不够。\n");

            return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("天罡北斗阵法只能用学(learn)的来增加熟练度。\n");
}

int form_array(object me,string arg)
{
        object enemy,*member;
        int beidou_time,i,mypos=0,power,bd_power,level;
        object here;
        string msg;
        float exp_diff;

        here = environment( me );

        if( me->is_busy() )
        {
                return notify_fail("你正忙着呢！\n");
        }

        if( me->query_skill_mapped("array") != "beidou-zhenfa")
                return notify_fail("你还没有激发好天罡北斗阵法！\n");

        member = me->query_team();
        level = sizeof(member) *20;

        if (sizeof(member) < 3 || sizeof(member) > 7)
                return notify_fail("天罡北斗阵最少三个人，最多七个人。\n");

        if( me->query_skill("beidou-zhenfa",1) < level)
                return notify_fail("你的天罡北斗阵法等级太低！\n");

        if (!arg)
                return notify_fail("指令格式：team form beidou-zhenfa 目标ID \n");

        if (!enemy = present(arg,here))
                return notify_fail("你要摆阵攻击的"+arg+"不在这里啊？\n");

        if( query("family/family_name", enemy) == "全真教" )
                return notify_fail("怎么？你们要同门残杀么？\n");

        if( query("race", enemy) != "人类" )
                return notify_fail("怎么？杀鸡还用牛刀么？\n");

        for( i = 0; i < sizeof(member); i++ )
        {
           if (!objectp(member[i]))
                return notify_fail("你的队伍有点问题，需要重新组合队伍。\n");

           if (environment(member[i]) != here)
                return notify_fail("你队伍中的" + member[i]->name() + "现在不在这里啊！\n");

           if( query("family/family_name", member[i]) != "全真教" )
                return notify_fail("你队伍中的" + member[i]->name() + "不是全真教弟子。\n");

           if (member[i]->is_busy())
                return notify_fail("你队伍中的" + member[i]->name() + "正忙着呢！\n");

           if (member[i]->query_skill_mapped("array") != "beidou-zhenfa")
                return notify_fail("你队伍中的" + member[i]->name() + "没有激发好天罡北斗阵法。\n");

           if (member[i]->query_skill("beidou-zhenfa",1) < level )
                return notify_fail("你队伍中的" + member[i]->name() + "天罡北斗阵法等级不够。\n");

           if ( member[i]->query_skill("quanzhen-jian",1) <60 ||
                query("combat_exp", member[i])<50000 || 
                member[i]->query_skill("dodge") <60)
                return notify_fail("你队伍中的" + member[i]->name() + "武功太差，不能参加「天罡北斗阵」。\n");

           if( query("neili", member[i])<500 )
                return notify_fail("你队伍中的" + member[i]->name() + "内力太差，不能参加「天罡北斗阵」。\n");

           if( query("jingli", member[i])<300 )
                return notify_fail("你队伍中的" + member[i]->name() + "精力太差，不能参加「天罡北斗阵」。\n");

           exp_diff=to_float(query("combat_exp", member[i])-query("combat_exp", me));
           exp_diff/=to_float(query("combat_exp", me));

           if( exp_diff > 0.4 || exp_diff < -0.4 )
                return notify_fail("你队伍中的" + member[i]->name() + "武功和你差距太大，不能共摆「天罡北斗阵」。\n");
        }

        power = me->query_skill("force");
        power += me->query_skill("sword");
        power+=query("str", me)*10;
        power += me->queyr("dex")*10;

        bd_power = me->query_skill("beidou-zhenfa",1);

        for (i = 0;i < sizeof(member); i++)
        {
                power += member[i]->query_skill("force");
                power += member[i]->query_skill("sword");
                power+=query("str", member[i])*10;
                power += member[i]->queyr("dex")*10;

                bd_power += member[i]->query_skill("beidou-zhenfa",1);
        }

        power /= 70;
        bd_power /= 35;
        power += bd_power;

        if(power>300)power=300;
        if(power<30)power=30;

        msg = "";

        for (i = 0;i < sizeof(member); i++)
        {
                start_beidouzhen(member[i],0,power/2,power);
                if (member[i] != me)
                {
                        msg += member[i]->name();
                        if (i != sizeof(member) -1)
                                msg += "、";
                }
        }

        message_vision(HIM"$N突然身形移动，发动" + msg +
                        "将" + enemy->name() + "围在中间，正是摆的「天罡北斗阵」阵法。\n\n"NOR, me);

        message_vision(HIR"\n$N对$n喝道：" + RANK_D->query_rude(enemy) +
                        "你一向为非作歹，今天本教要替天行道，纳命来！\n\n"NOR, me, enemy);

        for (i = 0;i < sizeof(member); i++)
        {
                member[i]->kill_ob(enemy);
                enemy->kill_ob(member[i]);
        }

        return 1;
}

void start_beidouzhen(object ob, int mypos,int beidou_time,int bd_power )
{
        set_temp("pending/beidou", 1, ob);
        set_temp("beidou_time", beidou_time, ob);
        set_temp("bd_pos", mypos, ob);
        set_temp("bd_power", bd_power, ob);
        addn_temp("apply/defense", bd_power, ob);
        addn_temp("apply/parry", bd_power/3, ob);
        addn_temp("apply/dodge", bd_power/3, ob);
        ob->start_busy((: beidouzhen :), (:halt_beidou:));
}

void check_leaving(object me)
{
        string name=query("id", me);

        if( !userp(me) )
                {
                 object enemy = offensive_target(me);
                 if( !objectp(enemy) && !me->is_busy() && !me->is_fighting() )
                 {
                         message_vision(HIY"\n$N作了个楫道：贫道先告退了！说完就快步离开了。\n"NOR, me);
                         call_out("destruct_me",10,me);
                         return;
                  }

                  call_out("check_leaving",5,me);
          }
}

int beidouzhen(object me)
{
        object *member,ob,where;
        int beidou_time,i,power,ok,mypos;
        object room, obj,enemy,weapon;

        enemy = offensive_target(me);
        beidou_time=query_temp("beidou_time", me);
        where = environment(me);
        mypos=query_temp("bd_pos", me);

        if (beidou_time < 1)
        {
                out_beidou(me);
                return 0;
        }

        if (!objectp(enemy) || environment(enemy) != where)
        {
                out_beidou(me);
                return 0;
        }

        if( query("neili", me)<300 || query("jingli", me)<100 )
        {
                out_beidou(me);
                return 0;
        }

        member = me->query_team();

        if (!member || sizeof(member) < 3 || sizeof(member) > 7)
        {
                out_beidou(me);
                return 0;
        }

        ok = 1;

        for ( i = 0;i < sizeof(member);i++)
        {
                if (environment(member[i]) != where)
                {
                        ok = 0;
                        break;
                }

                if( !query_temp("pending/beidou", member[i]) )
                {
                        ok = 0;
                        break;
                }
        }

        if (!ok)
        {
                out_beidou(me);
                return 0;
        }


        beidou_time = beidou_time-1;
        set_temp("beidou_time", beidou_time, me);

        power=query_temp("bd_power", me);

        if( random(6)==1 )
        {
                tell_room(environment(me), HIR"\n" + zhen[(int)random(4)] +"\n"NOR, this_object());
                if( objectp(enemy) &&
                    objectp(present(query("id", enemy),environment(me))) )
                        enemy->start_busy( random(2) );
        }

        if( random(2)==1 )
        {
                if(random(2)==0)
                        message_vision(WHT"\n" + position[mypos] + "位上的$N气沉丹田，暗运神功，猛然吐气开声，身形往前一纵。\n"NOR, me);
                else
                        message_vision(WHT"\n" + position[mypos] + "位上的$N挺身而出，步法精妙，长袖飘飘，攻势如虹。\n"NOR, me);

                addn_temp("apply/damage", power, me);
                addn_temp("apply/sword", power/2, me);
                addn_temp("apply/attack", power, me);
                addn("jiali", power, me);
                COMBAT_D->do_attack(me,enemy,query_temp("weapon", me));
                addn_temp("apply/damage", -power, me);
                addn_temp("apply/sword", -power/2, me);
                addn_temp("apply/attack", -power, me);
                addn("jiali", -power, me);
                addn("jingli", -15-random(15), me);
                addn("neili", -20-random(20), me);
        }

        return 1;
}

void restart (object me)
{
        start_beidouzhen(me,query_temp("bd_pos", me),query_temp("beidou_time", me),query_temp("bd_power", me));
}

int halt_beidou(object me)
{
        object weapon;
        int beidou_time=query_temp("beidou_time", me);
        if (beidou_time > 0)
        {
                if( !living(me) ) return 1;

                if(random(2)==1)
                {
                        message_vision(HIG"\n$N踉跄了一步，差点摔出北斗阵。\n"NOR, me);
                }
                else message_vision(HIG"\n$N被打的晃了几晃，不过又站稳了步子。\n"NOR, me);
                call_out("restart",4,me);
                return 1;
        }

        out_beidou(me);
        return 1;
}

void out_beidou(object me)
{
        object weapon;
        int bd_power;

        bd_power=query_temp("bd_power", me);

        if( !objectp(weapon=query_temp("weapon", me)) || 
           query("skill_type", weapon) != "sword" )
                message_vision(HIG"\n$N身子向后一纵，使一招『收山式』，右拳划了一圈，左掌往怀中一抱，退出「天罡北斗阵」。\n"NOR, me);
        else
                message_vision(HIG"\n$N身子向后一纵，使一招『收剑式』，将剑挽了一个剑花，往怀中一抱，退出「天罡北斗阵」。\n"NOR, me);

        addn_temp("apply/defense", -bd_power, me);
        addn_temp("apply/parry", -bd_power/3, me);
        addn_temp("apply/dodge", -bd_power/3, me);
        delete_temp("pending/beidou", me);
        delete_temp("beidou_time", me);
        delete_temp("bd_pos", me);
        delete_temp("bd_power", me);
        return;
}
