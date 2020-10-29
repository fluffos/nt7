#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","吴哥窟");
  set ("long", @LONG
十二世纪中期为供奉印度教毗湿奴神所建，可能是世界上最大
寺庙。13世纪后期，变成佛教寺庙。它由东南西北四廊（每廊又分
两翼），西参道、正门、三重回廊及以主殿中央尖塔为中心的五座
尖塔所构成。除西门外，另三面是假门，佛法认为人死后登西方极
乐，因此敞开西门让灵魂得以升天。吴哥窟是现存吴哥遗迹中规模
最大、保护得最好的代表之作。
LONG);

  set("exits", ([ 
"east":__DIR__"matou",        

       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
