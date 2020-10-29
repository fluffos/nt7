inherit ROOM;

void create()
{
      set("short", "八十四盘");
        set("long", @LONG
八十四盘，道路艰险陡峭，迂回盘折，令人不能喘息。路左是蔽
日遮天的冷杉林，路右是深不见底的绝壁峡谷。由此往上至接引殿，
北下到洗象池。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "northdown" : __DIR__"leidongping",
          "southwest" : __DIR__"bashisipan2",
          "southeast" : __DIR__"lengsl2",
      ]));
        set("coor/x", -560);
        set("coor/y", -270);
        set("coor/z", 190);
        setup();
      replace_program(ROOM);
}