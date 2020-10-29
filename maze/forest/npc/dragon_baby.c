#include <ansi.h>
#include <combat.h>
inherit NPC;


void do_attack();
void create()
{
        set_name("小龙", ({ "dragon baby", "dragon" }) );
        set("vendetta_mark","dragon");
        set("race", "野兽");
        set("gender", "雄性");
        set("age", 50);

        set("long", "胖呼呼的小龙。\n");

        set("str", 60+random(20));
        set("con", 52);
        set("dex", 20);
        set("fle",100);
        set("resistance/gin",30);
        set("resistance/sen",30);
        set("resistance/qi",30);
        set("no_curse",1);
        set("max_qi", 3000);
        set("max_jing", 1500);
        set("neili", 10000);
        set("max_neili", 10000);
        set("attitude", "peacefull");
        set("limbs", ({ "头部", "身体", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: do_attack :)
        }) );
        set("combat_exp", 300000);
        set("bellicosity", 100 );

        set_temp("apply/attack", 80);
        set_temp("apply/unarmed_damage", 80);
        set_temp("apply/armor", 80);
        setup();
        carry_object(__DIR__"obj/dragon_skin");
}

void do_attack()
{
        object *enemies,enemy;
        string msg;
        int be_damaged;
        enemies = query_enemy();
        if (!enemies || sizeof(enemies)==0)
                        return;
        enemy = enemies[random(sizeof(enemies))];
        addn_temp("apply/attack",50);
        addn_temp("apply/damage",50);
        msg = HIM"$N突然一转身，龙尾朝$n扫来！\n"NOR;
        message_combatd(msg, this_object(), enemy);
        COMBAT_D->do_attack(this_object(),enemy, 0, 0);
        addn_temp("apply/attack",-50);
        addn_temp("apply/damage",-50);
        start_busy(2);
}