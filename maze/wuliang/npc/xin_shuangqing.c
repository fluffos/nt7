// NPC :xin_shuangqing.c 辛双清
// By River 98/12
inherit NPC;
void create()
{
        set_name("辛双清", ({ "xin shuangqing", "xin", "shuangqing"}));
        set("title","无量剑西宗掌门");              
        set("gender", "女性" );
        set("age", 42);
        set("str", 27);
        set("con", 23);
        set("dex", 26);
        set("int", 25);
        set("per", 20);
   	set("attitude", "friendly");

        set("max_qi", 1800);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("neili", 2000);
	set("qi", 1800);	
        set("max_neili", 2000);
        set("jiali", 40);
        set("unique", 1);
        
        set("long","她是无量剑西宗的掌门，铁青着脸，嘴唇紧闭。\n");
        set("combat_exp", 350000);
        set("shen", 1000); 

        set_skill("parry", 120);
        set_skill("dodge", 100);
        set_skill("force", 100);
        set_skill("cuff", 100);
        set_skill("sword", 100);
        set_skill("qiantian-yiyang", 100);   
        set_skill("xiaoyaoyou", 100);
        set_skill("wuliang-jian", 100);
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "wuliang-jian");
        map_skill("sword", "wuliang-jian");
        map_skill("force", "qiantian-yiyang");         

        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}