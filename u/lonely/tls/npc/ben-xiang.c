//cool@SJ,990605
inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("本相大师", ({ "benxiang dashi","benxiang","dashi"}) );
        set("nickname", "牟尼堂老僧");
        set("long", "这位白须白眉，枯黄精瘦，身穿一袭金丝木
棉袈裟的老僧便是本因方丈的师兄本相大师。\n");
	set("gender", "男性" );
        set("attitude", "friendly");
	set("class", "bonze");
	set("age", 72);
	set("shen_type", 1);
	set("str", 25);
	set("int", 30);
	set("con", 25);
	set("dex", 25);
        create_family("天龙寺", 13, "弟子");
        set("unique", 1);
	set("qi", 3500);
	set("max_qi", 3500);
        set("eff_jingli", 2000);
	set("jing", 2000);
	set("jingli", 2000);
	set("max_jing", 2000);
	set("neili", 4000);
	set("max_neili", 4000);
	set("jiali", 100);
	set("combat_exp", 1450000);
	set("score",0);

        set_skill("strike", 165);
        set_skill("qingyan-zhang", 170);      
        set_skill("force", 175);
	set_skill("qiantian-yiyang", 180);     
	set_skill("dodge", 160);
	set_skill("tianlong-xiang", 155);
	set_skill("parry", 170);
	set_skill("finger", 175);
	set_skill("yiyang-zhi", 155);
        set_skill("kurong-changong", 120);
	set_skill("buddhism", 175);
	set_skill("literate", 140);
        set_skill("liumai-shenjian", 120);
        set_skill("medicine", 130);
	map_skill("force", "qiantian-yiyang");
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
        map_skill("strike", "qingyan-zhang");
	map_skill("finger", "yiyang-zhi");
	
	if(random(2)!=1) {		
        prepare_skill("finger","yiyang-zhi");
        set("chat_chance_combat", 30);
        set("chat_msg_combat",({ 
              (: perform_action, "finger.sandie" :),
        }));
        } else prepare_skill("strike","qingyan-zhang");
        setup();
         carry_object("/d/tls/obj/nianzhu")->wear();
        carry_object("/d/tls/obj/jiasha")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();
}
#include "ben.h";
