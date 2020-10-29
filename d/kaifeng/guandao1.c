// /kaifeng/guandao1.c
// Last modified by Lonely 2003.10.20

inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
这是条连接开封府与扬州府的官道，由于这条路治安较好行人也不
少。西面通向开封，东面通向南阳。
LONG);
        set("exits", ([
                  "east"      : __DIR__"tokaifeng",
                "west" : __DIR__"dongmen",
        ]));
        set("outdoors", "kaifeng");
        set("no_clean_up", 0);

	set("coor/x", -5010);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}