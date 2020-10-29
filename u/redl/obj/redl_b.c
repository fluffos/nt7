inherit BULLETIN_BOARD;

void create()
{
        set_name("波陀摩经", ({ "board" }) );
        set("location", "/data/room/redl/woshi");
        set("board_id", "redl_b");
        set("long", "这是Redl的笔记本。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}


