inherit ROOM;

void create()
{
        set("short", "朝天宫");
        set("long", @LONG
这里已近武当绝顶，只见石梯直耸，危蹬高悬，两旁辅以索链、
铁拦勾连。
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/qingxu": 1,
        ]));

        set("exits", ([
                "northdown" : __DIR__"hutouyan",
                "south" : __DIR__"huixianqiao",
        ]));
        set("outdoors", "wudang");
        set("coor/x", -350);
        set("coor/y", -370);
        set("coor/z", 150);
        setup();
        replace_program(ROOM);
}