#include <ansi.h>
inherit NPC;
void do_chan();
void do_dot();
void create()
{
        string *names = ({"紫斑王蛇","绿环王蛇","黑冠王蛇"});
        set_name( names[random(sizeof(names))], ({ "snake king","snake"}));
        set("vendetta_mark","snake");
        set("race", "野兽");
        set("gender", "雄性");
        set("age", 60);
        set("long", "这是一条王蛇。\n");

        set("str", 80);
        set("cor", 100);
        set("cps", 22);
        set("fle",70);
        set("resistance/gin",55);
        set("resistance/sen",55);
        set("max_qi", 4000);
        set("max_jing", 2000);
        set("max_neili", 5000);
        set("attitude", "peaceful");

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: do_dot() :),
        }) );
        set("limbs", ({ "头部", "身体", "尾巴", "七寸" }) );
        set("verbs", ({ "bite" }) );
        set("combat_exp", 400000);
        set("bellicosity", 5 );

        set_temp("apply/attack", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/unarmed_damage", 40);
        setup();
        carry_object(__DIR__"obj/snake_egg");
}

void do_chan() {
                object *enemies,enemy;
                string msg;
                int be_damaged;
                enemies = query_enemy();
                if (!enemies || sizeof(enemies)==0)
                                return;
                enemy = enemies[random(sizeof(enemies))];
        if (!this_object()->is_fighting(enemy) )
                return;
                msg = HIG"\n$N箭射一般扑上来，缠住了$n！\n"NOR;
                message_combatd(msg,this_object(),enemy);
                enemy->start_busy(3);
                start_busy(1);
}

void do_dot() {
                object *enemies,enemy;
                string msg;
                int be_damaged;
                enemies = query_enemy();
                if (!enemies || sizeof(enemies)==0)
                                return;
                enemy = enemies[random(sizeof(enemies))];
        if (!this_object()->is_fighting(enemy) )
                return;
                msg = HIG"\n$N喷出一口毒雾，将$n罩住！\n"NOR;
                //msg+= HIR"$n中了剧毒！\n"NOR;
                message_combatd(msg,this_object(),enemy);
                call_out("take_eff",1, enemy);
                //enemy->add_dot(500,4,"qi",this_object());
                start_busy(1);

}
void take_eff(object enemy,object me) {
                if (! enemy || environment(enemy) != environment() ||
                    ! is_fighting(enemy)) return;
                enemy->receive_damage("qi",50+random(50),me);
                enemy->receive_damage("jing",20+random(20),me);

                message_combatd(RED"\n$N身上的剧毒发作了！\n"NOR,enemy);
                COMBAT_D->report_status(enemy);

}