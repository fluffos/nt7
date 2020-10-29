#include <ansi.h>
inherit ROOM;

string look_duilian();

void create()
{
        set("short", "南天门");
        set("long", @LONG
到了南天门，才能望到衡山第一的祝融峰。南天门是花岗岩做成
的石碑坊，中门镌有「南天门」三字横额，左右二门的门楣上，分别
刻有「行云」和「施雨」二字。楹联(lian)破陋，显见岁月已久。
LONG );
        set("item_desc",([
                "lian" : (: look_duilian :),
        ]));
        set("exits", ([
                "eastup"    : __DIR__"liuyunping",
                "northeast" : __DIR__"shiziyan",
                "northwest" : __DIR__"shanlu14",
                "southeast" : __DIR__"denggaotai",
                "southwest" : __DIR__"shanlu13",
        ]));
 
        set("objects", ([
                __DIR__"npc/dizi1" :  4,
        ]));

        set("outdoors", "henshan");
	set("coor/x", -6940);
	set("coor/y", -5520);
	set("coor/z", 20);
	setup();
}

string look_duilian()
{
        return
        HIC "\n"
        "\t※※※※※※※        ※※※※※※※\n"
        "\t※※※※※※※        ※※※※※※※\n"
        "\t※※      ※※        ※※      ※※\n"
        "\t※※" NOR + WHT "　门　" HIC "※※        ※※" NOR + WHT "  路  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" NOR + WHT "　可　" HIC "※※        ※※" NOR + WHT "  承  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" NOR + WHT "　通　" HIC "※※        ※※" NOR + WHT "  绝  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" NOR + WHT "　天　" HIC "※※        ※※" NOR + WHT "  顶  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　仰　" HIC "※※        ※※" HIW "  俯  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　观　" HIC "※※        ※※" HIW "  瞰  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　碧　" HIC "※※        ※※" HIW "  翠  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　落　" HIC "※※        ※※" HIW "  微  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　星　" HIC "※※        ※※" HIW "  峦  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　辰　" HIC "※※        ※※" HIW "  屿  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　近　" HIC "※※        ※※" HIW "  低  " HIC "※※\n"
        "\t※※    　※※        ※※      ※※\n"
        "\t※※※※※※※        ※※※※※※※\n"
        "\t※※※※※※※        ※※※※※※※\n\n" NOR;
}