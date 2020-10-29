inherit ROOM;
#include <ansi.h> 

void create ()
{
  set ("short", "瀑布");
  set ("long",HIG @LONG
苍山峻岭，峰势崔巍，只见顶上白云飘飘，崖前树影寒寒，林
内松柏千千，四处怪石嶙嶙，令人举步维难。瀑布声震耳欲聋，水
花飞溅，如碎玉般漫天飘洒。山崖顶上隐隐有瑞气祥云，不知将有
何异象出现。
LONG);

  set("exits", ([
        "north"    : __DIR__"spirit9",
      ]));
  set("no_magic", 1);
        setup();
}

void init ()
{
  add_action ("do_climb","climb");
}

int do_climb (string arg)
{
  object who = this_player();

  message_vision ("$N手脚并用奋不顾身地向上爬去。\n",who);
  if( query("combat_exp", who)<10000 || 
      random(4))
  {
    message_vision ("\n……哗哗一声，$N失手滑了下来。\n",who);
    who->unconcious();    
  }
  else
    who->move(__DIR__"yashang");
  return 1;
}
