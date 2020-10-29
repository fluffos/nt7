// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("农妇", ({ "nong fu", "nong", "fu" }));

        set("long", "一个普通的农妇，跟凡间没什么两样。\n");

        set("gender", "女性");
        set("age", 23);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 121);

        
        set("inquiry", ([
		"蓬莱仙岛"               :   "我世代都居住在此，从未出过长生村。\n",
        ]));
             
        setup();

        carry_object("/clone/cloth/cloth")->wear();
}

void unconcious()
{
        die();
}
