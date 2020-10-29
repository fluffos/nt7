// Room: /d/playertown/huayuan3.c 花园
// Build 1999.12.10 bmw

inherit ROOM;

void create()
{
        set("short", "花园");
        set("long",
"你走在一条青砖小道上，两边整整齐齐地排着两排杨柳，湖上总有几\n"
"艘渔船正在打渔，渔夫们欢快地唱着歌，拖起一网活蹦乱跳的鱼儿。湖畔\n"
"边上是一片片翠绿的草坪，上面几对夫妇正相依在那，低头吟语着，偶尔\n"
"还传来一阵涩笑。\n"
);
        set("outdoors", "playertown");
//      set("no_clean_up", 0);
        set("exits", ([
                "west"        :        __DIR__"huayuan2",
                "south"        :        __DIR__"huayuan4",
        ]));
        setup();
        replace_program(ROOM);
}