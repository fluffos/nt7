// This program is a part of NT mudlib
// boss 模板

#include <ansi.h>

inherit BOSS;

int big_blowing();

void create()
{
        set_name( HIB "镇海神龙" NOR, ({ "sea dragon king", "dragon king", "dragon" }) );
        set("long", HIB "这是一条全身碧绿，吸大海之间的精华而长大"
                    "的神龙！它全身散发着碧绿色的光芒！\n\n" NOR);

        set("race", "野兽");
        set("gender", "雄性");
        set("age", 200);
        set("no_get", 1);
        set("shen_type", 0);
        set("attitude", "aggressive");
        set("limbs", ({ "头部", "身体", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("dex",100);
        set("con",100);
        set("int",100);
        set("str",100);

        set("combat_exp", 200000000);
        set("level", 70);
        set("qi", 2000000);
        set("max_qi", 2000000);
        set("jing", 1000000);
        set("max_jing", 1000000);
        set("neili", 4000000);
        set("max_neili", 4000000);
        set("neili", 4000000);
        set("jiali", 20000);

        set("unarmed", 1500);
        set("parry", 1500);
        set("claw", 1500);
        set("dodge", 1500);
        set("force", 1500);

        set("chat_chance", 5);
        set("chat_msg", ({
                HIB "海底打来一个巨浪！差点把你卷走！\n" NOR,
                HIB "镇海神龙突然吐出一颗湛蓝的珠子，又卷了回去！\n" NOR,
        }));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: big_blowing :),
        }));

        set_temp("apply/attack", 2000+random(1000));
        set_temp("apply/unarmed_damage",2000+random(1000));
        set_temp("apply/armor", 2000+random(1000));
        set_temp("apply/add_weak", 60);
        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 20);
        set_temp("apply/add_busy", 5);

        set("rewards", ([
                "exp"   : 70000,
                "pot"   : 35000,
                "mar"   : 7000,
                "score"   : 500,
                "gold"  : 100,
                "weiwang"   : 1000,
        ]));
        // 物品奖励
        // set("killer_reward", killer_reward("sea_dragon"));
        set("drops", ([
                "RA&RANDOM20"    :       100,  // 低级普通装备
                "RA&RANDOM80"    :       30,   // 中级普通装备
                "FI&/clone/fam/skpaper/finger1" :   50,
                "FI&/clone/fam/skpaper/hand1"   :   50,
                "FI&/clone/fam/skpaper/claw1"   :   50,
                "FI&/clone/tessera/rune10"      :   5,
                "FI&/clone/tessera/rune11"      :   5,
                "FI&/clone/tessera/rune12"      :   5,
                "MO&A1000"       :       10,
                "MO&A1001"       :       10,
                "MO&A1002"       :       10,
                "MO&A1003"       :       10,
                "MO&A1004"       :       10,
                "MO&A1005"       :       10,
                "MO&A1006"       :       10,
                "FI&/clone/herb/drug"+(1+random(10))   :   1,
        ]));

        setup();
}

void init()
{
        object me/*, ob*/;

        ::init();
        if (! interactive(me = this_player()))
                return;

        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}

int big_blowing()
{
        message_vision(HIB "$N" HIB "从海水里深深地吸入一口气，全身发出耀眼"
                       "的蓝色，整个龙腹胀大了几倍！！\n" NOR, this_object());

        remove_call_out("hurting");
        call_out("hurting", random(2) + 1);
        return 1;
}

int hurting()
{
        int dam, i , num;
        object *inv;

        message_vision(HIB "$N" HIB "吐出一股巨大的海浪．．．．．．整个天地似乎都被吞没！！！\n" NOR,
                       this_object());

        inv = all_inventory(environment(this_object()));

        num = sizeof(inv);
        if (num < 1) num = 1;
        if (num > 5) num = 5;

        dam = 25000 / num;

        for (i=sizeof(inv)-1; i>=0; i--)
        {
                if (living(inv[i]) && inv[i] != this_object())
                {
                        dam-=query_temp("apply/reduce_cold", inv[i]);
                        if (dam <0) dam = 0;

                        inv[i]->receive_damage("qi", dam, this_object());
                        inv[i]->receive_damage("jing", dam/2, this_object());
                        inv[i]->receive_wound("qi", dam, this_object());
                        inv[i]->receive_wound("jing", dam/2, this_object());
                        COMBAT_D->report_status(inv[i], 1);
                }
        }
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;
        int reduce;

        damage = 5000 + random(5000);
        reduce=query_temp("apply/reduce_cold", ob);
        damage = damage - damage * reduce / 100;
        if (damage < 0) damage = 0;
        ob->receive_damage("qi", damage, me);
        ob->receive_wound("qi", damage, me);
        set("neili",query("max_neili",  me), me);
        return HIB "$N" HIB "“哈”的一声吐出一口寒气，登时令$n"
               HIB "全身几乎冻僵。\n" NOR;
}
