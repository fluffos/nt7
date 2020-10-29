// 大唐双龙传

inherit NPC;

void create()
{
  
  set_name("老学究", ({"lao xuejiu", "xuejiu"}));
  set("gender", "男性");
  set("combat_exp", 3000);
  set("age", 38);
  set("per", 29);
  
  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);
  set_skill("literate", 400);
  setup();
  carry_object("/d/gaoli/obj/cloth")->wear();
}
