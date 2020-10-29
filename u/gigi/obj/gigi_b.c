// /clone/board/kedian_b.c

#include <ansi.h>  
inherit BULLETIN_BOARD;

void create()
{
        set_name(RED "相思石" NOR, ({ "stone" }) );
        set("location", "/u/gigi/workroom");
        set("board_id", "gigi_b");
        set("long", CYN "飞云过尽，归鸿无信，何处寄书得？\n渐写到别来，此情深处，红笺为无色。\n" NOR );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

