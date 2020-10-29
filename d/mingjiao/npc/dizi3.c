// dizi3.c 烈火旗教众
#include <ansi.h>
inherit NPC;
int hiting_ob(object ob);
void moving_ob(object ob);
void create()
{
       set_name("烈火旗教众", ({"jiao zhong","zhong"}));
       set("long", "他是身材高大，两臂粗壮，膀阔腰圆。他手持兵刃，\n"+
                   "身穿一红色圣衣，似乎有一身武艺。\n");
        set("gender", "男性");
        set("attitude", "peaceful");        
        set("age", 35);
        set("shen_type", 0);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 25);
        set("max_qi", 500);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("jiaji", 50);
        set("combat_exp", 50000+(random(50000)));
        set_skill("force", 50);
        set_skill("shenghuo-shengong", 50);
        set_skill("dodge", 50);
        set_skill("tiyunzong", 50);
        set_skill("cuff", 50);
        set_skill("liehuo-jian", 50);
        set_skill("parry", 50);
        set_skill("blade", 50);
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "liehuo-jian");
        map_skill("blade", "liehuo-jian");
        setup();
        create_family("明教",39,"教众");
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/mingjiao/obj/black-cloth")->wear();
}

void attempt_apprentice(object ob)
{     
        command("say 呵呵，我武功低微，可不敢收徒啊。");
        return;
}

#include "dizi.h";
