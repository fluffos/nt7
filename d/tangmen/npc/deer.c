// yelu.c 野鹿

inherit NPC;

void create()
{
        set_name( "野鹿", ({ "ye lu", "lu", "deer"}) );
        set("race", "野兽");
        set("age", 2 + random(3));
        set("long", "一只满身斑点的小野鹿，不停的蹦蹦跳跳。\n");
        set("attitude", "peaceful");
        set("str",30);
        set("max_qi",500);
        set("qi",500);
        set("max_jingli",800);
        set("jingli",800);
        
        set("limbs", ({ "头部", "身体", "前脚", "后脚", "尾巴" }) );
        set("verbs", ({ "knock", "hoof" }) );

        set("combat_exp", 30000);

        set_temp("apply/attack", 90);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 70);

        setup();
}