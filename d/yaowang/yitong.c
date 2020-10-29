inherit ROOM;

void create()
{
        set("short", "议事厅");
        set("long", @LONG
这里就是药王谷的议事厅。高大的殿堂，四处雕梁画栋。
正中是一把巨大的红木太师椅，后面一扇巨大的屏风上
雕刻着蟠龙飞凤。
LONG
        );
        set("exits", ([
  "south" : __DIR__"myuan",
  "north" : __DIR__"xiangfang",
]));
/*
        set("objects", ([
        CLASS_D("yaowang") + "/wuchen" : 1,
]));
*/
        setup();
        replace_program(ROOM);
}
