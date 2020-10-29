#include <ansi.h>
#include <combat.h>
inherit NPC;
void create()
{
        string *names = ({"白额猛虎","吊睛猛虎"});
        set_name( names[random(sizeof(names))], ({ "big tiger","tiger"}));
        set("vendetta_mark","tiger");
        set("race", "野兽");
        set("gender", "雄性");
        set("age", 20);
        set("long", "这是一只凶猛的老虎。\n");

        set("str", 50);
        set("cor", 120);
        set("cps", 22);
        set("fle",50);
        set("resistance/qi",25);
        set("max_qi", 4000);
        set("max_jing", 2000);
        set("max_neili", 4000);
        set("attitude", "peaceful");

        set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 300000);
        set("bellicosity", 5 );

        set_temp("apply/attack", 50);
        set_temp("apply/parry", 50);
        set_temp("apply/unarmed_damage", 50);

        setup();
        carry_object(__DIR__"obj/tiger_bone");
}

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        message_vision(HIY"\n$N突然发出一声响彻山林的怒吼，你顿时大惊失色！\n"NOR,this_object());
        ::start_busy(1);
}
