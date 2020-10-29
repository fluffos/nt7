
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "回春堂" );
        set("long",
"你走进这里就闻到浓重的药味，门上高高的挂着一块匾额"HBRED HIY"〖回春堂〗\n"NOR
"这里就是天下闻名的回春堂药局了，回春堂是药王谷在佛山开设的药局\n"
"出售药王谷炮制的药材。墙上挂着一个牌子(paizi)。\n"
);

        set("item_desc", ([
                "paizi" : YEL"本药局出售各种药材，另招收零工伙计。\n\n"
                                "看病、疗伤的请到正厅。\n"
                                "买药的请到南厅。\n"
                                "打工的请到北厅。\n"NOR,
        ]));
        set("exits", ([
        "north" : "/d/foshan/street1",
        "west" : __DIR__"tingyuan",
        ]));
        set("objects", ([
                __DIR__"npc/huoji" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
