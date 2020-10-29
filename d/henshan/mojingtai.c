inherit ROOM;

void create()
{
        set("short", "磨镜台");
        set("long", @LONG
磨镜台位于燕子岩下，与半山亭一沟相邻。台前峰回路转，台旁
古松苍翠，环境清幽。相传南宗禅宗怀让在此宣扬「顿悟法门」，坐
台高僧斗法，怀让磨镜，智服北宗道一，此台因而传名。「磨镜台之
幽」是衡山大四绝之一。
LONG );
        set("exits", ([
                "southdown"  : __DIR__"shanlu8",
                "westup"     : __DIR__"shanlu7",
                "northup"    : __DIR__"shanlu6",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 2,
        ]));               
 
        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5550);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}