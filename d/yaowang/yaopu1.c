inherit ROOM;

void create()
{
        set("short", "药圃");
        set("long", @LONG
这里是一处很大的药苗圃，遍地开着各色怪异的小花，空气
里弥漫着香臭混杂的怪味道。
LONG
        );
        set("exits", ([
  "northeast" : __DIR__"xiaodao5",
  "west" : __DIR__"lu2",
  "south" : __DIR__"xiaodao4",
]));

        set("objects", ([
                "/kungfu/class/yaowang/xue" : 1,
        ]));
        
        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
