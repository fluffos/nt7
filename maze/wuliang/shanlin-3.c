// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "森林");
	set("long", @LONG
行出数里，进了一座大树林中，四周都是是参天古木，当日阳光灿烂，林
中却黑沉沉地宛如黄昏。北面一直通向林子深处。?
LONG
	);
        set("outdoors", "大理");

	set("exits", ([
             "north" : __DIR__"shanlin-4",
	     "westdown" : __DIR__"shanlin-2",
	]));
        set("objects", ([
	      __DIR__"obj/yeguo" : 2,
	]));
	setup();
}