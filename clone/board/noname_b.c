inherit BULLETIN_BOARD;

void create()
{
        set_name("匿名留言版", ({ "board" }) );
        set("location", "/d/wizard/noname_room");
        set("board_id", "noname_b");
        set("noname_board", 1);
        set("private_board", 1);
        set("long", "说吧，除了巫师没人知道是你说的内容。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}


       
