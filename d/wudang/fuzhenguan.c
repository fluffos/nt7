inherit ROOM;

void create()
{
        set("short", "复真观五层楼");
        set("long", @LONG
复真观五层楼构造奇特，其间有十二根梁枋交叉重叠，下面仅用
一柱支撑，即有名的「一柱十二梁」。在这里俯瞰群山烟云迷离，远
望金顶，一柱擎天，为观景胜地。
LONG );
        set("exits", ([
                "west"     : __DIR__"taizipo",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -360);
        set("coor/y", -240);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}