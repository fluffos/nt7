// lu.c
inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
#include <ansi.h>;
void create()
{
        set_name("鲁连荣", ({ "lu lianrong", "lu", "lianrong" }) );
        set("nickname", HIY"金眼雕"NOR);
        set("gender", "男性");
        set("class", "swordsman");
        set("age", 45);
        set("attitude", "peaceful");
        set("per", 13);
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 1400);
        set("max_neili", 1400);
        set("jiali", 30);
        set("max_qi",1500);
        set("max_jing",800);
        set("combat_exp", 600000);
        set("shen_type", 1);

        set_skill("unarmed", 80);
        set_skill("sword", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("dodge", 80);
        set_skill("hengshan-sword", 80);
        set_skill("lingxu-bu", 80);

        map_skill("sword", "hengshan-sword");
        map_skill("parry", "hengshan-sword");
        map_skill("dodge", "lingxu-bu");

        create_family("衡山派", 13, "弟子");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
 carry_object("/clone/cloth/cloth");
}

