#include <ansi.h>
inherit NPC;
void create()
{
        set_name("王八衰", ({ "wang bashuai","wang","bashuai"}) );
        set("long",@LONG
这人勾鼻深目，皮包骨的脸像鬼而不似人，配合着似若从地狱里爬出来
的魔鹰，教人感到不寒而栗。
LONG
         );
        set("title",CYN"神箭八雄"NOR);
       set("nickname","鬼神箭");
        set("max_jing", 6000);
        set("max_qi", 8000);                    
        set("max_sen", 6000);
        set("max_neili",7000); 
        set("neili",7000);
        set("jiali",190);     
        set("combat_exp",15000000);
        set("cor",250);
        set("age",35);
        set_skill("pixie-jian", 420);
        set_skill("dodge", 500);
        set_skill("parry", 500);
        set_skill("sword",520);
        set_skill("force",800); //防止别人来弹指
        set_skill("hamagong",500);
        set_skill("tiyunzong",500);
        map_skill("sword","pixie-jian");
        map_skill("parry","pixie-jian");
        map_skill("dodge","tiyunzong");
        map_skill("force","hamagong");

        set_temp("apply/damage",150);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player())) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
         if(random(15) < 2)
                this_object()->set_leader(ob);
        }
}


