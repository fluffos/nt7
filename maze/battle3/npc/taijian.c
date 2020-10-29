#include <ansi.h>
inherit NPC;
void create()
{
        set_name("太监", ({ "tai jian", "gonggong"}));
        set("gender", "无性");
        set("age", random(20) + 20);

        set("long","这是一个京城皇宫中的一名太监，负责为皇帝传送奏本。\n");
        set("combat_exp", 80000);
        set("attitude", "peaceful");
        set("max_qi", 3000);
        set("max_jing", 2000);
        set("max_neili",2000);
        set("neili",1000);

        setup();
        carry_object("clone/misc/cloth")->wear();
}            