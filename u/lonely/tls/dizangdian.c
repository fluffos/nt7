#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"地藏殿"NOR);
        set("long",@LONG
眼前空地上一座大殿，殿中灯火明亮，殿里供奉着南无地藏王菩萨，
金身金袈，华丽之极。香案上供着各种鲜花，水果，许多香客都来到这
里为死去的亲人烧香保佑。
LONG);       
        set("exits", ([
                "east" : __DIR__"baodian",
                "south"  : __DIR__"zhonglou",
                "northwest"  : __DIR__"yz5",
	]));
        set("coor/x",-360);
  set("coor/y",-330);
   set("coor/z",20);
   setup();
}