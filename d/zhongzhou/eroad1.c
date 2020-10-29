inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
这是条连接开封府与中州府的官道，由于这条路治安较好
行人也不少。东面通向开封，西面是中州府。
LONG);
        set("exits", ([
                "west" : __DIR__"dongmeng",
                "east" : __DIR__"eroad2",
        ]));
        set("outdoors", "zhongzhou");
        set("no_clean_up", 0);

        set("coor/x", -8990);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}