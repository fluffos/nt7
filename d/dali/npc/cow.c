// cow.c

inherit NPC;

void create()
{
        set_name("水牛", ({ "shui niu", "niu" }));
        set("long","一头南方山区常见的水牛，是耕作的主力，也用来拉车载物。由于水草茂盛，长得十分肥壮。\n");
        set("race", "家畜");
        set("age", 5);
        set("int", 30);
        set("qi", 300);
        set("max_qi", 300);
        set("jing", 100);
        set("max_jing", 100);
        set("shen_type", 0);
        set("combat_exp",50000);
        set("attitude", "peaceful");

        set("limbs", ({ "头部", "腹部", "尾巴","后腿","前腿" }) );
        set("verbs", ({ "bite","hoof" }) );
        set_temp("apply/attack", 50);
        set_temp("apply/armor", 15);
        set_temp("apply/damage", 25);

        setup();
}
