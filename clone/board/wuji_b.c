
inherit BULLETIN_BOARD;

void create()
{
        set_name("工作笔记", ({ "board" }) );
        set("location", "/u/wuji/workroom");
        set("board_id", "wuji_b");
        set("long", "这是一个专供wuji使用的工作笔记。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

