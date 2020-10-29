// Room: /d/heimuya/basket.c

inherit ROOM;
void create()
{
        set("short", "竹篓");
        set("long", @LONG
这是一只大竹篓，足可装得十来石米。抬头上望，只见头顶有天
风崖壁，这黑木崖着实高得厉害。
LONG );
        set("outdoors", "heimuya");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}