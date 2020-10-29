// Inherit: snake.c 蛇类
// Update by Vin for Heros.cn
// 设置毒蛇毒性level和毒液的量remain/maximum，毒蛇每次咬中对
// 方，都会将perhit 指明的毒量注入到对方的体内，每过一段时间
// 毒蛇会自动恢复supply 量的毒液。level将和武功的force做比较。
// 设置level时候应该参考内功等级。毒量和中毒UPDATE_CONDITION
// 的次数成正比，设置毒量的时候应该参考气和精。

#include <ansi.h>
inherit NPC;

int is_snake()
{
        return 1;
}

void setup()
{
        mapping p;

        set("race", "蛇类");
        set("unit", "条");
        set("limbs", ({ "头部", "身体", "七寸", "尾巴" }));
        set("verbs", ({ "bite" }));
        set("attitude", "aggressive");

        p = query("snake_poison");

        if (! p)
        {
                ::setup();
                return;
        }

        if (! intp(p["level"]))   p["level"]   = 30;
        if (! intp(p["perhit"]))  p["perhit"]  = 10;
        if (! intp(p["maximum"])) p["maximum"] = 20;
        if (! intp(p["remain"]))  p["remain"]  = p["maximum"];
        if (! intp(p["supply"]))  p["supply"]  = 1;
        if (! stringp(p["id"]))   p["id"]      = "nature snake";

        ::setup();
}

void init()
{
        object me/*, ob*/;

        ::init();
        if (! interactive(me = this_player()))
                return;

        // 自动攻击蛇毒奇巧等级不高的玩家
        if (! present("xiong huang", this_player()) &&
            query_temp("owner") != query("id", me) &&
            (int)me->query_skill("shedu-qiqiao", 1) < 100)
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, me);
        }
        add_action("convert", "bian");
        add_action("convert", "convert");
        remove_call_out("disappear");
        call_out("disappear", 15);
}

mixed hit_ob(object me, object ob, int damage)
{
        mapping p;
        string  msg;
        int force;
        int dur;

        p = query("snake_poison", me);
        if (! p) return;
        if (damage / 3 + random(damage * 2 / 3) <
            (int)query_temp("apply/armor", ob))
        {
                // Defeated by armor
                return;
        }

        msg = "";
        dur = p["perhit"];
        if (dur > (int)p["remain"]) dur = p["remain"];
        p["remain"] = (int)p["remain"] - dur;
        this_object()->apply_condition("poison-supply", 1);
        if (! dur) return;

        force = (int)ob->query_skill("force");
        if (random(force / 2) + force / 2 >= (int)p["level"] &&
            query("neili", ob) > damage / 5)
        {
                if (query("qi", ob) < 150)
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时体力不支，难以施为。\n" NOR;
                } else
                if (query("jing", ob) < 60)
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时精神不济，难以施为。\n" NOR;
                } else
                if (query("neili", ob) < damage / 5 + 50)
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时内力不足，难以施为。\n" NOR;
                } else
                {
                        addn("neili", -damage/5, ob);
                        ob->receive_damage("qi", 20);
                        ob->receive_damage("jing", 10);
                        return HIM "你觉得被咬中的地方有些发麻，连忙运功"
                               "化解毒性。\n" NOR;
                }
        }

        if (ob->affect_by("poison", ([ "level" : (int)p["level"],
                                       "name"  : "蛇毒",
                                       "id"    : "nature poison",
                                       "duration" : dur, ])))
        {
                msg += HIR "$n" HIR "脸色一变，只觉被咬中的地方一阵麻木。\n" NOR;
        }
        return msg;
}

void die(object killer)
{
        object me, item;
        object ob = this_object();
        int power, skill;
        string msg;

        message_vision(HIR "\n只见$N" HIR "卷着身子在地上扑腾了"
                       "几下，死了。\n\n" NOR, ob);

        if (objectp(me = killer)
           || objectp(me = query_last_damage_from()))
        {
                // 如果为自己的猎物，则奖励之
                if (query("owner", ob) == query("id", me)
                   && query("combat_exp", me) <= 500000)
                {
                        // 根据猎物设定的参数来给予奖励
                        power = query("power", ob);

                        if (power < 5)
                                power = 5;

                        if (power > 500)
                                power = 500;

                        GIFT_D->delay_bonus(me, ([ "prompt" : "通过这次猎取" + ob->name() +
                                                              HIG "的经历",
                                                   "exp"    : random(power) + power,
                                                   "pot"    : random(power / 3) + power / 3,
                                                   "score"  : random(power / 4), ]));
                }
                skill = me->query_skill("hunting", 1);

                // 获得物品
                if (query("item1") && random(skill) > 10)
                {
                        item = new(query("item1"));
                        item->move(me, 1);

                        msg = HIC "你仔细翻寻" + ob->name() +
                              HIC "的尸体，从上面割下了一" +
                              query("base_unit", item) +
                              item->name() + HIC;

                        // 一定几率获得高级物品
                        if (query("item3") && random(skill) > 60
                           && random(5) > 3)
                        {
                                item = new(query("item3"));
                                item->move(me, 1);

                                msg += "及一" + query("base_unit", item) +
                                       item->name() + HIC;
                        } else
                        if (query("item2") && random(skill) > 30
                           && random(4) > 2)
                        {
                                item = new(query("item2"));
                                item->move(me, 1);

                                msg += "及一" + query("base_unit", item) +
                                       item->name() + HIC;
                        }
                        msg += "。\n\n" NOR;
                        tell_object(me, msg);
                }
        }
        destruct(ob);
}