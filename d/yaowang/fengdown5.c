inherit ROOM;

void create()
{
        set("short", "山谷");
        set("long", @LONG
这里是山谷的谷底，静悄悄地没有一点声响。漆黑的土地上
散落着奇形怪状的小山石，有些石头还很尖利，人走在上面东倒
西歪的。北面是一小片低矮的灌木丛。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"fengd1",
  "south" : __DIR__"fengdown4",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
