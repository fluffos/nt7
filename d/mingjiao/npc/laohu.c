// /d/mingjiao/npc/laohu.c 老虎
inherit NPC;
void create()
{
        set_name("老虎", ({ "lao hu", "hu" }) );
        set("race", "野兽");
        set("age", 5);
        set("long", "一只凶猛的大老虎。\n");
        set("attitude", "aggressive");
        set("limbs", ({ "头部", "身体", "前爪", "后爪", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 200000);
        set("str", 80);
        set("con", 80);
        set("no_get",1);
              set("chat_chance", 6);
              set("chat_msg", ({
              (: this_object(), "random_move" :),
              }) );
        set_temp("apply/damage", 30);
        set_temp("apply/armor", 50);
        setup();
}


