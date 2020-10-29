inherit BULLETIN_BOARD;

void create()
{
        set_name("蓬莱石壁", ({ "stone" }) );
        set("location", "/d/penglai/haitan");
        set("board_id", "penglai_shibi");
        set("long", "这是块石壁，可以在上面刻字留言(post)。\n" );
        setup();
        set("capacity", 300);
        replace_program(BULLETIN_BOARD);
}

