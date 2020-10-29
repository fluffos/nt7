//restroom2.c
inherit ROOM;

void create()
{
  set("short","休息室");
        set("long", @LONG
这里是间休息室，里面有张大床。在这里睡觉非常舒服，没人能
打扰。往北是一条长廊。
LONG );
  set("exits",([
      "north" : __DIR__"chlang3",
  ]));
  set("sleep_room", 1);
  set("no_fight",1);
  set("no_steal",1);
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}
