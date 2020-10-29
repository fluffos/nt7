inherit ROOM;

void create()
{
        set("short", "过道");
        set("long", @LONG
这里是一条宽敞的过道，用青砖铺就的地面非常整洁，两旁
是汉白玉的雕花栏杆，分外的华贵，每隔几步就有一个仆人打扮
的青年侍立两旁，看起来都身具武功，绝非等闲之辈。置身于此，
让人感觉到莫名的压力。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "south" : __DIR__"lianwu",
  "east" : __DIR__"tulu2",
  "west" : __DIR__"yuemen",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
