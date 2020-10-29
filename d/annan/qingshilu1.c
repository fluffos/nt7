inherit ROOM;


void create ()
{
  set ("short","青石路");
  set ("long", @LONG
这里是条青石路。南边就是安南的中心了，那边传来了热闹的声音。
东边有一家妓院，里面传来了阵阵笑声。有几个女子正在门口招呼着来
往的客人，当然有很多公子哥、江湖莽汉朝里边走去了。
LONG);

  set("exits", ([ 

  "south":__DIR__"center",
  "east":__DIR__"yingjunlou",
  "north":__DIR__"qingshilu2",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
