inherit ROOM;

void create()
{
        set("short", "炼药堂");
        set("long", @LONG
这是一间不大的房间，房间中央是一个灶台，灶上支着一个
大沙锅，咕嘟咕嘟的声响在门外都能听见，一个小童子在灶下拉
着风箱，另一个在看着锅里不时的放进一些药材。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"yz_xiaoyuan",
]));

        setup();
        replace_program(ROOM);
}
