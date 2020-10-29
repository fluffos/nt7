// /clone/board/bonze_b.c

#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
    set_name(HIC "古村留言版" NOR, ({ "board" }) );
    set("location", "/d/newbie/shijiezhishu");
        set("board_id", "newbie_b");
        set("long", "这是新手村的留言版，可以输入 post <标题> 留言。\n" );
        setup();
        set("capacity", 500);
        replace_program(BULLETIN_BOARD);
}

