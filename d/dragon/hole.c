#include <room.h>
inherit ROOM;

void create()
{
      set("short","凌云窟");
      set("long",
"祥云光满，瑞霭香浮。在这处远山里居然还有如此仙境。这里正是独\n"
"立云海，傲越千山的玄女峰。而这个深陷入岩壁的洞窟，似乎隐藏着什么\n"
"秘密呢。\n"
);
      set("exits",([ /* sizeof() == 1 */
//          "up"  : "/d/xuansu/shanjiao",
          "west"  : __DIR__"ground",
      ]));
      set("objects",([
//                 "/d/xuansu/npc/qilin" : 1,
      ]));
      set("no_magic", 1);
        setup();
      create_door("west", "石门", "east", DOOR_CLOSED);
}
