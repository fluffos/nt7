// /clone/board/huashan_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("唐门世家留言板", ({ "board" }) );
        set("location", "/d/tangmen/chashi");
        set("board_id", "tangmen_b");
        set("long", "这是一个供唐门世家门下交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}


