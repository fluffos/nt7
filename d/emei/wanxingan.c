inherit ROOM;

void create()
{
      set("short", "万行庵");
        set("long", @LONG
太子坪万行庵是古智禅师创建。庵外满山长满莎椤花，花数芭合
成一朵，叶包在花外，古人以其根坚难易而盛赞，以喻洁身自好之高
贵品质。由此向南上便至金顶，下至接引殿。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/jia" : 1,
      ]));
      set("outdoors", "emei");
      set("exits", ([
          "eastdown"  : __DIR__"jieyindian",
          "southup"   : __DIR__"jinding",
      ]));
      set("coor/x", -570);
        set("coor/y", -300);
        set("coor/z", 210);
        setup();
      replace_program(ROOM);
}