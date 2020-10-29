#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","马厩");
        set("long", @LONG
这是草棚边的马厩，常年供应新鲜草料。马夫们会把马牵到马厩
好生照看，将它们喂饱饮足，再洗刷得干乾净净，一直伺候到客人上
路。马厩中堆放著几堆草料，正中有口泔槽。马厩雨檐下的烂木柱上
钉着一块破木牌(paizi)。
LONG );
      set("outdoors", "emei");
      set("exits",([
                "south" : __DIR__"huayanding",
      ]));
      set("no_fight", 1);
      set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
      ]));
        set("coor/x", -520);
        set("coor/y", -230);
        set("coor/z", 120);
        setup();
      replace_program(TRANS_ROOM);
}