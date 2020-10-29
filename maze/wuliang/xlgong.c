// Room: xlgong.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "西练武厅");
	set("long", @LONG
这是无量山剑湖宫的练功房，两边有两个兵器架，十八武器样样俱全，墙
角还散放着几个练力的石锤和一些杂物，宫中弟子每天在此练功。
LONG
	);
	set("exits", ([ 
	    "east" : __DIR__"jhg",	    
        ]));

	setup();
}