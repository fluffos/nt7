#include <ansi.h>
inherit NPC;
void create()
{
        object sword;

        set_name("展飞", ({ "zhan fei"}) );
        set("long",@LONG
他年约六十馀，身形高瘦，手脚均较普通人长上一些，动作灵巧，双目
转动间使人感到他是个机灵多智的人物。
LONG
         );

        set("title",MAG"矛铲双飞"NOR);
        set("max_jing", 4000);
        set("max_qi", 3000);                    
        set("max_sen", 4000);
        set("max_neili",5000); 
        set("neili",10000);
        set("jiali",70);     
        set("combat_exp",3900000);
        set("bellicosity",50000);
        set("cor",150);
        set("age",65);

        set_skill("pixie-jian", 420);
        set_skill("dodge", 500);
        set_skill("parry", 500);
        set_skill("sword",420);
        set_skill("force",800); //防止别人来弹指
        set_skill("hamagong",400);
        set_skill("tiyunzong",400);
        map_skill("sword","pixie-jian");
        map_skill("parry","pixie-jian");
        map_skill("dodge","tiyunzong");
        map_skill("force","hamagong");
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
        }
}
