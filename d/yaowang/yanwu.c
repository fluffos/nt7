inherit ROOM;

void create()
{
        set("short", "演武厅");
        set("long", @LONG
这里是一处宽大的空场，空场中央立着的一块大木牌上写着
一个大大的“武”字。不少年轻人在这里练针灸、品药草，
一位一身黑衣的年轻人背着手四处巡视指点。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"fyuan",
]));

        set("objects", ([
                __DIR__"npc/buwawa" : 1,
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
