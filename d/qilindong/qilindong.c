inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "麒麟洞");
        set("long",
"这里就是麒麟洞，一只火麒麟盘踞在这里，看见有人进来，发出\n"
"一声震天巨吼，然后便发起了攻击。听说它守护着雄霸留下来的宝藏。\n"
"有空的话，搜索(search)一下或许会有收获。\n"
);
        set("exits", ([ 
              "south" : __DIR__"dong5", 
           ]));
        set("objects", ([ 
             __DIR__"npc/huoqilin" : 1,
          ]));        
        setup();
} 

void init()
{
     add_action ("do_search","search"); 
     add_action ("do_train","train");
}

int do_train(string arg)
{
    write("麒麟洞里的都是神兽，这你也想驯服？！\n");
    return 1;
} 

int do_search (string arg)
{
    object who = this_player();   
    object tu;  
 
   
   if ( who->query("reborn_start/qilindong/tu") )
   {
         write("你已经找到过图样了!\n");
         return 1;
   }

   if (random(10))
   {
      message_vision ("$N四处搜索了一番，什么也没有找到。\n",who);
      write("看来还得再仔细找找!\n");  
      who->start_busy(2 + random(2));
   }
   else
   {
      tu = new(__DIR__"npc/obj/tu");
      message_vision ("\n突然只见$N竟从枯树叶间找出一张"+YEL"残破的图样"NOR+"！\n",who);
     
      tu->move(who);  
      who->set("reborn_start/qilindong/tu",1);
      message("vision", HIW"【转世传闻】：据说"+ who->query("name") +
                       "在麒麟洞内找到了一张残破的图样。\n"NOR, users());
      
  }
  return 1;
}


