// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "森林");
	set("long", @LONG
这里四周都是是参天古木，当日阳光灿烂，林中却黑沉沉地宛如黄昏，越
走树林越密，有时不得不侧身而行。?
LONG
	);
        set("outdoors", "大理");

	set("exits", ([
            "south" : __DIR__"shanlin-3",
	    "west" : __DIR__"shanlin-5",
	]));

	setup();
}