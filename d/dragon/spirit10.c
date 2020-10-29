inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "小屋里");
        set("long",
"[1;32m这是一间朴素的小木屋，屋中的摆设都是些简单必要的家具\n"
"。窗下是一张小几，上面放着一些食物。一个精灵族的女子正在屋中忙碌\n"
"着什么。\n"
); 
        set("objects", ([ 
            "/quest/tulong/npc/spiritgirl" : 1,
            "/quest/tulong/npc/kid" : 1,
          ]));        
        set("exits", ([ /* sizeof() == 4 */
           "east" : __DIR__"village",
   ]));

        setup();
//        replace_program(ROOM);

}

void init()
{
  add_action ("do_search","search"); 
}

int do_search (string arg)
{
  object who = this_player ();
  object where = this_object ();
  object hook;
 
        if (  present("hook", who) ) {
                return notify_fail("你不是已经找到了吗？\n");
          }
  if (random(10))
  {
    message_vision ("$N四处搜索了一番，什么也没有找到。\n",who);  
  }
  else
  {
    hook = new ("/quest/tulong/obj/hook");
    message_vision ("$N把小屋的大小角落都找了个遍，发现了一个小钩子！\n",who,hook);
    hook->move(who);  
  }
  return 1;
}
