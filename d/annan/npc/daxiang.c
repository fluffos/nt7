// laofu.c 大象
// Date: Sep.22 1997

inherit NPC;

void create()
{
        set_name("大象", ({ "daxiang", "xiang","xiang" }) );
        set("race", "野兽");
        set("age", 20);
        set("long", @LONG
一只大象，雄伟极了。安南特产。大地之王。

LONG);
        set("attitude", "aggressive");
        set("shen_type", -1);

        set("limbs", ({ "象头", "象身", "象前脚", "象后脚", "象鼻" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 30000);
        set("neili",15800);
        set("max_qi",15800);
        set("max_jing",15800);
        set("max_neili",15800);
        set("jingli",5000);
        set("max_jingli",5000);

        set_temp("apply/attack", 200);
        set_temp("apply/defense", 300);
        set_temp("apply/armor", 1000);
        set_temp("apply/damage", 1000);

        setup();

}
