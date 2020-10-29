inherit ROOM;

void create()
{
        set("short", "昆仑山麓");
        set("long", @LONG
    四下无声，只有风吹松涛，幽韵天成，仰视苍天，注视群山，令
人不觉怆然而发思古之幽情！往前看，只见一道飞岩，下临绝崖，往
下看，峭壁如刀削，云卷雾涌，深不见底。
LONG );
        set("no_new_clean_up", 0);
        set("outdoors", "kunlun");

        set("exits", ([ /* sizeof() == 3 */
                "northeast" : __DIR__"kunlun1",
                "up" : __DIR__"kunlun3",
        ]));

        setup();
        replace_program(ROOM);
}