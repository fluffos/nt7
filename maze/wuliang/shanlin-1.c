// Modify By River 98/12 
inherit ROOM;

void create()
{
	set("short", "石道");
	set("long", @LONG
这里乱石荆刺满地，没有一条象样的路。你费力的走着，衣衫下摆被荆刺
撕成一片一片。西面是似乎来时候的森林。你喘了口气，突然发觉一条人影向
东面逃去。
LONG
	);
        set("outdoors", "大理");

	set("exits", ([
            "east" : __DIR__"shanlin-2",
	    "west" : __DIR__"shanlu12",
	]));

	setup();
}
