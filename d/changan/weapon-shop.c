//Room: weapon-shop.c

#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "兵器店");
        set("long", @LONG
这里是兵器店。店里到处银光闪闪，让人眼花缭乱。兵器架上摆
着各种兵器，十八般武器是应有尽有，样样俱全。兵器店老板是慕容
世家的传人。南墙上还写了一首诗(poem)。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/qixiang6",
        ]));
        set("item_desc", ([
                "poem": HIR @TEXT
        易水萧萧西风冷，壮士一去不复还！
        拼死但凭三尺剑，深情唯有负红颜！
TEXT NOR
        ]) );
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/murong-hao" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10690);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}