inherit ROOM;

void create()
{
        set("short", "太子坡");
        set("long", @LONG
此处地处坡陀之隘，形势险要，相传净乐国太子少年真武入山修
道时，曾在此留住读书，故名叫太子坡，好象一朵出水芙蓉，涌出绿
波，瓣萼历历可数。远处峰回路转，忽明忽灭尽在云雾之中。
LONG );
        set("exits", ([
                "northdown"  : __DIR__"shanlu1",
                "southdown"  : __DIR__"shiliang",
                "east"       : __DIR__"fuzhenguan",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -240);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}