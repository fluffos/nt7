inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "桃林");
        set("long",
"[1;32m这是片茂密的桃林(peachtree)，林中芳草鲜美，落英缤纷，\n"
"一层淡淡的薄雾，混合着青青的草香，弥漫在空气之中。偶尔的一两声鸟\n"
"鸣，愈发地显出幽静来。这里的小路已被落花铺满，早已辨不出痕迹来。\n"
"[2;37;0m\n"
);
        set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"lake1",
]));

        set("item_desc", ([
            "桃树": "粉云彩霞般的桃花，热热闹闹地开满了枝头。\n",
            "peach tree": "粉云彩霞般的桃花，热热闹闹地开满了枝头，让人忍不住想摘(pick)一枝桃枝(taozhi)下来。\n",
        ]) );

        set("no_magic", 1);
        setup();
}

void init() 
{
   add_action("do_pick", "pick");
}

int do_pick(string arg)
{
   object me, where, zhi;

   me = this_player(); 
        where=environment(me); 
   if(!arg || arg != "taozhi" && arg != "桃枝") return 0;       
   if( query_temp("marks/taozhi", where)){
      tell_object(me, "\n再摘桃树就秃了! \n");  
      return 1;
   }    
   zhi = new("/quest/tulong/obj/taozhi");
   zhi->move(me);
   set_temp("marks/taozhi", 1, where);
   message_vision("\n$N伸手摘了一枝桃花下来。\n", me);
        
   return 1;    
}
