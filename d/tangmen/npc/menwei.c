// menwei

inherit NPC;

void create()
{
        set_name("门卫", ({ "men wei", "wei"}));
        set("long", 
        "他是唐门世家的门卫，对保护唐门世家可谓忠贞不二。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 18);
        set("int", 25);
        set("con", 24);
        set("dex", 28);

        set("combat_exp", 700000);

        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("sword", 500);
        set_skill("blade", 300);    
        set_skill("strike", 300);
        create_family("唐门世家", 10, "家丁");

        setup();
        carry_object("/clone/misc/cloth")->wear();
}