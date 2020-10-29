// 大唐双龙传
 
//书生。

inherit NPC;

void create()
{
  set_name("书生", ({"shu sheng","shu","sheng"}));
  set("long","这是高丽的一个书生，整天苦读诗书。\n");
  set("gender", "男性");
  set("combat_exp", 3000);
  set("age", 20);
  set("attitude", "peaceful");
  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);
  setup();
  carry_object("/d/gaoli/obj/cloth")->wear();
}


