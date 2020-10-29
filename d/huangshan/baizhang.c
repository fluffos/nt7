// Room: /d/huangshan/baizhang.c
// Last Modified by Lonely on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "百丈泉");
        set("long", @LONG
黄山三大名瀑之一，因飞流直下而名，由观瀑亭远看极为壮观，到
此近观，但见飞珠溅玉，水声轰鸣，一股清凉之气扑面而来，别有一番
妩媚风情。东面的九龙瀑更是绝佳。
LONG
        );
        set("exits", ([ 
                "west"   : __DIR__"qingluan",
                "eastup" : __DIR__"jiulong",
        ]));
        set("resources/water",1);
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -1080);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}