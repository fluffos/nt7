#include <ansi.h> 
inherit ROOM;
int do_cai(string arg);

void create()
{
        set("short", "城西后林");
        set("long", @LONG
这是一片茂密的树林。很多棵几十丈高的大树聚在一块，象一把
把琼天大伞，连日月都被遮蔽得黯然无光。树林中还不时可以听到大
自然发出的声响。
LONG );
        set("exits", ([
                "west" : "/d/beijing/liandan_lin2",
        ]));

        set("no_clean_up", 0); 
	set("coor/x", -2850);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();       
}

#include "liandan_lin.h"