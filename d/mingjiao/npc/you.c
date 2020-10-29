inherit NPC;
#include <ansi.h>
void create()
{
        set_name("游客", ({ "you ke",  "ke" }) );
        if(random(10)<6) set("gender","男性");
        else set("gender","女性");
        set("age", 20+random(40));
        set("str", 16);
        set("attitude", "peaceful");
        set("long", "这个人看起来似乎不大高兴。\n");
        set("combat_exp", 1000+random(500));
        set_skill("unarmed", 60);
        set_skill("parry", 60);
        set_skill("dodge", 60);
        set_skill("force", 60);
        set_skill("literate", 60);
        set("chat_chance",3);
        set("chat_msg",({
                CYN"游客大叫道：倒霉！真倒霉！\n"NOR,
                CYN"游客看着你恶狠狠的说道：你！小心点！这事没这么容易了结！\n"NOR,
        }) );
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/gangjian")->wield();
        add_money("silver", 10);
}
