// fansong.c
#include <ansi.h>
inherit NPC;

void create()
{
    set_name("范松", ({"fan song", "fan", "song"}));
    set("nickname", HIW "大力神魔" NOR );
    set("title", "日月神教长老");
    set("gender", "男性");
    set("age", 42);
    set("shen_type", -1);
    set("long",
        "他是日月神教长老。\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 30);
    set("int", 30);
    set("con", 30);
    set("dex", 30);

    set("qi", 3000);
    set("max_qi", 3000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3000);
    set("max_neili", 3000);
    set("jiali", 300);

    set("combat_exp", 1500000);
    set("score", 0);

    set_skill("force", 150);
    set_skill("unarmed", 150);
    set_skill("changquan", 150);
    set_skill("dodge", 150);
    set_skill("lingxu-bu", 150);
    set_skill("parry", 150);
    set_skill("axe", 150);
    set_skill("duanyun-fu", 150);

    map_skill("axe", "duanyun-fu");
    map_skill("unarmed", "changquan");
    map_skill("dodge", "lingxu-bu");
    map_skill("parry", "duanyun-fu");

    create_family("日月神教", 2, "长老");

    setup();
    carry_object("/d/heimuya/npc/obj/dafu")->wield();
    carry_object("/clone/misc/cloth")->wear();
}
