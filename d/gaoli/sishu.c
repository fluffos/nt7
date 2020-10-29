// /d/gaoli/sishi
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "私塾");
        set("long", @LONG
你来到一间宽敞明亮的房间，只见四壁排满了书架，书架上的书籍
从诸子百家到诗词歌赋应有尽有。房间当中有一紫檀书桌，靠窗墙上悬
挂着一副字画，一位老先生坐在桌后。
LONG
        );
set("exits", ([
               "west":__DIR__"xuanwu-2", 
        ]));
      set("objects", ([
                "/d/gaoli/npc/xuejiu" : 1,
                __DIR__"npc/gongzi2":1,
        ]));
       setup();
        replace_program(ROOM);
}        
