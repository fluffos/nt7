// NPC :ge_guangpei.c 葛光佩
// By River 98/12
inherit NPC;
#include <ansi.h> 
void create()
{
        set_name("葛光佩", ({ "ge guangpei", "ge", "guangpei"}));
        set("title","无量剑西宗弟子");              
        set("gender", "女性" );
        set("age", 36);
        set("str", 27);
        set("con", 23);
        set("dex", 26);
        set("int", 25);
        set("per", 20);
        set("no_get","葛光佩对你来说太重了。\n");
   	set("attitude", "aggressive");

        set("max_qi", 1000);
        set("max_jing", 800);
        set("eff_jingli", 800);
        set("neili", 1000);
	set("qi", 1000);	
        set("max_neili", 1000);      
        set("unique", 1);
        
        set("long","她是无量剑西宗的弟子。\n");
        set("combat_exp", 200000);
        set("shen", -800); 

        set_skill("parry", 80);
        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("cuff", 80);
        set_skill("sword", 80);
        set_skill("qiantian-yiyang", 80);   
        set_skill("xiaoyaoyou", 80);
        set_skill("wuliang-jian", 80);
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "wuliang-jian");
        map_skill("sword", "wuliang-jian");
        map_skill("force", "qiantian-yiyang");         

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 0, ob);
        }
}

void greeting(object ob)
{
        command("say 既然被你撞见了，"+RANK_D->query_rude(ob)+"，拿命来吧！");
}