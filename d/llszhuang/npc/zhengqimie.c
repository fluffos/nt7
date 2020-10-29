#include <ansi.h>
inherit NPC;
void create()
{
        set_name("郑七灭", ({ "zheng qimie","zheng","qimie"}) );
        set("long",@LONG
郑七灭是武林第一美男子，一张英俊得绝无瑕疵的脸庞裹，嵌着一双比深黑
海洋里闪闪发光的宝石还明亮的眼睛，冷冷地扫视四方。
LONG
         );
        set("nickname","邪异箭");
        set("title",BLU"神箭八雄"NOR);
        set("max_jing", 4000);
        set("max_qi", 8000);                    
        set("max_sen", 4000);
        set("max_neili",7000); 
        set("neili",7000);
        set("jiali",50);     
        set("combat_exp",3500000);
        set("cor",100);
        set("age",35);

        set_skill("pixie-jian", 420);
        set_skill("dodge", 500);
        set_skill("parry", 400);
        set_skill("sword",420);
        set_skill("force",800); //防止别人来弹指
        set_skill("hamagong",400);
        set_skill("tiyunzong",400);
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
