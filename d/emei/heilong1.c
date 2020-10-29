inherit ROOM;

void create()
{
      set("short", "黑龙江栈道");
        set("long", @LONG
黑龙江栈道沿黑龙江而建。这里一山中开，两崖并立，形成一道
宽仅数尺，长达几百米的深峡——白云峡。黑龙江栈道就从狭窄的白
云峡中转折穿过，架设在绝壁上。走在栈道上只觉道窄人危；俯视深
涧，急流飞旋，山静而觉动；仰观头顶天光如隙，崖开而欲合。这就
是天开画图的「一线天」。栈道南通千佛庵，北至清音阁。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "south" : __DIR__"heilong2",
          "north" : __DIR__"qingyinge",
      ]));
      set("no_clean_up", 0);
        set("coor/x", -460);
        set("coor/y", -230);
        set("coor/z", 100);
        setup();
      replace_program(ROOM);
}