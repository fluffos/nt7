// Room: /city/zhengting.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "正厅");
        set("long", @LONG
这里是福威镖局的正厅，几只太师椅一字排开，正中央坐着总镖
头，手持烟袋杆正在闭目沉思。墙上挂着几幅字画和一把宝剑。
LONG );
        set("no_fight", 1);
	set("exits", ([
		"north" : __DIR__"biaoju",
	]));
	set("objects", ([
                "/quest/quest1/linzhennan" : 1,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -30);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
