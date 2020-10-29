inherit ROOM;

void create()
{
        set("short", "头天门");
        set("long", @LONG
只见有石梯无数通往山巅，一座石坊上写着头天门三个大字，这
是攀登武当绝顶天柱峰的起点。
LONG );
        set("exits", ([
                "north" : __DIR__"huixianqiao",
                "southup" : __DIR__"ertiangate",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -390);
        set("coor/z", 150);
        setup();
        replace_program(ROOM);
}