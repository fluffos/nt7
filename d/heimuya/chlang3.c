//chlang3
inherit ROOM;

void create()
{
  set("short","长廊");
        set("long", @LONG
这里是非常气派的长廊，戒备森严。东边就是日月神教圣姑任大
小姐的居室。
LONG );
  set("exits",([
      "east"  : __DIR__"shenggu",
      "west"  : __DIR__"dating4",
      "south" : __DIR__"restroom2",
  ]));                     
  set("no_fight",0);
  set("no_steal",0);
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}
