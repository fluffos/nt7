inherit ROOM;

void create()
{
      set("short","华严顶");
        set("long", @LONG
华严顶挺拔高峭，古刹云深，殿宇孤耸，风景奇险。这里视野开
阔，仰可见金顶巍巍，俯可望群峰罗列，许多蹲伏山间的寺院也在眼
底。由此向西过数坡，即到莲花石，东下过十二盘可到万年寺。北面
是一间马厩。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/li" : 1,
           __DIR__"npc/girldizi" : 1,
      ]));
      set("outdoors", "emei");
      set("exits", ([
          "north"    : __DIR__"majiu2",
          "westup"   : __DIR__"lianhuashi",
          "eastdown" : __DIR__"shierpan4",
      ]));
        set("coor/x", -520);
        set("coor/y", -240);
        set("coor/z", 120);
        setup();
      replace_program(ROOM);
}