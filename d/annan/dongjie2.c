inherit ROOM;


void create ()
{
  set ("short","东街");
  set ("long", @LONG
这里是安南的东街。东边就是安南的东门了。北面有一家钱庄，钱
庄的金字招牌在阳光的照耀下闪闪发光。东边的东门传来了官兵吆喝的
声音。
LONG);

  set("exits", ([ 

  "north":__DIR__"qianzhuang",
  "east":__DIR__"dongmen",
  "west":__DIR__"dongjie1",
      ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
