#include <ansi.h>

inherit NPC;

void do_stun();
void create()
{
        string *names = ({"棕熊","黑熊","白熊"});
        set_name( names[random(sizeof(names))], ({ "big bear","bear"}));
        set("vendetta_mark","bear");
        set("race", "野兽");
        set("gender", "雄性");
        set("age", 20);
        set("long", "这是一只凶猛的熊。\n");

        set("str", 100);
        set("dex", 40);
        set("con", 100);
        set("max_qi", 3000);
        set("max_jing", 1500);
        set("neili", 3000);
        set("max_neili", 3000);
        set("combat_exp", 300000);
        set("attitude", "peaceful");

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: do_stun() :),
        }) );

        set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set_temp("apply/attack", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/unarmed_damage", 40);
        setup();
        carry_object(__DIR__"obj/bear_hand");
}

void do_stun()
{
        object *enemies,enemy;
        string msg;
        int be_damaged;

        enemies = query_enemy();
        if (!enemies || sizeof(enemies)==0)
                return;
        enemy = enemies[random(sizeof(enemies))];
        msg = HIC"\n$N突然站立起来，抡起熊掌朝$n拍来！\n"NOR;
        message_combatd(msg, this_object(), enemy);
        COMBAT_D->do_attack(this_object(),enemy, 0, 0);
        start_busy(2);
}