#include <ansi.h>
inherit NPC;
void create()
{
        set_name("李四摧", ({ "li sicui","li","sicui"}) );
        set("long",@LONG
他一副慢条斯理的悠闲神态。瘦削的脸庞，高挺微勾的鼻，轮廓清楚分明，
两眼似开似闭，时有精光电闪，一看便知道是难惹的人物。他看来只有三十许，
还算得上相当英俊，但他成名江湖最少有四十年以上，如此估计，他的年岁应该
不少於六十。只不过先天气功到了他们这类境界，往往能克服衰老这个障碍。
LONG
         );
        set("title",RED"神箭八雄"NOR);
       set("nickname","毒手箭");
        set("max_jing", 6000);
        set("max_qi", 6000);                    
        set("max_sen", 6000);
        set("max_neili",6000); 
        set("neili",6000);
        set("jiali",150);     
        set("combat_exp",3800000);
        set("cor",140);
        set("age",45);

        set_skill("pixie-jian", 420);
        set_skill("dodge", 500);
        set_skill("parry", 500);
        set_skill("sword",420);
        set_skill("force",800); //防止别人来弹指
        set_skill("hamagong",400);
        set_skill("tiyunzong",500);
        map_skill("sword","pixie-jian");
        map_skill("parry","pixie-jian");
        map_skill("dodge","tiyunzong");
        map_skill("force","hamagong");
        prepare_skill("claw","spicyclaw");
        set_temp("apply/damage",50);
        set("chat_chance_combat",10);
        set("chat_msg_combat", ({
                (: exert_function,"powerup" :),
        }) );

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
