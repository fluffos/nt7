// lu.c
inherit NPC;
void create()
{
        set_name("梅花鹿", ({ "meihua lu", "lu" }) );
        set("race", "野兽");
        set("age", 5);
        set("long", "一只温顺可爱的梅花鹿。\n");
        set("limbs", ({ "头部", "身体", "前爪", "后爪", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 1000);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 10);
        setup();
}
