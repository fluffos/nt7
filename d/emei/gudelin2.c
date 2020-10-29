inherit ROOM;

void create()
{
      set("short", "古德林");
        set("long", @LONG
这是一片密密的楠木林，株株秀挺俊何，枝叶分披上捧如两手拥
佛，据说有七万株，要是不熟悉地形很容易迷路。林中有一片空地，
几只楠木桩排成梅花模样。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "south"     : __DIR__"bailongdong",
          "southeast" : __DIR__"gudelin1",
          "southwest" : __DIR__"gudelin1",
          "northeast" : __DIR__"gudelin1",
          "northwest" : __DIR__"gudelin1",
      ]));
       set("objects", ([
                "/kungfu/class/misc/houwang" : random(3)+2,
        ]));
      set("no_clean_up", 0);
      set("coor/x", -480);
        set("coor/y", -230);
        set("coor/z", 80);
        set("coor/x", -480);
        set("coor/y", -230);
        set("coor/z", 80);
        setup();
      replace_program(ROOM);
}
