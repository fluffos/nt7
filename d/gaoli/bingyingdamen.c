

inherit ROOM;

void create()
{
        set("short", "兵营大门");
        set("long", @LONG
你正站在兵营的门口，面对着一排简陋的营房，可以看到穿着制服
的官兵正在操练，不时地传来呐喊声。老百姓是不允许在此观看的，你
最好还是赶快走开为妙。
LONG
        );

        set("exits", ([
                "north" : __DIR__"qinglong-1",
                "south" : __DIR__"bingying",
        ]));
           set("objects", ([
                "/d/gaoli/npc/bing" : 2,
        ]));
 setup();
        replace_program(ROOM);
}        
