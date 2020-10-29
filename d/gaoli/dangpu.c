// /d/gaoli/dangpu
// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "高丽当铺");
        set("long", @LONG
你走进了高丽的当铺，这里略现昏暗，当前巨大的柜台用手指粗细
的铁栏杆围着，一副小心谨慎的模样，老板是个很精明的生意人，见你
走了进来，很客气地和你寒暄，但眼睛里却没有什么笑意，很审慎地打
量着你。
LONG
          );
set("exits", ([
                "west":__DIR__"zhuque-2",    
        ]));
 set("objects", ([
                "/d/gaoli/npc/jin1" : 1,
        ]));
       setup();
        replace_program(ROOM);
}
