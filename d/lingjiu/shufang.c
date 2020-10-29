inherit ROOM;

void create()
{
        set("short", "沁芳轩");
        set("long", @LONG
这是灵鹫宫的书房，靠墙摆放着一溜书架，上面整齐地排列着各
种书籍。屋子正中是一张墨色小几，几上的香炉冒出缕缕轻烟，几前
有个蒲团可供你盘坐而读，除此外别无他物。你不由低呼，好一个雅
静所在。
LONG );
        set("exits", ([
                "west" : __DIR__"men2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}