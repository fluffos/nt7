// wanyanhonglie.c

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("完颜洪烈", ({"wanyan honglie", "honglie", "wanyan"}));
        set("gender", "男性");
        set("title", HIY"大金国赵王爷"NOR);
        set("age", 31);
        set("class", "officer");
        set("long", "[1;31m他看起来受了很重的伤，看上去快要不行了。[0m\n");
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 26);
        set("per", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 26);

        set("qi", 300);
        set("max_qi", 1000);
        set("jing", 200);
        set("max_jing", 200);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", 10);

        set("combat_exp", 30000);
        set("score", 10000);

        set_skill("force", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("unarmed",40);

        setup();
        carry_object("/clone/cloth/jinduan")->wear();
        carry_object("/clone/cloth/guanxue")->wear();

}

