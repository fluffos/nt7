inherit ROOM;

void create()
{
        set("short", "山谷");
        set("long", @LONG
这里是山谷的谷底，静悄悄地没有一点声响。漆黑的土地上
散落着奇形怪状的小山石，有些石头还很尖利，人走在上面东倒
西歪的。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "northwest" : __DIR__"fengdown3",
  "east" : __DIR__"fengdown1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
