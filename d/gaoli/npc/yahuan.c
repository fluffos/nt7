// 大唐双龙传

inherit NPC;

void create()
{
  set_name("丫鬟", ({"ya huan","huan"}));
  set("long","这是一位丫鬟。\n");
  set("gender", "女性");
  set("combat_exp", 3000);
  set("age", 18);
  set("per", 23);
  set("attitude", "friendly");
  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);
 
  setup();
  carry_object("/d/gaoli/obj/cloth")->wear();
}

void init()
{
   object ob;
   
   ob=this_player();
   
   if(!ob||is_fighting()) return;
   
   remove_call_out("welcome");
   call_out("welcome",1,ob);
   
}

void welcome(object ob)
{
   if(!ob) return;
   if(environment(ob)!=environment(this_object()))
   return;
   
   switch(random(2)){
    case 0:
     command("say 奴家这厢有礼了！");
     break;
    case 1:
     command("say 据说老爷要把我纳做小妾，不知道是真是假。");
   }
   
}


