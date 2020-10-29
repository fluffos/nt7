// 大唐双龙传
 
// girl.女子。

inherit NPC;

void create()
{
  set_name("水手", ({"shui shou","shui","shou"}));
  set("long","这是在战船上工作的一个水手。\n");
  set("gender", "男性");
  set("combat_exp", 20000);
  set("age", 18);
  set("attitude", "peaceful");
  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);
  setup();
  carry_object("/d/gaoli/obj/sengyi")->wear();
}


