// xiantong.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("仙童", ({ "xian tong", "xian", "tong" }));
        set("gender", "女性");
        set("age", 20);
        set("max_qi", 99999);
        set("qi", 99999);
        set("max_jingli", 99999);
        set("max_jing", 99999);
        set("max_neili", 99999);
        set("jing", 99999);
        set("jingli", 99999);
        set("neili", 99999);

        set("per", 25);
        set("con", 88);
        set("int", 88);
        set("dex", 88);
        set("str", 88);

        set("combat_exp", 10000000);
        set("shen_type", 1);
        setup();
        carry_object(__DIR__"cloth/feature");
        carry_object(__DIR__"cloth/feature")->wear();
}

