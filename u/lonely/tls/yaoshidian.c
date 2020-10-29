#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"药师殿"NOR);
        set("long",@LONG
眼前空地上一座大殿，香火兴旺，殿里供奉着南无药师琉璃光如来，
金身金袈，华丽之极。香案上供着各种鲜花，水果，香油。大殿里的
香客都在虔诚的磕头烧香，保佑自己生病的亲人早日康复。
LONG
        );
       
        set("exits", ([
                "west" : __DIR__"baodian",
                "south"  : __DIR__"gulou",
                "northeast"  : __DIR__"yz4",
        ]));


	set("objects",([
                __DIR__"npc/guest" : 2,
        ]));

        set("coor/x",-340);
  set("coor/y",-330);
   set("coor/z",30);
   setup();
}