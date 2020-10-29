inherit ROOM;


void create ()
{
  set ("short","碎石路");
  set ("long", @LONG
这里是条碎石路。这里的行人很少。四周也没有什么建筑物，显得
有些冷清。北边不时传来热闹的声音。只见几个安南帮弟子从你的身旁
走过，不时回头打量了你几眼。
LONG);

  set("exits", ([ 

  "north":__DIR__"xijie1",
  "south":__DIR__"suishilu2",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
