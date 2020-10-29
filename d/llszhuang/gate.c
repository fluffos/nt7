#include <ansi.h>
inherit ROOM;
void create()
{
         set("short", "柳绿山庄正门");
        set("long",
"柳绿山庄现在就耸立在你的面前，这山庄看起来已久久无人居住，大\n"
"雪堆积在檐上，瓦上，廊上，梁上，隐隐有一股杀气透出来。庄墙外到处\n"
"是积雪，一支生锈的铁箭订在墙上，兀自涔涔滴血。雪地上是触目惊心的\n"
"血字：\n"+ 
        HIR"                      一 入 柳 绿 庄\n" 
       "                      此 生 不 还 乡\n\n\n"NOR 
);

        set("exits", ([ /* sizeof() == 2 */
          "north" : __DIR__"yongdao1",
          "south" : __DIR__"xueyuan",
        ]));
        set("no_magic", "1");


        setup();
}
