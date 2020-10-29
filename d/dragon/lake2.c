inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "三清湖");
        set("long",
"[1;32m湖水清澈透明，不时可以看到几尾鱼跳上水面。湖水尽头是\n"
"一个大瀑布。在这里可以听到瀑布从山上直冲而下，发出的轰轰雷声。湖\n"
"边一块巨石，上写＂三清湖＂。这里风非常大，吹得人得衣衫猎猎做响。\n"
);
   set("exits", ([ 
      "northeast" : __DIR__"lake1",
   ]));

        set("no_magic", 1);
        setup();
}

void kite_notify(object obj, int i)
{
   object  me, room;
   int j;
        
   me = this_player();
   message_vision("突然一阵微风拂过"+obj->name()+"缓缓的升了起来，越来越高。\n\n" , me);
   switch( random(2) ) {
   case 0:
      tell_object(me, me->name()+"手中的"+obj->name()+"越飞越高。 \n");
      message_vision("只听一阵清悦的哨音从高空传过！ \n", me);
      call_out("boat_come", 2, me);
   break;
   case 1:
      message_vision("一阵劲风吹过，$N手中的线断了，"+obj->name() 
+"越来越高，慢慢的不见了。 \n",me);
      destruct(obj);
      break;
   }
   return; 
}

void boat_come(object me)
{
   object  boat, *inv, ob;
   int i;
        

   if (query("exits/down")) return ;
   if (!objectp(boat=find_object(__DIR__"boat")))
      boat=load_object("/u/night/room/boat");
   inv=all_inventory(boat);
   for(i=0; i<sizeof(inv); i++) {
      ob = inv[i];
      if(living(ob)){
         message("vision","半晌，湖上还是没有丝毫动静。\n",this_object()); 
         return;
      }
   }
   message("vision","过了半晌，一叶小舟缓缓地从雾中荡出，靠到了湖边。\n",this_object()); 
    set("exits/up", __DIR__"lake2", boat);
  set("exits/down",__DIR__"boat");
   call_out("boat_leave",10,boat);
   return ;
}

void boat_leave(object boat)
{
        if (query("exits/down")) delete("exits/down");
        if( query("exits/up", boat))delete("exits/up", boat);
        message("vision","一阵微风拂过，小船荡离了岸边。\n",this_object()); 
        message("vision","一阵微风拂过，小船荡离了岸边。\n",boat); 
        return;
}

int valid_leave(object me, string dir)
{
   object *inv, boat, ob;
   int i;

   if (userp(me) && dir == "down") {
      boat=find_object(__DIR__"boat");
      if (!objectp(boat))
         boat=load_object(__DIR__"boat");
         inv=all_inventory(boat);
            for(i=0; i<sizeof(inv); i++) {
               ob = inv[i];
               if(living(ob)){
                  tell_object(me, "船太小了，只能乘坐一个人。\n");      
                  return notify_fail("");
               }
           }
   }
   return 1;
}
