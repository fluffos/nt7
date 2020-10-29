inherit ROOM;
#include <ansi.h> 
void create ()
{
  set ("short", "迷雾");
  set ("long", HIG@LONG
这里一片朦胧，什么都看不清。但在迷雾中仿佛包藏着无尽的
杀机。忽然间三只奇怪的野兽从朦胧中猛扑出来，爪如钢刀，须如
利剑，你措手不及，顿时陷入了包围中。
LONG);

  set("exits", ([
         "west"    : __DIR__"outlet1",
         "south"    : __DIR__"entrance",
      ]));
  set("objects", ([
         "/quest/tulong/npc/beast" : 3,
      ]));
  set("no_magic", 1);
        setup();
}

int valid_leave (object me, string dir)
{
  object beast = present("beast", this_object());

  if (dir == "west" &&  beast &&
      ! beast->is_busy() )
    return notify_fail("观想兽挡住去路，死活不让你过！\n");
  return ::valid_leave(me,dir);
}
