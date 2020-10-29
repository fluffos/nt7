inherit BULLETIN_BOARD;

void create()
{
        set_name("主页维护室留言版", ({ "board" }) );
        set("location", "/u/viremploy/webmaster");
        set("board_id", "webmaster_b");
        set("long", "请认真记录。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

