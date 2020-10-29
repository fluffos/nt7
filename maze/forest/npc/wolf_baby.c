#include <ansi.h>
inherit NPC;
void create()
{
        string *names = ({"灰毛恶狼","黄毛恶狼","白毛恶狼"});
        set_name( names[random(sizeof(names))], ({ "wolf"}));
        set("vendetta_mark","wolf");
        set("race", "野兽");
        set("gender", "雄性");
        set("age", 20);
        set("long", "这是一只残忍的恶狼。\n");

        set("str", 40);
        set("cor", 100);
        set("cps", 22);
        set("max_qi", 2000);
        set("max_jing", 1000);
        set("max_neili", 2000);
        set("attitude", "peaceful");
        set("chat_chance", 2);

        set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 100000);
        set("bellicosity", 5 );

        set_temp("apply/attack", 20);
        set_temp("apply/dodge", 20);
        set_temp("apply/parry", 20);
        set_temp("apply/unarmed_damage", 10);
        setup();
        carry_object(__DIR__"obj/wolf_skin");
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("qi",30+random(30), me);
        victim->receive_wound("qi",10+random(10), me);
        message_combatd(HIW"\n$N"+HIW"锋利的爪子在$n"+HIW"身上留下一道血淋淋的伤口！"NOR,me,victim);
        return;
}