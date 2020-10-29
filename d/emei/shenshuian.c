inherit ROOM;

void create()
{
      set("short", "神水庵");
        set("long", @LONG
神水庵位于宝掌峰下，庵前有大峨石和玉液泉，泉出石下清澈无
比，终年不涸。一株大海棠树已是数百苍龄，抱可数围高达十余丈。
旁边有福寿庵；由此西上中峰寺东下纯阳殿。
LONG );
      set("exits", ([
          "eastdown"  : __DIR__"chunyangdian",
          "westup"    : __DIR__"zhongfengsi",
          "south"     : __DIR__"fushouan",
      ]));
      set("outdoors", "emei");
      set("no_clean_up", 0);
        set("coor/x", -440);
        set("coor/y", -230);
        set("coor/z", 70);
        setup();
      replace_program(ROOM);
}