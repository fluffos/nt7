inherit ROOM;

void create()
{
      set("short","密林");
        set("long", @LONG
这是黑森森的一片密林，楠木参天，浓阴蔽日。这里西上是报国
寺，东边林间隐藏着一座庙宇。
LONG );
      set("exits", ([
          "eastdown"  : __DIR__"fhs",
          "westup"    : __DIR__"jietuopo",
      ]));
      set("outdoors", "emei");
      set("no_clean_up", 0);
        set("coor/x", -390);
        set("coor/y", -230);
        set("coor/z", 20);
        setup();
      replace_program(ROOM);
}