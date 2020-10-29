#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大门");
        set("long", @LONG
这里是一处庄正高大石门，与众不同的是门两旁各摆着一个
青石雕刻的卧虎，门上还有不少的小孔，也不知道是做什么用的，
门的正上方的墙里嵌着一块石板，石板上刻着“药王谷”三个苍
劲的大字，原来这里就是令武林人士变色的药王谷。在门的右边
立着一块石碑(bei)。
LONG
        );
        set("exits", ([
        "north" : __DIR__"bridge1",
        "east" : __DIR__"lcd07",
        "west" : __DIR__"tiandi1",
        "south" : __DIR__"tiandi2",
]));
        set("item_desc", ([
                "bei" :  HIW"\n     ┏----┓\n"+
                   HIW"     ┃ "HIB"药"HIW" ┃\n"+
                   HIW"     ┃ "HIB"王"HIW" ┃\n"+
                   HIW"     ┃ "HIB"谷"HIW" ┃\n"+
                   HIW"     ┃ "HIB"重"HIW" ┃\n"+
                   HIW"     ┃ "HIB"地"HIW" ┃\n"+
                   HIW"     ┃ "HIB"擅"HIW" ┃\n"+
                   HIW"     ┃ "HIB"闯"HIW" ┃\n"+
                   HIW"     ┃ "HIB"者"HIW" ┃\n"+
                   HIW"     ┃    ┃\n"+
                   HIW"     ┃ "HIR"杀"HIW" ┃\n"+
                   HIW"     ┃ "HIR"无"HIW" ┃\n"+
                   HIW"     ┃ "HIR"赦"HIW" ┃\n"+
                   HIW"     ┗----┛\n"NOR,
        ]));
        set("outdoors", "yaowang");

        setup();
        replace_program(ROOM);
}
int valid_leave(object me, string dir)
{
        if( dir=="north"
         && query("party/party_name", me) != "药王谷" )
                return notify_fail(WHT"请看石碑！\n"NOR);
        return ::valid_leave(me, dir);
}
