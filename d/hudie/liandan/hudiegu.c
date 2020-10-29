inherit ROOM;

void create()
{
	set("short", "蝴蝶谷");
	set("long", @LONG
过了花丛，眼前是一条小径。但见蝴蝶越来越多，或花或白、或黑
或紫，翩翩起舞。蝴蝶也不畏人，飞近时便在人头上、肩上、手上停留。
行到过午，只见一条清溪旁结着七、八间茅屋，茅屋之前是几块花圃，
种满了诸般花草。茅屋之后是好大的一片果园，只是看起来一派破败气
象，与『蝶谷医仙』的名头殊不相称。
LONG
	);
       set("outdoors", "mingjiao");
       set("no_fight",1);
       set("no_steal",1);
       set("no_beg",1);

	set("exits", 
	([
		"southeast" : "/d/mingjiao/diecong1",
          	"south" : __DIR__"huapu",
          	"north" : __DIR__"guoyuan",

	]));
        set("objects", 
	([
		__DIR__"huqingniu" : 1,
	]));
    
	setup();
}
