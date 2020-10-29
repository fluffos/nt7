// /u/cool/tls/goudi.c
// 1997.2.13
#include <ansi.h>
inherit ROOM;

void create()
{
  set("short","百丈桥底");
  set("long",@LONG
这里是百丈桥底，四周都是大石。一条小河顺流而下，四周有不
少骨骸，大概都是失足摔死的。这里东面山坡上是一片松林，看来只
好从那边上。
LONG);

     set("outdoors", "天龙寺");
     set("exits",([
           "eastup" : __DIR__"road5",
     ]));
     setup();
}
