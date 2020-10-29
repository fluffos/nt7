inherit BULLETIN_BOARD;

void create()
{
        set_name("新手导师室留言版", ({ "board" }) );
        set("location", "/u/viremploy/teacher");
        set("board_id", "teacher_b");
        set("long", "请认真记录。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

