//cool@SJ,990605

inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("本参大师", ({ "bencan dashi","bencan","dashi"}) );
        set("nickname", "牟尼堂老僧");
        set("long", "一位白须白眉的老僧，身穿一袭金丝木棉袈裟。
他身材魁梧，是本因方丈的师弟。\n");
	set("gender", "男性" );
        set("attitude", "friendly");
	set("class", "bonze");
	set("age", 65);
	set("shen_type", 1);
	set("str", 30);
	set("int", 23);
	set("con", 26);
	set("dex", 23);
	set("unique", 1);
	set("per",24);
        create_family("天龙寺", 13, "弟子");

	set("qi", 2500);
	set("max_qi", 2500);
        set("eff_jingli", 2000);
	set("jing", 2500);
	set("jingli", 2000);
	set("max_jing", 2000);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 100);
	set("combat_exp", 1300000);
	set("score",0);

	set_skill("force", 150);
	set_skill("qiantian-yiyang", 160);
	set_skill("dodge", 140);
        set_skill("duanjia-quan", 175);
	set_skill("tianlong-xiang", 140);
	set_skill("parry", 165);
	set_skill("finger", 160);
        set_skill("cuff", 170);
	set_skill("yiyang-zhi", 160);
	set_skill("kurong-changong", 40);
	set_skill("buddhism", 160);
        set_skill("liumai-shenjian", 80);
	set_skill("literate", 120);
        set_skill("medicine", 110);
	map_skill("force", "qiantian-yiyang");
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
        map_skill("cuff", "duanjia-quan");
	map_skill("finger", "yiyang-zhi");
	
	if(random(2)!=1) {		
        prepare_skill("finger","yiyang-zhi");
        set("chat_chance_combat", 30);
        set("chat_msg_combat",({ 
              (: perform_action, "finger.sandie" :),
        }));
        } else prepare_skill("cuff","duanjia-quan");
        
        setup();
        carry_object("/d/tls/obj/nianzhu")->wear();
        carry_object("/d/tls/obj/jiasha")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();
}
#include "ben.h";
