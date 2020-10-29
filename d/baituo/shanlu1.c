inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这里是白驼山庄广场西边的一条小路，寻常百姓平时都是经过这
条小路上山。
LONG );
          set("exits", ([
                      "north" : __DIR__"shulin",
                      "south" : __DIR__"shanlu",
             ]));
          set("outdoors", "baituo");
          set("objects", ([
                      __DIR__"npc/qiaofu" : 1 ,
              ]));
          set("coor/x", -49990);
        set("coor/y", 19990);
        set("coor/z", 0);
        setup();
          replace_program(ROOM);
}