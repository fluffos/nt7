#include <ansi.h>
inherit NPC;
void create()
{
        set_name("赵一伤", ({ "zhao yishang","zhao","yishang"}) );
        set("long",@LONG
赵一伤是马贼起家，凶残暴烈，早名震西陲。此人身形雄伟之极，脸的下
半部长满了针剌般的短髭，连棱角分明的厚唇也差点遮盖了，一对眼铜铃般大，
闪闪生威，顾盼间自有一股慑人气态。
LONG
         );
        set("title",RED"神箭八雄"NOR);
        set("nickname","穿身箭");
        set("max_jing", 5000);
        set("max_qi", 8000);
        set("max_sen", 5000);
        set("max_neili",5000); 
        set("neili",5000);
        set("jiali",150);     
        set("combat_exp",3500000);
        set("cor",100);
        set("age",35);
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
        set_temp("apply/damage",150);

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
