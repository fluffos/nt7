// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        set_name(HIY "七彩" HIM "琉璃兽" NOR, ({ "qicai liulishou", "qicai", "liulishou" }) );
        set("title", HIW "圣诞" HIR "怪兽" NOR);
        set("gender", "男性");
        set("age", 8888);
        set("long", @LONG
这是一只长相奇特怪兽，全身幻出七彩之色，头大身小，一对浑圆的眼
珠闪烁出摄人的光芒。
LONG );
        set("combat_exp", 2000000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 5000000);
        set("neili", 5000000);
        set("max_jing", 5000000);
        set("jing", 5000000);
        set("max_qi", 900000000);
        set("eff_qi", 900000000);
        set("qi", 900000000);
        set("jingli", 5000000);
        set("max_jingli", 5000000);

        set("no_nuoyi", 1); // 不被挪移影响

        set("str", 200);
        set("int", 100);
        set("con", 100);
        set("dex", 300);

        set_skill("unarmed", 4000);
        set_skill("sword", 4000);
        set_skill("parry", 4000);
        set_skill("dodge", 4000);
        set_skill("force", 4000);

        set("jiali", 1000);

        //set("end_time", 300);
        set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 100000,
                "pot"   : 50000,
                "mar"   : 10000,
                "score" : 30,
                "gold"  : 5,
        ]));

        set("drops", ([
                "RA&RANDOM30"    :       100,   // 低级普通装备
                "RA&RANDOM40"    :       40,    // 低级普通装备
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/armor/qicai-xue"      :   20,
        ]));

        set_temp("apply/attack", 150000);
        set_temp("apply/unarmed_damage", 100000);
        set_temp("apply/damage", 100000);
        set_temp("apply/armor", 10000);

/*
        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set_temp("born_time", time());
                //keep_heart_beat();
        }
*/

        setup();
}

int accept_fight(object ob)
{
        message_vision("$N一声巨吼，扑了过来。\n",
                       this_object(), ob);
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->start_busy(20 + random(10));
        me->receive_wound("qi", 5000 + random(3000), ob);
        return HIY "$N" HIY "周围雾气缭绕，直逼得$n" HIY "头晕目眩。\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1)
                set("neili", query("max_neili"));

        ::heart_beat();
}

void random_move()
{
        object env;

        if (time() - query_temp("born_time") > 1800)
        {
                env = environment(this_object());
                message_vision("$N长啸一声，化作一团火焰，消失在天际。\n", this_object());
                
                //CHANNEL_D->channel_broadcast("news", HIG "听说" + HIW +
//                            env->short() + "(" + LOOK_CMD->locate(base_name(env)) + ")" HIG "一带出现的" + 
//                      HIR + this_object()->short() + HIG "消失了。\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        command("mess 看来这趟东方之行实在是自讨没趣！");
        message_vision("$N长啸一声，化作一团火焰，消失在天际。\n", this_object());
        //CHANNEL_D->channel_broadcast("news",
                        //"听说" + name() + HIM "被一群武林异士打败，败兴而归。" NOR);
}
