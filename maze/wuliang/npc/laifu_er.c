// NPC :laifu_er.c 来福儿 
// By River 98/12
inherit NPC;
void create()
{
        set_name("来福儿", ({ "laifu er", "laifu", "er"}));
        set("title","万劫谷家人");                
        set("gender", "男性" );
        set("age", 33);
        set("str", 17);
        set("con", 23);
        set("dex", 26);
        set("int", 25);
        set("per", 14);
   	set("attitude", "friendly");

        set("max_qi", 500);
        set("max_jing", 300);
        set("eff_jingli", 300);
        set("neili", 500);
	set("qi", 500);	
        set("max_neili", 500);      
        set("unique", 1);
        
        set("long","一个老老实实的人，已经在万劫谷中多年了。\n");
        set("combat_exp", 50000);
        set("shen", 0); 

        set_temp("apply/attack",  50);
        set_temp("apply/defense", 50); 

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}