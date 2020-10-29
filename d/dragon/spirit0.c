inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "山谷");
        set("long",
"[1;32m此处有些稀疏的树木，眼前矗立着一座千层叠翠、万里点苍\n"
"的山峰，围成一处幽谷，中有一泓清潭，泉水从峰间奔流而下，喷珠泄玉，\n"
"直入清潭，还有几只小精灵正在潭边飞舞。此处空气清凉湿润，沁人心肺，\n"
"四周却看不见任何明显的出路，看来，你只好四处转转(around)看了。\n"
); 
        set("exits", ([
        ]) );

        set("objects", ([
//        "/quest/tulong/npc/spirit1": 4,
        ]) );

        set("no_magic", 1);
        setup();
}
void init()
{
   add_action("do_west", "xifang");
   add_action("do_catch", "catch");
   add_action("do_around", "around");

}

int do_around(string arg)
{
   object me, room;

   me = this_player(); 
   if (random(20)<10)
   { 
   tell_object(me, "你转来转去，也没找到出口，你迷了路！！\n\n");
   room = find_object(__DIR__"liechang");
   if(!objectp(room)) room=load_object(__DIR__"liechang");
   me->move(room);
   return 1;
   }
   else  
     tell_object(me, "你发现西边似乎有条路(xifang)。\n\n");
return 1;}

int do_catch(string arg)
{
   object spirit, me, room;

   me = this_player();
   if(!arg || arg != "小精灵" && arg != "spirit" ) return 0;
   spirit = present("spirit", this_object());
   if(!objectp(spirit)||userp(spirit)) return 0;

   switch ( random (7)) {
   case 0:
      message_vision("$N向前一扑！小精灵往後一闪，$N落了个空。 \n", me); 
      break;
   case 1:
      message_vision("$N向右一扑！小精灵向左一闪，$N落了个空。 \n", me); 
      break;
   case 2:
      message_vision("$N向左一扑，小精灵向右一闪，$N落了个空。\n", me); 
      break;
   case 3:
      message_vision("$N左扑右挡紧紧地跟着小精灵，深怕一转眼就不见了……\n", me);
   break;
   case 4:
      message_vision("$N合身扑上，小精灵向旁边一晃躲开了$N，$N收势不住摔了个嘴啃泥。  \n", me);
   break;
   case 5:
      message_vision("$N蹑手蹑脚地朝小精灵摸过去，想从后面抓住它，小精灵机灵地向前一冲，$N没成功。\n", me);
   break;
   case 6:
      message_vision("$N往前一扑，小精灵向前一冲，从$N的手边飞快的飞了过去。 \n", me); 
      message_vision("$N调头便向小精灵逃跑的方向追去……\n", me); 
      message_vision("\n小精灵三转两转，倏地一下不见了踪影。\n\n", me); 
      message("vision", me->name() + "紧紧跟着小精灵倏地一下也不见了踪影。\n", environment(me), me);
      room = find_object(__DIR__"outlet2");
      if(!objectp(room)) room=load_object(__DIR__"outlet2");
      me->move(room);
      destruct(spirit);
      break;
   }

   return 1;
}

int do_west(string arg)
{
        object me;
        object room;
        me = this_player();
        message_vision("$N往西边的树林走去 . \n", me);

        room = load_object(__DIR__"spirit3");
        if(room) me->move(room);

        return 1;
}
