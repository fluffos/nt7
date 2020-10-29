inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short",HIY"承德殿内"NOR);
        set("long", @LONG
这里是承德殿内，也是大宋皇帝和文武百官议事的地方，殿内金
碧辉煌，煞是雄伟壮观，大殿的正中央的龙椅上端坐的是宋徽宗，两
面分立着众宫女太监，文武百官依品次排列左右。
LONG );

        set("indoors", "city2");
        set("no_fly",1);
        set("no_fight",1);
        set("have_quest",1);

        set("exits", ([
                "out"    : __DIR__"cddian",
        ]));

        set("objects", ([
           __DIR__"song/liu" : 1,
           __DIR__"npc/taijian"     : 2, 
        ]));
        setup();
        replace_program(ROOM);
}
