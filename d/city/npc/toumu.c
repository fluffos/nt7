// liumang.c 流氓

inherit NPC;

void create()
{
        set_name("小刀会头目", ({ "tou mu", "toumu" }));
        set("gender", "男性");
        set("age", 19);
        set("long", "他是一个成天虎背熊腰的彪形大汉，两眼透露着一股凶狠的目光。\n");
        
        set("combat_exp", 100000);
        set("shen_type", -1);

        set("attitude", "peaceful");
        
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}