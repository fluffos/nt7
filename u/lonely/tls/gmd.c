#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"大光明殿"NOR);
        set("long",@LONG
这座大殿由四支大红圆柱托住。殿上一个牌匾，上书“正法久住”
几个楷书大字。殿里供奉着阿弥陀佛及西方三圣。
LONG);       
        set("exits", ([
                "east" : __DIR__"yz3",
                "south" : __DIR__"sjt",
	]));
        set("coor/x",-360);
  set("coor/y",-290);
   set("coor/z",20);
   setup();
}