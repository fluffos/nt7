inherit ROOM;


void create ()
{
  set ("short","青石路");
  set ("long", @LONG
这里是条青石路。北边是安南的北门。这里的行人很多，往南边走
就可以到安南的中心了。由于近年安南帮活动猖獗，他们有是以贩卖人
口为职业，所以安南的街头少见年轻女子了。
LONG);

  set("exits", ([ 

  "south":__DIR__"qingshilu1",
// "east":"/d/clone/room/cityroom/baling",
  "north":__DIR__"beimen",
       ]));
 set("objects",([
         __DIR__"npc/boy":1,
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
