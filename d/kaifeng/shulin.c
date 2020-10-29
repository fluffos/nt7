inherit ROOM;

void create()
{
        set("short", "树林");
        set("long", @LONG
一片杂树林，落叶掉了满地，斑驳的枝叶显露出天气的无情。绿
色的小草就从树之间的空隙长出来。林中点点的都是绿色。小路穿过
树林不远就是禹王台。西面是中州方向。
LONG );
        set("no_clean_up", 0);

        set("exits", ([
                "northwest" : __DIR__"dadao1",
                "east" : __DIR__"yuwang",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5030);
	set("coor/y", 2100);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}