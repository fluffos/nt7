inherit ROOM;
void create()
{
        set("short", "昆仑山麓");
        set("long", @LONG
这一带树木丛生，山石嶙峋，行走甚是不便，山上积雪更厚，道
路崎岖，行走自是费力。转过两个山坡，进了一座大松林。林中松树
都是数百年的老树，枝柯交横。
LONG );
        set("no_new_clean_up", 0);
        set("outdoors", "kunlun");
        set("exits", ([ /* sizeof() == 2 */
                "southwest" : __DIR__"kunlun2",
                "northeast" : __DIR__"klshanlu",

        ]));

        setup();
        replace_program(ROOM);
}