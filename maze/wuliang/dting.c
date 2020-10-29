// Room: dting.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "东厅");
	set("long", @LONG
这里是供来无量剑的客人休息之用，一应茶点具备，窗边一溜平放着不少
锦凳，墙上挂着几幅山水画，几缕阳光透过窗外的绿荫中直射进来。
LONG
	);
	set("exits", ([ 
	    "west" : __DIR__"wlj",	    
        ]));

	setup();
}