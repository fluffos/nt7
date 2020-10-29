inherit BULLETIN_BOARD;

void create()
{
        set_name("意见反馈板", ({ "board" }) );
        set("location", "/d/city/advice/advice");
        set("board_id", "game_advice");
        set("long", "有用的话就往这里说，乱灌水杀无赦。\n" );
        setup();
        set("capacity", 100000);
        replace_program(BULLETIN_BOARD);
}



