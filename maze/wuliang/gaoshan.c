// cool 98.3.17
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "无量山峰");
	set("long", @LONG
这里是无量山的高峰上，寂静无人。只听山峰下轰隆、轰隆，奔腾澎湃的
水声不断传来，你向下看，但见澜沧江浩浩荡荡的从山脚下涌过，煞是壮观。
西面山下是江边，南面是来时候的森林。
LONG
	);
        set("outdoors", "大理");
	set("exits",([
             "south" : __DIR__"shanlu12",
             "westdown" : __DIR__"anbian",	
	]));

        set("objects", ([
	      __DIR__"obj/yeguo" : 2,
	]));
	setup();
}