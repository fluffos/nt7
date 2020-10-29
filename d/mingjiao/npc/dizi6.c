// dizi6.c 天字门教众
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("天字门教众", ({"jiao zhong","zhong"}));
        set("long","这是一位杨逍属下天字门的教众。\n");
        set("gender", "男性");
        set("attitude", "peaceful");
        set("age", 15+random(20));
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 400);
        set("max_jing", 300);
        set("neili", 400);
        set("max_neili", 400);
        set("jiaji", 1);
        set("combat_exp", 30000+(random(30000)));
        set_skill("force", 30);
        set_skill("shenghuo-shengong", 30);
        set_skill("dodge", 30);
        set_skill("piaoyi-shenfa", 30);
        set_skill("cuff", 30);
        set_skill("lieyan-dao", 30);
        set_skill("parry", 30);
        set_skill("blade", 30);
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("parry", "lieyan-dao");
        map_skill("blade", "lieyan-dao");
        setup();
        create_family("明教",39,"教众");
        carry_object("/clone/weapon/blade")->wield();
        carry_object("/d/mingjiao/obj/black-cloth")->wear();
}

void attempt_apprentice(object ob)
{     
        command("say 呵呵，我武功低微，可不敢收徒啊。");
        return;
}
