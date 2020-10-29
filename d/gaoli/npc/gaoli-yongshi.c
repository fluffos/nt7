inherit NPC;
void create()
{
  set_name("高丽勇士",({ "gaoli yongshi","yongshi"}) );
        set("gender", "男性" );
        set("age", 35);
   set("long", "这是高丽的勇士，在高丽少有敌手。\n");
   set("combat_exp",1500000+random(3000));
   set_skill("dodge",680);
   set_skill("parry",680);
   set_skill("unarmed",680);
   set("attitude", "peaceful");
   set("chat_chance",20);
   set("chat_msg",({
    "高丽勇士一笑：谁敢和我挑战？真是活得不耐烦了！\n",
    "高丽勇士朝你哼了一声：小角色，以后别让我见到你！\n",
    "高丽勇士把头一昂，冷冷地看了你一眼。\n",
    "高丽勇士一晒：据说谁杀了我会得到什么称号，我看这样的人还没出生呢！\n",
    }));
  setup();
  
}

void die()
{
   object ob;
   
   ob=query_temp("last_damage_from");
   
   if(!ob) return ::die();
   if(!userp(ob)) return ::die();
   
   if(random(100)>95){
     CHANNEL_D->do_channel(this_object(),"rumor",ob->name()+"杀死高丽勇士，获得了"+
      "「高丽王者」的称号！\n");
     ob->set_temp("rank/class","高丽王者");
   }
   
   return ::die();
   
}
