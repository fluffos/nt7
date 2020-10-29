// huangboliu.c
inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;
#include <ansi.h>;
void create()
{
        set_name("黄伯流", ({ "huang boliu","huang","boliu"}) );
        set("gender", "男性" );
        set("title", "日月神教风雷堂香主");
        set("nickname", HIW"银髯蛟"NOR);
        set("age", 85);
        set("long", "一部白须，直垂至胸，身材魁梧之极。\n");
        set("attitude", "friendly");
        set("shen_type", 1);

        set("per", 21);
        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 20);

        set("max_qi", 1000);
        set("max_jing",1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("combat_exp", 350000);
        set("jiali", 100);
        set("score", 30000);

        set_skill("force", 100);
        set_skill("dodge", 90);
        set_skill("unarmed", 100);
        set_skill("parry", 80);
        set_skill("changquan",70);
        set_skill("tiyunzong", 80);

        map_skill("dodge", "tiyunzong");
        map_skill("parry", "changquan");
        map_skill("unarmed", "changquan");

        create_family("日月神教",2,"弟子 风雷堂香主");

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

