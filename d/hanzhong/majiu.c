#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","马厩");
        set("long", @LONG
这是武功镇的马厩，因为平时来往的人不多，显得有些破旧。马
厩雨檐下的烂木柱上钉着一块破木牌 (paizi)。厩中堆放著几堆草料，
正中有一口泔槽。
LONG );
      set("outdoors", "hanzhong");
      set("no_fight", 1);
      set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
      ]));
      set("exits",([ /* sizeof() == 1 */
                "west" : __DIR__"kedian1",
      ]));
        set("coor/x", -12230);
	set("coor/y", 820);
	set("coor/z", 0);
	setup();
      replace_program(TRANS_ROOM);
}
