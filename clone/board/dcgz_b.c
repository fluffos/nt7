// /clone/board/lonely_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("温馨笔记", ({ "board" }) );
        set("location", "/data/room/dcgz/woshi");
        set("board_id", "dcgz_b");
        set("long", "这是一个专供Juice使用的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

