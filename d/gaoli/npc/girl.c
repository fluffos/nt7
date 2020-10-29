// 大唐双龙传
 
// girl.女子。

inherit NPC;

void create()
{
  set_name("小姐", ({"girl"}));
  set("long","这是高丽的一个小姐，正在这里闲逛。\n");
  set("gender", "女性");
  set("combat_exp", 3000);
  set("age", 18);
  set("per", 29);
  set("attitude", "friendly");
  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);
  set("inquiry",([
    "真冰河":"他啊，他也是高丽人呢，你们不知道吗？！\n",
    "yanyan":"他其实是朝鲜人，也就是现在的高丽人。\n",
    ]));
  setup();
  carry_object("/d/gaoli/obj/cloth")->wear();
}


