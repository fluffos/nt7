// 大唐双龙传
 
// ma.c 马夫子

inherit NPC;

void create()
{
//  reload("gaoli_ma");
  set_name("马夫子", ({"ma fuzhi", "ma", "fuzhi"}));
  set("gender", "男性");
  set("combat_exp", 3000);
  set("age", 38);
  set("per", 29);
  set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);
  setup();
  carry_object("/d/gaoli/obj/cloth")->wear();
}


