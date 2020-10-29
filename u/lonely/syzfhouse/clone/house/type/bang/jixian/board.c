
#include <ansi.h>
inherit "/inherit/misc/bang_board";

void create()
{
    set_name("帮会留言板", ({ "board" }));
    set("unit", "块");
    set("board_id", "bang_b");
    set("long", "这是一块供帮内人士交流的留言板。\n" );
    set("capacity", 300);
    setup();
}
