

inherit ROOM;

void create()
{
        set("short", "打铁铺");
        set("long", @LONG
这是一家简陋的打铁铺，中心摆着一个火炉，炉火把四周照得一片
通红，你一走进去就感到浑身火热。墙角堆满了已完工的菜刀、铁锤、
铁棍、匕首、盔甲等物。一位铁匠满头大汗挥舞着铁锤，专心致志地在
打铁。门口有一牌子(paizi)。
LONG
        );

        set("exits", ([
                "west" : __DIR__"xuanwu-1",
        ]));

        set("objects", ([
__DIR__"npc/tiejiang1" : 1,
        ]));
        set("item_desc", ([ /* sizeof() == 1 */
                "paizi" : "牌子上写道：东西都在墙角堆着。\n"]));
        set("no_clean_up", 0);
        set("objects", ([
                "/d/gaoli/npc/tiejiang" : 1,
        ]));

        setup();
        replace_program(ROOM);
}

