//room: 
inherit ROOM;
void create()
{
  set("short","长廊");
        set("long", @LONG
这里是白虎堂的长廊。两边一片狼籍，看样子刚被洗劫一场，遍
地横尸，残不忍赌。
LONG );
  set("exits",([
     "north" : __DIR__"baistep1",
      "south" : __DIR__"baihutang",
  ]));
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}