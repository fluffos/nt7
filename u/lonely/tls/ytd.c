#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"圆通殿"NOR);
        set("long",@LONG
眼前这座大殿极为宏伟。殿里供奉着南无大慈大悲广大灵感观世
音菩萨，这殿中的千手观音，隐然是用一块大汉白玉精雕而成，镶嵌
各种宝石，金银，华丽之极，世间罕见，和寺中的三塔一样被列为天
龙五宝之一，殿中香案上放着香客供的各种礼品。
LONG);       
        set("exits", ([
             "north" : __DIR__"xmd",
             "west" : __DIR__"yz6",
	]));

        set("coor/x",-340);
  set("coor/y",-300);
   set("coor/z",20);
   setup();
}