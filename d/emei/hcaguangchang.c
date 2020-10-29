inherit ROOM;

void create()
{
      set("short","华藏庵广场");
        set("long", @LONG
这里是峨嵋华藏庵的广场，地上铺着青砖。正前方有一道台阶，
通往大雄宝殿。殿前有个丈许高的大香炉，香炉前的香台上，红烛高
烧，香烟飘绕。广场上几个小师太正在练功。自此左右各有一条走廊
通向后殿。
LONG );
              set("objects", ([
                CLASS_D("emei") + "/first" : 1,
                   CLASS_D("emei") + "/xu" : 1,
              ]));

              set("outdoors", "emei");

              set("exits", ([
                  "north" : __DIR__"hcazhengdian", 
                  "south" : __DIR__"hcadadian", 
                  "west"  : __DIR__"hcawest1", 
                  "east"  : __DIR__"hcaeast1", 
              ]));

              set("valid_startroom", 1);

              set("coor/x", -560);
        set("coor/y", -330);
        set("coor/z", 220);
        setup();
              replace_program(ROOM);
              "/clone/board/emei_b"->foo();
}
