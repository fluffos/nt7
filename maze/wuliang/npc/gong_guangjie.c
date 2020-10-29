// NPC :gong_guangjie.c 龚光杰
// By River 98/12
inherit NPC;
void create()
{
        set_name("龚光杰", ({ "gong guangjie", "gong", "guangjie"}));
        set("title","无量剑东宗弟子");              
        set("gender", "男性" );
        set("age", 36);
        set("str", 27);
        set("con", 23);
        set("dex", 26);
        set("int", 25);
        set("per", 15);
   	set("attitude", "friendly");

        set("max_qi", 1000);
        set("max_jing", 800);
        set("eff_jingli", 800);
        set("neili", 1000);
	set("qi", 1000);	
        set("max_neili", 1000);      
        set("unique", 1);
        
        set("long","他是无量剑东宗的弟子。\n");
        set("combat_exp", 200000);
        set("shen", 800); 

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
        carry_object(__DIR__"obj/changpao")->wear();
}