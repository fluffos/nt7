// shuidai.c

inherit NPC;
#include <ansi.h>;
void create()
{
       set_name("水笙", ({ "shui sheng", "shui" }));
       set("long", 
     "她就是南四奇“落花流水”中的老四水岱的女儿，长的很清秀美丽。\n");
       set("gender", "女性");
       set("age", 21);
       set("attitude", "peaceful");
       set("shen_type", 0);
       set("str", 35);
       set("int", 38);
       set("con", 35);
       set("dex", 35);

       set("max_qi", 2000);
       set("max_jing", 500);
       set("neili", 2000);
       set("max_neili", 2000);
       set("jiali", 30);
       set("combat_exp", 800000);
       set("shen_type", 1);

       set_skill("force", 100);
       set_skill("huashan-neigong", 100);
       set_skill("dodge", 100);
       set_skill("huashan-shenfa", 100);
       set_skill("strike", 100);
       set_skill("huashan-zhang", 100);
       set_skill("parry", 100);
       set_skill("sword", 100);
       set_skill("huashan-sword", 100);
       set_skill("literate", 80);

       map_skill("force", "huashan-neigong");
       map_skill("dodge", "huashan-shenfa");
       map_skill("strike", "huashan-zhang");
       map_skill("parry", "huashan-sword");
       map_skill("sword", "huashan-sword");

       setup();
       carry_object("/clone/weapon/changjian")->wield();
}

