inherit ROOM;


void create ()
{
  set ("short","东街");
  set ("long", @LONG
这里是安南的东街，这里的行人很多。西边是安南的中心了，那里
传来了热闹的声音。南边是一条小巷，阴暗无光，是地痞流氓聚集的场
所，里面传来了吵架、打骂的声音。
LONG);

  set("exits", ([ 

  "northwest":__DIR__"center",
  "east":__DIR__"dongjie2",
  "south":__DIR__"xiaoxiang1",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
