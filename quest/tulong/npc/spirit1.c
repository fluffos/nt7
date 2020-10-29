inherit NPC;

void create()
{
        set_name("小精灵", ({ "spirit" }) );
        set("race", "人类");
        set("age", 5);
        set("long", 
"一只长着透明羽翼的小精灵，在忽上忽下地飞舞，看上去似乎不难抓(catch)到。\n");
        set("max_qi", 90);
        set("limbs", ({ "头部", "身体" }) );
        set("verbs", ({ "bite" }) );

        set_skill("dodge", 100); 
        set_skill("spirit-dodge", 100);
        map_skill("dodge", "spirit-dodge");
        setup();
}
