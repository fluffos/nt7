inherit BULLETIN_BOARD;

void create()
{
        set_name("游戏宣传室留言版", ({ "board" }) );
        set("location", "/u/viremploy/presell");
        set("board_id", "presell_b");
        set("long", "请认真记录。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

