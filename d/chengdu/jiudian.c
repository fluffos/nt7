// Room: jiudian.c

inherit ROOM;
void create()
{
        set("short", "蓉城酒楼");
        set("long", @LONG
这是一座有着三开间门面的大酒楼，虽说不上雕梁画栋，却也气
派不凡。正首门梁上挂着一幅黑漆匾，上写着『蓉城酒楼』四个金漆
大字。楼中桌洁椅净，座中客人衣饰豪奢，十九是富商大贾。这是一
家百年老店，传到现在的这位掌柜已经是第四代，据说和提督大人有
点不清楚，却也保佑了这间酒楼的日进斗金。东南角有一道方梯通往
楼上雅座，往西南则可以出到东大街。
LONG );
        set("exits", ([
                "southwest" : __DIR__"eastroad1",
                "east" : __DIR__"chufang",
        ]));
        set("objects", ([
                __DIR__"npc/tanghua" : 1,
                __DIR__"npc/xiaoer2" : 1,
        ]) );
        set("coor/x", -15190);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}