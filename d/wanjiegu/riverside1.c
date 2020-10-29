inherit ROOM;

void create()
{
        set("short", "江边小路");
        set("long", @LONG
这是澜沧江边的一条小路，江水滔滔从下面奔腾而过，江面上不
时传来艄公的号子声，与江风的呼啸声形成一曲动人的交响乐，令人
精神为之一振。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([
                "northup" : __DIR__"riverside2",
        ]));
        set("objects", ([
                "/d/wanjiegu/npc/duck" : 2,
        ]));
        setup();
        replace_program(ROOM);
}