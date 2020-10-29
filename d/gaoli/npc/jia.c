// 大唐双龙传
 
// jia.c

inherit NPC;
inherit F_DEALER;

void create()
{
 
  set_name("贾大夫", ({"jia daifu", "jia", "daifu"}));
        set("title", "药铺掌柜");
        set("gender", "男性");
  set("shop_id",({"jia dafu", "jia", "dafu"}));
  set("age", 37);
  set("combat_exp", 30000);
   set("long",
"贾大夫是高丽城中最有名的大夫,每天找他看病的人络绎不绝.\n");
  set("age", 38);
 set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);

  setup();
  carry_object("/d/gaoli/obj/cloth")->wear();
}



