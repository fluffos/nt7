inherit ROOM;

void create()
{
        set("short", "三老峰");
        set("long", @LONG
此处乃武当山三老峰，只见三座奇峰突兀，惊险无比，行人多不
敢放胆在此玩赏风景。
LONG );
        set("exits", ([
                "northdown": __DIR__"wuyaling",
                "southup"  : __DIR__"wulaofeng",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -340);
        set("coor/z", 120);
        setup();
        replace_program(ROOM);
}