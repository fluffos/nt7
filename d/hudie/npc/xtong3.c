// xtong3.c 小童

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("小童", ({ "xiao tong","xiao","tong" }) );
        set("gender", "男性" );
        set("age", 13);
        set("long", "这是一个清秀的小童，身着一身青衣，一付可爱的样子。\n");
        set("shen_type", 1);
        set("combat_exp", 50000);
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set("attitude", "friendly");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("silver",random(50));
}
