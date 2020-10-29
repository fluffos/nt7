// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>
#define SNAKE_STAFF query_temp("weapon", this_player())

inherit F_SSERVER;

string name() { return "驱蛇咬人"; }
//void remove_bite(object);

int perform(object me, object target)
{
        string type, snake_path, msg;
        object weapon, snake;
        int t, lv, poison, poi_amount, train_lv, snake_lv, damage, dp, i;

        t=query_temp("baituo/bite", me);
        lv = (int)me->query_skill("lingshe-zhangfa", 1);
        poison = (int)me->query_skill("poison", 1);
        train_lv = (int)me->query_skill("training", 1);

        poi_amount = lv + poison;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("你只能纵蛇偷袭战斗中的对手。\n");

        if (lv < 200 )
                return notify_fail("你的灵蛇杖法不够娴熟，无法在使杖攻敌之余纵蛇伤人。\n");

        if (poison < 200 )
                return notify_fail("你对使毒的法门所知有限。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                 return notify_fail("你手上没有盘蛇的兵器。\n");
        
        type=query("snake_type", weapon);
        
        /*
        if( !type && query("id", weapon) != "she zhang" )
                return notify_fail("你的"+weapon->name()+"上并没有蛇。\n");
        */
        if( t && (time() - t) < 5 )
                return notify_fail("你刚刚已经纵蛇伤人，这麽快就故技重施，祗怕难以奏效。\n");

        if( me->query_skill("training",1) < 100 )
               return notify_fail("你的驭兽术无法顺利驱使毒蛇伤人。\n");

        if( query("neili", me)<poi_amount )
                return notify_fail("你的内力不够，难以在纵蛇袭击时稳控"+weapon->name()+"。\n");

        if( query("jingli", me)<300 )
                return notify_fail("你的精力不够，难以在纵蛇袭击时稳控"+weapon->name()+"。\n");

        if(( me->query_skill_mapped("force") != "hamagong") && ( me->query_skill_mapped("force") != "jiuyin-hamagong"))
                return notify_fail("你所用的内功与「灵蛇杖法」气路相悖！\n");

        addn("neili", -(poi_amount/2+50), me);
        addn("jingli", -200, me);

        switch (type) {
        case "怪蛇" :
        snake_path = "/d/baituo/npc/guaishe";
        break;
        case "灵蛇" :
        snake_path = "/d/baituo/npc/lingshe";
        break;
        default:
        snake_path = "/d/baituo/npc/snake";
        type = "毒蛇";
        }

        seteuid(getuid());

        snake = new(snake_path);

        snake_lv = (train_lv + lv)*2/3;

        set("bite_busy", 1, snake);
        set("env/invisible", 10, snake);
        set("owner", me, snake);
        snake->move(environment(me));
        set("default_actions", (:call_other,__FILE__,"query_action":), snake);
        set("combat_exp",query("combat_exp",  me), snake);

        addn_temp("apply/speed", 2, snake);
        addn_temp("apply/attack", snake_lv, snake);
        addn_temp("apply/damage", snake_lv, snake);
        set("neili",query("neili",  me), snake);
        set("jingli",query("max_jingli",  me)*2, snake);
        set("max_jingli",query("max_jingli",  me), snake);
        set("snake_poison", poi_amount*5, snake);
        snake->kill_ob(target);

        message_combatd(HIB"\n$N将"+weapon->name()+HIB"一抖，杖上金环当啷啷一阵乱响，一条"+type+HIB"从杖底直盘上来。\n"NOR,me);

        me->start_busy(1);

        COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));
        COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));

        if( query("snake", weapon) == 2){
                set("second_attack", 1, snake);
                COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));
                COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));
        }

        destruct(snake);
        damage = lv +  poison + train_lv + me->query_skill("staff",1);
        damage += (damage);
        dp=target->query_skill("dodge")+target->query_skill("training",1);
        if (damage/2+random(damage)>dp)
        {
                addn("neili", -200, me);
                message_combatd(HIB"\n$N忽然将"+weapon->name()+HIB"当头打了下来，$n因为防备毒蛇而躲闪不及。\n"NOR,me,target);
                COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100);
        }

        target->kill_ob(me);
        set_temp("baituo/bite", time(), me);

        call_out("remove_bite", 5, me, type);

        return 1;
}

void remove_bite(object me, string type)
{
        if (! objectp(me)) return;
        delete_temp("baituo/bite", me);
        tell_object(me, type+"昂起了头，嘶地一吐舌头。\n");
}

mapping query_action(object me)
{
        string msg1, msg2;
        msg1 = HIR"祗见"+SNAKE_STAFF->name()+HIR"从$n眼前掠过，缠杖盘旋的一条$N吞吐伸缩，猛然张口咬向$n$l，狰狞诡异之极！"NOR;
        msg2 = HIW BLK"一条$N才刚窜出，冷不防"+SNAKE_STAFF->name()+HIW BLK"上另一条$N也已悄没声息地昂首而起，一口向$n$l咬去！"NOR;
        return ([
        "action":query("second_attack", me)?msg2:msg1,
        "force" : 400,
        "dodge" : 0,
        "parry" : 0,
        "damage" : 400,
        "weapon" :"毒牙",
        "damage_type":"咬伤"]);
}