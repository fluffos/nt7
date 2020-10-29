#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "赤壁古战场");
        set("long", @LONG
这里就是有名的古赤壁战场，对岸一面巨大的悬崖绝壁之上书有
「赤壁」两个大字，想当年曹操百万精兵在此被周愈杀的片甲不留，
含恨而归。文学家苏东坡游临此地，便感慨的留下了『遥想公谨当年，
小乔初嫁了，羽扇纶巾，雄姿英发，谈笑间，强虏灰飞烟灭……』令
后人引为佳句。从这里向江面看去，只见滚滚江水东流去，江面上若
隐若现一条条大铁索，原来是当年吴国为了抵御曹操而修的锁江链。
LONG );
        set("outdoors", "jingzhou");
        set("item_desc", ([
                "tiesuo" : WHT "只见一条条铁锁链横在江中，多年江水冲"
                           "击依然不朽。\n" NOR,
        ]));
        set("exits", ([
                "east" : __DIR__"chibi5",
                            
        ]));
        set("objects", ([
                "/d/beijing/npc/shiren" : 1,
        ]));
        set("coor/x", -370);
        set("coor/y", -230);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
} 